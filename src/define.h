 ///
 /// @file    define.h
 /// @author  marrs(chenchengxi993@gmail.com)
 /// @date    2017-07-15 18:41:04
 ///


#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include <pthread.h>

#include <iostream>

#define random(x) (rand()%x)

namespace marrs{

using namespace std;

enum Direction
{
	EN_DIR_UP = 0,
	EN_DIR_DOWN,
	EN_DIR_LEFT,
	EN_DIR_RIGHT,
};

struct Coordinate
{
	int int_x;
	int int_y;
};

typedef struct Snake_Base
{
	Snake_Base* pNext;
	char char_icon;              //图标
	Coordinate coordinate_cur;   //当前坐标
}SnakeBase;

typedef struct Snake_Head
{
	char char_icon;              //图标
	int int_direction;           //前进方向
	int int_size;                //当前长度
	Coordinate coordinate_cur;   //当前坐标
	Snake_Base* pNext;           //下一节   
}SnakeHead;

enum MapStatus
{
	EN_MAP_EMPTY = 0,  //空地
	EN_MAP_WALL,       //边界
	EN_MAP_NEW_NODE,   //新节点
	EN_MAP_SNAKE,      //蛇

};

struct MapBase
{
	int int_type;
	char char_icon;
};

enum Collision
{
	EN_COLLISION_NEW_EMPTY = 0,
	EN_COLLISION_NEW_NODE,
	EN_COLLISION_DEAD,
};

}

#endif
