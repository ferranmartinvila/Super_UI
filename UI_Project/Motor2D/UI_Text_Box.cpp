#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"

#include "UI_Text_Box.h"

//Constructors ============================================
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, const UI_String& Text_entered, bool IsPassword) :UI_Element(box, TEXT_BOX), Text_entered(Text_entered), IsPassword(IsPassword) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* copy) : UI_Element(copy->box, copy->ui_type), Text_entered(copy->Text_entered) , IsPassword(copy->IsPassword) {}

UI_Text_Box::UI_Text_Box() : UI_Element({0,0,0,0}, TEXT_BOX), IsPassword(false) {}


//Destructor ==============================================
UI_Text_Box::~UI_Text_Box()
{

}


// Game Loop ==============================================
void UI_Text_Box::Draw(bool debug) const
{
	//Draw the debug Quad
	if (debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 25, 25, 25);
	
	//Draw the cursor
	if(App->gui->ItemSelected == this)App->render->DrawQuad({ box.x + (int)Cursor_screen_pos, box.y + 0,3,15 }, 120, 50, 200);

	//Draw the Text
	if (Text_entered.GetLenght())Text_entered.DrawAt(box.x, box.y);

	DrawChilds(debug);
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
		Text_entered.DeleteChar(Cursor_pos - 1);
		Cursor_pos--;
		
	}

	//Supr ===============================================
	else if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN && Cursor_pos < Text_entered.GetLenght())
	{
		Text_entered.DeleteChar(Cursor_pos);
	}


	//Update the position of the cursor on the screen
	Cursor_screen_pos = Text_entered.GetPixelLenght(Cursor_pos);
}


// Functionality ==========================================
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

void UI_Text_Box::PushTextSegment(char * textsegment, uint position)
{
	Text_entered.PushString(textsegment, position);
}

void UI_Text_Box::DeleteTextChar(uint position)
{
	Text_entered.DeleteChar(position);
}

void UI_Text_Box::SetCursorPos(uint position)
{
	Cursor_pos = position;
}

uint UI_Text_Box::GetCursorPos() const
{
	return Cursor_pos;
}