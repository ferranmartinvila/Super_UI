#include "UI_Interactive_String.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"


//Contructors
UI_Interactive_String::UI_Interactive_String(const iPoint & position, const SDL_Rect & box, const UI_String& string) : UI_Interactive_Element(position, box, INTERACTIVE_STRING),string(string) {}

UI_Interactive_String::UI_Interactive_String(const UI_Interactive_String * copy) : UI_Interactive_Element(copy->position, copy->box, copy->ui_type), string(copy->string) {}

UI_Interactive_String::UI_Interactive_String() : UI_Interactive_Element({ 0,0 }, {0,0,0,0}, INTERACTIVE_STRING), string() {}


//Destructor
UI_Interactive_String::~UI_Interactive_String()
{


}



// ==========================
void UI_Interactive_String::Draw() const
{
	App->render->Blit(App->font->Print(string.text, { 255,255,255,255 }, string.text_font), position.x - App->render->camera.x, position.y - App->render->camera.y);
}

char * UI_Interactive_String::GetString() const
{
	return string.text;
}

void UI_Interactive_String::SetString(char * new_text)
{
	string.text = new_text;
}
