#pragma once

class GamePlayStatics
{
public:
	static void SetGameMode(class GameMode* gameMode) { worldGameMode = gameMode; }
	static class GameMode*  GetGameMode() { return worldGameMode; }

private:
	static class GameMode* worldGameMode;
};

