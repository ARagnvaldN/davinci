#include "app_wrapper.h"
#include <vector>

APP_U32 g_white = 0xffffff;
APP_U32 g_black = 0x000000;

int main_loop(app_t* app, void*)
{
	const size_t width = 640;
	const size_t height = 400;
	auto canvas = std::vector<APP_U32>(width * height, g_white);  // Create a canvas and make it white
	
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
	return davinci::register_process(main_loop);
}
