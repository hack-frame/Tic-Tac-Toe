#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "header.hpp"

struct	data_player
{
	int pos_x;
	int pos_y;
	int	index_x;
	int index_y;
};

class Player
{
private:
	bool					Check_index(int ind_x, int ind_y);
	
	std::vector<data_player> _data_player;
	Surface					_apply;
	char					_symbol;
	//SDL_Texture		*_icon;
public:
	Player();
	~Player();
	bool	Set_value(int x, int y, char (&buf)[8][8], char c);
	void	Draw_player(SDL_Renderer *renderer, SDL_Texture	*icon);
	char	Get_symbol();
};

#endif