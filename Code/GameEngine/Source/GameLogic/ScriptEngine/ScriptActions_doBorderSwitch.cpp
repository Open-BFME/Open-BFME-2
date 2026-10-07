// cl: /DNDEBUG /MD /EHsc
//
// ?doBorderSwitch@ScriptActions@@IAEXH@Z,
// retail 0x003BC3A8, 101 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp,
// ScriptActions::doBorderSwitch): the observer player keeps the map permanently
// revealed across border switches, so undo the permanent reveal, switch the
// active boundary, then re-reveal. The retail body follows the reference source
// exactly: the name key resolves through the matched 0x148E1A row, the player
// lookup through the 0x2A7A41 pin, the boundary switch through the 0x28069E
// pin, and both shroud calls dispatch through the 8-byte this-adjust thunks at
// 0x7397B0/0x739790 (pinned).

typedef int Int;

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	// Matched callers use the target player index at +0x54 directly;
	// avoid an out-of-line getter shared with incompatible layouts.
	unsigned char m_pad[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};

extern PlayerList *ThePlayerList;

class PartitionManager
{
public:
	void undoRevealMapForPlayerPermanently(Int playerIndex);
	void revealMapForPlayerPermanently(Int playerIndex);
};

extern PartitionManager *TheShroudManager;

class TerrainLogic
{
public:
	void setActiveBoundary(Int newActiveBoundary);
};

extern TerrainLogic *TheTerrainLogic;

class ScriptActions
{
protected:
	void doBorderSwitch(Int borderToUse);
};

// ?doBorderSwitch@ScriptActions@@IAEXH@Z
void ScriptActions::doBorderSwitch(Int borderToUse)
{
	/*
	 *	The observer player always has to have the map completely revealed for him.
	 *	Border switching doesn't play nice with the permanent map reveal so for the
	 *	observer player we need to undo the old permanent reveal, switch map borders,
	 *	and re-reveal the map. BGC
	*/
	Int observerPlayerIndex = -1;
	if (ThePlayerList != NULL)
	{
		Player *observer = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey("ReplayObserver"));

		if (observer != NULL) {
			observerPlayerIndex = observer->m_playerIndex;
		}
	}

	if (observerPlayerIndex != -1)
	{
		TheShroudManager->undoRevealMapForPlayerPermanently(observerPlayerIndex);
	}

	TheTerrainLogic->setActiveBoundary(borderToUse);

	if (observerPlayerIndex != -1)
	{
		TheShroudManager->revealMapForPlayerPermanently(observerPlayerIndex);
	}
}
