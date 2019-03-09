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
	SDL_Texture		*_image[5];
	Surface			_apply;
	Player			_player_1;
	Player			_player_2;
	Algorithm		_algorithm;
	Menu			_menu;
	
	bool			_move;
	char			_map[8][8];
	bool			_side;

	void			Load_textures();
	void			Mouse_event();
	bool			Key_event();
	void			Init_lib(int x, int y);
	bool			Message_event();
	void			Draw_delay(int x);
	Renderer();

public:
	Renderer(int x, int y);
	~Renderer();
	void			Game();
};

#endif
