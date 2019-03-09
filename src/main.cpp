#include "Renderer.hpp"
#include "ConsoleGame.hpp"

int	main(int argc, char *argv[])
{
	if (argc > 2){
		std::cout << "Enter 1/2 (Game mod : Window / Console)(Read more in README)\n";
		return 0;
	}
	srand(time(NULL));
	if (argc == 1){
		Renderer *render = new Renderer(1000, 700);	
		render->Game();
	}
	else if (argc > 1){
		ConsoleGame *console = new ConsoleGame();
		console->Game();
	}
	system("leaks -q tic_tac");
	return 0;
}
