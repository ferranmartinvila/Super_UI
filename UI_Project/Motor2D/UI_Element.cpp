#include "UI_Element.h"

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
	return true;
}

void UI_Element::Draw()const
{

}

void UI_Element::Handle_Input()
{

}

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
