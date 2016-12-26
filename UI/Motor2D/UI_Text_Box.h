#ifndef _UI_TEXT_BOX_
#define _UI_TEXT_BOX_

#include "UI_Element.h"
#include "UI_String.h"

class UI_Text_Box : public UI_Element {
public:

	UI_Text_Box(const SDL_Rect& box, const UI_String& Text_entered, uint Cursor_w, uint Cursor_h, bool IsPassword = false, const SDL_Color& Cursor_color = {255,255,255,255});
	UI_Text_Box(const UI_Text_Box* copy);
	UI_Text_Box();

	~UI_Text_Box();

private:
	
	bool		IsPassword;
	UI_String	Text_entered;
	uint		Cursor_pos = 0;
	uint		Cursor_screen_pos = 0;
	SDL_Color	Cursor_color;
	uint		Cursor_w, Cursor_h;

public:

	//Game Loop
	void	Draw(bool debug)const;
	void	HandleInput();

	//Functionality
	char*	GetText()const;
	uint	GetTextLength()const;
	void	SetText(char* new_text);
	void	PushTextSegment(char* textsegment, uint position);
	void	DeleteTextChar(uint position);
	
	void	SetCursorPos(uint position);
	void	SetCursorScreenPos(uint position);
	uint	GetCursorPos()const;
};

#endif