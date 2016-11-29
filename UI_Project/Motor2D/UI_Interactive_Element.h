#ifndef _UI_INTERACTIVE_ELEMENT_
#define _UI_INTERACTIVE_ELEMENT_

#include "UI_Element.h"
#include "SDL\include\SDL_rect.h"

class UI_Interactive_Element : public UI_Element {
public:

	UI_Interactive_Element(const iPoint& position, const SDL_Rect& box, UI_TYPE ui_type);
	UI_Interactive_Element(const UI_Interactive_Element* copy);
	UI_Interactive_Element();

	~UI_Interactive_Element();

public:

	SDL_Rect box;

public:

	bool MouseIsIn(const iPoint& mouse_pos)const;
	void ResizeBox(const iPoint& new_size);
	void MoveBox(const iPoint& new_pos);

};

#endif
