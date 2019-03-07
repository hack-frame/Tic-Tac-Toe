#ifndef MENU_ACTION_HPP
#define MENU_ACTION_HPP

#include "header.hpp"

class Menu
{
private:
	SDL_Texture *_background;
	Surface 	_apply;
	SDL_Texture *_human;
	SDL_Texture *_eye_right;
	SDL_Texture *_eye_left;

	int			_game_mod;
	double		_angle;

	std::vector<std::string> _str;
	bool		key_event();

public:
	Menu();
	~Menu();
	void		Action(SDL_Renderer	*renderer);
	int			Get_game_mod();
	double		angle( int x1, int y1, int x2, int y2);
};

#endif