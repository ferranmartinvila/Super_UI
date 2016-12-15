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
	IMG,
	SCROLL

};

class UI_Element {
public:

	UI_Element(const SDL_Rect& box = {0,0,0,0}, UI_TYPE ui_type = UNDEFINED, bool IsActive = true);
	UI_Element(const UI_Element* copy);
	UI_Element();

	~UI_Element();

public:

	SDL_Rect				box;
	uint					layer = 0;
	uint					tab_num = 0;
	mutable bool			IsActive = true;
	enum UI_TYPE			ui_type;

	UI_Element*				parent;
	p2List<UI_Element*>		childs;

public:

	//App Loop
	virtual bool	Update();
	bool			UpdateChilds();
	virtual bool	CleanUp();
	bool			CleanUpChilds();
	virtual void	Draw(bool debug)const;
	virtual void	DrawAt(int x, int y)const;
	void			DrawChilds(bool debug)const;
	virtual void	HandleInput();

	//Functionality
	bool			MouseIsIn(int x = 0, int y = 0)const;
	
	void			SetBoxPosition(int new_pos_x, int new_pos_y);
	virtual void	MoveBox(int x_vel, int y_vel);
	void			ResizeBox(const iPoint& new_size);
	
	bool			RectIsIn(const SDL_Rect* target, int x_vel, int y_vel, bool x_axis = false)const;
	
	bool			Drag();
	bool			Select();
	void			SetTabable();

	void			Activate();
	void			Desactivate();
	
	void			AddChild(UI_Element* child, uint start_layer = 0);
	bool			Delete_Child(UI_Element* child);
	bool			Delete_Child(uint index);
	UI_Element*		SetParent(const UI_Element* parent);
};

#endif // __UI_ELEMENT__