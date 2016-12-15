#ifndef _UI_IMG_
#define _UI_IMG_

#include "UI_Element.h"

class UI_IMG : public UI_Element {
public:

	UI_IMG(const SDL_Rect& box, const SDL_Rect& texture_rect = {0,0,0,0}, int texture_id = -1, int x_img = 0, int y_img = 0);
	UI_IMG(const UI_IMG* copy);
	UI_IMG();

	~UI_IMG();

public:

	SDL_Rect	texture_rect;
	int			texture_id;
	int			x_img, y_img;

public:

	void				Draw(bool debug)const;
	SDL_Rect			AdjustBox();
	void				DrawAt(int x, int y)const;
	void				ChangeTextureRect(SDL_Rect new_rect);
};

#endif // __UI_IMG__