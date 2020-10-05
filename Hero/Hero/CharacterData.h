#pragma once
#include<string>




class CharacterData
{
public:
	CharacterData();
	~CharacterData();

	// 데미지
	int GetDamage();
	//체력 증감
	virtual void AddHP(int value);
	void AddExp(int value) { Exp += value; }
	void AddMoney(int value) { money += value; }
	std::string RPSintToString(int RPS);

	void SettingCharacterData(std::string name, int characterLevel, int attackValue, int maxHP, int Exp, int money);
	void SettingCharacterData(int characterLevel, int maxHP, int Exp, int money);

	inline void SetName(std::string name) { this->name = name; }
	inline void SetInput(std::string input) { this->input = input; }
	inline void SetMoney(int Value) { money = Value; }
	inline void SetMaxHP(int Value) { maxHP = Value; }
	inline void SetHP(int Value) { HP = Value; }
	inline void SetLevel(int Value) { characterLevel = Value; }
	inline void SetAttackvalue(int Value) { attackValue = Value; }
	inline void SetRPSNum(int Value) { RPSNum = Value; }

	inline std::string GetName() { return name; }
	inline std::string GetInput() { return input;}
	inline int GetMaxHP() { return maxHP; }
	inline int GetCharacterLevel() { return characterLevel; }
	inline int GetMoney() { return money; }
	inline int GetExp() { return Exp; }
	inline int GetHP() { return HP; }
	inline int GetRPSNum() { return RPSNum; }

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

