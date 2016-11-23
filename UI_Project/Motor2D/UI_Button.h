#ifndef _UI_BUTTON_
#define _UI_BUTTON_

#include "UI_Interactive_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"


enum BUTTON_STATE {

	ON,
	OFF,
	OVER

};

class UI_Button : public UI_Interactive_Element {
public:

	UI_Button(const iPoint& position, const SDL_Rect& box, UI_IMG& tex_on, UI_IMG& tex_off, UI_IMG& tex_over, UI_String& name);
	UI_Button(const UI_Button& copy);
	UI_Button();

	~UI_Button();

public:

	UI_IMG tex_on;
	UI_IMG tex_off;
	UI_IMG tex_over;

	UI_String name;

	BUTTON_STATE button_state;

public:

	bool Update();
	void Draw()const;
	void Change_State(BUTTON_STATE new_button_state);

};

#endif