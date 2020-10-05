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
		//�¸�
	case -2:
	case 1:
		return RPSState::Win;
		//���
	case 0:
		return RPSState::Draw;
		//�й�
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
		return "����";
	case RPS::Rock:
		return "����";
	case RPS::Paper:
		return "��";
	default:
		return "����";
	}
}




void RPSGameMode::SettingHero(MapData* mapData,CharacterData* playerData)
{
	bool isOk = false;
	string inputName;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "			���� ������		 " << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "�������� ����� �̸��� �Է��ϼ��� : ";
	cin >> inputName;
	playerData->SetName(inputName);

	int input;
	Position mapMax;
	cout << "�� ũ�⿡���� ���̵��� �޶����ϴ�. \n";
	while (true)
	{

		cout << "��ũ ���� ũ�⸦ �����ּ��� : ";
		cin >> input;

		if (input <= 0)
		{
			cout << "�߸� �Է��߽��ϴ�. " << endl;
			continue;
		}
		if (input >= 60)
			input = 60;
		
		mapMax.x = input;
		break;
	}

	while (true)
	{
		cout << "��ũ ���� ũ�⸦ �����ּ��� : ";
		cin >> input;

		if (input <= 0)
		{
			cout << "�߸� �Է��߽��ϴ�. " << endl;
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
	// ���̵������� �ʱ� �ڱ��� �޶���
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
	SettingMonsterData(&monster[Map_Tile::Land], "���", 1, 3, 100, 10, 50);
	SettingMonsterData(&monster[Map_Tile::Land + 1], "���� ���", 2, 4, 150, 15, 70);
	SettingMonsterData(&monster[Map_Tile::Land + 2], "��� ��θӸ� ", 3, 5, 250, 30, 100);

	SettingMonsterData(&monster[Map_Tile::Forest], "����", 1, 4, 80, 8, 40);
	SettingMonsterData(&monster[Map_Tile::Forest + 1], "��", 2, 5, 150, 15, 70);
	SettingMonsterData(&monster[Map_Tile::Forest + 2], "ȣ���� ", 3, 6, 200, 25, 90);

	SettingMonsterData(&monster[Map_Tile::Swamp], "���� ������", 1, 3, 50, 5, 20);
	SettingMonsterData(&monster[Map_Tile::Swamp + 1], "���� ŷ������", 2, 4, 80, 8, 40);
	SettingMonsterData(&monster[Map_Tile::Swamp + 2], "���� �� ", 3, 5, 400, 50, 180);
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
		cout << "Player �� �������� �̴�." << endl;
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

	// ���� ���� ������ ü�º���
	int resultCharacterLevel = spwanEnemy.GetCharacterLevel() + playerData->GetCharacterLevel();// *playerData.data.gameLevelCorrection);
	int resultMaxHP = static_cast<int>(spwanEnemy.GetMaxHP() + (resultCharacterLevel * 15));
	int resultMoney = static_cast<int>(spwanEnemy.GetMoney() * resultCharacterLevel);
	int resultExp = static_cast<int>(spwanEnemy.GetExp() * resultCharacterLevel);
	spwanEnemy.SettingCharacterData(resultCharacterLevel, resultMaxHP, resultExp, resultMoney);

	cout << "���� " << spwanEnemy.GetCharacterLevel() << "�� " << spwanEnemy.GetName() << " ��(��) ��Ÿ���� " << endl;
	cout << playerData->GetName() << " ��(��) ���� �غ� ����." << endl;

	while (true)
	{
		cout << spwanEnemy.GetName() << " ü�� : " << spwanEnemy.GetHP() << " / " << spwanEnemy.GetMaxHP() << endl;
		cout << playerData->GetName() << " ü�� : " << playerData->GetHP() << " / " << playerData->GetMaxHP() << endl;
		cout << "���� ���� �� �Է�(���� , ���� ,�� , 0(����) ,1(����) ,2(��) ,3(��������))" << endl;
		string input;
		cin >> input;
		playerData->SetInput(input);
		cout << endl;
		system("cls");

		if (playerData->GetInput() == "����" || playerData->GetInput() == "0")
		{
			playerData->SetRPSNum(0);
		}
		else if (playerData->GetInput() == "����" || playerData->GetInput() == "1")
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
		else if (playerData->GetInput() == "��" || playerData->GetInput() == "2")
		{
			playerData->SetRPSNum(2);
		}
		else if (playerData->GetInput() == "3")
		{
			
			damage = spwanEnemy.GetDamage();
			playerData->AddHP(-damage);
			cout << "������ ������ ������ �޾Ҵ�. " << endl;
			cout << playerData->GetName() << "�� " << damage << "�� �������� �޾Ҵ�. " << endl;
			if (playerData->GetHP() <= 0)
			{
				cout << playerData->GetName() << "��(��) " << spwanEnemy.GetName() << "���� ������ ���ߴ�." << endl;
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
			cout << "�߸� �Է���ϴ�. " << endl;
			cout << endl;
			continue;
		}

		// �� ���������� ����
		spwanEnemy.SetRPSNum(RandRange(3));

		// ���������� ���ڸ� ���ڿ��� ��ȯ
		playerData->SetInput(RPSintToString(playerData->GetRPSNum()));
		spwanEnemy.SetInput(RPSintToString(spwanEnemy.GetRPSNum()));

		//���������� ǥ��
		cout << playerData->GetName() << " : " << playerData->GetInput() << endl;
		cout << spwanEnemy.GetName() << " : " << spwanEnemy.GetInput() << endl;
		cout << endl;

		RPSResult = RPSWinCheck(playerData->GetRPSNum(), spwanEnemy.GetRPSNum());

		switch (RPSResult)
		{
		case RPSState::Win:
			damage = playerData->GetDamage();
			spwanEnemy.AddHP(-damage);
			cout << "���ݿ� �����ߴ�. " << endl;
			cout << spwanEnemy.GetName() << "���� " << damage << "�� �������� �־���. " << endl;
			break;
		case RPSState::Draw:
			cout << "������ ������ ��������. " << endl;
			break;
		case RPSState::Lose:
			damage = spwanEnemy.GetDamage();
			playerData->AddHP(-damage);
			cout << "���ݿ� �����ߴ�. " << endl;
			cout << playerData->GetName() << "�� " << damage << "�� �������� �޾Ҵ�. " << endl;
			break;
		case RPSState::Error:
			cout << " ���������� ��� ����" << endl;
			break;
		}

		if (spwanEnemy.GetHP() <= 0)
		{
			cout << spwanEnemy.GetName() << "��(��) óġ�ߴ�. " << endl;
			cout << spwanEnemy.GetMoney() << "���� " << spwanEnemy.GetExp() << "�� ����ġ�� �����." << endl;
			playerData->AddExp (spwanEnemy.GetExp());
			playerData->AddMoney(spwanEnemy.GetMoney());
			playerData->LevelUpCheck();
			_getch();
			system("cls");
			break;
		}

		if (playerData->GetHP() <= 0)
		{
			cout << playerData->GetName() << "��(��) " << spwanEnemy.GetName() << "���� ������ ���ߴ�." << endl;
			_getch();
			system("cls");
			return false;
		}
	}
	return true;
}
