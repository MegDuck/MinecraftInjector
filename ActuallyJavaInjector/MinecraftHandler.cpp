#include "MinecraftHandler.h"


MinecraftHandler::MinecraftHandler(HMODULE module) {
    this->module = module;

    this->CreateConsole();

    this->logger = Logger();
    logger.log("Initialized logger!");
    
    logger.log("Created console");

    this->hookJVM();
	
	this->mapping = Mapping();

    printf("I'm in\n");

    std::string MinecraftVersion = this->getVersion();
    printf(MinecraftVersion.c_str());

    logger.close();
    
}

void MinecraftHandler::hookJVM()
{
    jni_GetCreatedJavaVMs = (GetCreatedJavaVMs)GetProcAddress(GetModuleHandleA("jvm.dll"), "JNI_GetCreatedJavaVMs");

    jni_GetCreatedJavaVMs(&vm, 1, NULL);
    vm->AttachCurrentThread((void**)&env, NULL);

    logger.log("Hooked JVM!");
}

Logger& MinecraftHandler::getLogger()
{
	return this->logger;
}

Mapping& MinecraftHandler::getMapping()
{   
	return this->mapping;
}

JavaVM* MinecraftHandler::getVM()
{
	return this->vm;
}

JNIEnv* MinecraftHandler::getEnv()
{
	return env;
}

void MinecraftHandler::CreateConsole()
{
    AllocConsole();
    /*if (!) {
        logger.log("Not being able to allocate console");
        logger.close();
        return;
    }*/

    //logger.log("Allocated console");

    // std::cout, std::clog, std::cerr, std::cin

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    // std::wcout, std::wclog, std::wcerr, std::wcin
    HANDLE hConOut = CreateFile(TEXT("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hConIn = CreateFile(TEXT("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
    SetStdHandle(STD_ERROR_HANDLE, hConOut);
    SetStdHandle(STD_INPUT_HANDLE, hConIn);
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();

    SetConsoleCtrlHandler(NULL, true);
}

void MinecraftHandler::stop() {
    logger.close();
    FreeConsole();

    FreeLibraryAndExitThread(module, 0);
}

std::string MinecraftHandler::getVersion() {

    MappingClass MinecraftVersionClass = mapping.getClass("net/minecraft/MinecraftVersion");

    jfieldID minecraftVersion = MinecraftVersionClass.getField("name");

    jstring jname = static_cast<jstring>(env->GetObjectField(MinecraftVersionClass.getObject(), minecraftVersion));

    const char* rawString = env->GetStringUTFChars(jname, nullptr);

    std::string minecraftVersionString = std::string(rawString, env->GetStringLength(jname));

    std::cout << minecraftVersionString;

    env->ReleaseStringUTFChars(jname, rawString);

    return minecraftVersionString;
}