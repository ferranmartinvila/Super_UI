#include "UI_Text_Box.h"

//Constructors
UI_Text_Box::UI_Text_Box(const iPoint & position, const SDL_Rect& box, UI_String& name, UI_IMG& box_texture, uint box_capacity, bool IsPassword) :UI_Interactive_Element(position, box), name(name), box_texture(box_texture), box_capacity(box_capacity), IsPassword(IsPassword) { ui_type = TEXT_BOX; }

UI_Text_Box::UI_Text_Box(const UI_Text_Box & copy) : UI_Interactive_Element(copy.position, copy.box), name(copy.name), box_texture(copy.box_texture), box_capacity(copy.box_capacity), IsPassword(copy.IsPassword) { ui_type = TEXT_BOX; }

UI_Text_Box::UI_Text_Box() : UI_Interactive_Element(), box_capacity(0), IsPassword(false) { ui_type = TEXT_BOX; }

UI_Text_Box::~UI_Text_Box()
{

}


// ==========================
bool UI_Text_Box::Update()
{
	return true;
}

void UI_Text_Box::Draw() const
{
	box_texture.Draw();
}

void UI_Text_Box::Handle_Input()
{

}

char * UI_Text_Box::GetText() const
{
	return text_entered.GetString();
}
