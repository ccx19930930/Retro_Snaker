 ///
 /// @file    map.cc
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 10:08:01
 ///
 
#include "map.h"

namespace marrs{

Map::Map()
: _int_x_size(20)
, _int_y_size(20)
{
	_bool_is_init_fail = init();
}

Map::Map(int int_x, int int_y)
: _int_x_size(int_x)
, _int_y_size(int_y)
{
	_bool_is_init_fail = init();
}

Map::~Map()
{
	delete [] _p_map;
}

int Map::init()
{
	int map_size = _int_x_size * _int_y_size;
	_p_map = new MapBase[map_size];
	if (_p_map == NULL)
	{
		return true;
	}
	int int_pos;

	for (int int_idx = 0; int_idx < _int_x_size; ++int_idx)
	{
		for (int int_idy = 0; int_idy < _int_y_size; ++int_idy)
		{
			int_pos = get_map_pos(int_idx, int_idy);
			if ((int_idx == 0 && (int_idy == 0 || int_idy == _int_y_size - 1))
				|| (int_idx == _int_x_size - 1 && (int_idy == 0 || int_idy == _int_y_size - 1)))
			{
				_p_map[int_pos].int_type = EN_MAP_WALL;
				_p_map[int_pos].char_icon = '+';
			}
			else if (int_idx == 0 || int_idx == _int_x_size - 1)
			{
				_p_map[int_pos].int_type = EN_MAP_WALL;
				_p_map[int_pos].char_icon = '=';
			}
			else if (int_idy == 0 || int_idy == _int_y_size - 1)
			{
				_p_map[int_pos].int_type = EN_MAP_WALL;
				_p_map[int_pos].char_icon = '|';
			}
			else
			{
				reset_point(int_idx, int_idy);
			}
		}
	}
	return false;

}

int Map::get_map_pos(int int_x, int int_y)
{
	if (int_x >= _int_x_size || int_y >= _int_y_size)
	{
		return -1;
	}
	
	int int_pos = int_y * _int_x_size + int_x;
	return int_pos;
}

int Map::get_map_val(int int_x, int int_y, MapBase & map_val)
{
	int int_pos = get_map_pos(int_x, int_y);
	if (int_pos == -1)
	{
		return -1;
	}
	map_val = _p_map[int_pos];
	return map_val.int_type;

}

int Map::set_map_val(int int_x, int int_y, MapBase map_val)
{
	int int_pos = get_map_pos(int_x, int_y);
	if (int_pos == -1)
	{
		return -1;
	}
	_p_map[int_pos] = map_val;
	return map_val.int_type;

}

int Map::get_x_size()
{
	return _int_x_size;

}

int Map::get_y_size()
{
	return _int_y_size;

}

int Map::reset_point(int int_x, int int_y)
{
	int int_pos = get_map_pos(int_x, int_y);
	_p_map[int_pos].int_type = EN_MAP_EMPTY;
	_p_map[int_pos].char_icon = ' ';
	return 0;

}

Coordinate Map::get_map_center_pos()
{
	Coordinate coordinate;
	coordinate.int_x = (_int_x_size + 1) / 2;
	coordinate.int_y = (_int_y_size + 1) / 2;
	return coordinate;	

}

ostream & operator << (ostream & output, MapBase & map)
{
	output << map.char_icon;
	return output;
}

int Map::output_map(int int_x, int int_y)
{
	int int_pos = get_map_pos(int_x, int_y);
	cout << _p_map[int_pos] << _p_map[int_pos];

	return 0;
}

}
