#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "header.hpp"

class Surface
{
public:
	Surface();
	~Surface();
	void	ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);
	SDL_Texture 	*load_texture(std::string file, SDL_Renderer *renderer);
	SDL_Surface		*load_surface(const char *path);
	bool			writte_text(std::string text, int x, int y, int font_size, bool num, SDL_Renderer *ren);
	void			fliping(int x, int y, SDL_Rect* clip, double angle,
					SDL_Point* center, SDL_RendererFlip flip, SDL_Texture *surf,
					SDL_Renderer	*gRenderer);
};

#endif