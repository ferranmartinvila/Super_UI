#include "UI_Text_Box.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Fonts.h"

//Constructors
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, char* Text_entered, bool IsPassword) :UI_Element(box, TEXT_BOX), Text_entered(box,Text_entered), IsPassword(IsPassword) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* copy) : UI_Element(copy->box, copy->ui_type), Text_entered(copy->box,copy->Text_entered.GetString()) , IsPassword(copy->IsPassword) {}

UI_Text_Box::UI_Text_Box() : UI_Element({0,0,0,0}, TEXT_BOX), IsPassword(false) {}

//Destructor
UI_Text_Box::~UI_Text_Box()
{

}


// ==========================

void UI_Text_Box::Draw(bool debug) const
{
	if (debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 50, 0);
	App->render->DrawQuad({ box.x + (int)Cursor_pos, box.y + 0,5,15 }, 50, 50, 50);

	if(Text_entered.GetLenght())Text_entered.Draw(false);

	DrawChilds(debug);
}

bool UI_Text_Box::Update()
{
	HandleInput();

	bool ret = UpdateChilds();

	return ret;
}

void UI_Text_Box::HandleInput()
{
	if (App->gui->ItemSelected != this)return;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN && Cursor_pos > 0)Cursor_pos--;

	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN && Cursor_pos < Text_entered.GetLenght())Cursor_pos++;

	else if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && Cursor_pos > 0) {
		Text_entered.BackSpace(Cursor_pos);
		Cursor_pos--;
	}
}

char * UI_Text_Box::GetText() const
{
	return Text_entered.GetString();
}

uint UI_Text_Box::GetTextLength() const
{
	return Text_entered.GetLenght();
}

void UI_Text_Box::SetText(char * new_text)
{
	Text_entered.SetString(new_text);
}

void UI_Text_Box::SetCursorPos(uint position)
{
	Cursor_pos = position;
}

uint UI_Text_Box::GetCursorPos() const
{
	return Cursor_pos;
}
