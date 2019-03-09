# include "Menu_action.hpp"

Menu::~Menu(){}

void	Menu::Choose_mod(int x, int y)
{
	if (y < 200) _game_mod = 2;
	else if (y > 350) _game_mod = 0;
	else if (x < WIDTH / 2) _game_mod = 1;
	else _game_mod = 3;
	_angle_left = Angle(x - (WIDTH / 2 - 15), y - HEIGHT / 2, (WIDTH / 2 - 15) / 2, 0);
	_angle_right = Angle(x -  (WIDTH / 2 + 50), y - HEIGHT / 2, (WIDTH / 2 + 50)/ 2, 0);
}

bool	Menu::Key_event(){
	
	SDL_Event	event;
	int x, y;
	if (MOUSE_PRESS) return (true);
	Choose_mod(x, y);
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			_game_mod = 0;
			return (true);
		}
		if (PRESS == SDLK_ESCAPE){
			_game_mod = 0;
			return (true);
		}
		if (PRESS == SDLK_RETURN) return (true);
	}
	return (false);
}

int		Menu::Get_game_mod(){
	return (this->_game_mod);
}

double		Menu::Angle( int x1, int y1, int x2, int y2)
{
	double angle = (x1*x2+y1*y2)/(sqrt((double)x1*x1+y1*y1)*sqrt((double)x2*x2+y2*y2));

	if (y1 >= 0) return (acos(angle) * (180.0 / M_PI) - 90.0);
	else return (270.0 - acos(angle) * (180.0 / M_PI));
}

void	Menu::Init_action(SDL_Renderer *renderer){

	_background = _apply.Load_texture("./MediaFiles/menu.png", renderer);
	_human = _apply.Load_texture("./MediaFiles/human.png", renderer);
	_eye = _apply.Load_texture("./MediaFiles/eye.png", renderer);
	_symbol = 1;
	_str.push_back("Exit");
	_str.push_back("Player x Player");
	_str.push_back("Player x Bot");
	_str.push_back("Bot x Bot");
}
/*
void	Menu::Choose_symbol(SDL_Renderer *renderer){
	static int i;
	while (1)
	{
		printf("%d\n", _game_mod);
		int x, y;
		if (MOUSE_PRESS && x > > 40) break;
		if (x < WIDTH / 2) _symbol = 1;
		else _symbol = 2;
		_apply.ApplySurface(0,0,_background,renderer);
		_apply.writte_text("X", 100, 100, 80, _symbol-1, renderer);
		SDL_RenderPresent(renderer);
		i++;	
	}
}
*/
void	Menu::Action(SDL_Renderer *renderer){
	Init_action(renderer);
	SDL_RendererFlip flipType = SDL_FLIP_VERTICAL;
	while (1){
		if (Key_event()) break;
		_apply.ApplySurface(0,0,_background,renderer);
		_apply.ApplySurface(280,130,_human,renderer);
		for (int i = 0; i < 4; i++)
		{
			int pos_x = (i == 0) ? 370 : -120;
			int pos_y = (i == 3) ? 700 : 400;
			(i == _game_mod) ?
			_apply.Writte_text(_str.at(i), pos_x + (i * 220), pos_y - (i * 150), 30, true, renderer) :
			_apply.Writte_text(_str.at(i), pos_x + (i * 220), pos_y - (i * 150), 30, false, renderer);
		}
		_apply.Fliping(366, 248, NULL, _angle_left + 45, NULL, flipType, _eye, renderer);
		_apply.Fliping(429, 248, NULL, _angle_right + 45, NULL, flipType, _eye, renderer);
		SDL_RenderPresent(renderer);
	}
	// if (_game_mod == 2) Choose_symbol(renderer);
}

Menu::Menu(){}
