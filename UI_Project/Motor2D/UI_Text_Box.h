#ifndef _UI_TEXT_BOX_
#define _UI_TEXT_BOX_

#include "UI_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"

class UI_Text_Box : public UI_Element {
public:

	UI_Text_Box(const SDL_Rect& box,UI_IMG& Box_texture, bool IsPassword);
	UI_Text_Box(const UI_Text_Box* copy);
	UI_Text_Box();

	~UI_Text_Box();

public:
	
	UI_IMG		Box_texture;
	bool		IsPassword;
	
	UI_String	Text_entered;
	uint		Cursor_pos;
	
public:

	bool Update();
	void Draw(bool debug)const;
	void Handle_Input();
	char* GetText()const;
	
	/*
	supr/backspace
	home/end
	cursor movement
	*/
};

#endif