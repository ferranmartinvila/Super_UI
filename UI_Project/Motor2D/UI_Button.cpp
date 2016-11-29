#include "UI_Button.h"

//Constructors
UI_Button::UI_Button(const iPoint& position, const SDL_Rect & box, const UI_IMG& tex_on, const UI_IMG& tex_off, const UI_IMG& tex_over, const UI_String& name) :UI_Interactive_Element(position, box), tex_on(tex_on), tex_off(tex_off), tex_over(tex_over), name(name), button_state(OFF) { ui_type = BUTTON; }

UI_Button::UI_Button(const iPoint & position, const SDL_Rect & box, const UI_IMG & tex_on, const UI_IMG & tex_off, const UI_IMG & tex_over) : UI_Interactive_Element(position, box), tex_on(tex_on), tex_off(tex_off), tex_over(tex_over), name(), button_state(OFF) { ui_type = BUTTON; }

UI_Button::UI_Button(const UI_Button* copy):UI_Interactive_Element(copy->position,copy->box), tex_on(copy->tex_on), tex_off(copy->tex_off), tex_over(copy->tex_over), name(copy->name), button_state(OFF) { ui_type = BUTTON; }

UI_Button::UI_Button() : UI_Interactive_Element(), button_state(OFF) {}

//Destructor
UI_Button::~UI_Button()
{

}


// ==========================
bool UI_Button::Update()
{
	return true;
}

void UI_Button::Draw()const
{
	switch (button_state) {

	case BUTTON_STATE::ON: tex_on.Draw(); break;
	case BUTTON_STATE::OFF: tex_off.Draw(); break;
	case BUTTON_STATE::OVER: tex_over.Draw(); break;

	}

	if (name.GetString() != NULL)name.Draw();

}

void UI_Button::Change_State(BUTTON_STATE new_button_state)
{
	button_state = new_button_state;
}
