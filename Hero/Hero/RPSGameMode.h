#pragma once
#include "GameMode.h"


enum RPSState
{
	Win = 0,
	Draw = 1,
	Lose = 2,
	Error,
};

enum RPS
{
	Scissors = 0,
	Rock = 1,
	Paper = 2
};


class RPSGameMode :public GameMode
{
public:
	RPSGameMode() {};
	~RPSGameMode() {};

	virtual void PlayGame();

	int RPSWinCheck(int playerRPS, int enemyRPS);

	//// ����� ����
	void SettingHero(class MapData* mapData, class CharacterData* playerData);


	//// ������ ���� ����
	//void SettingMonsterData(CharacterData* MonsterData, string name, int characterLevel, int attackValue, int maxHP, int Exp, int money, float gameLevelCorrection = 1.0f);
	//// ���� ������ ������ ����
	//void SaveMonsterData(CharacterData** MonsterData, int Max, float gameLevelCorrection = 1.0f);
	//// ���� ������ �ε�
	//CharacterData LoadMonsterData(CharacterData* MonsterData, int TileNumber);
	//// ���� �Ҵ�����
	//void ClearMonster(CharacterData* MonsterData);
	//// ������ üũ
	//void LevelUpCheck(PlayerData& characterData);
	//// ��Ʋ ���� false == ���� ����
	//bool BattleLoop(MapData& mapData, PlayerData& playerData, CharacterData* enemyData);

private:
	int gameLevel;
	// ���� ����
	float gameLevelCorrection;
};

