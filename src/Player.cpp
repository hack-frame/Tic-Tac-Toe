#include "Player.hpp"

Player::Player(){}
Player::~Player(){}

void	Player::Set_wins(){
	_wins +=1;
}

void	Player::Set_wins(int x){
	_wins = x;
}

char	Player::Get_symbol(){
	return (this->_symbol);
}

bool	Player::Check_index(int ind_x, int ind_y){
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

bool	Player::Set_value(int x, int y, char (&buf)[NET][NET], char c){
	if ((x >= 0 && x < 453) && (y >= 0 && y < 453))
	{
		_symbol = c;
		data_player data;
		data.index_x = x / STEP;
		data.index_y = y / STEP;
		if (!Check_index(data.index_x, data.index_y) || buf[data.index_y][data.index_x] != '-')
			return false;
		data.pos_x = 57 + (STEP * data.index_x);
		data.pos_y = 47 + (STEP * data.index_y);
		_data_player.push_back(data);
		buf[data.index_y][data.index_x] = c;
		return true;
	}
	else
		return false;
}

void	Player::Draw_player(SDL_Renderer *renderer, SDL_Texture	*icon){
	if (_data_player.size() > 0){
		std::vector<data_player>::iterator start = _data_player.begin();
		std::vector<data_player>::iterator end = _data_player.end();
		while (start < end){
			_apply.ApplySurface(start->pos_x, start->pos_y, icon, renderer);
			++start;
		}
	}
	if (_symbol == 'x' || _symbol == 'o'){
		std::string str;
		str.push_back(_symbol);
		str = str + " : wins " + std::to_string(_wins) + " times";
		int pos_y = (_symbol == 'x') ? 50 : 150;
		_apply.Writte_text(str, 530, pos_y, 35, true,renderer);
	}
}

void	Player::Free_data(){
	int size = _data_player.size();
	int iter = -1;
	while (++iter < size)
		_data_player.pop_back();
}














