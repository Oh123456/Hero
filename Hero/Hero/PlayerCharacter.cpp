#include "PlayerCharacter.h"
#include <iostream>
#include <string>
PlayerCharacter::PlayerCharacter() : upExp(40)
{

}
PlayerCharacter::~PlayerCharacter()
{

}

//������ üũ ����ġ�� �Ѿ��ٸ� ����������
void PlayerCharacter::LevelUpCheck()
{

	while (true)
	{


		if (upExp <= Exp)
		{
			Exp -= upExp;
			characterLevel++;
			maxHP = maxHP + (characterLevel * 4);
			AddHP(maxHP);
			std::cout << name << "��(��) " << characterLevel << "�� �������� �ߴ�." << std::endl;
			upExp = static_cast<int>(40 * (static_cast<float>(characterLevel) * 0.5f));
		}
		else
			break;
	}

}

