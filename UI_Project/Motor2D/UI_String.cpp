#include "UI_String.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"

//Contructors
UI_String::UI_String(const iPoint & position, char * text, uint text_size, _TTF_Font * text_font) : UI_Element(position, STRING), text(text), text_size(text_size), text_font(text_font) {}

UI_String::UI_String(const UI_String* copy) : UI_Element(copy->position, STRING), text(copy->text), text_size(copy->text_size), text_font(copy->text_font) {}

UI_String::UI_String():UI_Element(), text(nullptr), text_font(nullptr){}

UI_String::~UI_String()
{

}

void UI_String::Draw() const
{
	App->render->Blit(App->font->Print(text, { 255,255,255,255 }, text_font), position.x - App->render->camera.x, position.y - App->render->camera.y);
}

char * UI_String::GetString() const
{
	return text;
}

void UI_String::SetString(char * new_text)
{
	text = new_text;
}

