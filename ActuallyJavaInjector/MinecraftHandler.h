#pragma once
#include "Logger.h"
#include "Mapping.h"
#include <Windows.h>
#include <jni.h>

class MinecraftHandler
{
public:
	MinecraftHandler(HMODULE module);
	MinecraftHandler() = default;

	Logger& getLogger();
	Mapping& getMapping();
	JavaVM* getVM();
	JNIEnv* getEnv();

	void stop();

	std::string getVersion();


private:
	// prototype function 
	typedef jint(JNICALL* GetCreatedJavaVMs)(JavaVM**, jsize, jsize*);
	GetCreatedJavaVMs jni_GetCreatedJavaVMs;

	Logger logger;
	Mapping mapping;
	JavaVM* vm;
	JNIEnv* env;
	HMODULE module;

	void hookJVM();
	void CreateConsole();

};

