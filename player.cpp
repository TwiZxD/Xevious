#include "player.h"

Player::Player(AvancezLib *system, PlayerGraphicComponent *graphicComponent, std::vector<Observer*>* globalListeners)
{
	this->system = system;
	this->graphicComponent = graphicComponent;
	this->globalListeners = globalListeners;

	setWidth(41);
	setHeight(43);
}

void Player::create(ObjectPool<Rocket>* rockets_pool, ObjectPool<Rocket>* missile_pool)
{	
	behaviourComponent = new PlayerBehaviourComponent(this, rockets_pool, missile_pool, &componentListeners, globalListeners);
	inputComponent = new PlayerOneInputController(system, &componentListeners);
	
	addComponentListener(inputComponent);
	addComponentListener(behaviourComponent);
	addComponentListener(graphicComponent);

	addComponentUpdaters(inputComponent);
	addComponentUpdaters(behaviourComponent);
}

void Player::init(int x, int y) {
	setX(x);
	setY(y);
	life = 2;
	level = 0;
	enabled = true;
	invulnerableTimer = 60;
	rocketWeaponsEnabled = false;
}

void Player::update() {
	if (invulnerableTimer > 0) {
		invulnerableTimer--;
	}
	for (int i = 0; i < componentUpdateList.size(); i++) {
		componentUpdateList[i]->update();
	}
}

void Player::render() {
	if (invulnerableTimer%6 == 0){
		graphicComponent->render(getX(), getY());
	}	
	for (int i = 0; i < renderComponents.size(); i++) {
		renderComponents[i]->update();
	}
}

void Player::destroy() {
	behaviourComponent->destroy();
	delete behaviourComponent;

	inputComponent->destroy();
	delete inputComponent;
}

void Player::gainPowerUp(itemType type)
{
	switch (type) {
	case HEALTH:
		life++;
		break;
	case ROCKET:
		rocketWeaponsEnabled = true;
		break;
	case LASER:
		gainLevel();
		break;

	}
}


void Player::addComponentUpdaters(Component * component)
{	
	componentUpdateList.push_back(component);
}

void Player::addComponentListener(Component *component)
{	
	componentListeners.push_back(component);
}

void Player::addRenderComponent(Component * component)
{
	renderComponents.push_back(component);
}

void Player::gainLevel()
{
	level = level + 1;
}

int Player::getPlayerLevel()
{
	return level;
}

PlayerGraphicComponent Player::getGraphicsComponent()
{
	return *graphicComponent;
}

void Player::takeDamage(int damage) {
	if (invulnerableTimer <= 0) {
		invulnerableTimer = 60;
		life--;
		sendGlobal(PLAY_SHIELD_HIT);
	}
}

int Player::getLife() {
	return life;
}

void Player::Receive(Message2 msg)
{
	if (msg == HIT) {
		if (life >= 1) {
			takeDamage(1);
		}
		else {
			sendGlobal(PLAY_DIE);
			enabled = false;
		}
	}
}

void Player::Send(Message m) {
	for (auto i = 0; i < componentListeners.size(); i++)
	{
		componentListeners[i]->receive(m);
	}
}

void Player::sendGlobal(Message_Observers m)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m);
	}
}
