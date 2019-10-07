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

struct Button {

	SDL_Rect ButtRect;

	SDL_Texture *OutClick;
	SDL_Texture *OnClick;

	bool isCollaiding;



};


bool isCollaiding(SDL_Rect rectA, SDL_Rect mouse) {

	if (((mouse.x + mouse.w) > rectA.x && (rectA.x + rectA.w) > mouse.x) && ((mouse.y + mouse.h) > rectA.y &&  mouse.y < (rectA.y + rectA.h))) {
			return true;
	}
	else
		return false;
		

};


int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "Cant load SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "Cant load SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "Cant load SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() == -1)
		throw "Cant load SDL_TTF";
		
	//-->SDL_Mix
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		throw "Cant load mix system";

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//-->Animated Sprite ---



	// --- TEXT ---
	TTF_Font *font(TTF_OpenFont("../../res/ttf/saiyan.ttf",80));
	SDL_Surface *tmpSurf(TTF_RenderText_Blended(font, "My first SDL Game", SDL_Color{ 255,165,0, 0 }));
	SDL_Texture *text{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Rect textRect{ 100, 50 , tmpSurf->w, tmpSurf->h };

	// --- AUDIO ---
		Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load song";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	// --- MOUSE ---

	Vec2 mouseCords;
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "Cant load texture";
	SDL_Rect playerRect{ 0, 0, 87, 47 };
	SDL_Rect playerTarget{ 0, 0, 50, 50 }; // Support for center the mouse

	// ---BUTTONS---

	//Reload de font with changed size
	font = (TTF_OpenFont("../../res/ttf/saiyan.ttf", 60));
	if (playerTexture == nullptr) throw "Cant load Font";

		//PlayButton

	Button playButton;
	//Load out click color
	tmpSurf = (TTF_RenderText_Blended(font, "Play", SDL_Color{ 0, 0, 0, 0 })); 
	playButton.ButtRect = { 330, 200 ,tmpSurf->w,  tmpSurf->h};
	playButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//Load on click color
	tmpSurf = (TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,165,0, 0 }));
	playButton.OnClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };


		//SoundButton

	Button soundButton;
	tmpSurf = (TTF_RenderText_Blended(font, "Sound on off", SDL_Color{ 0, 0, 0, 0 }));
	soundButton.ButtRect = { 250, 350 ,tmpSurf->w,  tmpSurf->h };
	soundButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	tmpSurf = (TTF_RenderText_Blended(font, "Sound on off", SDL_Color{ 255,165,0, 0 }));
	soundButton.OnClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };


		//ExitButton

	Button ExitButton;
	tmpSurf = (TTF_RenderText_Blended(font, "Exit", SDL_Color{ 0, 0, 0, 0 }));
	ExitButton.ButtRect = { 330, 500 ,tmpSurf->w,  tmpSurf->h };
	ExitButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	tmpSurf = (TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255, 0, 0, 0 }));
	ExitButton.OnClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

		
	

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	bool playPressed = false;
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
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				//Mouse
				playerTarget.x = mouseCords.x - playerTarget.h / 2;
				playerTarget.y = mouseCords.y - playerTarget.w / 2;
				break;
			case  SDL_MOUSEBUTTONDOWN:
				//Exit Button
				if(ExitButton.isCollaiding)
					isRunning = false;
				//Sound Button
				else if (soundButton.isCollaiding) {
					if (Mix_PausedMusic())
						Mix_Resume;//Mix_PlayMusic(soundtrack, -1);
					else 
						Mix_PauseMusic();
				}
				//Play Button
				else if (playButton.isCollaiding) {
					if (playPressed)
						playPressed = false;
					else
						playPressed = true;
				}
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
		SDL_RenderCopy(m_renderer, text, nullptr, &textRect);
			//PlayButton
		playButton.isCollaiding = isCollaiding(playButton.ButtRect, playerRect);
		if(playButton.isCollaiding)
			SDL_RenderCopy(m_renderer, playButton.OnClick, nullptr, &playButton.ButtRect);
		else {
			//Changing color when clicking
			if (playPressed) {
				tmpSurf = (TTF_RenderText_Blended(font, "Play", SDL_Color{ 124,252, 0, 0 }));
				playButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			}
			else {
				tmpSurf = (TTF_RenderText_Blended(font, "Play", SDL_Color{ 255, 0, 0, 0 }));
				playButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			}
			SDL_RenderCopy(m_renderer, playButton.OutClick, nullptr, &playButton.ButtRect);
		}
			//ExitButton
		ExitButton.isCollaiding = isCollaiding(ExitButton.ButtRect, playerRect);
		if (ExitButton.isCollaiding)
			SDL_RenderCopy(m_renderer, ExitButton.OnClick, nullptr, &ExitButton.ButtRect);
		else
			SDL_RenderCopy(m_renderer, ExitButton.OutClick, nullptr, &ExitButton.ButtRect);
			//SoundButton
		soundButton.isCollaiding = isCollaiding(soundButton.ButtRect, playerRect);
		if (soundButton.isCollaiding)
			SDL_RenderCopy(m_renderer, soundButton.OnClick, nullptr, &soundButton.ButtRect);
		else
			SDL_RenderCopy(m_renderer, soundButton.OutClick, nullptr, &soundButton.ButtRect);
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