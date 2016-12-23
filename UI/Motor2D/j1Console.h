#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

class j1Console : public j1Module {
public:

	j1Console();
	~j1Console();

public:

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Rect console_area;
	uint r = 0;
	uint g = 0;
	uint b = 0;
	uint a = 0;

public:

	void ActiveConsole();

};
#endif