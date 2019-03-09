#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL_net.h"
# include "Surface.hpp"
# include <vector>
# include <string>
# include <sstream>

# define NET 8
# define WIDTH 800
# define HEIGHT 533
# define RECT_X 54 //початок сітки на вікні
# define RECT_Y 42
# define STEP 57


# define PRESS event.type == SDL_KEYDOWN && event.key.keysym.sym
# define MOUSE_PRESS (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))

# define F_DIGITAL "fonts/auto_digital.ttf"
# define F_ARIAL 	"fonts/ARIAL.TTF"
# define F_MOR 	"fonts/MORPHEUS.TTF"
# define F_ICE  "fonts/LadyIceRevisited.ttf"
# define F_OPEN  "fonts/OpenSans-Semibold.ttf"

struct		font_data
{
	SDL_Surface		*font_surf;
	SDL_Texture		*font_textr;
	TTF_Font		*font_ttf;
	SDL_Rect		font_rect;
};

#endif