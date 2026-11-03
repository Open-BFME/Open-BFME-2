// cl: /DNDEBUG /MD /EHsc
// platformsdk
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

#include <windows.h>

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

class PartitionManager
{
public:
	void undoRevealMapForPlayerPermanently(Int playerIndex);
	void revealMapForPlayerPermanently(Int playerIndex);
};

extern PartitionManager *TheShroudManager;

#include "../../../Include/GameLogic/TerrainLogic.h"

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
