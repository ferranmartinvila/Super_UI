#ifndef _UI_STRING_
#define _UI_STRING_

#include "UI_Element.h"
#include "j1App.h"
#include "j1Fonts.h"

struct p2SString;
struct _TTF_Font;
struct SDL_Texture;

class UI_String : public UI_Element {
public:

	UI_String(const SDL_Rect& box, char* text, const SDL_Color& text_color = {255,255,255,255}, _TTF_Font* text_font = App->font->default);
	UI_String(const UI_String* copy);
	UI_String();

	~UI_String();

private:
	
	p2SString			text;
	_TTF_Font*			text_font;
	SDL_Texture*		text_texture;
	SDL_Color			text_color;

public:

	//App loop
	void		Draw(bool debug)const;

	//Functionality
	char*		GetString()const;
	uint		GetLenght()const;
	void		SetString(char* new_text);
	void		PushString(char* new_text,uint position);
	void		DeleteChar(uint position);
	uint		GetPixelLenght(uint end)const;
	void		DrawAt(int x, int y)const;
	bool		TokenizeString();
};

#endif