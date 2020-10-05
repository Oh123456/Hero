#pragma once
#include<string>




class CharacterData
{
public:
	CharacterData();
	~CharacterData();

	// ������
	int GetDamage();
	//ü�� ����
	void AddHP(int value);
	std::string RPSintToString(int RPS);

	inline void SetName(std::string name) { this->name = name; }
	inline void SetMoney(int Value) { money = Value; }
	inline void SetMaxHP(int Value) { maxHP = Value; }
	inline void SetLevel(int Value) { characterLevel = Value; }
	inline void SetAttackvalue(int Value) { attackValue = Value; }

	inline std::string GetName() { return name; }
	inline std::string* GetInput() { return &input;}
	inline int GetMaxHP() { return maxHP; }

protected:
	std::string name;
	std::string input;
	int attackValue;
	int RPSNum;
	int HP;
	int maxHP;
	int money;
	int characterLevel;
	int Exp;
};

