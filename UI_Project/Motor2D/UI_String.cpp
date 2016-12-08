#include "UI_String.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "p2SString.h"

//Contructors
UI_String::UI_String(const SDL_Rect& box, char * text, _TTF_Font * text_font) : UI_Element(box, STRING), text(text), text_font(text_font) {}

UI_String::UI_String(const UI_String* copy) : UI_Element(copy->box, STRING), text(copy->text), text_font(copy->text_font) {}

UI_String::UI_String() : UI_Element({0,0}, STRING), text(nullptr), text_font(nullptr) {}

//Destructor
UI_String::~UI_String()
{

}


// ==========================
void UI_String::Draw(bool debug) const
{
	//This Draw
	int x = this->box.x;
	int y = this->box.y;
	if (parent != nullptr) {
		x += parent->box.x;
		y += parent->box.y;
	}
	bool ret = App->render->Blit(App->font->Print(text.GetString(), { 255,255,255,255 }, text_font), x - App->render->camera.x, y - App->render->camera.y);
	if (!ret) {
		x += 70;
	}
	//Childs Draw
	DrawChilds(debug);
}


// ==========================
char * UI_String::GetString() const
{
	return (char*)text.GetString();
}

uint UI_String::GetLenght() const
{
	return uint(text.Length());
}

void UI_String::SetString(char * new_text)
{
	text.create(new_text);
}

void UI_String::PushString(char * new_text, uint position)
{
	char* test = text.InsertString(new_text, position);
	text.create(test);
}

void UI_String::BackSpace(uint position)
{
	text.DeleteChar(position);
}

