#ifdef __ANDROID__

#include "SDLAndroidAPI.h"

#include <SDL_image.h>
#include <SDL_test_common.h>
#include "SDL_opengles2.h"

#include "InputHandler.h"
#include "EngineValues.h"
#include <string>

namespace sre
{

static SDLTest_CommonState* state;
static SDL_GLContext* context = NULL;

void SDLAndroidAPI::init()
{
	const int depth = 16;
	char** argv = new char* [1];
	argv[0] = new char[15]{ EngineValues::APPLICATION_NAME };

	/* Initialize test framework */
	state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);

	/* Set OpenGL parameters */
	state->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;
	state->gl_red_size = 5;
	state->gl_green_size = 5;
	state->gl_blue_size = 5;
	state->gl_depth_size = depth;
	state->gl_major_version = 2;
	state->gl_minor_version = 0;
	state->gl_profile_mask = SDL_GL_CONTEXT_PROFILE_ES;

	SDLTest_CommonInit(state);

	context = (SDL_GLContext*)SDL_calloc(state->num_windows, sizeof(context));

	/* Create OpenGL ES contexts */
	context[0] = SDL_GL_CreateContext(state->windows[0]);

	if (state->render_flags & SDL_RENDERER_PRESENTVSYNC)
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);

	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	SDL_Log("Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
	SDL_Log("\n");
	SDL_Log("Vendor     : %s\n", glGetString(GL_VENDOR));
	SDL_Log("Renderer   : %s\n", glGetString(GL_RENDERER));
	SDL_Log("Version    : %s\n", glGetString(GL_VERSION));
	SDL_Log("Extensions : %s\n", glGetString(GL_EXTENSIONS));
	SDL_Log("\n");

	/* Set rendering settings for each context */
	SDL_GL_MakeCurrent(state->windows[0], context[0]);

	SDL_GL_GetDrawableSize(state->windows[0], &EngineValues::SCREEN_WIDTH, &EngineValues::SCREEN_HEIGHT);

	this->window = state->windows[0];
	this->imGuiAPI = UPTR<ImGuiAPI>{ new ImGuiAPI };

	delete[] argv[0];
	delete[] argv;
}

void SDLAndroidAPI::processInput(InputHandler* inputHandler)
{
	glm::vec2 position;

	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		switch (currentEvent.type)
		{
		case SDL_QUIT:		inputHandler->onQuit(); break;
		case SDL_KEYDOWN:	inputHandler->onKeyPressed(currentEvent.key.keysym.sym); break;
		case SDL_KEYUP:		inputHandler->onKeyReleased(currentEvent.key.keysym.sym); break;

		case SDL_MOUSEMOTION:
			position = glm::vec2{ currentEvent.motion.x, currentEvent.motion.y };
			inputHandler->onMouseMove(position);

			position = glm::vec2{ currentEvent.motion.xrel, currentEvent.motion.yrel };
			inputHandler->onMouseMoveRelative(position);
			break;

		case SDL_MOUSEBUTTONDOWN:
			position = glm::vec2{ currentEvent.button.x, currentEvent.button.y };
			inputHandler->onMouseButtonPressed(currentEvent.button.button, position);
			break;

		case SDL_MOUSEBUTTONUP:
			position = glm::vec2{ currentEvent.button.x, currentEvent.button.y };
			inputHandler->onMouseButtonReleased(currentEvent.button.button, position);
			break;

		case SDL_MOUSEWHEEL:
			inputHandler->onMouseWheel(currentEvent.wheel.y);
			break;
		}
	}
}

void* SDLAndroidAPI::loadTexture(const std::string& fileName, uint32_t* outWidth, uint32_t* outHeight, uint8_t* outBpp)
{
	void* result = nullptr;

	std::string resultFileName = ASSETS_FOLDER + fileName;
	SDL_RWops* file = SDL_RWFromFile(resultFileName.c_str(), "rb");
	SDL_Surface* surface = IMG_Load_RW(file, 1);

	if (surface == nullptr)
		throw "[SDLAPI] Can't load texture file: " + fileName;

	*outWidth = surface->w;
	*outHeight = surface->h;
	*outBpp = surface->format->BytesPerPixel;

	uint32_t size = surface->pitch * surface->h;
	result = malloc(sizeof(char) * size);
	memcpy(result, surface->pixels, size);

	SDL_FreeSurface(surface);

	return result;
}

void SDLAndroidAPI::release()
{
	int i;

	if (context != NULL) {
		for (i = 0; i < state->num_windows; i++) {
			if (context[i]) {
				SDL_GL_DeleteContext(context[i]);
			}
		}

		SDL_free(context);
	}

	IMG_Quit();
	SDLTest_CommonQuit(state);
}

} // namespace

#endif
