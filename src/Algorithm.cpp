#include "Algorithm.hpp"

Algorithm::Algorithm(){}
Algorithm::~Algorithm(){}

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
	while (++count < 6 && Is_in_zone(pos_x) && Is_in_zone(pos_y))
	{
		if (map[pos_y][pos_x] != c && map[pos_y][pos_x] != '-')
			break;
		_mass_map[pos_y][pos_x] += 6 - count;
		pos_x += pl_x;
		pos_y += pl_y;
	}
}

void	Algorithm::Made_mass_map(char map[8][8], char c, int pos_x, int pos_y)
{
	Made_mass_position(map, c, pos_x, pos_y + 1, 0, 1);
	Made_mass_position(map, c, pos_x + 1, pos_y , 1, 0);

	Made_mass_position(map, c, pos_x, pos_y - 1, 0, -1);
	Made_mass_position(map, c, pos_x - 1, pos_y , -1, 0);

	Made_mass_position(map, c, pos_x + 1, pos_y + 1, 1, 1);
	Made_mass_position(map, c, pos_x - 1, pos_y - 1, -1, -1);

	Made_mass_position(map, c, pos_x + 1, pos_y - 1, 1, -1);
	Made_mass_position(map, c, pos_x - 1, pos_y + 1, -1, 1);

}

void	Algorithm::Find_best_place(char (&map)[8][8], char c, Player &player)
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
	// printf("-------- pos_x : %d\n", pos_x);
	// printf("-------- pos_y : %d\n", pos_y);
	player.Set_value(pos_x * 52, pos_y * 55, map, 'o');
}

void	Algorithm::Buse_place(char (&map)[8][8])
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

void	Algorithm::Start_algorithm(char (&map)[8][8], char c, Player &player)
{
	Free_mass_map();
	int x = - 1;
	while (++x < 8)
	{
		int y = -1;
		while (++y < 8)
		{
			if (map[y][x] == c)
			{
				Made_mass_map(map, c, x, y);
			}
		}
	}
	Buse_place(map);
	Find_best_place(map, c, player);
	/*int q = -1;
	while (++q < 8)
	{
		int j = -1;
		while (++j < 8)
		{
			printf("%d ", _mass_map[q][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");*/
}













