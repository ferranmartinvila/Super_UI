#include "UI_Button.h"

//Constructors
UI_Button::UI_Button(const SDL_Rect & box, const UI_IMG& tex_on, const UI_IMG& tex_off, const UI_IMG& tex_over, const UI_String& name) :UI_Element(box, BUTTON), tex_on(tex_on), tex_off(tex_off), tex_over(tex_over), name(name), button_state(OFF) {}

UI_Button::UI_Button(const SDL_Rect & box, const UI_IMG & tex_on, const UI_IMG & tex_off, const UI_IMG & tex_over) : UI_Element(box, BUTTON), tex_on(tex_on), tex_off(tex_off), tex_over(tex_over), name(), button_state(OFF) {}

UI_Button::UI_Button(const UI_Button* copy) : UI_Element(copy->box, copy->ui_type), tex_on(copy->tex_on), tex_off(copy->tex_off), tex_over(copy->tex_over), name(copy->name), button_state(OFF) {}

UI_Button::UI_Button() : UI_Element({ 0,0,0,0 }, BUTTON), button_state(OFF) {}

//Destructor
UI_Button::~UI_Button()
{

}


// ==========================
void UI_Button::Draw()const
{
	//This Draw
	switch (button_state) {

		case BUTTON_STATE::ON:		tex_on.Draw();		break;
		case BUTTON_STATE::OFF:		tex_off.Draw();		break;
		case BUTTON_STATE::OVER:	tex_over.Draw();	break;

	}
	if (name.GetString() != NULL)name.Draw();

	//Childs Draw
	DrawChilds();
}

void UI_Button::Change_State(BUTTON_STATE new_button_state)
{
	button_state = new_button_state;
}
