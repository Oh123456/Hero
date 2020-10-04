#include "CharacterData.h"
#include "RPSGameMode.h"


CharacterData::CharacterData() : Exp(0), RPSNum(0), attackValue(10)
{

}

CharacterData::~CharacterData()
{

}

int CharacterData::GetDamage()
{
	int result = static_cast<int>(characterLevel * 5) + attackValue;
	return result;
}

void CharacterData::AddHP(int value)
{
	HP += value;
	if (HP >= maxHP)
		HP = maxHP;
	if (HP <= 0)
		HP = 0;
}



std::string CharacterData::RPSintToString(int RPS)
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