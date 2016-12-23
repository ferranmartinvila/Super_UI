#include "j1Console.h"
#include "j1App.h"
#include "j1Render.h"


//Constructors ============================================
j1Console::j1Console()
{
	name.create("console");
}


//Destructors =============================================
j1Console::~j1Console()
{

}

//Game Loop ===============================================
bool j1Console::Awake(pugi::xml_node& config)
{
	//Load console window size
	console_area.x = config.child("area").attribute("x").as_int();
	console_area.y = config.child("area").attribute("y").as_int();
	console_area.w = config.child("area").attribute("w").as_int();
	console_area.h = config.child("area").attribute("h").as_int();
	//Load console window color
	r = config.child("color").attribute("r").as_int();
	g = config.child("color").attribute("g").as_int();
	b = config.child("color").attribute("b").as_int();
	a = config.child("color").attribute("a").as_int();
	return true;
}

bool j1Console::Start()
{
	return true;
}

bool j1Console::PostUpdate()
{
	App->render->DrawQuad(console_area, r, g, b, a);
	return true;
}

bool j1Console::CleanUp()
{
	return true;
}


// Functionality =========================================
void j1Console::ActiveConsole()
{
	active = !active;
}
