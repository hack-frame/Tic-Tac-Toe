#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "header.hpp"
#include "Player.hpp"

struct  Attack
{
	int length_attack;
	int potencial;
};

class Algorithm
{
private:
	int _mass_map[8][8];
//	std::vector<Attack> _attacks;
	void	Free_mass_map();
public:
	Algorithm();
	~Algorithm();
	void	Start_algorithm(char (&map)[8][8], char c, Player &player);
	bool	Is_in_zone(int x);
	void	Made_mass_map(char map[8][8], char c, int pos_x, int pos_y);
	void	Made_mass_position(char map[8][8], char c, int pos_x, int pos_y, int pl_x, int pl_y);
	void	Find_best_place(char (&map)[8][8], char c, Player  &player);
	void	Buse_place(char (&map)[8][8]);
};

#endif