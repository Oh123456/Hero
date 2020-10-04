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

	//// 히어로 세팅
	void SettingHero(class MapData* mapData, class CharacterData* playerData);


	//// 몬스터의 값을 세팅
	//void SettingMonsterData(CharacterData* MonsterData, string name, int characterLevel, int attackValue, int maxHP, int Exp, int money, float gameLevelCorrection = 1.0f);
	//// 몬스터 데이터 세팅후 저장
	//void SaveMonsterData(CharacterData** MonsterData, int Max, float gameLevelCorrection = 1.0f);
	//// 몬스터 데이터 로딩
	//CharacterData LoadMonsterData(CharacterData* MonsterData, int TileNumber);
	//// 몬스터 할당해제
	//void ClearMonster(CharacterData* MonsterData);
	//// 레벨업 체크
	//void LevelUpCheck(PlayerData& characterData);
	//// 배틀 루프 false == 게임 오버
	//bool BattleLoop(MapData& mapData, PlayerData& playerData, CharacterData* enemyData);

private:
	int gameLevel;
	// 레벨 보정
	float gameLevelCorrection;
};

