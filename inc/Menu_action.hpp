#ifndef MENU_ACTION_HPP
#define MENU_ACTION_HPP

#include "header.hpp"

class Menu
{
private:
	SDL_Texture *_background;
	Surface 	_apply;
	SDL_Texture *_human;
	SDL_Texture *_eye;

	int			_symbol;
	int			_game_mod;
	double		_angle;
	double		_angle_right;
	double		_angle_left;
	std::vector<std::string> _str;
	
	bool		Key_event();
	void		Init_action(SDL_Renderer *renderer);
	double		Angle(int x1, int y1, int x2, int y2);
	void		Choose_mod(int x, int y);
	void		Choose_symbol(SDL_Renderer *renderer);
public:
	Menu();
	~Menu();
	void		Action(SDL_Renderer	*renderer);
	int			Get_game_mod();
};

#endif