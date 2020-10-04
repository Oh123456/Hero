#include "PlayerCharacter.h"
#include <iostream>
#include <string>
PlayerCharacter::PlayerCharacter() : upExp(40)
{

}
PlayerCharacter::~PlayerCharacter()
{

}

//레벨업 체크 겸험치가 넘었다면 레벨업까지
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
			std::cout << name << "은(는) " << characterLevel << "로 레벨업을 했다." << std::endl;
			upExp = static_cast<int>(40 * (static_cast<float>(characterLevel) * 0.5f));
		}
		else
			break;
	}

}

