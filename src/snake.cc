 ///
 /// @file    snake.cc
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 11:02:32
 ///

#include <string.h>
#include <iostream>
#include "snake.h"

namespace marrs{
 
Snake::Snake()
{
}

Snake::~Snake()
{
}

int Snake::init(char char_icon, int int_direction, int int_size, Coordinate coordinate)
{
	_snake.char_icon = char_icon;
	_snake.int_direction = int_direction;
	_snake.int_size = int_size;
	_snake.coordinate_cur = coordinate;
	_snake.pNext = NULL;

	if (int_size > 1)
	{
		for (int int_idx = 0; int_idx < int_size; ++int_idx)
		{
			//todo add_new_node
		}
	}
	return 0;

}

int Snake::change_direction(int int_direction)
{
	_snake.int_direction = int_direction;
	return int_direction;
}

int Snake::add_new_node(Coordinate coordinate_new, char char_icon_new)
{
	Snake_Base* pNode = new Snake_Base;
	memset(pNode, 0, sizeof(Snake_Base));
	pNode->coordinate_cur = _snake.coordinate_cur;
	pNode->char_icon = _snake.char_icon;

	if (_snake.pNext == NULL)
	{
		_snake.pNext = pNode;		
	}else{
		pNode->pNext = _snake.pNext;
		_snake.pNext = pNode;
	}
	
	_snake.coordinate_cur = coordinate_new;
	_snake.char_icon = char_icon_new;

	return 0;
}

int Snake::forward()
{
	switch(_snake.int_direction)
	{
		case EN_DIR_UP:
			_snake.coordinate_cur.int_y -= 1;
			break;
		case EN_DIR_DOWN:	
			_snake.coordinate_cur.int_y += 1;
			break;
		case EN_DIR_LEFT:	
			_snake.coordinate_cur.int_x -= 1;
			break;
		case EN_DIR_RIGHT:	
			_snake.coordinate_cur.int_x += 1;
			break;
		default:break;

	}
	return _snake.int_direction;

}

Snake_Base* Snake::get_snake_base()
{
	return _snake.pNext;

}

SnakeHead* Snake::get_snake_head()
{
	return &_snake;

}
}
