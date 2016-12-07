#ifndef _UI_SCROLL_
#define _UI_SCROLL_

#include "UI_Element.h"
struct UI_String;
#include "UI_IMG.h"

class UI_Scroll : public UI_Element {

	UI_Scroll(const SDL_Rect& box, const SDL_Rect& Scroll, const SDL_Rect& ContentWindow, const UI_IMG& ScrollItem, const UI_IMG& ScrollBack, const UI_Element* Content);


public:

	SDL_Rect	ContentWindow;
	SDL_Rect	ScrollArea;
	UI_Element* Content;
	UI_IMG		ScrollItem;
	UI_IMG		ScrollBack;

public:

	void	Draw(bool debug)const;
	bool	MoveScroll(int mouse_y_motion);

};
#endif