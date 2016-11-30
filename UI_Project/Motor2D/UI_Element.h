#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_

#include "p2Point.h"
#include "p2Defs.h"
#include "p2List.h"

enum UI_TYPE {

	UNDEFINED,
	BUTTON,
	TEXT_BOX,
	STRING,
	INTERACTIVE_STRING,
	IMG

};

class UI_Element {
public:

	UI_Element(const iPoint& position, UI_TYPE ui_type, bool IsActive = true);
	UI_Element(const UI_Element* copy);
	UI_Element();

	~UI_Element();

public:

	bool			IsActive;
	iPoint			position;
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
	void			SetPosition(const iPoint& new_position);
	void			Activate();
	void			Desactivate();
	
	UI_Element*		AddChild(const UI_Element* child);
	bool			Delete_Child(UI_Element* child);
	bool			Delete_Child(uint index);
	UI_Element*		SetParent(const UI_Element* parent);
};

#endif // __UI_ELEMENT__