 ///
 /// @file    main.cc
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 18:20:18
 ///
 
#include "game.h" 
using namespace marrs;

int main()
{
	Game game;
	game.init();
	for(int int_idx = 0; int_idx < 5; ++int_idx)
	{
		game.forward();	
		game.refresh_map();
		sleep(1);
	}
	



	return 0;
}
