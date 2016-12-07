#include "UI_Element.h"
#include "UI_Text_Box.h"
#include "UI_Button.h"

#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"

//Constructors
UI_Element::UI_Element(const SDL_Rect& box, UI_TYPE ui_type, bool IsActive) :box(box), ui_type(ui_type), IsActive(IsActive) {}

UI_Element::UI_Element(const UI_Element* copy) : box(copy->box), ui_type(copy->ui_type), IsActive(copy->IsActive) {}

UI_Element::UI_Element() : box({0,0,0,0}), ui_type(UNDEFINED), IsActive(false) {}

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

void UI_Element::Draw(bool debug)const
{
	/*
			This Draw
	*/

	//Childs Draw
	DrawChilds(debug);
}

void UI_Element::DrawChilds(bool debug) const
{
	p2List_item<UI_Element*>* item = childs.start;
	while (item) {

		if (item->data->IsActive)
			item->data->Draw(debug);

		item = item->next;
	}
}

// ==========================
void UI_Element::SetPosition(const iPoint & new_pos)
{
	box.x = new_pos.x;
	box.y = new_pos.y;
}

void UI_Element::MoveBox(int x_vel, int y_vel)
{
	box.x += x_vel;
	box.y += y_vel;

	p2List_item<UI_Element*>* item = childs.start;
	while (item) {

		item->data->MoveBox(x_vel, y_vel);
		item = item->next;

	}
}

bool UI_Element::MouseIsIn() const
{	
	int x_pos,ypos;

	App->input->GetMousePosition(x_pos, ypos);

	return ((box.x < x_pos && (box.x + box.w) > x_pos) && (box.y < ypos && (box.y + box.h) > ypos));
}

void UI_Element::ResizeBox(const iPoint & new_size)
{
	box.w = new_size.x;
	box.h = new_size.y;
}

void UI_Element::Drag(uint upper_element)
{
	UI_Element* temp = App->gui->ItemSelected;
	j1KeyState mouse_button_1 = App->input->GetMouseButtonDown(1);
	if (mouse_button_1 == KEY_IDLE)return;
	int x_motion, y_motion;
	App->input->GetMouseMotion(x_motion, y_motion);

	if (App->gui->ItemSelected == this && mouse_button_1 == KEY_UP)App->gui->ItemSelected = nullptr;

	else if (App->gui->ItemSelected == this && mouse_button_1 == KEY_REPEAT)this->MoveBox(x_motion, y_motion);

	else if (MouseIsIn() && App->gui->ItemSelected == NULL && mouse_button_1 == KEY_REPEAT && upper_element == this->layer)App->gui->ItemSelected = this;
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
UI_Element * UI_Element::AddChild(const UI_Element* child, uint start_layer)
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
	//Set child layer
	new_child->layer = this->layer + 1 + start_layer;
	//Add the new element to the list of this childs
	this->childs.add(new_child);

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

UI_Element * UI_Element::SetParent(const UI_Element* parent)
{
	this->box.x += parent->box.x;
	this->box.y += parent->box.y;
	return this->parent = ((UI_Element*)parent);
}
