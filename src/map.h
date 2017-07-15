 ///
 /// @file    map.h
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 09:45:50
 ///

#ifndef __MAP_H__
#define __MAP_H__

#include "define.h" 

namespace marrs{

class Map
{
	public:
		Map();
		Map(int int_x, int int_y);
		~Map();

	public:
		int init();
		int get_map_val(int int_x, int int_y, MapBase & map_val);
		int set_map_val(int int_x, int int_y, MapBase int_val);

		int get_x_size();
		int get_y_size();

		int reset_point(int int_x, int int_y);

		Coordinate get_map_center_pos();

		friend ostream & operator << (ostream & output, MapBase & map); 

		int output_map(int int_x, int int_y);

	private:
		int get_map_pos(int int_x, int int_y);

	private:
		int _int_x_size;
		int _int_y_size;
		MapBase * _p_map;
		bool _bool_is_init_fail;
};
 
}

#endif
