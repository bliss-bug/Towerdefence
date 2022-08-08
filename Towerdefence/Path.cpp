#include "Path.h"

Path path[3];
QVector<QVector<int>>cell;
QVector<QVector<int>>remotecell;

void import_path()
{
	path[0].type = 0;
	path[1].type = 0;
	path[2].type = 1;
	path[0].p = { {11,0},{10,0},{9,0},{8,0},{7,0},{6,0},{5,0},{5,1},
		{5,2},{5,3},{4,3},{3,3},{2,3},{1,3},{0,3} };
	path[1].p = { {11,5},{10,5},{9,5},{8,5},{7,5},{7,4},{6,4},
		{5,4},{4,4},{4,5},{4,6},{3,6},{2,6},{1,6},{0,6} };
	path[2].p = { {11,7},{10,7},{9,7},{8,7},{6,7},{5,7},{4,7},{3,7},{2,7},{1,7},{0,7} };

	// 0：无用格 1：敌方起始格 2：敌方终点格
	// 3：地面格 4：空中格 5：远程格
	cell = { {0,0,5,2,0,0,2,2},
			{0,0,5,3,5,5,3,4},
			{0,0,5,3,5,5,3,4},
			{0,0,5,3,5,5,3,4},
			{5,5,5,3,3,3,3,4},
			{3,3,3,3,3,5,5,4},
			{3,5,5,5,3,5,5,4},
			{3,5,0,5,3,3,5,4},
			{3,5,0,5,5,3,5,4},
			{3,5,0,0,5,3,5,4},
			{3,5,0,0,5,3,5,4},
			{2,0,0,0,0,2,0,2} };

	remotecell = { {0,2},{1,2},{1,4},{1,5},{2,2},{2,4},{2,5},{3,2},{3,4},{3,5},{4,0},
	{4,1},{4,2},{5,5},{5,6},{6,1},{6,2},{6,3},{6,5},{6,6},{7,1},{7,3},
	{7,6},{8,1},{8,3},{8,4},{8,6},{9,1},{9,4},{9,6},{10,1},{10,4},{10,6} };
}

void import_path2()
{
	path[0].type = 0;
	path[1].type = 1;
	path[2].type = 0;
	path[0].p = { {11,2},{10,2},{9,2},{8,2},{8,1},{8,0},{7,0},{6,0},{5,0},
		{5,1},{5,2},{5,3},{4,3},{3,3},{3,2},{2,2},{1,2},{0,2} };
	path[1].p = { {11,3},{10,3},{9,3},{8,3},{8,4},{8,5},{7,5},{6,5},
		{5,5},{4,5},{3,5},{2,5},{2,4},{1,4},{0,4} };
	path[2].p = { {11,5},{10,5},{10,6},{9,6},{9,7},{8,7},{7,7},
		{6,7},{5,7},{4,7},{3,7},{2,7},{1,7},{0,7} };

	cell = { {0,0,2,0,2,0,0,2},
			{0,5,3,5,4,5,5,3},
			{0,5,3,5,4,4,5,3},
			{0,5,3,3,5,4,5,3},
			{5,5,5,3,5,4,5,3},
			{3,3,3,3,5,4,5,3},
			{3,5,5,5,5,4,5,3},
			{3,5,5,5,5,4,5,3},
			{3,3,3,4,4,4,5,3},
			{5,5,3,4,5,5,3,3},
			{0,5,3,4,5,3,3,5},
			{0,0,1,1,0,1,5,0} };

	remotecell = { {1,1},{1,3},{1,5},{1,6},{2,1},{2,3},{2,6},{3,1},{3,4},{3,6},{4,0},{4,1},
		{4,2},{4,4},{4,6},{5,4},{5,6},{6,1},{6,2},{6,3},{6,4},{6,6},{7,1},{7,2},
		{7,3},{7,4},{7,6},{8,6},{9,0},{9,1},{9,4},{9,5},{10,1},{10,4},{10,7},{11,6} };
}