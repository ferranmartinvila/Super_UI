#ifndef _C_VAR_
#define _C_VAR_

#include <stdlib.h>
#include "j1Module.h"

enum C_VAR_TYPE {

	UNDEF,
	INT_VAR,
	FLOAT_VAR,
	CHAR_VAR,
	BOOLEAN_VAR
};

class Cvar {
public:

	Cvar(const char* name, const char* description, char* value, C_VAR_TYPE var_type,j1Module* module_var) :name(name), description(description), value(value), var_type(var_type), module_var(module_var) {}
	Cvar() {};

private:

	const char*		name;
	const char*		description;
	char*		value;
	C_VAR_TYPE	var_type;
	j1Module*	module_var;

public:

	//Cvar general data functions -------------------------
	//Get cvar name
	const char*	GetCvarName()const
	{
		return name;
	}
	//Get cvar description
	const char* GetCvarDescription()const
	{
		return description;
	}
	//Get cvar type
	C_VAR_TYPE GetCvarType()const
	{
		return var_type;
	}
	//Get cvar module
	j1Module*	GetCvarModule()const
	{
		return module_var;
	}


	//Cvar value functions --------------------------------
	//Get cvar value with the cvar type
	template<class cvar_data>
	cvar_data&	GetValue()const
	{
		switch (var_type)
		{
		case INT:		return atoi(value);								break;
		case FLOAT:		return atof(value);								break;
		case CHAR:		return value;									break;
		case BOOL:		(value == "true") ? return true : return false;	break;
		}
	}
	//Get cvar value string
	char*	GetValueString()const
	{
		return value;
	}
	//Set cvar value
	void	SetValue(char* new_value)
	{
		value = new_value;
	}

};
#endif
