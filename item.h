#pragma once
#include "gameObject.h"
#include "components.h"
#include "observer.h"
#include "avancezlib.h"
#include "itemGraphicComponent.h"
#include "itemTypes.h"

class Item : public GameObject {
public:
	Item();
	void create(AvancezLib * system, std::vector<Observer*> *globalListeners);
	void init(int x, int y, itemType type);
	void update();
	void render();
	void destroy();

	itemType getItemType();

	void addComponentUpdaters(Component * component);
	void setRenderComponent(ItemGraphicComponent * component);

	void Receive(Message2 msg);
	void sendGlobal(Message_Observers m);
private:
	itemType type;
	std::vector<Component*> componentUpdateList;
	std::vector<Component*> componentListeners;
	std::vector<Observer*> *globalListeners;
	ItemGraphicComponent * renderComponent;
};