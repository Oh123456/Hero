#include "RPSGameMode.h"
#include <iostream>
#include <string>

#include "CharacterData.h"
#include "MapData.h"


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