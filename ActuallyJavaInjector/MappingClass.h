#pragma once
#include <string>
#include <jni.h>
#include <map>

class MappingClass
{
public:
	MappingClass(std::string mojmap, JNIEnv* env);
	MappingClass() = default;
	void addMethod(std::string mojmap, std::string signature, std::string yarnName, JNIEnv *env);
	void addField(std::string mojmap, std::string signature, std::string yarnName, JNIEnv *env);
	jmethodID getMethod(std::string name);
	jfieldID getField(std::string name);
	jclass getObject();

private:
	std::map<std::string, jmethodID> methods;

	std::map<std::string, jfieldID> fields;

	jclass javaClass;
};

