#ifndef _UI_STRING_
#define _UI_STRING_

#include "UI_Element.h"
#include "j1App.h"
#include "j1Fonts.h"

struct p2SString;
struct _TTF_Font;

class UI_String : public UI_Element {
public:

	UI_String(const SDL_Rect& box, char* text, _TTF_Font* text_font = App->font->default);
	UI_String(const UI_String* copy);
	UI_String();

	~UI_String();

public:
	
	p2SString		text;
	_TTF_Font*	text_font;

public:

	//App loop
	void	Draw(bool debug)const;
	
	//Functionality
	char*	GetString()const;
	void	SetString(char* new_text);

};

#endif