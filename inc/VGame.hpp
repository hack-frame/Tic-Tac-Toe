#ifndef VGAME_HPP
#define VGAME_HPP

#include "header.hpp"
#include "Player.hpp"
#include "Algorithm.hpp"
#include "Menu_action.hpp"

class VGame
{
protected:
	Player			_player_1;
	Player			_player_2;
	Algorithm		_algorithm;
	
	bool			_multiplayer;
	bool			_move;
	char			_map[8][8];
	
	virtual bool			key_event();
public:
	//VGame(int x, int y, int width, int height);
	VGame(){};
	~VGame(){};
	//virtual void			Init_all();
	virtual void			game();
	virtual void			Message_event();
};

#endif