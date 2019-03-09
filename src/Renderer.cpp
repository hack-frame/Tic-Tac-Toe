#include "Renderer.hpp"

Renderer::Renderer(){}
Renderer::~Renderer(){}

Renderer::Renderer(int x, int y)
{
	_move = true;
	int tm_x = -1;
	while (++tm_x < NET)
	{
		int tm_y = -1;
		while (++tm_y < NET)
			_map[tm_x][tm_y] = '-';
	}
	Init_lib(x, y);
	Load_textures();
	_player_1.Set_wins(0);
	_player_2.Set_wins(0);
}

void			Renderer::Init_lib(int x, int y){

	if ((window = SDL_CreateWindow("Tic Tac Toe",
					x, y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL)))
		if ((renderer = SDL_CreateRenderer(window, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
			if ((texture = SDL_CreateTexture(renderer,
							SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
				std::cout << "Let's go" << std::endl;
}

void			Renderer::Load_textures(){

	_image[0] = _apply.Load_texture("./MediaFiles/back.png", renderer);
	_image[1] = _apply.Load_texture("./MediaFiles/player1.png", renderer);
	_image[2] = _apply.Load_texture("./MediaFiles/player2.png", renderer);
	_image[3] = _apply.Load_texture("./MediaFiles/massage.png", renderer);
	_image[4] = _apply.Load_texture("./MediaFiles/retry.png", renderer);
}

bool			Renderer::Key_event(){

	SDL_Event	event;
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT)
			return (true);
		if (PRESS == SDLK_ESCAPE)
			return (true);
	}
	return (false);
}

void			Renderer::Draw_delay(int x)
{
	if (x == 1) SDL_Delay(500);
	_player_1.Draw_player(renderer, _image[1]);
	SDL_RenderPresent(renderer);
	SDL_Delay(500);
	_player_2.Draw_player(renderer, _image[2]);
}

void			Renderer::Mouse_event(){
	SDL_PumpEvents();
	int x, y;
	static int count;
	static bool rand_1;
	static bool rand_2;
	_side = rand() % 2;
	if ((SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) && count > 20){
		if (_menu.Get_game_mod() == 1)
			_move ? (!_player_1.Set_value(x - RECT_X, y - RECT_Y, _map, 'x') ?
					_move = true : _move = false) :
				!_player_2.Set_value(x - RECT_X, y - RECT_Y, _map, 'o') ?
				_move = false : _move = true;
		else if (_menu.Get_game_mod() == 2)
		{
			if (_player_1.Set_value(x - RECT_X, y - RECT_Y, _map, 'x'))
			{
				rand_2 ? (_algorithm.Start_algorithm(_map, _player_2)) :
					_player_2.Set_value((rand() % NET * STEP),rand() % NET * STEP, _map, 'o');
				rand_2 = true;
			}
			Draw_delay(2);
		}
		else if (_menu.Get_game_mod() == 3)
		{
			rand_1 ? (_algorithm.Start_algorithm(_map, _player_1)) :
				_player_1.Set_value((rand() % NET * STEP),rand() % NET * STEP, _map, 'x');
			rand_2 ? (_algorithm.Start_algorithm(_map, _player_2)) :
				_player_2.Set_value((rand() % NET * STEP),rand() % NET * STEP, _map, 'o');
			rand_1 = true;
			rand_2 = true;
			Draw_delay(1);
		}
		count = 0;
	}
	count++;
}

bool			Renderer::Message_event()
{
	if (_algorithm.Who_winner(_map) == "PLAYER 1") _player_1.Set_wins();
	else if (_algorithm.Who_winner(_map) == "PLAYER 2") _player_2.Set_wins();
	while (1){
		int x, y;
		if(MOUSE_PRESS && x > 620 && x < 690 && y > 270 && y < 335){
			_algorithm.Reset_winner(_map);
			_player_1.Free_data();
			_player_2.Free_data();
			return(true);
		}
		_player_1.Draw_player(renderer, _image[1]);
		_player_2.Draw_player(renderer, _image[2]);
		_apply.Writte_text("WINNER IS", 580, 350, 40, false,renderer);
		_apply.ApplySurface(620, 230,_image[4],renderer);
		_apply.Writte_text(_algorithm.Who_winner(_map).c_str(), 580, 400, 40, true,renderer);
		SDL_RenderPresent(renderer);
		if (Key_event()) return (false);
	}
	return (true);
}

void			Renderer::Game(){
	_side = rand() % 2;
	_menu.Action(renderer);
	if (_menu.Get_game_mod() > 0)
		while (1)
		{
			if (Key_event()) break;
			if (_algorithm.Who_winner(_map) == "nul") Mouse_event();
			else if (!Message_event()) break;
			_apply.ApplySurface(0,0,_image[0],renderer);
			_apply.ApplySurface(510, 300,_image[3],renderer);
			_player_1.Draw_player(renderer, _image[1]);
			_player_2.Draw_player(renderer, _image[2]);
			SDL_RenderPresent(renderer);
		}
}


















