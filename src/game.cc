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
	_snake.init('O', EN_DIR_DOWN, 1, coordinate);	
	
	MapBase map;
	map.char_icon = 'O';
	map.int_type = EN_MAP_SNAKE;
	_map.set_map_val(coordinate.int_x, coordinate.int_y, map);
	_bool_is_need_exit = false;

	reset_random_point();
	output_map();

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
	while(_random_point.int_x == 0)
	{
		_random_point.int_x = random(_map.get_x_size());
	}
	while(_random_point.int_x == 0)
	{
		_random_point.int_y = random(_map.get_y_size());
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
	if(int_ret)
	{
		return int_ret;
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
		change_direction();
		forward();
		refresh_map();

	}
	return 0;	

}

}
