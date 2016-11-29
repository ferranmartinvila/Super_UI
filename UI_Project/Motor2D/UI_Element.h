#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_

#include "p2Point.h"
#include "p2Defs.h"

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

	iPoint position;
	enum UI_TYPE ui_type;
	bool IsActive;

public:

	virtual bool Update();
	virtual void Draw()const;
	virtual void Handle_Input();

	void SetPosition(const iPoint& new_position);
	void Activate();
	void Desactivate();
	
};

#endif