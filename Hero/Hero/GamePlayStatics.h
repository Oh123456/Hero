#pragma once

class GamePlayStatics
{
public:
	static void SetGameMode(class GameMode* gameMode) { worldGameMode = gameMode; }
	static void SetPlayerData(class CharacterData* playerData) { PlayerCharacter = playerData; }

	static class GameMode*  GetGameMode() { return worldGameMode; }
	static class CharacterData* GetPlayerData() { return PlayerCharacter; }

private:
	static class GameMode* worldGameMode;
	static class CharacterData* PlayerCharacter;
};

