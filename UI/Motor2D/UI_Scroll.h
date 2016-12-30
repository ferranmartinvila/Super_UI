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

	SCROLL_TYPE				Scroll_Type;
	bool					ScrollSelected;
	
	SDL_Rect				ContentWindow;

	uint					ContentLenght = 0;
	uint					ScrollPosition = 0;
	
	float					Value = 0.0f;
	uint					MaxValue = 0;

	//List of the scroll items 
	p2List<UI_Element*>		Items;
	p2List<iPoint>			Items_location;
	
public:

	UI_Image				ScrollItem;
	UI_Image				ScrollBack;

private:

	int			CalculateScrollDesp();
	
public:

	//Game Loop
	void		Draw(bool debug);
	

	//Functionality
	bool		MoveScroll(int mouse_y_motion, int mouse_x_motion);
	void		UnselectScroll();
	void		AddScrollItem(UI_Element* new_item);
	void		AddScrollItemAtBottom(UI_Element* new_item);
	uint		GetScrollItemsNum()const;
	UI_Element*	GetScrollItem(uint index);

};
#endif