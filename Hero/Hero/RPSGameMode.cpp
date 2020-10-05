#include "RPSGameMode.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "CharacterData.h"
#include "PlayerCharacter.h"
#include "MapData.h"
#include "Rand.h"
#include "GamePlayStatics.h"

using namespace std;

void RPSGameMode::PlayGame()
{

}

int RPSGameMode::RPSWinCheck(int playerRPS, int enemyRPS)
{
	int result = playerRPS - enemyRPS;

	switch (result)
	{
		//승리
	case -2:
	case 1:
		return RPSState::Win;
		//비김
	case 0:
		return RPSState::Draw;
		//패배
	case -1:
	case 2:
		return RPSState::Lose;

	default:
		return RPSState::Error;
	}
}

std::string RPSGameMode::RPSintToString(int RPS)
{
	switch (RPS)
	{
	case RPS::Scissors:
		return "가위";
	case RPS::Rock:
		return "바위";
	case RPS::Paper:
		return "보";
	default:
		return "에러";
	}
}




void RPSGameMode::SettingHero(MapData* mapData,CharacterData* playerData)
{
	bool isOk = false;
	string inputName;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "			용사는 구조적		 " << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "구조적인 당신의 이름을 입력하세요 : ";
	cin >> inputName;
	playerData->SetName(inputName);

	int input;
	Position mapMax;
	cout << "맵 크기에따라 난이도가 달라집니다. \n";
	while (true)
	{

		cout << "맵크 가로 크기를 정해주세요 : ";
		cin >> input;

		if (input <= 0)
		{
			cout << "잘못 입력했습니다. " << endl;
			continue;
		}
		if (input >= 60)
			input = 60;
		
		mapMax.x = input;
		break;
	}

	while (true)
	{
		cout << "맵크 세로 크기를 정해주세요 : ";
		cin >> input;

		if (input <= 0)
		{
			cout << "잘못 입력했습니다. " << endl;
			continue;
		}
		if (input >= 60)
			input = 60;
		mapMax.y = input;
		break;
	}

	mapData->SetMapMax(mapMax);
	mapData->ClearMapData();
	int mapSize = mapMax.y * mapMax.x;

	playerData->SetMoney(0);
	if (mapSize <= 30 * 30)
		gameLevel = 1;
	else if (mapSize <= 40 * 40)
		gameLevel = 2;
	else if (mapSize <= 50 * 50)
		gameLevel = 3;
	else
		gameLevel = 4;




	switch (gameLevel)
	{
	case 1:
		gameLevelCorrection = 1.0f;
		break;
	case 2:
		gameLevelCorrection = 1.2f;
		break;
	case 3:
		gameLevelCorrection = 1.5f;
		break;
	case 4:
		gameLevelCorrection = 1.8f;
		break;
	}
	playerData->SetMaxHP(static_cast<int>(300 * gameLevelCorrection));
	playerData->AddHP(playerData->GetMaxHP());
	playerData->SetLevel(1);
	playerData->SetAttackvalue(static_cast<int>(70 - 10 *gameLevelCorrection));
	// 난이도에따라 초기 자금이 달라짐
	playerData->SetMoney(static_cast<int>(20 * gameLevelCorrection));
}

void RPSGameMode::SettingMonsterData(CharacterData * MonsterData, string name, int characterLevel, int attackValue, int maxHP, int Exp, int money, float gameLevelCorrection)
{
	int resultmaxHP = static_cast<int>(maxHP * gameLevelCorrection);
	int resultMoney = static_cast<int>(money * gameLevelCorrection);
	MonsterData->SettingCharacterData(name, characterLevel,attackValue, resultmaxHP,  Exp, resultMoney);
}

void RPSGameMode::SaveMonsterData(CharacterData ** MonsterData, int Max, float gameLevelCorrection)
{
	CharacterData* monster = new CharacterData[Max];
	SettingMonsterData(&monster[Map_Tile::Land], "고블린", 1, 3, 100, 10, 50);
	SettingMonsterData(&monster[Map_Tile::Land + 1], "정예 고블린", 2, 4, 150, 15, 70);
	SettingMonsterData(&monster[Map_Tile::Land + 2], "고블린 우두머리 ", 3, 5, 250, 30, 100);

	SettingMonsterData(&monster[Map_Tile::Forest], "늑대", 1, 4, 80, 8, 40);
	SettingMonsterData(&monster[Map_Tile::Forest + 1], "곰", 2, 5, 150, 15, 70);
	SettingMonsterData(&monster[Map_Tile::Forest + 2], "호랑이 ", 3, 6, 200, 25, 90);

	SettingMonsterData(&monster[Map_Tile::Swamp], "늪지 슬라임", 1, 3, 50, 5, 20);
	SettingMonsterData(&monster[Map_Tile::Swamp + 1], "늪지 킹슬라임", 2, 4, 80, 8, 40);
	SettingMonsterData(&monster[Map_Tile::Swamp + 2], "진흙 골램 ", 3, 5, 400, 50, 180);
	*MonsterData = monster;
}

CharacterData RPSGameMode::LoadMonsterData(CharacterData * MonsterData, int TileNumber)
{

	switch (TileNumber)
	{
	case Map_Tile::Land:
		return MonsterData[RandRangeAToB(Map_Tile::Land, Map_Tile::Land + 2) + Map_Tile::Land];
	case Map_Tile::Forest:
		return MonsterData[RandRangeAToB(Map_Tile::Forest, Map_Tile::Forest + 2, Map_Tile::Forest)];
	case Map_Tile::Swamp:
		return MonsterData[RandRangeAToB(Map_Tile::Swamp, Map_Tile::Swamp + 2, Map_Tile::Swamp)];
	}

	CharacterData noData;

	return noData;
}

void RPSGameMode::ClearMonster(CharacterData * MonsterData)
{
	delete[] MonsterData;
}

void RPSGameMode::LevelUpCheck()
{
	CharacterData* asdf = GamePlayStatics::GetPlayerData();
	PlayerCharacter* Player = dynamic_cast<PlayerCharacter*>(GamePlayStatics::GetPlayerData());
	

#ifdef _DEBUG
	if (Player == nullptr)
		cout << "Player 가 널포인터 이다." << endl;
	_getch();

#endif // DEBUG

	if (Player == nullptr)
		return;


	Player->LevelUpCheck();
}

bool RPSGameMode::BattleLoop(MapData & mapData, PlayerCharacter * playerData, CharacterData * enemyData)
{

	bool isBattle = true;
	bool isGameOver = false;
	bool isClear = false;
	bool isCPUWin = false;
	int RPSResult = RPSState::Win;
	int damage = 0;

	CharacterData spwanEnemy = LoadMonsterData(enemyData, mapData.GetStandingTile());

	// 몬스터 레벨 보정및 체력보정
	int resultCharacterLevel = spwanEnemy.GetCharacterLevel() + playerData->GetCharacterLevel();// *playerData.data.gameLevelCorrection);
	int resultMaxHP = static_cast<int>(spwanEnemy.GetMaxHP() + (resultCharacterLevel * 15));
	int resultMoney = static_cast<int>(spwanEnemy.GetMoney() * resultCharacterLevel);
	int resultExp = static_cast<int>(spwanEnemy.GetExp() * resultCharacterLevel);
	spwanEnemy.SettingCharacterData(resultCharacterLevel, resultMaxHP, resultExp, resultMoney);

	cout << "레벨 " << spwanEnemy.GetCharacterLevel() << "의 " << spwanEnemy.GetName() << " 이(가) 나타났다 " << endl;
	cout << playerData->GetName() << " 은(는) 전투 준비에 들어갔다." << endl;

	while (true)
	{
		cout << spwanEnemy.GetName() << " 체력 : " << spwanEnemy.GetHP() << " / " << spwanEnemy.GetMaxHP() << endl;
		cout << playerData->GetName() << " 체력 : " << playerData->GetHP() << " / " << playerData->GetMaxHP() << endl;
		cout << "가위 바위 보 입력(가위 , 바위 ,보 , 0(가위) ,1(바위) ,2(보) ,3(도망가기))" << endl;
		string input;
		cin >> input;
		playerData->SetInput(input);
		cout << endl;
		system("cls");

		if (playerData->GetInput() == "가위" || playerData->GetInput() == "0")
		{
			playerData->SetRPSNum(0);
		}
		else if (playerData->GetInput() == "바위" || playerData->GetInput() == "1")
		{
			playerData->SetRPSNum(1);
		}
		else if (playerData->GetInput() == "die" || playerData->GetInput() == "444")
		{
			isGameOver = true;
			return false;
			break;
		}
		else if (playerData->GetInput() == "kill")
		{



			//if (!isBattle)
			{
				spwanEnemy.SetHP(0);

			}
		}
		else if (playerData->GetInput() == "보" || playerData->GetInput() == "2")
		{
			playerData->SetRPSNum(2);
		}
		else if (playerData->GetInput() == "3")
		{
			
			damage = spwanEnemy.GetDamage();
			playerData->AddHP(-damage);
			cout << "도망을 갔지만 공격을 받았다. " << endl;
			cout << playerData->GetName() << "는 " << damage << "의 데미지를 받았다. " << endl;
			if (playerData->GetHP() <= 0)
			{
				cout << playerData->GetName() << "은(는) " << spwanEnemy.GetName() << "에게 죽음을 당했다." << endl;
				_getch();
				system("cls");
				return false;
			}
			_getch();
			system("cls");
			return true;
		}
		else
		{
			cout << "잘못 입력됬습니다. " << endl;
			cout << endl;
			continue;
		}

		// 적 가위바위보 생성
		spwanEnemy.SetRPSNum(RandRange(3));

		// 가위바위보 숫자를 문자열로 변환
		playerData->SetInput(RPSintToString(playerData->GetRPSNum()));
		spwanEnemy.SetInput(RPSintToString(spwanEnemy.GetRPSNum()));

		//가위바위보 표시
		cout << playerData->GetName() << " : " << playerData->GetInput() << endl;
		cout << spwanEnemy.GetName() << " : " << spwanEnemy.GetInput() << endl;
		cout << endl;

		RPSResult = RPSWinCheck(playerData->GetRPSNum(), spwanEnemy.GetRPSNum());

		switch (RPSResult)
		{
		case RPSState::Win:
			damage = playerData->GetDamage();
			spwanEnemy.AddHP(-damage);
			cout << "공격에 성공했다. " << endl;
			cout << spwanEnemy.GetName() << "에게 " << damage << "의 데미지를 주었다. " << endl;
			break;
		case RPSState::Draw:
			cout << "서로의 공격이 빗나갔다. " << endl;
			break;
		case RPSState::Lose:
			damage = spwanEnemy.GetDamage();
			playerData->AddHP(-damage);
			cout << "공격에 실패했다. " << endl;
			cout << playerData->GetName() << "는 " << damage << "의 데미지를 받았다. " << endl;
			break;
		case RPSState::Error:
			cout << " 가위바위보 결과 에러" << endl;
			break;
		}

		if (spwanEnemy.GetHP() <= 0)
		{
			cout << spwanEnemy.GetName() << "을(를) 처치했다. " << endl;
			cout << spwanEnemy.GetMoney() << "원과 " << spwanEnemy.GetExp() << "의 경험치를 얻었다." << endl;
			playerData->AddExp (spwanEnemy.GetExp());
			playerData->AddMoney(spwanEnemy.GetMoney());
			playerData->LevelUpCheck();
			_getch();
			system("cls");
			break;
		}

		if (playerData->GetHP() <= 0)
		{
			cout << playerData->GetName() << "은(는) " << spwanEnemy.GetName() << "에게 죽음을 당했다." << endl;
			_getch();
			system("cls");
			return false;
		}
	}
	return true;
}
