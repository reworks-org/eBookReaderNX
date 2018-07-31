///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

///
/// Entry point.
///
int main(int argc, char **argv)
{
	// Initialize SDL2.
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	// Main loop.
    while(appletMainLoop())
	{
		hidScanInput();
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS)
		{
			SDL_Quit();
			break;
		}
	}

	// Clean up SDL2.
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}