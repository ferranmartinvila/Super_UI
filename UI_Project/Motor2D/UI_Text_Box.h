#ifndef _UI_TEXT_BOX_
#define _UI_TEXT_BOX_

#include "UI_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"

class UI_Text_Box : public UI_Element {
public:

	UI_Text_Box(const SDL_Rect& box, char* Text_entered = nullptr, bool IsPassword = false);
	UI_Text_Box(const UI_Text_Box* copy);
	UI_Text_Box();

	~UI_Text_Box();

public:
	
	bool		IsPassword;
	UI_String	Text_entered;
	uint		Cursor_pos;
	
public:

	void	Draw(bool debug)const;
	char*	GetText()const;
	void	SetText(char* new_text);

	/*
	supr/backspace
	home/end
	cursor movement
	*/
};

#endif