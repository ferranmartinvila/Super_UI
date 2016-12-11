#ifndef _UI_TEXT_BOX_
#define _UI_TEXT_BOX_

#include "UI_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"

class UI_Text_Box : public UI_Element {
public:

	UI_Text_Box(const SDL_Rect& box,const UI_String& Text_entered, bool IsPassword = false);
	UI_Text_Box(const UI_Text_Box* copy);
	UI_Text_Box();

	~UI_Text_Box();

public:
	
	bool		IsPassword;
	UI_String	Text_entered;
	uint		Cursor_pos = 0;
	uint		Cursor_screen_pos = 0;

public:

	//App Loop
	void	Draw(bool debug)const;
	void	HandleInput();

	//Functionality
	char*	GetText()const;
	uint	GetTextLength()const;
	void	SetText(char* new_text);
	void	SetCursorPos(uint position);
	uint	GetCursorPos()const;

	/*
	home/end
	*/
};

#endif