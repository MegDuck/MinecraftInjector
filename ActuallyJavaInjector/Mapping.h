#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "MappingClass.h"
	

class Mapping
{
public:
	Mapping(JNIEnv* env);
	Mapping() = default;

	MappingClass getClass(std::string name);

private:
	JNIEnv* env;
	std::map <std::string, MappingClass> classes;

	enum parameters {
		METHOD,
		FIELD,
		CLASS,
		PARAMETER,
		NONE
	};
};

