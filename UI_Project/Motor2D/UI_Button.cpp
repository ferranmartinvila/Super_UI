#include "UI_Button.h"

#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"

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
void UI_Button::Draw(bool debug)const
{

	//This Draw
	int x = this->box.x;
	int y = this->box.y;

	if(debug)App->render->DrawQuad({ x, y, box.w, box.h }, 150, 50, 0);

	//This Draw
	switch (button_state) {

		case BUTTON_STATE::ON:		tex_on.DrawAt(x,y);			break;
		case BUTTON_STATE::OFF:		tex_off.DrawAt(x, y);		break;
		case BUTTON_STATE::OVER:	tex_over.DrawAt(x, y);		break;

	}
	if (name.GetString() != NULL)name.Draw(debug);

	//Childs Draw
	DrawChilds(debug);
}

void UI_Button::Change_State(BUTTON_STATE new_button_state)
{
	button_state = new_button_state;
}

void UI_Button::CheckState()
{
	if (App->gui->ItemSelected != this && App->gui->ItemSelected != nullptr)return;

	j1KeyState mouse_key_1 = App->input->GetMouseButtonDown(1);

	if ((mouse_key_1 == KEY_DOWN || mouse_key_1 == KEY_REPEAT) && MouseIsIn())this->button_state = ON;
	else if (MouseIsIn())this->button_state = OVER;
	else button_state = OFF;

}
