#include "Mapping.h"


Mapping::Mapping(JNIEnv* env)
{
	this->env = env;
	std::string word;
	std::ifstream Mappings("C:\\logs\\resources\\mappings.tiny");
	
	/*
	* tiny	2		0	official	intermediary	named
	c	cca	net/minecraft/class_2573	net/minecraft/block/entity/BannerBlockEntity
	f	Z	g	field_11770	patternListTagRead
	f	Lnr;	a	field_11772	customName
	f	Lmj;	c	field_11773	patternListTag
	f	Lbkx;	b	field_11774	baseColor
	f	Ljava/util/List;	h	field_11769	patterns
	*/

	// Class -> desc: name, class, fields, methods;
	// fields -> field: name, jfieldID
	// methods -> method: name, jmethodID

	int count = 1;
	int parameter = NONE;


	std::string obfuscated = "";

	std::getline(Mappings, word);

	std::string currentClass = "";
	std::string intermediaryData[2];

	while (std::getline(Mappings, word, '\t')) {
		if (count == 1) {
			if (word == "m") {
				parameter = METHOD;
			}
			else if (word == "f") {
				parameter = FIELD;
			}
			else if (word == "c") {
				parameter = CLASS;
			}
		}
		if (parameter == NONE) {
			count += 1;
			continue;
		}

		if (parameter == METHOD) {
			// def	  sig	  mojmap   intmd		yarn mappings
			// m	(Lnr;)V		a	method_16842	setCustomName
			// https://en.cppreference.com/w/cpp/utility/pair
			if (count == 2) { // signature of method
				intermediaryData[0] = word;
			}
			else if (count == 3) { // obfuscated mappings
				intermediaryData[1] = word;
			}
			else if (count == 5) { // yarn mappings
				classes[currentClass].addMethod(intermediaryData[1], intermediaryData[0], word, env);
			}
		}
		else if (parameter == FIELD) {
			// def	  sig	  mojmap    intmd		yarn mappings
			// f	  Lgj;		a	 field_16410		  inventory
			// https://en.cppreference.com/w/cpp/utility/pair

			if (count == 2) { // signature of field
				intermediaryData[0] = word;
			}
			else if (count == 3) { // obfuscated mappings
				intermediaryData[1] = word;
			}
			else if (count == 5) { // yarn mappings
				classes[currentClass].addField(intermediaryData[1], intermediaryData[0], word, env);
			}
		}
		else if (parameter == CLASS) {
			if (count == 2) {
				intermediaryData[0] = word;
			}
			else if (count == 4) {
				currentClass = word;
				classes[word] = MappingClass(intermediaryData[0], env);
			}
		}
		count += 1;
	}

	Mappings.close();
}


MappingClass Mapping::getClass(std::string name) {
	return classes[name];
}