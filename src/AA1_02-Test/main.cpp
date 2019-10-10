#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>
#include "Buttons.h"
#include "Utils.h"

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60


int main(int, char*[])
{
	//  ---------------INIT SDL---------------
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "Cant load SDL subsystems";

	//  ---------------WINDOW ---------------
	SDL_Window *m_window{ SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "Cant load SDL_Window";

	//  ---------------RENDERER---------------
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
	//if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		//throw "Cant load mix system";

	//  ---------------SPRITES---------------
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	
	//-->Animated Sprite ---

	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/sp01.png") };
	SDL_Rect playerRect, playerPosition;
	int textW, textH, frameW, frameH;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textW, &textH);
	//Search the correct frame
	frameW = textW / 6; //6 colum 
	frameH = textH / 1; // 1 line
	//Position
	playerPosition.x = 120;
	playerPosition.y = 120;
	//Propotion
	playerRect.x = playerRect.y = 0; //Const Ratio

	playerPosition.h = playerRect.h = frameH;
	playerPosition.w = playerRect.w = frameW;
	int frameTime = 0;

	// ---------------TEXT---------------
	TTF_Font *font(TTF_OpenFont("../../res/ttf/saiyan.ttf",80));
	SDL_Surface *tmpSurf(TTF_RenderText_Blended(font, "My first SDL Game", SDL_Color{ 255,165,0, 0 }));
	SDL_Texture *text{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	SDL_Rect textRect{ 100, 50 , tmpSurf->w, tmpSurf->h };

	//  ---------------AUDIO---------------
		Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load song";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	//  ---------------MOUSE---------------

	Vec2 mouseCords;
	SDL_Texture *mouseTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (mouseTexture == nullptr) throw "Cant load texture";
	SDL_Rect mouseRect{ 0, 0, 87, 47 };
	SDL_Rect mouseTarget{ 0, 0, 50, 50 }; // Support to center the mouse

	//  ---------------BUTTONS---------------

	//Reload de font with changed size 
	font = (TTF_OpenFont("../../res/ttf/saiyan.ttf", 60)); 
	if (font == nullptr) throw "Cant load Font";

		//PlayButton

	Button playButton (m_renderer, 330, 200, "Play", SDL_Color{ 255,165,0, 0 }, SDL_Color{ 255, 0, 0, 0 }, font);

		//SoundButton

	Button soundButton (m_renderer, 250, 350, "Sound on of",  SDL_Color{ 255,165,0, 0 }, SDL_Color{ 0, 0, 0, 0 }, font);

		//ExitButton

	Button exitButton (m_renderer, 330, 500, "Exit", SDL_Color{ 255, 0, 0, 0 }, SDL_Color{ 0, 0, 0, 0 }, font);


	//  ---------------GAME LOOP---------------
	SDL_Event event;
		//Control Bool
	bool isRunning = true;
	bool playPressed = false;
	bool EscPressed = false;
	bool mouseMov = false;
	bool mouseClick = false;
	while (isRunning) {		
		//Bool Update
		EscPressed = false;
		mouseMov = false;
		mouseClick = false;
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				//if (event.key.keysym.sym == SDLK_ESCAPE) EscPressed = true;
				if (event.key.keysym.sym == SDLK_LCTRL) EscPressed = true;
				break;
			case SDL_MOUSEMOTION:
				mouseMov = true;
				break;
			case  SDL_MOUSEBUTTONDOWN:
				mouseClick = true;
				break;
			default:;
			}
		}

	//  ---------------UPDATE---------------
			//Player
		frameTime++;
		if (FPS / frameTime <= 9) {
			frameTime = 0;
			playerRect.x += frameW;
			if (playerRect.x >= textW)
				playerRect.x = 0;
		}


			//Quit
		//if (EscPressed)isRunning = false;
		if (EscPressed)
			playerPosition.x++;

			//Mouse
		
	
		if (mouseMov) {
			
			mouseCords.x = event.motion.x;
			mouseCords.y = event.motion.y;
			mouseTarget.x = mouseCords.x - mouseTarget.h / 2;
			mouseTarget.y = mouseCords.y - mouseTarget.w / 2;
		}
		
		mouseRect.x += (mouseTarget.x - mouseRect.x) / 10;
		mouseRect.y += (mouseTarget.y - mouseRect.y) / 10;
			//Play Button
		playButton.isCollaiding = isCollaiding(playButton.ButtRect, mouseRect);
				//Texture
		if (playButton.isCollaiding)
			playButton.ActualTexture = playButton.OnClick;
		else
			playButton.ActualTexture = playButton.OutClick;
				//Action
		if (playButton.isCollaiding && mouseClick) {
			if (playPressed)
				playPressed = false;
			else
				playPressed = true;
				//Changing color when clicking
			if (playPressed) {
				tmpSurf = (TTF_RenderText_Blended(font, "Play", SDL_Color{ 124,252, 0, 0 }));
				playButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
				playButton.ActualTexture = playButton.OutClick;
			}
			else {
				tmpSurf = (TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0, 0, 0 }));
				playButton.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
				playButton.ActualTexture = playButton.OutClick;
			}
		}

			//ExitButton
				//Texture
		exitButton.isCollaiding = isCollaiding(exitButton.ButtRect, mouseRect);
		if (exitButton.isCollaiding)
			exitButton.ActualTexture = exitButton.OnClick;
		else
			exitButton.ActualTexture = exitButton.OutClick;
				//Action
		if (exitButton.isCollaiding && mouseClick)
			isRunning = false;
		
			//Sound Button
				//Texture
		soundButton.isCollaiding = isCollaiding(soundButton.ButtRect, mouseRect);
		if (soundButton.isCollaiding)
			soundButton.ActualTexture = soundButton.OnClick;
		else
			soundButton.ActualTexture = soundButton.OutClick;
				//Action
		if (soundButton.isCollaiding && mouseClick) {
			if (Mix_PausedMusic())
				Mix_ResumeMusic();
			else
				Mix_PauseMusic();
		}

		
	// ---------------DRAW---------------
		SDL_RenderClear(m_renderer);
			//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
			//Text
		SDL_RenderCopy(m_renderer, text, nullptr, &textRect);
			//PlayButton
		SDL_RenderCopy(m_renderer, playButton.ActualTexture, nullptr, &playButton.ButtRect);   
			//ExitButton
		SDL_RenderCopy(m_renderer, exitButton.ActualTexture, nullptr, &exitButton.ButtRect);
			//SoundButton
		SDL_RenderCopy(m_renderer, soundButton.ActualTexture, nullptr, &soundButton.ButtRect);
			//Mouse
		SDL_RenderCopy(m_renderer, mouseTexture, nullptr, &mouseRect);
			//Player
		SDL_RenderCopy(m_renderer, playerTexture, &playerRect, &playerPosition);
		
	
		SDL_RenderPresent(m_renderer);
		SDL_RenderClear(m_renderer);
	
		
	}

	// --- DESTROY ---
	Mix_CloseAudio();
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(mouseTexture);
	SDL_DestroyTexture(playerTexture);
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}