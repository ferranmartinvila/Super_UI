#ifndef _UI_SCROLL_
#define _UI_SCROLL_

#include "UI_Element.h"
#include "UI_Image.h"

enum SCROLL_TYPE {

	VERTICAL,
	VERTICAL_INV,

};

class UI_Scroll : public UI_Element {
public:

	UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const UI_Image& ScrollItem, const UI_Image& ScrollBack, SCROLL_TYPE Scroll_Type = VERTICAL, uint MaxValue = 0);
	UI_Scroll(const UI_Scroll* copy);
	~UI_Scroll();

private:

	SDL_Rect				ContentWindow;
	SCROLL_TYPE				Scroll_Type;
	uint					ContentLenght = 0;
	float					Value = 0.0f;
	uint					MaxValue = 0;

	int						ScrollLastLocation = 0;
	int						ScrollLocation = 0;

	p2List<UI_Element*>		Items;
	
	bool					ScrollSelected;

public:

	UI_Image				ScrollItem;
	UI_Image				ScrollBack;
	
public:

	//Game Loop
	void	Draw(bool debug)const;
	bool	Update();
	void	HandleInput();


	//Functionality
	bool			MoveScroll(int mouse_y_motion, int mouse_x_motion);
	void			AddScrollItem(UI_Element* new_item);

};
#endif