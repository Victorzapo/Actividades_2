#pragma once



struct Button {

	SDL_Rect ButtRect;

	SDL_Texture *OutClick;
	SDL_Texture *OnClick;

	bool isCollaiding;

};

Button createButton(Button butt,SDL_Renderer *m_renderer, int x, int y, const char *text, SDL_Color OnClick, SDL_Color OutClick, TTF_Font *font) {

	
	SDL_Surface *tmpSurf = (TTF_RenderText_Blended(font, text , OutClick));
	butt.ButtRect = { x, y ,tmpSurf->w,  tmpSurf->h };
	butt.OutClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	tmpSurf = (TTF_RenderText_Blended(font, text , OnClick));
	butt.OnClick = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

	return butt;
};