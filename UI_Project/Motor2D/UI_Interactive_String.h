#ifndef _UI_INTERACTIVE_STRING_
#define _UI_INTERACTIVE_STRING_

#include "UI_Interactive_Element.h"
#include "UI_String.h"
struct _TTF_Font;

class UI_Interactive_String : public UI_Interactive_Element {
public:

	UI_Interactive_String(const iPoint& position, const SDL_Rect& box, const UI_String& string);
	UI_Interactive_String(const UI_Interactive_String* copy);
	UI_Interactive_String();

	~UI_Interactive_String();

public:

	UI_String string;

public:

	void Draw()const;
	char* GetString()const;
	void SetString(char* new_text);

};

#endif // __UI_Interactive_String__