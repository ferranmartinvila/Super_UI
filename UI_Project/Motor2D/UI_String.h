#ifndef _UI_STRING_
#define _UI_STRING_

#include "UI_Element.h"

struct _TTF_Font;

class UI_String : public UI_Element {
public:

	UI_String(const iPoint& position, char* text, uint text_size, _TTF_Font* text_font);
	UI_String(const UI_String* copy);
	UI_String();

	~UI_String();

public:
	
	char* text;
	uint text_size;
	_TTF_Font* text_font;

public:

	void Draw()const;
	char* GetString()const;
	void SetString(char* new_text);

};

#endif