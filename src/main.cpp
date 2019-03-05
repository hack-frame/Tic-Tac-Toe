#include "Renderer.hpp"

int	main(int argc, char const *argv[])
{
	srand(time(NULL));
	Renderer *render = new Renderer(1000, 700, 800, 533);
	render->game();
	system("leaks -q tic_tac");
	return 0;
}