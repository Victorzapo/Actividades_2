#pragma once



struct Button {

	SDL_Rect ButtRect;

	SDL_Texture *OutClick;
	SDL_Texture *OnClick;

	SDL_Texture *ActualTexture;
	

	bool isCollaiding;
	
	Button(SDL_Renderer *m_renderer, int x, int y, const char *text, SDL_Color OnClickC, SDL_Color OutClickC, TTF_Font *font) {

		SDL_Surface *tmpSurf = (TTF_RenderText_Blended(font, text, OutClickC));
		ButtRect = { x, y ,tmpSurf->w,  tmpSurf->h };
		OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		tmpSurf = (TTF_RenderText_Blended(font, text, OnClickC));
		OnClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_FreeSurface;
	};


};