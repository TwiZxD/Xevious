#include "item.h"

Item::Item()
{
}

void Item::create(AvancezLib * system, std::vector<Observer*>* globalListeners)
{	
	this->globalListeners = globalListeners;
	setWidth(30);
	setHeight(30);
}

void Item::init(int x, int y, itemType type)
{	
	enabled = true;
	setX(x);
	setY(y);
	this->type = type;
}


void Item::update()
{
	for (int i = 0; i < componentUpdateList.size(); i++) {
		componentUpdateList[i]->update();
	}
}

void Item::render()
{
	if (renderComponent == NULL) {
		SDL_Log("Can't find render component in item");
	}
	else {
		renderComponent->render(getX(), getY(), type);
	}
}

void Item::destroy()
{
	for (int i = 0; i < componentUpdateList.size(); i++) {
		if (componentUpdateList[i] != NULL) {
			delete componentUpdateList[i];
			componentUpdateList[i] = NULL;
		}
	}
	for (int i = 0; i < componentListeners.size(); i++) {
		if (componentListeners[i] != NULL) {
			delete componentListeners[i];
			componentListeners[i] = NULL;
		}
	}
}

itemType Item::getItemType()
{
	return type;
}

void Item::addComponentUpdaters(Component * component)
{
	componentUpdateList.push_back(component);
}

void Item::setRenderComponent(ItemGraphicComponent * component)
{
	this->renderComponent = component;
}

void Item::Receive(Message2 msg)
{
	if (msg == HIT) {
		enabled = false;
		switch (type)
		{
		case POWER_UP:
			break;
		case HEALTH:
			sendGlobal(PLAY_GAIN_HP);
			break;
		case ROCKET:
			sendGlobal(PLAY_GAIN_ROCKET);
			break;
		case LASER:
			sendGlobal(PLAY_POWER_UP);
			break;
		default:
			break;
		}
	}
}

void Item::sendGlobal(Message_Observers m)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m);
	}
}


