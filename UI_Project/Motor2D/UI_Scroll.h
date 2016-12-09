#ifndef _UI_SCROLL_
#define _UI_SCROLL_

#include "UI_Element.h"
struct UI_String;
#include "UI_IMG.h"

class UI_Scroll : public UI_Element {
public:

	UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_IMG& ScrollItem, const UI_IMG& ScrollBack, UI_Element* Content);
	UI_Scroll(const UI_Scroll* copy);
	~UI_Scroll();

public:

	SDL_Rect	ContentWindow;
	UI_Element*	Content;
	UI_IMG		ScrollItem;
	UI_IMG		ScrollBack;

public:

	void	Draw(bool debug)const;
	bool	MoveScroll(int mouse_y_motion, int mouse_x_motion);
	void	MoveBox(int x_vel, int y_vel);

};
#endif