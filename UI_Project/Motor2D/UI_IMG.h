#ifndef _UI_IMG_
#define _UI_IMG_

#include "UI_Element.h"
#include "SDL\include\SDL_rect.h"

class UI_IMG : public UI_Element {
public:

	UI_IMG(const iPoint& position, int texture_id = -1, const SDL_Rect& texture_rect = {0,0,0,0});
	UI_IMG(const iPoint& position, const SDL_Rect& texture_rect = { 0,0,0,0 });
	UI_IMG(const UI_IMG* copy);
	UI_IMG();

	~UI_IMG();

public:

	SDL_Rect	texture_rect;
	int			texture_id;

public:

	void Draw()const;

};

#endif // __UI_IMG__