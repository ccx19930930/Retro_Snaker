 ///
 /// @file    snake.h
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 09:32:47
 ///

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "define.h" 

namespace marrs{

class Snake
{
	public:
		Snake();
		~Snake();

	public:
		int init(char char_icon, int int_direction, int int_size, Coordinate coordinate);
		int change_direction(int int_direction);	
		int add_new_node(Coordinate coordinate_new, char char_icon_new);
		int add_new_node(char char_icon_new);
		Snake_Base* del_tail_node();
		Snake_Base* forward();
		Snake_Base* get_snake_base();
		SnakeHead* get_snake_head();
		int get_snake_size();

	private:
		SnakeHead _snake;

};

}

#endif
