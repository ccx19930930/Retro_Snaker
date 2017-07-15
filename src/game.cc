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

	Coordinate coordinate_pre = _snake.get_snake_head()->coordinate_cur;
	Coordinate coordinate_tmp;

	MapBase map_tmp;
	map_tmp.int_type = EN_MAP_SNAKE;
	map_tmp.char_icon = _snake.get_snake_head()->char_icon;

	Snake_Base* pSnake = _snake.get_snake_base(); 
	while(pSnake)
	{
		coordinate_tmp = pSnake->coordinate_cur;
		pSnake->coordinate_cur = coordinate_pre;
		coordinate_pre = coordinate_tmp;

	}

	_snake.forward();
	_map.reset_point(coordinate_pre.int_x, coordinate_pre.int_y);
	_map.set_map_val(_snake.get_snake_head()->coordinate_cur.int_x,
				_snake.get_snake_head()->coordinate_cur.int_y,
				map_tmp);

	return 0;
}

int Game::check_collision()
{

	return 0;
}

}
