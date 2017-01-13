#include "j1Console.h"

#include "p2Log.h"

#include "j1App.h"
#include "j1Input.h"
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
	LOG("Console Awake");
	App->gui->SetDefaultInputTarget(this);

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
	
	LOG("Console Config data Loaded");
	
	
	//Build Console Text
	UI_String* console_text = new UI_String({ 0,0,0,0 }, "", { font_color.r,font_color.g,font_color.b,font_color.a }, font);
	console_input_box = new UI_Text_Box(input_box, console_text, cursor_w, cursor_h);
	
	//Build Console Labels Scroll
	UI_Image scroll_item({ console_area.w - 28,20 }, { 1000,880,19,20 });
	scroll_item.AdjustBox();
	UI_Image scroll_back({ console_area.w - 25,20 }, { 985,874,13,149 });
	scroll_back.AdjustBox();
	SDL_Rect scroll_area = { console_area.x,console_area.y,console_area.w,console_area.y - (console_area.y - input_box.y) };
	SDL_Rect viewport_area = { scroll_area.x,scroll_area.y,scroll_item.GetBox()->x,input_box.y };
	console_labels_scroll = new UI_Scroll(scroll_area, viewport_area, scroll_item, scroll_back);

	LOG("Console UI Build");

	return true;
}

bool j1Console::Start()
{
	//Now is able to generate texture for console scrolllabels
	can_texturize_strings = true;
	UpdateConsoleLabels();

	//Add Console Commands
	AddCommand("get", this);
	AddCommand("set", this);

	LOG("Console Labels Generated");
	return true;
}

bool j1Console::PostUpdate()
{
	//Update Console Input Box
	console_input_box->HandleInput();
	console_labels_scroll->HandleInput();
	
	UpdateConsoleLabels();

	//Draw Console Area
	App->render->DrawQuad(console_area, console_color.r, console_color.g, console_color.b, console_color.a);

	//Draw console labels
	if(console_labels_scroll->GetActiveState())console_labels_scroll->Draw(false);

	//Draw Console Input Box
	if(console_input_box->GetActiveState())console_input_box->Draw(true);
	
	return true;
}

bool j1Console::CleanUp()
{
	can_texturize_strings = false;

	uint var_count = console_variables.Count();
	for (uint k = 0; k < var_count; k++)
	{
		delete console_variables[k];
	}
	uint labels_count = console_labels.Count();
	for (uint k = 0; k < labels_count; k++)
	{
		delete console_labels[k];
	}
	delete console_input_box;
	delete console_labels_scroll;

	return true;
}

//Functionality ===========================================
void j1Console::GUI_Input(UI_Element * target, GUI_INPUT input)
{
	int x, y;
	App->input->GetMouseMotion(x, y);
	switch (input)
	{
	case UP_ARROW:
		break;
	case DOWN_ARROW:
		break;
	case LEFT_ARROW:
		break;
	case RIGHT_ARROW:
		break;
	case MOUSE_LEFT_BUTTON_DOWN:
		break;
	case MOUSE_LEFT_BUTTON_REPEAT:
		if (target == console_labels_scroll)
		{
			console_labels_scroll->MoveScroll(x, y);
		}
		break;
	case MOUSE_LEFT_BUTTON_UP:
		if (target == console_labels_scroll)
		{
			console_labels_scroll->UnselectScroll();
		}
		break;
	case MOUSE_RIGHT_BUTTON:
		break;
	case BACKSPACE:
		break;
	case SUPR:
		break;
	case MOUSE_IN:
		break;
	case MOUSE_OUT:
		break;
	case ENTER:
		if (target == console_input_box)
		{
			//Get data from input
			Cvar* target_cvar = GetCvarfromInput(console_input_box->GetText());
			p2SString input = GetValuefromInput(console_input_box->GetText());
			Command* command = GetCommandfromInput(console_input_box->GetText());

			//Send command to each module or print error str
			if (command == nullptr)
			{
				App->console->GenerateConsoleLabel("Error Command Input: %s", console_input_box->GetText());
			}
			else
			{
				if (command->GetModuleTarget() != nullptr)
				{
					command->GetModuleTarget()->Console_Command_Input(command, target_cvar, &input);
				}
				else
				{
					App->Console_Command_Input(command, target_cvar, &input);
				}
			}
			
			//Clean console box
			console_input_box->SetText(nullptr);
			//Go at bottom of scroll
			console_labels_scroll->GoBottom();
		}
		break;
	case TAB:
		if (target == console_input_box)
		{
			AutoCompleteInputBox(console_input_box->GetText());
		}
		break;
	}
}

// Functionality =========================================
void j1Console::ChangeConsoleState()
{
	active = !active;
	if (active)
	{
		App->gui->ItemSelected = console_input_box;
		console_input_box->Activate();
		console_labels_scroll->Activate();
	}
	else
	{
		console_input_box->SetText(nullptr);
		console_input_box->Desactivate();
		console_labels_scroll->Desactivate();
	}
}

//Console UI interaction --------------------
void j1Console::GoScrollBottom()
{
	console_labels_scroll->GoBottom();
}

bool j1Console::AutoCompleteInputBox(char* input)
{
	//Get imput str len
	uint char_num = strlen(input);
	uint input_step = 0;

	//Get input current step
	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '/')
		{
			if (input_step < 1)input_step = 1;
			else return false;
		}
		else if (input[k] == '.')
		{
			if (input_step < 1)input_step = 2;
			else return false;
		}
		else if (input[k] == '=')
		{
			if (input_step < 1)input_step = 3;
			else return false;
		}
	}

	//Try to autocomplete the step
	switch (input_step)
	{
	case 1:
		//Check command autocomplete
		break;
	case 2:
		//Check module autocomplete
		break;
	case 3:
		//Check cvar autocomplete
		break;
	}

	return true;
}

//Console Output ----------------------------
void j1Console::AddConsoleText(char* new_text)
{
	UI_String* label = new UI_String({ 0,0,0,0 }, new_text, font_color, font);
	if (!can_texturize_strings)
	{
		console_labels.PushBack(label);
	}
	else
	{
		console_labels.PushBack(label);
		UpdateConsoleLabels();
		console_labels_scroll->GoBottom();
	}
}

char * j1Console::GenerateConsoleLabel(char * new_text,...)
{
	static char tmp_string[1000];
	static va_list ap;

	va_start(ap,new_text);
	vsprintf_s(tmp_string, 1000, new_text, ap);
	va_end(ap);

	UI_String* label = new UI_String({ 0,0,0,0 }, tmp_string, font_color, font);
	console_labels.PushBack(label);
	UpdateConsoleLabels();

	return tmp_string;
}

void j1Console::UpdateConsoleLabels()
{
	uint labels_num = console_labels.Count();
	uint scroll_labels_num = console_labels_scroll->GetScrollItemsNum();

	if (scroll_labels_num == labels_num)return;
	
	for (uint k = scroll_labels_num; k < labels_num; k++)
	{
		console_labels_scroll->AddScrollItemAtBottom(((UI_String*)*console_labels.At(k)));
		console_labels[k]->SetFont(font);
		console_labels[k]->SetColor(font_color);
		console_labels[k]->GenerateTexture();
		console_labels[k]->AdjustBox();
	}
}

//Console Input -----------------------------
Cvar * j1Console::GetCvarfromInput(char * input) const
{

	//String position of input elements
	uint name_init = 0;
	uint name_end = 0;
	uint module_init = 0;

	//Get the var name start and end position
	uint char_num = strlen(input) + 1;
	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '/' && module_init == 0)module_init = k + 1;
		else if (input[k] == '.' && name_init == 0)name_init = k + 1;
		else if ((input[k] == '\0' || input[k] == '=') && name_end == 0)name_end = k;
	}

	if (module_init == 0 || name_init == 0)return nullptr;

	//Build the module & cvar name
	char* cvar_name = new char[10];
	char* module_name = new char[10];
	
	//Copy the cvar name in a new string
	uint j = 0;
	for (uint pos = name_init; pos < name_end; pos++)
	{
		cvar_name[j] = input[pos];
		j++;
	}
	cvar_name[j] = '\0';

	//Copy the cvar module name in a new string
	j = 0;
	for (uint k = module_init; k < name_init - 1; k++)
	{
		module_name[j] = input[k];
		j++;
	}
	module_name[j] = '\0';

	//Search the Cvar with the name build
	uint cvar_num = console_variables.Count();
	for (uint k = 0; k < cvar_num; k++)
	{
		if (*console_variables[k]->GetCvarName() == cvar_name)return console_variables[k];
	}
	return nullptr;
}

char* j1Console::GetValuefromInput(char * input) const
{
	uint char_num = strlen(input);
	char* value = new char[char_num];
	uint init = 0;
	uint val_pos = 0;
	
	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '=')init = k;
		if (k > init && init != 0)
		{
			value[val_pos] = input[k];
			val_pos++;
		}
	}
	char* temp = value;
	delete value;
	return temp;
}

Command* j1Console::GetCommandfromInput(char* input)const
{
	//Build the command string
	const uint char_num = strlen(input);
	char* command_type = new char[char_num];

	for (uint k = 0; k < char_num; k++)
	{
		if (input[k] == '/')
		{
			command_type[k] = '\0';
			break;
		}
		command_type[k] = input[k];

	}
	
	//Search the commands in the array
	uint command_num = commands.Count();
	for (uint k = 0; k < command_num; k++)
	{
		if (*commands[k]->GetCommandStr() == command_type)
		{
			delete command_type;
			return commands[k];
			
		}
	}

	delete command_type;
	return nullptr;
}

//Transformations ---------------------------
char * j1Console::CvarTypetoString(C_VAR_TYPE cvar_type) const
{
	switch (cvar_type)
	{
	case INT_VAR:		return "integrer";	break;
	case FLOAT_VAR:		return "float";		break;
	case CHAR_VAR:		return "character";	break;
	case BOOLEAN_VAR:	return "boolean";	break;
	case UNDEF:			return "undefined";	break;
	}
}

C_VAR_TYPE j1Console::StringtoCvarType(const p2SString* string) const
{
	if			(*string == "integrer")			return INT_VAR;
	else if		(*string == "float")			return FLOAT_VAR;
	else if		(*string == "character")		return CHAR_VAR;
	else if		(*string == "boolean")			return BOOLEAN_VAR;
	else return UNDEF;
}

//Console Variables Creation ----------------
Cvar* j1Console::AddCvar(const char* name, const char* description,const char* value, C_VAR_TYPE cvar_type, j1Module* module_target, bool only_read)
{
	//Check if the cvar already exist
	uint num = console_variables.Count();
	for (uint k = 0; k < num; k++)
	{
		if (*console_variables[k]->GetCvarName() == name)return nullptr;
	}

	//Create the new cvar
	Cvar* new_cvar = new Cvar(name, description, (char*)value, cvar_type, module_target, only_read);

	//Add it to the cvars array
	console_variables.PushBack(new_cvar);

	return new_cvar;
}

Cvar* j1Console::LoadCvar(const char* name, const char* description,const char* value, C_VAR_TYPE cvar_type, j1Module* module_target, bool only_read)
{
	//Create the new cvar
	uint cvars_num = console_variables.Count();
	for (uint k = 0; k < cvars_num; k++)
	{
		if (console_variables[k]->GetCvarName()->GetString() == name)return nullptr;
	}

	//Create the new Cvar
	Cvar* new_cvar = new Cvar(name, description, (char*)value, cvar_type, module_target, only_read);
	console_variables.PushBack(new_cvar);

	return new_cvar;
}

//Console Commands Creation -----------------
Command * j1Console::AddCommand(const char * command_str, j1Module * module_target)
{
	//Check if the command already exist
	uint commands_num = commands.Count();
	for (uint k = 0; k < commands_num; k++)
	{
		if (commands[k]->GetCommandStr()->GetString() == command_str)
		{
			return nullptr;
		}
	}

	//Create the new command
	Command* new_command = new Command(command_str, module_target);
	commands.PushBack(new_command);
	
	LOG("- %s - command added", new_command->GetCommandStr()->GetString());

	return new_command;
}

//Handle Console Input ----------------------
void j1Console::Console_Command_Input(Command * command, Cvar * cvar, p2SString * input)
{
	//Get command
	if (*command->GetCommandStr() == "get")
	{
		//Check cvar
		if (cvar == nullptr)
		{
			App->console->GenerateConsoleLabel("Error set command Cvar is NULL");
			return;
		}
		//Show cvar value
		GenerateConsoleLabel("%s: %s", cvar->GetCvarName()->GetString(), cvar->GetValueString()->GetString());
	}

	//Set command
	else if (*command->GetCommandStr() == "set")
	{
		//Check cvar
		if (cvar == nullptr)
		{
			App->console->GenerateConsoleLabel("Error set command Cvar is NULL");
			return;
		}

		//Set cvar value
		cvar->SetValue(input->GetString());
		
		//Update cvar state
		if (cvar->GetCvarModule() != nullptr)
		{
			cvar->GetCvarModule()->Console_Cvar_Input(cvar, command, input);
		}
		else
		{
			App->Console_Cvar_Input(cvar, command, input);
		}

		//Show cvar value
		GenerateConsoleLabel("-- %s = %s", cvar->GetCvarName()->GetString(),cvar->GetValueString()->GetString());
	}

	//Help command
}
