#include "Renderer.hpp"
#define F_AG "fonts/AG.ttf"
# define F_ARIAL 	"fonts/ARIAL.TTF"
# define F_MOR 	"fonts/MORPHEUS.TTF"
# define F_ICE  "fonts/LadyIceRevisited.ttf"
# define F_OPEN  "fonts/OpenSans-Semibold.ttf"

Renderer::Renderer(){}
Renderer::~Renderer(){}

Renderer::Renderer(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
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
	init_lib();
	load_textures();
}


void			Renderer::init_lib(){

	if ((window = SDL_CreateWindow("Crimson",
		_x, _y, _width, _height, SDL_WINDOW_OPENGL)))
			if ((renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
					if ((texture = SDL_CreateTexture(renderer,
						SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, _width, _height)))
							std::cout << "Let's go" << std::endl;
}

void			Renderer::load_textures(){

	_back = _apply.load_texture("./MediaFiles/back.png", renderer);
	_image[0] = _apply.load_texture("./MediaFiles/player1.png", renderer);
	_image[1] = _apply.load_texture("./MediaFiles/player2.png", renderer);
}

bool			Renderer::key_event(){
	
	SDL_Event	event;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
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
	static bool tmp = false;
	if ((SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) && count > 20)
	{
		if (_multiplayer)
			_move ? (!_player_1.Set_value(x, y, _map, 'x') ? _move = true : _move = false) :
				!_player_2.Set_value(x, y, _map, 'o') ? _move = false : _move = true;
		else
		{
			if (_player_1.Set_value(x - 80, y - 54, _map, 'x'))
			{
				if (tmp)
					_algorithm.Start_algorithm(_map, 'o', _player_2);
				else
					_player_2.Set_value((rand() % 8 * 52),rand() % 8 * 55, _map, 'o');
				tmp = true;
			}
		}


		count = 0;
	}
	count++;
}

void			Renderer::game(){
	// _map[rand() % 8][rand() % 8] = 'o';
	while (1)
	{
		if (key_event())
			break;
		mouse_event();
		_apply.ApplySurface(0,0,_back,renderer);
		_player_1.Draw_player(renderer, _image[0]);
		_player_2.Draw_player(renderer, _image[1]);
		_apply.writte_text(F_OPEN, "Point", 600, 100, 24, renderer);
		//_algorithm.Start_algorithm(_map, 'x', _player_2);
		SDL_RenderPresent(renderer);
	}
	int y = -1;
	while (++y < 8)
	{
		int x = -1;
		while (++x < 8)
		{
			printf("%c ", _map[y][x]);
		}
		printf("\n");
	}
}


















