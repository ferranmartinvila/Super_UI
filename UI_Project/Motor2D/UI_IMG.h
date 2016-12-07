#ifndef _UI_IMG_
#define _UI_IMG_

#include "UI_Element.h"

class UI_IMG : public UI_Element {
public:

	UI_IMG(const SDL_Rect& box, int texture_id = -1, const SDL_Rect& texture_rect = {0,0,0,0});
	UI_IMG(const SDL_Rect& box , const SDL_Rect& texture_rect = { 0,0,0,0 });
	UI_IMG(const UI_IMG* copy);
	UI_IMG();

	~UI_IMG();

public:

	SDL_Rect	texture_rect;
	int			texture_id;

public:

	void				Draw(bool debug)const;
	SDL_Rect			AdjustBox();
	void				DrawAt(int x, int y)const;
};

#endif // __UI_IMG__