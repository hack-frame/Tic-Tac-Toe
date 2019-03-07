#include "Player.hpp"

Player::Player(){}
Player::~Player(){}

char	Player::Get_symbol()
{
	return (this->_symbol);
}

bool	Player::Check_index(int ind_x, int ind_y)
{
	std::vector<data_player>::iterator start = _data_player.begin();
	std::vector<data_player>::iterator end = _data_player.end();
	if (ind_x > 7 || ind_y > 7) return false;
	while (start < end)
	{
		if (start->index_x == ind_x && start->index_y == ind_y) return false;
		++start;
	}
	return true;
}

bool	Player::Set_value(int x, int y, char (&buf)[8][8], char c)
{
	if ((x >= 0 && x < 453) && (y >= 0 && y < 453))
	{
		_symbol = c;
		data_player data;
		data.index_x = x / 57;
		data.index_y = y / 55;
		printf("index x : %d\n", data.index_x);
		if (!Check_index(data.index_x, data.index_y) || buf[data.index_y][data.index_x] != '-')
			return false;
		data.pos_x = 57 + (57 * data.index_x);
		data.pos_y = 50 + (56 * data.index_y);
		_data_player.push_back(data);
		buf[data.index_y][data.index_x] = c;
		return true;
	}
	else
		return false;
}

void	Player::Draw_player(SDL_Renderer *renderer, SDL_Texture	*icon)
{
	if (_data_player.size() > 0)
	{
		std::vector<data_player>::iterator start = _data_player.begin();
		std::vector<data_player>::iterator end = _data_player.end();
		while (start < end)
		{
			_apply.ApplySurface(start->pos_x, start->pos_y, icon, renderer);
			++start;
		}
	}
}