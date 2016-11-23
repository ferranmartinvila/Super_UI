#ifndef _UI_IMG_
#define _UI_IMG_

#include "UI_Element.h"
#include "SDL\include\SDL_rect.h"

class UI_IMG : public UI_Element {
public:

	UI_IMG(const iPoint& position, const SDL_Rect& texture_rect);
	UI_IMG(const UI_IMG* copy);
	UI_IMG();

	~UI_IMG();

public:

	SDL_Rect texture_rect;

public:

	void Draw()const;

};

#endif