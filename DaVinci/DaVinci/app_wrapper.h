#pragma once

#define  APP_IMPLEMENTATION
#define  APP_WINDOWS

extern "C" {
#include "app.h"
}

#include <cstdlib> // for rand and __argc/__argv

// pass-through so the program will build with either /SUBSYSTEM:WINDOWS or /SUBSYSTEN:CONSOLE
extern "C" int __stdcall WinMain(struct HINSTANCE__*, struct HINSTANCE__*, char*, int) { return main(__argc, __argv); }

namespace davinci{

	int register_process(int (*func) (app_t*, void*))
	{
		return app_run(func, NULL, NULL, NULL, NULL);
	}

}