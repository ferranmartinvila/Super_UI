#ifndef _UI_STRING_
#define _UI_STRING_

#include "UI_Element.h"

struct _TTF_Font;

class UI_String : public UI_Element {
public:

	UI_String(const iPoint& position, char* text, _TTF_Font* text_font);
	UI_String(const UI_String* copy);
	UI_String();

	~UI_String();

public:
	
	char*		text;
	_TTF_Font*	text_font;

public:

	//App loop
	void	Draw()const;
	
	//Functionality
	char*	GetString()const;
	void	SetString(char* new_text);

};

#endif