#include "MapData.h"

MapData::~MapData() 
{
	ClearMapData();
}

void MapData::CreateMap()
{
	Map = new int*[mapMax.y];
	for (int i = 0; i < mapMax.y; i++)
		Map[i] = new int[mapMax.x];

	int mapSize = mapMax.x * mapMax.y;
	mapSize = mapSize;
}


void MapData::ClearMapData()
{
	for (int i = 0; i < mapMax.y; i++)
	{
		delete[] Map[i];
		Map[i] = nullptr;
	}
	delete[] Map;
}