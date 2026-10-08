// cl: /DNDEBUG /MD /EHsc
//
// ?getSciencePurchaseCost@ScienceStore@@QBEHW4ScienceType@@@Z @0x1FF3DC (86B):
// findScienceInfo (matched 0x1FF3AD) plus the BFME2 online-mode gate: the
// multiplayer predicate is called first, the mode dword (+0x110) is only read
// on the false path, and modes 2/3 (with TheRecorder::isMultiplayer for a
// replay) select the alt purchase cost at +0x2C over +0x28. The conditional
// mode load is what keeps retail's `mov esi,[esi+0x110]` coalescing and the
// load below the isInMultiplayerGame branch.
enum ScienceType { SCIENCE_INVALID = -1 };

class ScienceInfo
{
	char m_pad[0x28];
public:
	int m_sciencePurchasePointCost;
	int m_sciencePurchasePointCostMP;
};

class GameLogic
{
	char m_pad[0x110];
public:
	int m_gameMode;
	bool isInMultiplayerGame();
};

class RecorderClass
{
public:
	bool isMultiplayer();
};

extern GameLogic *TheGameLogic;
extern struct Bfme939Helper *g_bfme939Helper;

class ScienceStore
{
	const ScienceInfo *findScienceInfo(ScienceType st) const;
public:
	int getSciencePurchaseCost(ScienceType st) const;
};

// ?getSciencePurchaseCost@ScienceStore@@QBEHW4ScienceType@@@Z
int ScienceStore::getSciencePurchaseCost(ScienceType st) const
{
	const ScienceInfo *si = findScienceInfo(st);
	if (si)
	{
		GameLogic *game = TheGameLogic;
		const bool mp = game->isInMultiplayerGame();
		int mode = 0;
		if (!mp)
			mode = game->m_gameMode;
		if (mp || mode == 2 ||
		    (mode == 3 && (*(RecorderClass **)&g_bfme939Helper) && (*(RecorderClass **)&g_bfme939Helper)->isMultiplayer()))
			return si->m_sciencePurchasePointCostMP;
		return si->m_sciencePurchasePointCost;
	}
	return 0;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?TheRecorder@@3PAVRecorderClass@@A=?g_bfme939Helper@@3PAUBfme939Helper@@A")
