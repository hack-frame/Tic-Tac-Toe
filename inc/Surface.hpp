#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "header.hpp"

class Surface
{
public:
	Surface();
	~Surface();
	void	ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);
	SDL_Texture 	*Load_texture(std::string file, SDL_Renderer *renderer);
	SDL_Surface		*Load_surface(const char *path);
	bool			Writte_text(std::string text, int x, int y, int font_size, bool num, SDL_Renderer *ren);
	void			Fliping(int x, int y, SDL_Rect* clip, double angle,
					SDL_Point* center, SDL_RendererFlip flip, SDL_Texture *surf,
					SDL_Renderer	*gRenderer);
};

#endif