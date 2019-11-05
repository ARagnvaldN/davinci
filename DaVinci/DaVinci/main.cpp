#define  APP_IMPLEMENTATION
#define  APP_WINDOWS

extern "C" {
#include "app.h"
}

#include <cstdlib> // for rand and __argc/__argv

#include <array>

APP_U32 g_white = 0xffffff;
APP_U32 g_black = 0x000000;

int app_proc(app_t* app, void*)
{
	const size_t width = 320;
	const size_t height = 200;
	auto canvas = std::array<APP_U32, width * height>();			// Create a canvas
	std::fill(std::begin(canvas), std::end(canvas), g_white);  // clear to white
	
	app_screenmode(app, APP_SCREENMODE_WINDOW);  // As opposed to APP_SCREENMODE_FULLSCREEN

	// keep running until the user close the window
	while (app_yield(app) != APP_STATE_EXIT_REQUESTED)
	{
		// plot a random pixel on the canvas
		const auto x = rand() % width;
		const auto y = rand() % height;
		const auto color = rand() | (rand() << 16);
		canvas[x + y * width] = color;

		// display the canvas
		app_present(app, canvas.data(), width, height, g_white, g_black);
	}
	return 0;
}

int main(int argc, char** argv)
{
	(void)argc, argv;
	return app_run(app_proc, NULL, NULL, NULL, NULL);
}

// pass-through so the program will build with either /SUBSYSTEM:WINDOWS or /SUBSYSTEN:CONSOLE
extern "C" int __stdcall WinMain(struct HINSTANCE__*, struct HINSTANCE__*, char*, int) { return main(__argc, __argv); }