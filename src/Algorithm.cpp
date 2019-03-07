#include "Algorithm.hpp"

Algorithm::Algorithm(){}
Algorithm::~Algorithm(){}

int		Algorithm::Length_max_attack(char map[8][8], char c, int pos_x, int pos_y, int pl_x, int pl_y, bool flag)
{
	int count = -1;
	while (++count < 6 && Is_in_zone(pos_x) && Is_in_zone(pos_y))
	{
		if (!flag && map[pos_y][pos_x] != c && map[pos_y][pos_x] != '-')
			break;
		else if (flag && map[pos_y][pos_x] != c)
			break;
		pos_x += pl_x;
		pos_y += pl_y;
	}
	return count;
}

char		Algorithm::Find_winner(char map[8][8])
{
	int count = 0;
	int dash = 0;
	int y = -1;
	while (++y < 8)
	{
		int x = -1;
		while (++x < 8)
		{
			if (map[y][x] != '-')
			{
				if ((Length_max_attack(map, map[y][x], x, y + 1, 0, 1, true)) >= 4
					|| (Length_max_attack(map, map[y][x], x + 1, y, 1, 0, true)) >= 4
					|| (Length_max_attack(map, map[y][x], x + 1, y + 1, 1, 1, true)) >= 4
					|| (Length_max_attack(map, map[y][x], x + 1, y - 1, 1, -1, true)) >= 4)
					return (map[y][x]);
			}
			else if (map[y][x] == '-')
				dash++;
		}
	}
	if (dash == 0)
		return '=';
	return ('-');
}

bool 	Algorithm::Who_winner(char map[8][8])
{
	char result = Find_winner(map);
	if (result != '-')
	{
		if (result == '=') _winner = "DRAW";
		else if (result == 'x') _winner = "PLAYER 1";
		else if (result == 'o') _winner = "PLAYER 2";
		return true;
	}
	else return false;
}

void	Algorithm::Reset_winner()
{
	_winner = "";
}

int		Algorithm::Name_winner()
{
	if (_winner == "PLAYER 1") return 1;
	else if (_winner == "PLAYER 2") return 2; 
	else if (_winner == "DRAW") return 0;
	else return -1;
}

bool	Algorithm::Is_in_zone(int x)
{
	if (x >= 0 && x <= 7)
		return true;
	return false;
}

void	Algorithm::Free_mass_map()
{
	int x = -1;
	while (++x < 8)
	{
		int y = -1;
		while (++y < 8)
			_mass_map[x][y] = 0.0;
	}
}

void	Algorithm::Made_mass_position(char map[8][8], char c, int pos_x, int pos_y, int pl_x, int pl_y)
{
	int count = -1;
	float koef = (_symbol == c ? 1.1 : 1.5);
	while (++count < 6 && Is_in_zone(pos_x) && Is_in_zone(pos_y))
	{
		if (map[pos_y][pos_x] != c && map[pos_y][pos_x] != '-')
			break;
		if (map[pos_y][pos_x] == c) koef *= 2.0;
		_mass_map[pos_y][pos_x] += (6 - count) *koef;
		pos_x += pl_x;
		pos_y += pl_y;
		if (map[pos_y - pl_y][pos_x - pl_x] != c)
			koef =(_symbol == c ? 1.1 : 1.5);
	}
}

void	Algorithm::Made_mass_map(char map[8][8], char c, int pos_x, int pos_y)
{
	if ((Length_max_attack(map, c, pos_x, pos_y + 1, 0, 1, false) +
		Length_max_attack(map, c, pos_x, pos_y - 1, 0, -1, false)) >= 4)
	{
		Made_mass_position(map, c, pos_x, pos_y + 1, 0, 1);
		Made_mass_position(map, c, pos_x, pos_y - 1 , 0, -1);
	}
	if ((Length_max_attack(map, c, pos_x + 1, pos_y, 1, 0, false) +
		Length_max_attack(map, c, pos_x - 1, pos_y , -1, 0, false)) >= 4)
	{
		Made_mass_position(map, c, pos_x + 1, pos_y, 1, 0);
		Made_mass_position(map, c, pos_x - 1, pos_y , -1, 0);
	}
	if ((Length_max_attack(map, c, pos_x + 1, pos_y + 1, 1, 1, false) +
		Length_max_attack(map, c, pos_x - 1, pos_y - 1, -1, -1, false)) >= 4)
	{
		Made_mass_position(map, c, pos_x + 1, pos_y + 1, 1, 1);
		Made_mass_position(map, c, pos_x - 1, pos_y - 1, -1, -1);
	}
	if (Length_max_attack(map, c, pos_x + 1, pos_y - 1, 1, -1, false) +
		Length_max_attack(map, c, pos_x - 1, pos_y + 1, -1, 1, false) >= 4)
	{
		Made_mass_position(map, c, pos_x + 1, pos_y - 1, 1, -1);
		Made_mass_position(map, c, pos_x - 1, pos_y + 1, -1, 1);
	}
}

void	Algorithm::Find_best_place(char (&map)[8][8], Player &player)
{
	int max = 0;
	int x = -1;
	int pos_x;
	int pos_y;
	while (++x < 8)
	{
		int y = -1;
		while (++y < 8)
			if (_mass_map[y][x] >= max && map[y][x] == '-')
			{
				max = _mass_map[y][x];
				pos_x = x;
				pos_y = y;
			}
	}
	player.Set_value(pos_x * 57, pos_y * 56, map, player.Get_symbol());
}

void	Algorithm::Busy_place(char (&map)[8][8])
{
	int x = -1;
	while (++x < 8)
	{
		int y = -1;
		while (++y < 8)
		{
			if (map[y][x] != '-')
				_mass_map[y][x] = 0;
		}
	}
}

bool	Algorithm::Start_algorithm(char (&map)[8][8],Player &player)
{
	_symbol = player.Get_symbol();
	Free_mass_map();
	int x = - 1;
	while (++x < 8)
	{
		int y = -1;
		while (++y < 8)
			if (map[y][x] != '-')
				Made_mass_map(map, map[y][x], x, y);
	}
	Busy_place(map);
	Find_best_place(map, player);
	// int q = -1;
	// while (++q < 8)
	// {
	// 	int j = -1;
	// 	while (++j < 8)
	// 	{
	// 		printf("%d   ", _mass_map[q][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n\n\n");
	if (Who_winner(map))
	{
		printf("true\n");
		return true;
	}
	return false;
}













