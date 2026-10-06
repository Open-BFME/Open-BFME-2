// cl: /DNDEBUG /MD /GX-
// ?Rva0052C06CGet@@YAHPAVGameInfo@@@Z @0x0052C06C 92B: random unlocked untaken color via MultiplayerSettings and GameInfo.
// Evidence: TheMultiplayerSettings +0x40 +0x38 refill, GetGameLogicRandomValue 0-A8 file, getColor +0x3C check, isColorTaken -1 loop, caller 0x0052C629, neighbours Rva0052BF33DestroyTagged.
class MultiplayerColorDefinition {
public:
	unsigned char m_pad[0x3C];
	bool m_3C;
};
class MultiplayerSettings {
public:
	unsigned char m_pad[0x38];
	int m_38;
	int m_3C;
	int m_40;
	MultiplayerColorDefinition *getColor(int i);
};
extern MultiplayerSettings *TheMultiplayerSettings;
class GameInfo {
public:
	bool isColorTaken(int color, int ignore) const;
};
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
static char s_file[] = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp";
int Rva0052C06CGet(GameInfo *game)
{
loop:
	int *pNum = (int *)((char *)TheMultiplayerSettings + 0x40);
	if (*pNum == 0)
		*pNum = *(int *)((char *)TheMultiplayerSettings + 0x38);
	int num = *pNum;
	int r = GetGameLogicRandomValue(0, num - 1, s_file, 168);
	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(r);
	if (def->m_3C == 0)
		goto set;
	if (!game->isColorTaken(r, -1))
		goto ok;
set:
	r = -1;
ok:
	if (r == -1)
		goto loop;
	return r;
}
