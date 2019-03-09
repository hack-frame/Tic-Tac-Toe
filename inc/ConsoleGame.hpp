#ifndef CONSOLEGAME_HPP
#define CONSOLEGAME_HPP

#include "header.hpp"
#include "Player.hpp"
#include "Algorithm.hpp"
#include "Menu_action.hpp"

class ConsoleGame
{
private:

	Player			_player_1;
	Player			_player_2;
	Algorithm		_algorithm;
	
	int				_index;
	bool			_multiplayer;
	bool			_move;
	char			_map[8][8];
	
	bool			Key_event(std::string str);
	void			Draw_map();

public:
	ConsoleGame();
	~ConsoleGame();
	void			Game();
	void			Message_event();
};

#endif