#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_

#include "p2Point.h"
#include "p2Defs.h"

enum UI_TYPE {

	UNDEFINED,
	BUTTON,
	TEXT_BOX,
	STRING,
	IMG

};

class UI_Element {
public:

	UI_Element(const iPoint& position, UI_TYPE ui_type);
	UI_Element(const UI_Element& copy);
	UI_Element();

	~UI_Element();

public:

	iPoint position;
	enum UI_TYPE ui_type;

public:

	virtual bool Update();
	virtual void Draw();
	virtual void Handle_Input();
	void SetPosition(const iPoint& new_position);

};

#endif