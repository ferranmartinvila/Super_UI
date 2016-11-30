#ifndef _UI_TEXT_BOX_
#define _UI_TEXT_BOX_

#include "UI_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"

class UI_Text_Box : public UI_Element {
public:

	UI_Text_Box(const SDL_Rect& box,UI_String& name, UI_IMG& box_texture, uint box_capacity, bool IsPassword);
	UI_Text_Box(const UI_Text_Box* copy);
	UI_Text_Box();

	~UI_Text_Box();

public:
	
	UI_String name;
	UI_IMG box_texture;
	uint box_capacity;
	bool IsPassword;
	
	UI_String text_entered;
	uint cursor_pos;
	uint cursor_rate;
	uint text_selected;
	
	bool IsActive;
	
public:

	bool Update();
	void Draw()const;
	void Handle_Input();
	char* GetText()const;
	
};

#endif