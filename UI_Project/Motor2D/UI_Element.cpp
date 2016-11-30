#include "UI_Element.h"
#include "UI_Text_Box.h"
#include "UI_Button.h"
#include "UI_Interactive_String.h"

//Constructors
UI_Element::UI_Element(const iPoint & position, UI_TYPE ui_type, bool IsActive) :position(position), ui_type(ui_type), IsActive(IsActive) {}

UI_Element::UI_Element(const UI_Element* copy) : position(copy->position), ui_type(copy->ui_type), IsActive(copy->IsActive) {}

UI_Element::UI_Element() : position(0, 0), ui_type(UNDEFINED), IsActive(false) {}

//Destructor
UI_Element::~UI_Element()
{

}


// ==========================
bool UI_Element::Update()
{
	/*
			This Update
	*/

	//Childs Update
	UpdateChilds();

	return true;
}

bool UI_Element::UpdateChilds()
{

	bool ret = true;

	p2List_item<UI_Element*>* item = childs.start;
	while (item) {

		if (item->data->IsActive)
			ret = item->data->Update();

		item = item->next;
	}
	return ret;

}

bool UI_Element::CleanUp()
{
	/*
			This CleanUp
	*/

	//Childs CleanUp
	CleanUpChilds();
	return true;

}

bool UI_Element::CleanUpChilds()
{
	bool ret = true;

	p2List_item<UI_Element*>* item = childs.start;
	while (item) {

		ret = item->data->CleanUp();
		childs.del(item);

		item = item->next;
	}

	return ret;
}

void UI_Element::Draw()const
{
	/*
			This Draw
	*/

	//Childs Draw
	DrawChilds();
}

void UI_Element::DrawChilds() const
{
	p2List_item<UI_Element*>* item = childs.start;
	while (item) {

		if (item->data->IsActive)
			item->data->Draw();

		item = item->next;
	}
}

// ==========================
void UI_Element::SetPosition(const iPoint & new_position)
{
	position = new_position;
}

void UI_Element::Activate()
{
	IsActive = true;
}

void UI_Element::Desactivate()
{
	IsActive = false;
}



// ==========================
UI_Element * UI_Element::AddChild(const UI_Element* child)
{
	//Pointer to new
	UI_Element* new_child = nullptr;

	//Create the new element
	switch (child->ui_type) {
		case UI_TYPE::IMG:					new_child = new UI_IMG(((UI_IMG*)child));										break;
		case UI_TYPE::STRING:				new_child = new UI_String((UI_String*)child);									break;
		case UI_TYPE::BUTTON:				new_child = new UI_Button((UI_Button*)child);									break;
		case UI_TYPE::TEXT_BOX:				new_child = new UI_Text_Box((UI_Text_Box*)child);								break;

	}

	//Set the new element parent
	new_child->SetParent(this);
	//Add the new element to the list of this childs
	childs.add(new_child);

	return new_child;
}

bool UI_Element::Delete_Child(UI_Element* child)
{
	return childs.del(childs.At(childs.find(child)));
}

bool UI_Element::Delete_Child(uint index)
{
	return childs.del(childs.At(index));
}

UI_Element * UI_Element::SetParent(const UI_Element& parent)
{
	return this->parent = ((UI_Element*)&parent);
}
