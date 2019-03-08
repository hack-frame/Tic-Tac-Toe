#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "header.hpp"
#include "Player.hpp"

class Algorithm
{
private:
	int 		_mass_map[8][8];
	char		_symbol;

	void	Free_mass_map();
	bool	Is_in_zone(int x);
	void	Made_mass_map(char map[8][8], char c, int pos_x, int pos_y);
	void	Made_mass_position(char map[8][8], char c, int pos_x, int pos_y, int pl_x, int pl_y);
	void	Find_best_place(char (&map)[8][8], Player  &player);
	void	Busy_place(char (&map)[8][8]);
	int		Length_max_attack(char map[8][8], char c, int pos_x, int pos_y, int pl_x, int pl_y, bool flag);

public:
	Algorithm();
	~Algorithm();
	bool		Start_algorithm(char (&map)[8][8], Player &player);
	char		Find_winner(char map[8][8]);
	std::string	Who_winner(char map[8][8]);
	int			Name_winner();
	void		Reset_winner();
};

#endif