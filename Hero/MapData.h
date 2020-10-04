#pragma once


enum Map_Tile
{
	Land = 0,
	Forest = 3,
	Swamp = 6,
	Shop = 9,
	Player = 10,

	Max

};

struct Position
{
	int x = 0;
	int y = 0;
};


class MapData
{
public:
	MapData() {}
	~MapData();

	inline void SetMapMax(Position pos) { mapMax.x = pos.x; mapMax.y = pos.y; }
	void CreateMap();
	// �ʷ���
	//bool MapLoop(MapData& mapData, PlayerData& playerData);
	// �ʻ���
	//void CreateMap(MapData& mapData);
	// Ÿ�� ����
	//void CreateTile(MapData& mapData, int Range, int tileNumber);
	// �Ҵ�����
	void ClearMapData();


private:
	Position mapMax;
	Position shop;
	Position player;
	Position playerBefore;
	int** Map;
	int mapSize;
	int standingTile;

};

