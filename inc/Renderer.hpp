#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "header.hpp"
#include "Player.hpp"
#include "Algorithm.hpp"
#include "Menu_action.hpp"

class Renderer
{
private:
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Texture		*_image[4];

	Surface			_apply;
	Player			_player_1;
	Player			_player_2;
	Algorithm		_algorithm;
	Menu			_menu;
	
	int				_width;
	int				_height;
	bool			_multiplayer;
	bool			_move;
	char			_map[8][8];
	
	void			load_textures();
	void			mouse_event();
	bool			key_event();
	void			init_lib(int x, int y);
	Renderer();
/*52 x 52*/
/*420 x 440*/
/*74 x 50*/
public:
	Renderer(int x, int y, int width, int height);
	~Renderer();
	void			Game();
	void			Message_event();
};

#endif