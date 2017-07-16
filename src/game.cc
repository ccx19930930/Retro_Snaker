 ///
 /// @file    game.cc
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 18:05:24
 ///
 
#include <iostream>
#include "game.h"

namespace marrs{

int Game::init()
{
	Coordinate coordinate = _map.get_map_center_pos();
	_snake.init('O', EN_DIR_DOWN, 5, coordinate);	
	
	MapBase map;
	map.char_icon = 'O';
	map.int_type = EN_MAP_SNAKE;
	_map.set_map_val(coordinate.int_x, coordinate.int_y, map);

	_bool_is_need_exit = false;

	reset_random_point();
	output_map();

	::pthread_t pthid;
	::pthread_create(&pthid, NULL, Game::pthread_func, this);

	return 0;

}

int Game::output_map()
{
	int int_map_x_size = _map.get_x_size();
	int int_map_y_size = _map.get_y_size();

	for (int int_idx = 0; int_idx < int_map_x_size; ++int_idx)
	{
		for (int int_idy = 0; int_idy < int_map_y_size; ++int_idy)
		{
			_map.output_map(int_idx, int_idy);
		}
		cout << endl;
	}
	return 0;
	
}

int Game::refresh_map()
{
	int int_map_y_size = _map.get_y_size();
	printf("\033[%dA", int_map_y_size);
	output_map();
	return 0;

}

int Game::gen_random_point()
{
	if(_random_point.int_x * _random_point.int_y)
	{
		return 0;
	}
	MapBase map;
	while(true)
	{
		while(_random_point.int_x == 0 || _random_point.int_x == _map.get_x_size() - 1)
		{
			_random_point.int_x = random(_map.get_x_size());
		}
		while(_random_point.int_y == 0 || _random_point.int_y == _map.get_y_size() - 1)
		{
			_random_point.int_y = random(_map.get_y_size());
		}
		int int_map_type = _map.get_map_val(_random_point.int_x, _random_point.int_y, map);
		if (int_map_type == EN_MAP_EMPTY)
		{
			map.char_icon = '0';
			map.int_type = EN_MAP_NEW_NODE;
			_map.set_map_val(_random_point.int_x, _random_point.int_y, map);
			break;
		}else
		{
			reset_random_point();
		}
	}	

	return 0;

}

int Game::reset_random_point()
{
	_random_point.int_x = 0;
	_random_point.int_y = 0;
	return 0;
}

int Game::forward()
{
	int int_ret = check_collision();

	switch(int_ret)
	{
		case EN_COLLISION_NEW_NODE:
			_snake.add_new_node(_snake.get_snake_head()->char_icon);
			reset_random_point();
			break;
		case EN_COLLISION_DEAD:
			return EN_COLLISION_DEAD;
		case EN_COLLISION_NEW_EMPTY:
		default:break;

	}

	Snake_Base* snake_tmp = _snake.forward();

	_map.reset_point(snake_tmp->coordinate_cur.int_x, snake_tmp->coordinate_cur.int_y);
	delete snake_tmp;
	MapBase map_tmp;
	map_tmp.int_type = EN_MAP_SNAKE;
	map_tmp.char_icon = _snake.get_snake_head()->char_icon;
	_map.set_map_val(_snake.get_snake_head()->coordinate_cur.int_x,
				_snake.get_snake_head()->coordinate_cur.int_y,
				map_tmp);

	return 0;
}

int Game::check_collision()
{
	Coordinate coordinate = _snake.get_next_coordinate();
	MapBase map;
	int int_map_type = _map.get_map_val(coordinate.int_x, coordinate.int_y, map);
	switch(int_map_type)
	{
		case EN_MAP_WALL:
		case EN_MAP_SNAKE:
			return EN_COLLISION_DEAD;
		case EN_MAP_NEW_NODE:
			return EN_COLLISION_NEW_NODE;
		case EN_MAP_EMPTY:
		default:break;

	}

	return 0;
}

int Game::input()
{
	struct termios stored_settings;  
	struct termios new_settings;  
	tcgetattr (0, &stored_settings);  
	new_settings = stored_settings;  
	new_settings.c_lflag &= (~ICANON);  
	new_settings.c_cc[VTIME] = 0;  
	new_settings.c_cc[VMIN] = 1;  
	tcsetattr (0, TCSANOW, &new_settings);  
	char char_input = getchar();
	putchar('\b');
	tcsetattr (0, TCSANOW, &stored_settings);
	switch(char_input)
	{
		case 'w':return EN_DIR_UP;
		case 's':return EN_DIR_DOWN;
		case 'a':return EN_DIR_LEFT;
		case 'd':return EN_DIR_RIGHT;
		default:break;

	}

	return -1;
}

int Game::change_direction()
{
	int int_new_direction = input();
	if (int_new_direction == -1)
	{
		_bool_is_need_exit = true;
	}else
	{
		_snake.change_direction(int_new_direction);
	}
	return 0;
}

int Game::loop()
{
	while(!_bool_is_need_exit)
	{
		gen_random_point();
		forward();
		refresh_map();
		//sleep(1);
		usleep(100000);
	}
	return 0;	

}

void* Game::pthread_func(void* p_args)
{
	Game* game_tmp = static_cast<Game*> (p_args);
	while(!game_tmp->_bool_is_need_exit)
	{
		game_tmp->change_direction();
	}
}

}
