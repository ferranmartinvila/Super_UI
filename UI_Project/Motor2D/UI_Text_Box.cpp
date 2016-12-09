#include "UI_Text_Box.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Fonts.h"
#include "p2Log.h"

//Constructors
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, char* Text_entered, bool IsPassword) :UI_Element(box, TEXT_BOX), Text_entered(box,Text_entered), IsPassword(IsPassword) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* copy) : UI_Element(copy->box, copy->ui_type), Text_entered(copy->box,copy->Text_entered.GetString()) , IsPassword(copy->IsPassword) {}

UI_Text_Box::UI_Text_Box() : UI_Element({0,0,0,0}, TEXT_BOX), IsPassword(false) {}

//Destructor
UI_Text_Box::~UI_Text_Box()
{

}


// Game Loop ==========================
void UI_Text_Box::Draw(bool debug) const
{
	//Draw the debug Quad
	if (debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 25, 25, 25);
	
	//Draw the cursor
	if(App->gui->ItemSelected == this)App->render->DrawQuad({ box.x + (int)Cursor_screen_pos, box.y + 0,3,15 }, 120, 50, 200);

	//Draw the Text
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

	//Move Cursor to the Left =============================
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN && Cursor_pos > 0)
	{
		Cursor_pos--;
	}

	//Move Cursor to the Right ============================
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN && Cursor_pos < Text_entered.GetLenght())
	{
		Cursor_pos++;
	}

	//Backspace ===========================================
	else if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && Cursor_pos > 0)
	{
		Text_entered.BackSpace(Cursor_pos - 1);
		Cursor_pos--;
		
	}

	//Supr ===============================================
	else if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN && Cursor_pos < Text_entered.GetLenght())
	{
		Text_entered.BackSpace(Cursor_pos);
	}


	//Update the position of the cursor on the screen
	Cursor_screen_pos = Text_entered.GetPixelLenght(Cursor_pos);
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

void UI_Text_Box::MoveBox(int x_vel, int y_vel)
{
	box.x += x_vel;
	box.y += y_vel;

	Text_entered.MoveBox(x_vel, y_vel);

	p2List_item<UI_Element*>* item = childs.start;
	while (item) {

		item->data->MoveBox(x_vel, y_vel);
		item = item->next;

	}
}
