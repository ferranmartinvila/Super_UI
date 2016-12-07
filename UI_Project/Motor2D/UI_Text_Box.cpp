#include "UI_Text_Box.h"
#include "j1App.h"
#include "j1Render.h"

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

	Text_entered.Draw(false);

	DrawChilds(debug);
}

char * UI_Text_Box::GetText() const
{
	return Text_entered.GetString();
}

void UI_Text_Box::SetText(char * new_text)
{
	Text_entered.SetString(new_text);
}
