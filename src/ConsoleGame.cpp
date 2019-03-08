#include "ConsoleGame.hpp"

ConsoleGame::~ConsoleGame(){}
ConsoleGame::ConsoleGame(){
	int tm_x = -1;
	while (++tm_x < 8)
	{
		int tm_y = -1;
		while (++tm_y < 8)
			_map[tm_x][tm_y] = '-';
	}
}


void			ConsoleGame::Draw_map(){
	int y  = -1;
	while (++y < 8)
	{
		int x = -1;
		while (++x < 8)
		{
			int ind = (y * 8) + x;
			if (_map[y][x] == '-' && ind <= 9) std::cout << " [ " << ind + 1 << "]";
			else  if (_map[y][x] == '-')std::cout << " [" <<ind + 1 << "]\033[0m";
			else  std::cout << " \033[1;31m[ " << (char)toupper(_map[y][x]) << "]\033[0m";
		//	else std::cout << " \033[1;31m[ " << _map[y][x] << "]\033[0m";
		}
		std::cout << std::endl;
	}
}

bool			ConsoleGame::Key_event(std::string str){
	_index = atoi(str.c_str());
	if (_index == 0 || _index > 64)
	{
		std::cout << "Bad index" << std::endl;
		return false;
	}
	static bool rand_1;
	if (_player_1.Set_value(((_index - 1) % 8) * 57, ((_index - 1) / 8) * 56, _map, 'x'))
	{
		rand_1 ? (_algorithm.Start_algorithm(_map, _player_2)) :
		_player_2.Set_value((rand() % 8 * 55),rand() % 8 * 55, _map, 'o');
		rand_1 = true;
		return true;
	}
	else
	{
		std::cout << "Choose other index" << std::endl;
		return false;
	}

}



void			ConsoleGame::Message_event()
{
/*	if (_algorithm.Name_winner() == 0) std::cout<< "\n\nIt's DRAW\n";
	if (_algorithm.Name_winner() == 1) std::cout<< "\n\nPlayer with symb. \' X \' WIN\n";
	if (_algorithm.Name_winner() == 2) std::cout<< "\n\nPlayer with symb. \' O \' WIN\n";*/
	std::cout << _algorithm.Who_winner(_map) <<std::endl;
}

void			ConsoleGame::Game(){

	std::string str;
	while (1)
	{
		std::cout << "Enter index :\n";
		if(!(std::getline(std::cin, str))) exit(0);
		if (str == ";;") break;
		if (_algorithm.Who_winner(_map) == "nul")
		{
			if (Key_event(str))
				Draw_map();
		}
		else{
			(Message_event());
			break;
		}
	}
}


















