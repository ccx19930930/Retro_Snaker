 /// /// @file    snake.cc
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
	_snake.int_size = 1;
	_snake.coordinate_cur = coordinate;
	_snake.pNext = NULL;

	if (int_size > 1)
	{
		for (int int_idx = 0; int_idx < int_size; ++int_idx)
		{
			add_new_node(char_icon);
		}
	}
	return 0;

}

int Snake::change_direction(int int_direction)
{
	_snake.int_direction = int_direction;
	return int_direction;
}

int Snake::add_new_node(char char_icon_new)
{
	Snake_Base* pNode = new Snake_Base;
	pNode->char_icon = char_icon_new;
	pNode->pNext = NULL;
	if (_snake.int_size == 1)
	{
		_snake.pNext = pNode;
	}else{
		Snake_Base* pPre = _snake.pNext;
		while(pPre->pNext)
		{
			pPre = pPre->pNext;
		}
		pPre->pNext = pNode;
	}
	++_snake.int_size;

	return 0;

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
	++_snake.int_size;

	return 0;
}

Snake_Base* Snake::del_tail_node()
{
	Snake_Base* pPre;
	Snake_Base* pCur;
	if(_snake.int_size == 1)
	{
		return NULL;
	}
	pCur = _snake.pNext;
	if(!pCur->pNext)
	{
		_snake.pNext = NULL;
	}
	else{
		while(pCur->pNext)
		{
			pPre = pCur;
			pCur = pCur->pNext;
		}
		pPre->pNext = NULL;
	}
	--_snake.int_size;
	return pCur;

}

Snake_Base* Snake::forward()
{
	Snake_Base* pReturn = NULL;
	if(_snake.int_size > 1)
	{
		add_new_node(_snake.coordinate_cur, _snake.char_icon);
		pReturn = del_tail_node();
	}
	else
	{
		pReturn = new Snake_Base;
		pReturn->coordinate_cur = _snake.coordinate_cur;
	}

	switch(_snake.int_direction)
	{
		case EN_DIR_UP:
			_snake.coordinate_cur.int_x -= 1;
			break;
		case EN_DIR_DOWN:	
			_snake.coordinate_cur.int_x += 1;
			break;
		case EN_DIR_LEFT:	
			_snake.coordinate_cur.int_y -= 1;
			break;
		case EN_DIR_RIGHT:	
			_snake.coordinate_cur.int_y += 1;
			break;
		default:break;

	}
	return pReturn;

}

Snake_Base* Snake::get_snake_base()
{
	return _snake.pNext;

}

SnakeHead* Snake::get_snake_head()
{
	return &_snake;

}

int Snake::get_snake_size()
{
	return _snake.int_size;
}

}
