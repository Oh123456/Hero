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
		return "가위";
	case RPS::Rock:
		return "바위";
	case RPS::Paper:
		return "보";
	default:
		return "에러";
	}
}