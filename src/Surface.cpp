#include "Surface.hpp"

Surface::Surface(){}
Surface::~Surface(){}

void			 Surface::ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
{
   SDL_Rect pos;
   pos.x = x;
   pos.y = y;
   SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
   SDL_RenderCopy(rend, tex, NULL, &pos);
}

SDL_Surface		*Surface::Load_surface(const char *path)
{
	SDL_Surface	*texture;

	texture = IMG_Load(path);
	if (texture == NULL)
	{
			std::cout << "bad load" << std::endl;
			exit(1);
	}
	return (texture);
}

SDL_Texture 	*Surface::Load_texture(std::string file, SDL_Renderer *renderer)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = Load_surface(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		std::cout << SDL_GetError() << std::endl;
	return texture;
}

bool			Surface::Writte_text(std::string text, int x, int y, int font_size, bool num, SDL_Renderer *ren)
{
	font_data _font_data;
	int tw;
	int th;

	if (text == "") return (0);
	if (font_size < 1 || font_size > 999) return (0);
	TTF_Init();
	_font_data.font_ttf = TTF_OpenFont(F_DIGITAL, font_size);
	if (!_font_data.font_ttf) return false;
	SDL_Color color;
	color.r = (num) ? 255: 144;
	color.g = (num) ? 255: 144;
	color.b = (num) ? 255: 144;
	_font_data.font_surf = TTF_RenderText_Solid(_font_data.font_ttf, text.c_str(), color);
	_font_data.font_textr = SDL_CreateTextureFromSurface(ren, _font_data.font_surf);
	SDL_QueryTexture(_font_data.font_textr, NULL, NULL, &tw, &th);
	_font_data.font_rect.x = x;
	_font_data.font_rect.y = y;
	_font_data.font_rect.w = tw;
	_font_data.font_rect.h = th;
	SDL_RenderCopy(ren, _font_data.font_textr, NULL, &_font_data.font_rect);
	SDL_DestroyTexture(_font_data.font_textr);
	SDL_FreeSurface(_font_data.font_surf);
	TTF_CloseFont(_font_data.font_ttf);
	return (1);
}

void			Surface::Fliping(int x, int y, SDL_Rect* clip, double angle,
				SDL_Point* center, SDL_RendererFlip flip, SDL_Texture *surf,
				SDL_Renderer	*gRenderer)
{
	SDL_Rect renderQuad = { x, y, 41, 41};

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx( gRenderer, surf, clip, &renderQuad, angle, center, flip );
}
