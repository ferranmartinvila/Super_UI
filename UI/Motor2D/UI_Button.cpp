#include "UI_Button.h"

#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"

//Constructors
UI_Button::UI_Button(const SDL_Rect & box, const UI_Image& tex_on, const UI_Image& tex_off, const UI_Image& tex_over) :UI_Element(box, BUTTON), tex_on(tex_on), tex_off(tex_off), tex_over(tex_over), button_state(OFF) {}

UI_Button::UI_Button(const UI_Button* copy) : UI_Element(copy->box, copy->ui_type), tex_on(copy->tex_on), tex_off(copy->tex_off), tex_over(copy->tex_over), button_state(OFF) {}

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

	if(debug)App->render->DrawQuad({ x, y, box.w, box.h }, 150, 250, 0);

	//This Draw
	switch (button_state) {

		case BUTTON_STATE::ON:		tex_on.DrawAt(x,y);			break;
		case BUTTON_STATE::OFF:		tex_off.DrawAt(x, y);		break;
		case BUTTON_STATE::OVER:	tex_over.DrawAt(x, y);		break;

	}

	//Childs Draw
	DrawChilds(debug);
}

bool UI_Button::Update()
{
	HandleInput();


	UpdateChilds();
	return true;
}

BUTTON_STATE UI_Button::Change_State(BUTTON_STATE new_button_state)
{
	BUTTON_STATE last = button_state;
	button_state = new_button_state;
	return last;
}

BUTTON_STATE UI_Button::Get_State() const
{
	return button_state;
}

void UI_Button::HandleInput()
{

	j1KeyState mouse_key_1 = App->input->GetMouseButtonDown(1);

	//Pass Case
	if (mouse_key_1 == KEY_IDLE && MouseIsIn() && App->gui->upper_element == this->layer) {
		button_state = OVER;
	}
	//Push Case
	else if (mouse_key_1 == KEY_DOWN && App->gui->upper_element == this->layer && MouseIsIn()) {
		this->button_state = ON;
		App->gui->ItemSelected = this;
	}
	else if (App->gui->ItemSelected == this && mouse_key_1 == KEY_REPEAT  && MouseIsIn()) {
		button_state = ON;
	}
	//Idle Case
	else button_state = OFF;

}
