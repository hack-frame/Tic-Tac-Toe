#include "Menu_action.hpp"
#define PRESS event.type == SDL_KEYDOWN && event.key.keysym.sym
Menu::~Menu(){}

bool	Menu::key_event(){
	
	SDL_Event	event;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (true);
		if (PRESS == SDLK_ESCAPE)
			return (true);
		if (PRESS == SDLK_RETURN)
			return (true);
		if (PRESS == SDLK_LEFT)
			_game_mod = 1;
		if (PRESS == SDLK_RIGHT)
			_game_mod = 3;
		if (PRESS == SDLK_UP)
			_game_mod = 2;
		if (PRESS == SDLK_DOWN)
			_game_mod = 0;
	}
	return (false);
}

int		Menu::Get_game_mod(){
	return (this->_game_mod);
}

double		Menu::angle( int x1, int y1, int x2, int y2)
{
	double angle = (x1*x2+y1*y2)/(sqrt((double)x1*x1+y1*y1)*sqrt((double)x2*x2+y2*y2));
	
	if (y1 >= 0)
	{
		return (acos(angle) * (180.0 / M_PI) - 90.0);
	}
	else
		return (270.0 - acos(angle) * (180.0 / M_PI));
}

void	Menu::Action(SDL_Renderer	*renderer){
	_background = _apply.load_texture("./MediaFiles/menu.png", renderer);
	_human = _apply.load_texture("./MediaFiles/human.png", renderer);
	_eye_right = _apply.load_texture("./MediaFiles/eye.png", renderer);
	_eye_left = _apply.load_texture("./MediaFiles/eye.png", renderer);
	_game_mod = 2;
	_str.push_back("Exit");
	_str.push_back("Player x Player");
	_str.push_back("Player x Bot");
	_str.push_back("Bot x Bot");
	int x, y;
	SDL_RendererFlip flipType = SDL_FLIP_VERTICAL;
	while (1)
	{
		if (key_event()) break;
		SDL_GetMouseState(&x, &y);
		_apply.ApplySurface(0,0,_background,renderer);
		_apply.ApplySurface(280,130,_human,renderer);
		// _apply.ApplySurface(366,247,_eye_right,renderer);
		// _apply.ApplySurface(428,247,_eye_left,renderer);
		for (int i = 0; i < 4; i++)
		{
			int pos_x = (i == 0) ? 370 : -120;
			int pos_y = (i == 3) ? 550 : 350;
			(i == _game_mod) ? _apply.writte_text(_str.at(i), pos_x + (i * 220), pos_y - (i * 100), 30, true,renderer) :
			_apply.writte_text(_str.at(i), pos_x + (i * 220), pos_y - (i * 100), 30, false,renderer);
		}
		_angle = angle(x - 400 / 2, y - 266 /2, 400/ 2, 0);
		_apply.fliping(366, 248, NULL, _angle, NULL, flipType, _eye_right, renderer);
		_apply.fliping(428, 248, NULL, _angle, NULL, flipType, _eye_left, renderer);
		SDL_RenderPresent(renderer);
	}
}

Menu::Menu(){}
