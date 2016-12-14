#include "UI_String.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "p2SString.h"

//Contructors
UI_String::UI_String(const SDL_Rect& box, char * text, const SDL_Color& text_color, _TTF_Font * text_font) : UI_Element(box, STRING), text(text), text_font(text_font), text_texture(App->font->Print(this->text.GetString(), text_color, text_font)), text_color(text_color) {}

UI_String::UI_String(const UI_String* copy) : UI_Element(copy->box, STRING), text(copy->text), text_font(copy->text_font), text_texture(copy->text_texture), text_color(copy->text_color) {}

UI_String::UI_String() : UI_Element({0,0}, STRING), text(nullptr), text_font(nullptr) {}

//Destructor
UI_String::~UI_String()
{

}


// ==========================
void UI_String::Draw(bool debug) const
{
	//This Draw
	App->render->Blit(text_texture, box.x - App->render->camera.x, box.y - App->render->camera.y);

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
	text_texture = App->font->Print(text.GetString(), text_color, text_font);
}

void UI_String::PushString(char * new_text, uint position)
{
	char* test = text.InsertString(new_text, position);
	text.create(test);
	text_texture = App->font->Print(text.GetString(), text_color, text_font);
}

void UI_String::DeleteChar(uint position)
{
	text.DeleteChar(position);
	text_texture = App->font->Print(text.GetString(), text_color, text_font);
}

uint UI_String::GetPixelLenght(uint end) const
{
	char* segment = text.StringSegment(0, end);
	int x, y;
	App->font->CalcSize(segment, x, y, text_font);
	return x;
}

void UI_String::DrawAt(int x, int y) const
{
	//This Draw
	App->render->Blit(text_texture, box.x + x - App->render->camera.x, box.y + y - App->render->camera.y);

}

bool UI_String::TokenizeString()
{
	SDL_SetRenderTarget(App->render->renderer, text_texture);
	SDL_SetTextureBlendMode(text_texture, SDL_BlendMode::SDL_BLENDMODE_ADD);

	char* copy = (char*)text.GetString();
	char* token = strtok(copy, "\n");
	SDL_Texture* token_texture = nullptr;
	while (token != NULL) {


		token_texture = App->font->Print(copy, text_color, App->font->default);
		App->render->Blit(token_texture, 10, 10);
		token = strtok(NULL, "\n");
	}
	
	text_texture = SDL_CreateTexture(App->render->renderer, NULL, NULL, 400, 600);
	return false;
}

