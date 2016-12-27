#include "j1Console.h"
#include "j1App.h"
#include "j1Render.h"

#include "UI_Scroll.h"
#include "UI_String.h"
#include "UI_Text_Box.h"

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
	console_color.r = config.child("area_color").attribute("r").as_int();
	console_color.g = config.child("area_color").attribute("g").as_int();
	console_color.b = config.child("area_color").attribute("b").as_int();
	console_color.a = config.child("area_color").attribute("a").as_int();

	//Load Console Text Box
	SDL_Rect input_box;
	input_box.x = config.child("input_box").attribute("x").as_int();
	input_box.y = config.child("input_box").attribute("y").as_int();
	input_box.w = config.child("input_box").attribute("w").as_int();
	input_box.h = config.child("input_box").attribute("h").as_int();
	
	//Load Console Text Font
	font = App->font->Load(config.child("console_font").attribute("file").as_string(), config.child("console_font").attribute("size").as_int());
	font_color.r = config.child("font_color").attribute("r").as_int();
	font_color.g = config.child("font_color").attribute("g").as_int();
	font_color.b = config.child("font_color").attribute("b").as_int();
	font_color.a = config.child("font_color").attribute("a").as_int();
	
	//Load Text Cursor
	int cursor_w = config.child("cursor").attribute("w").as_int();
	int cursor_h = config.child("cursor").attribute("h").as_int();
	
	//Build Console Text
	UI_String* console_text = new UI_String({ 0,0,0,0 }, "", { 255,255,255,255 }, font);
	console_input_box = new UI_Text_Box(input_box, console_text, cursor_w, cursor_h);
	return true;
}

bool j1Console::Start()
{
	return true;
}

bool j1Console::PostUpdate()
{
	//Draw Console Area
	App->render->DrawQuad(console_area, console_color.r, console_color.g, console_color.b, console_color.a);
	
	//Draw Console Input Box
	console_input_box->Draw(true);

	//Update Console Input Box
	console_input_box->HandleInput();
	return true;
}

bool j1Console::CleanUp()
{
	return true;
}


// Functionality =========================================
void j1Console::ChangeConsoleState()
{
	active = !active;
	if(active == true)App->gui->ItemSelected = console_input_box;
	else this->console_input_box->SetText("");
}

void j1Console::AddConsoleText(char * new_text)
{
	UI_String* label = new UI_String({0,0,0,0},new_text);
	console_scroll->AddScrollItem(label);
}
