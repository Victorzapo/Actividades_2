#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


struct Vec2 {
	int x = 0;
	int y = 0;
};

int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() == -1)
		throw "No se puede inicializar SDL_TTF";
		
	//-->SDL_Mix

	

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//-->Animated Sprite ---

	// --- TEXT ---
	TTF_Font *font(TTF_OpenFont("../../res/ttf/saiyan.ttf",80));
	SDL_Surface *tmpSurf(TTF_RenderText_Blended(font, "My first SDL Game", SDL_Color{ 0, 0, 0, 0 }));
	SDL_Texture *textPlayNorm{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Rect textRect{ 100, 50 , tmpSurf->w, tmpSurf->h };
	// --- AUDIO ---
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		throw "No se pudo abrir los sistemas de MIX";
	
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load song";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);
	// --- CURSOR ---
	Vec2 mouseCords;
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "No se pudo crear las texturas";
	SDL_Rect playerRect{ 0, 0, 175, 94 };
	SDL_Rect playerTarget{ 0, 0, 100, 100 }; // Soporte para centrar el ratón


	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			//Mouse Update
			mouseCords.x = event.motion.x;
			mouseCords.y = event.motion.y;
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) Mix_PauseMusic();//isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				playerTarget.x = mouseCords.x - playerTarget.h / 2;
				playerTarget.y = mouseCords.y - playerTarget.w / 2;
				break;
			default:;
			}
		}

		// UPDATE
		SDL_RenderClear(m_renderer);
		playerRect.x += (playerTarget.x - playerRect.x) /10;
		playerRect.y += (playerTarget.y - playerRect.y) /10;

		
	
		// DRAW
			//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
			//Text
		SDL_RenderCopy(m_renderer, textPlayNorm, nullptr, &textRect);
			//Player
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderPresent(m_renderer);
		
		SDL_RenderClear(m_renderer);
	
		
	}

	// --- DESTROY ---
	Mix_CloseAudio();
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}