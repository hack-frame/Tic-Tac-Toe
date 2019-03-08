#include "Renderer.hpp"

Renderer::Renderer(){}
Renderer::~Renderer(){}

Renderer::Renderer(int x, int y, int width, int height)
{
	_width = width;
	_height = height;
	_move = true;
	int tm_x = -1;
	while (++tm_x < 8)
	{
		int tm_y = -1;
		while (++tm_y < 8)
			_map[tm_x][tm_y] = '-';
	}
	init_lib(x, y);
	load_textures();
}


void			Renderer::init_lib(int x, int y){

	if ((window = SDL_CreateWindow("Tic Tac Toe",
		x, y, _width, _height, SDL_WINDOW_OPENGL)))
			if ((renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
					if ((texture = SDL_CreateTexture(renderer,
						SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, _width, _height)))
							std::cout << "Let's go" << std::endl;
}

void			Renderer::load_textures(){

	_image[0] = _apply.load_texture("./MediaFiles/back.png", renderer);
	_image[1] = _apply.load_texture("./MediaFiles/player1.png", renderer);
	_image[2] = _apply.load_texture("./MediaFiles/player2.png", renderer);
	_image[3] = _apply.load_texture("./MediaFiles/massage.png", renderer);
}

bool			Renderer::key_event(){
	
	SDL_Event	event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (true);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			return (true);
	}
	return (false);
}

void			Renderer::mouse_event(){
	SDL_PumpEvents();
	int x, y;
	static int count;
	static bool rand_1;
	static bool rand_2;
	if ((SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) && count > 40){
		if (_menu.Get_game_mod() == 1)
			_move ? (!_player_1.Set_value(x - 54, y - 42, _map, 'x') ? _move = true : _move = false) :
				!_player_2.Set_value(x - 54, y - 42, _map, 'o') ? _move = false : _move = true;
		else if (_menu.Get_game_mod() == 2)
		{
			if (_player_1.Set_value(x - 54, y - 42, _map, 'x'))
			{
				rand_2 ? (_algorithm.Start_algorithm(_map, _player_2)) :
				_player_2.Set_value((rand() % 8 * 55),rand() % 8 * 55, _map, 'o');
				rand_2 = true;
			}
		}
		else if (_menu.Get_game_mod() == 3)
		{
			rand_1 ? (_algorithm.Start_algorithm(_map, _player_1)) :
				_player_2.Set_value((rand() % 8 * 55),rand() % 8 * 55, _map, 'x');
		
			rand_2 ? (_algorithm.Start_algorithm(_map, _player_2)) :
				_player_2.Set_value((rand() % 8 * 55),rand() % 8 * 55, _map, 'o');
			rand_1 = true;
			rand_2 = true;
		}
		count = 0;
	}
	count++;
}

void			Renderer::Message_event()
{
	while (1)
	{
		_player_1.Draw_player(renderer, _image[1]);
		_player_2.Draw_player(renderer, _image[2]);
		_apply.writte_text("WINNER IS", 580, 350, 40, false,renderer);
		_apply.writte_text(_algorithm.Who_winner(_map).c_str(), 580, 400, 40, true,renderer);
		SDL_RenderPresent(renderer);
		if (key_event())
		{
			//_algorithm.Reset_winner();
			//break;
			exit(1);
		}
	}
}

void			Renderer::Game(){

	_menu.Action(renderer);
	if (_menu.Get_game_mod() > 0)
		while (1)
		{
			if (key_event()) break;
			if (_algorithm.Who_winner(_map) == "nul") mouse_event();
			else (Message_event());
			_apply.ApplySurface(0,0,_image[0],renderer);
			_apply.ApplySurface(510, 300,_image[3],renderer);
			_player_1.Draw_player(renderer, _image[1]);
			_player_2.Draw_player(renderer, _image[2]);
			SDL_RenderPresent(renderer);
		}
}


















