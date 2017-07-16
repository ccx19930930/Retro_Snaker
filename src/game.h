 ///
 /// @file    game.h
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 11:42:03
 ///

#ifndef __GAME_H__
#define __GAME_H__

#include "map.h"
#include "snake.h"

namespace marrs{

class Game
{
	public:
		int init();	
		int output_map();	
		int refresh_map();
		int gen_random_point();
		int reset_random_point();
		
		int forward();
		int check_collision();

		int input();
		int change_direction();
		int loop();

		static void* pthread_func(void* p_args);

	private:
		Map _map;
		Snake _snake;	
		Coordinate _random_point;
		bool _bool_is_need_exit;
};
 
}

#endif
