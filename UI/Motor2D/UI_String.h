#ifndef _UI_STRING_
#define _UI_STRING_

#include "UI_Element.h"
#include "j1Fonts.h"

struct p2SString;
struct _TTF_Font;
struct SDL_Texture;

class UI_String : public UI_Element {
public:

	UI_String(const SDL_Rect& box, char* text, const SDL_Color& text_color = { 255,255,255,255 }, _TTF_Font* text_font = App->font->default);
	UI_String(const UI_String* copy);
	UI_String();

	~UI_String();

private:
	
	p2SString			text;
	_TTF_Font*			text_font;
	SDL_Texture*		text_texture;
	SDL_Color			text_color;

public:

	//Game loop
	void		Draw(bool debug)const;

	//Functionality
	char*		GetString()const;
	void		SetString(char* new_text);
	void		PushString(char* new_text,uint position);
	bool		DeleteChar(uint position);

	uint		GetPixelLenght(uint end)const;
	uint		GetLenght()const;

	void		DrawAt(int x, int y)const;
	bool		TokenizeString(uint margin = 0);
	SDL_Rect	AdjustBox();
	bool		SetFont(char* font_dir, uint size);

};

#endif