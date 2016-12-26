#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"

#include "UI_Text_Box.h"

//Constructors ============================================
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, const UI_String& Text_entered, uint Cursor_w, uint Cursor_h, bool IsPassword, const SDL_Color& Cursor_color) :UI_Element(box, TEXT_BOX), Text_entered(Text_entered), Cursor_w(Cursor_w), Cursor_h(Cursor_h), IsPassword(IsPassword), Cursor_color(Cursor_color) {}

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
	if (App->gui->ItemSelected == this)
	{
		App->render->DrawQuad({ box.x + (int)Cursor_screen_pos, box.y ,(int)Cursor_w,(int)Cursor_h }, Cursor_color.r, Cursor_color.g, Cursor_color.b, Cursor_color.a);
	}

	//Draw the Text
	if (Text_entered.GetLenght() > 0)
	{
		Text_entered.DrawAt(box.x, box.y);
	}

	DrawChilds(debug);
}

void UI_Text_Box::HandleInput()
{

	//Mouse In/Out ------------------------------
	if (this->MouseIsIn())
	{
		App->gui->GetInputTarget()->GUI_Input(this, MOUSE_IN);
	}
	else
	{
		App->gui->GetInputTarget()->GUI_Input(this, MOUSE_OUT);
	}

	//Mouse Left Button -------------------------
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (this->MouseIsIn() && App->gui->upper_element == this->layer)
		{
			App->gui->ItemSelected = this;
			App->gui->GetInputTarget()->GUI_Input(this, MOUSE_LEFT_BUTTON_DOWN);
		}
		else if (App->gui->ItemSelected == this)
		{
			App->gui->ItemSelected = nullptr;
			return;
		}
	}
	if (App->gui->ItemSelected != this)return;
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		App->gui->GetInputTarget()->GUI_Input(this, MOUSE_LEFT_BUTTON_REPEAT);
	}
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		App->gui->GetInputTarget()->GUI_Input(this, MOUSE_LEFT_BUTTON_UP);
	}

	//Mouse Right Button ------------------------
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		App->gui->GetInputTarget()->GUI_Input(this, MOUSE_RIGHT_BUTTON);
	}

	//Arrows ------------------------------------
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		if (Cursor_pos > 0)
		{
			Cursor_pos--;
			Cursor_screen_pos = Text_entered.GetPixelLenght(Cursor_pos);
		}
		App->gui->GetInputTarget()->GUI_Input(this, LEFT_ARROW);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		if (Cursor_pos < Text_entered.GetLenght())
		{
			Cursor_pos++;
			Cursor_screen_pos = Text_entered.GetPixelLenght(Cursor_pos);
		}
		App->gui->GetInputTarget()->GUI_Input(this, RIGHT_ARROW);
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		App->gui->GetInputTarget()->GUI_Input(this, UP_ARROW);
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		App->gui->GetInputTarget()->GUI_Input(this, DOWN_ARROW);
	}

	//Backspace/Delete --------------------------
	else if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
	{
		if (Text_entered.DeleteChar(Cursor_pos - 1))
		{
			Cursor_pos--;
			Cursor_screen_pos = Text_entered.GetPixelLenght(Cursor_pos);
		}
		App->gui->GetInputTarget()->GUI_Input(this, BACKSPACE);
	}
	else if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
	{
		Text_entered.DeleteChar(Cursor_pos);
		App->gui->GetInputTarget()->GUI_Input(this, SUPR);
	}
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
	SetCursorScreenPos(position);
}

void UI_Text_Box::SetCursorScreenPos(uint position)
{
	Cursor_screen_pos = Text_entered.GetPixelLenght(position);
}

uint UI_Text_Box::GetCursorPos() const
{
	return Cursor_pos;
}