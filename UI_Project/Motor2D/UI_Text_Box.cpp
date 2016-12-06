#include "UI_Text_Box.h"

//Constructors
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, UI_String& name, UI_IMG& box_texture, uint box_capacity, bool IsPassword) :UI_Element(box, TEXT_BOX), name(name), box_texture(box_texture), box_capacity(box_capacity), IsPassword(IsPassword) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* copy) : UI_Element(copy->box, copy->ui_type), name(copy->name), box_texture(copy->box_texture), box_capacity(copy->box_capacity), IsPassword(copy->IsPassword) {}

UI_Text_Box::UI_Text_Box() : UI_Element({0,0,0,0}, TEXT_BOX), box_capacity(0), IsPassword(false) {}

//Destructor
UI_Text_Box::~UI_Text_Box()
{

}


// ==========================
bool UI_Text_Box::Update()
{
	return true;
}

void UI_Text_Box::Draw(bool debug) const
{
	box_texture.Draw(debug);
}

void UI_Text_Box::Handle_Input()
{

}

char * UI_Text_Box::GetText() const
{
	return text_entered.GetString();
}
