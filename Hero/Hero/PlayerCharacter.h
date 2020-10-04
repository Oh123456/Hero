#pragma once
#include "CharacterData.h"

class PlayerCharacter :public CharacterData
{
public:
	PlayerCharacter();
	~PlayerCharacter();



	void LevelUpCheck();

private:
	int upExp;
};

