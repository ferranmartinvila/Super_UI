#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_

#include "p2Point.h"
#include "p2Defs.h"
#include "p2List.h"
#include "SDL\include\SDL_rect.h"

enum UI_TYPE {

	UNDEFINED,
	BUTTON,
	TEXT_BOX,
	STRING,
	IMG

};

class UI_Element {
public:

	UI_Element(const SDL_Rect& box = {0,0,0,0}, UI_TYPE ui_type = UNDEFINED, bool IsActive = true);
	UI_Element(const UI_Element* copy);
	UI_Element();

	~UI_Element();

public:

	SDL_Rect		box;
	bool			IsActive;
	bool			IsSelected;
	enum UI_TYPE	ui_type;

	UI_Element*				parent;
	p2List<UI_Element*>		childs;

public:

	//App Loop
	virtual bool	Update();
	bool			UpdateChilds();
	virtual bool	CleanUp();
	bool			CleanUpChilds();
	virtual void	Draw()const;
	void			DrawChilds()const;

	//Functionality
	bool			MouseIsIn()const;
	void			SetPosition(const iPoint& new_pos);
	void			MoveBox(int x_vel, int y_vel);
	void			ResizeBox(const iPoint& new_size);
	void			Activate();
	void			Desactivate();
	
	UI_Element*		AddChild(const UI_Element* child);
	bool			Delete_Child(UI_Element* child);
	bool			Delete_Child(uint index);
	UI_Element*		SetParent(const UI_Element* parent);
};

#endif // __UI_ELEMENT__