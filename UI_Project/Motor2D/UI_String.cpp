#include "UI_String.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"

//Contructors
UI_String::UI_String(const iPoint & position, char * text, _TTF_Font * text_font) : UI_Element(position, STRING), text(text), text_font(text_font) {}

UI_String::UI_String(const UI_String* copy) : UI_Element(copy->position, STRING), text(copy->text), text_font(copy->text_font) {}

UI_String::UI_String() : UI_Element({0,0}, STRING), text(nullptr), text_font(nullptr) {}

//Destructor
UI_String::~UI_String()
{

}


// ==========================
void UI_String::Draw() const
{
	//This Draw
	int x = this->position.x;
	int y = this->position.y;
	if (parent != nullptr) {
		x += parent->position.x;
		y += parent->position.y;
	}
	App->render->Blit(App->font->Print(text, { 255,255,255,255 }, text_font), x - App->render->camera.x, y - App->render->camera.y);

	//Childs Draw
	DrawChilds();
}


// ==========================
char * UI_String::GetString() const
{
	return text;
}

void UI_String::SetString(char * new_text)
{
	text = new_text;
}

