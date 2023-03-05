#include "MappingClass.h"


MappingClass::MappingClass(std::string mojmap, JNIEnv *env) {
	this->javaClass = env->FindClass(mojmap.c_str());
}

void MappingClass::addMethod(std::string mojmap, std::string signature, std::string yarnName, JNIEnv *env) {
	methods[yarnName] = env->GetMethodID(javaClass, mojmap.c_str(), signature.c_str());
}

void MappingClass::addField(std::string mojmap, std::string signature, std::string yarnName, JNIEnv *env) {
	fields[yarnName] = env->GetFieldID(javaClass, mojmap.c_str(), signature.c_str());
}

jmethodID MappingClass::getMethod(std::string name) {
	return methods[name];
}

jfieldID MappingClass::getField(std::string name) {
	return fields[name];
}

jclass MappingClass::getObject()
{
	return javaClass;
}
