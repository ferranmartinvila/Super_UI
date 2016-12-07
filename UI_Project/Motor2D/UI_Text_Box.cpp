#include "UI_Text_Box.h"
#include "j1App.h"
#include "j1Render.h"

//Constructors
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, UI_IMG& Box_texture, bool IsPassword) :UI_Element(box, TEXT_BOX), Box_texture(Box_texture), IsPassword(IsPassword) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* copy) : UI_Element(copy->box, copy->ui_type), Box_texture(copy->Box_texture), IsPassword(copy->IsPassword) {}

UI_Text_Box::UI_Text_Box() : UI_Element({0,0,0,0}, TEXT_BOX), IsPassword(false) {}

//Destructor
UI_Text_Box::~UI_Text_Box()
{

}


// ==========================
bool UI_Text_Box::Update()
{
	return true;
}

void UI_Text_Box::Draw(bool debug) const
{
	if (debug)App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 50, 0);
	
	Box_texture.Draw(debug);
}

void UI_Text_Box::Handle_Input()
{

}

char * UI_Text_Box::GetText() const
{
	return Text_entered.GetString();
}
