#include "UI_Interactive_Element.h"


//Constructors
UI_Interactive_Element::UI_Interactive_Element(const iPoint & position, const SDL_Rect & box) :UI_Element(position, UNDEFINED), box(box) {}

UI_Interactive_Element::UI_Interactive_Element(const UI_Interactive_Element* copy) : UI_Element(copy->position, UNDEFINED), box(copy->box) {}

UI_Interactive_Element::UI_Interactive_Element() : UI_Element(), box({ 0, 0, 0, 0 }) {}

//Destructor
UI_Interactive_Element::~UI_Interactive_Element()
{

}


// ==========================
bool UI_Interactive_Element::MouseIsIn(const iPoint & mouse_pos) const
{
	return ((box.x < mouse_pos.x && (box.x + box.w) > mouse_pos.x) && (box.y < mouse_pos.y && (box.y + box.h) > mouse_pos.y));
}

void UI_Interactive_Element::ResizeBox(const iPoint & new_size)
{
	box.w = new_size.x;
	box.h = new_size.y;
}

void UI_Interactive_Element::MoveBox(const iPoint & new_pos)
{
	box.x = new_pos.x;
	box.y = new_pos.y;
}
