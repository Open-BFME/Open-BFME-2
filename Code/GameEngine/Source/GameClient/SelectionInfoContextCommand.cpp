// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// contextCommandForNewSelection, retail 0x0030ECD6 (767 bytes).
//
// Zero Hour's SelectionInfo.cpp body (GameEngine/Source/GameClient/
// SelectionInfo.cpp) carried to BFME 2. Target facts read from the retail
// body: the kind-of tests are inline reads of the template's flag words at
// +0x108 (infantry bit 8, structure bit 7, crate bit 48); Drawable::getObject
// is +0xFC and Object::getTeam +0x304; TheInGameUI keeps force-attack,
// force-move and prefer-selection at +0x8B8..+0x8BA; TheGlobalData's
// alternate-mouse flag is +0x5C; GameClient::evaluateContextCommand is
// virtual slot 18. BFME 2 adds one test under the alternate mouse: the GUI
// command InGameUI slot 48 returns must exist and not be of type 10.
// Drawable::getPosition and ActionManager::canPlayerGarrison are called out of
// line, as retail does. The Zero Hour headers disagree with these offsets, so
// this unit declares only the views the body needs.
#include <list>

namespace _STL {
// Compare nodes locally so this TU does not emit an iterator-base wrapper.
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define TRUE true
#define FALSE false

enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum { KINDOF_STRUCTURE = 7, KINDOF_INFANTRY = 8, KINDOF_CRATE = 48 };
enum { CONTEXT_EVALUATE_ONLY = 2 };

struct Coord3D;
class Team;
class Player
{
public:
	Relationship getRelationship(const Team *that) const;
};

struct SelectionTemplateView
{
	char m_pad[0x108];
	UnsignedInt m_kindOf[2];	// +0x108 kind-of flag words
};

class Object
{
public:
	Bool isLocallyControlled() const;
	const Team *getTeam() const { return m_team; }
	// The kind-of test reads the template's flag word and tests the bit in
	// place (test ah,1 / test byte [..],0x80), never materializing a Bool.
	__forceinline UnsignedInt isKindOf(Int bit) const
	{
		return m_template->m_kindOf[bit >> 5] & (1u << (bit & 31));
	}

private:
	void *m_vtbl;
	const SelectionTemplateView *m_template;	// +0x04
	char m_pad08[0x304 - 8];
	Team *m_team;	// +0x304
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
	const Coord3D *getPosition() const;

private:
	char m_pad[0xFC];
	Object *m_object;	// +0xFC
};

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

struct SelectionInfo
{
	Int currentCountEnemies;
	Int currentCountCivilians;
	Int currentCountMine;
	Int currentCountMineInfantry;
	Int currentCountMineBuildings;
	Int currentCountFriends;

	Int newCountEnemies;
	Int newCountCivilians;
	Int newCountMine;
	Int newCountMineBuildings;
	Int newCountFriends;
	Int newCountGarrisonableBuildings;
	Int newCountCrates;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }

private:
	char m_pad[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

class ActionManager
{
public:
	Bool canPlayerGarrison(const Player *player, const Object *target, CommandSourceType commandSource);
};
extern ActionManager *TheActionManager;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct SelectionGlobalDataView
{
	char m_pad[0x5C];
	Bool m_useAlternateMouse;	// +0x5C
};
#define TheGlobalData ((const SelectionGlobalDataView *)TheWritableGlobalData)

#define SELECTION_VSLOT(n) virtual void vslot##n();

struct SelectionGUICommandView
{
	char m_pad[0x14];
	Int m_commandType;	// +0x14
};

class InGameUI;
extern InGameUI *TheInGameUI;
class SelectionInGameUIView
{
public:
	SELECTION_VSLOT(00) SELECTION_VSLOT(01) SELECTION_VSLOT(02) SELECTION_VSLOT(03)
	SELECTION_VSLOT(04) SELECTION_VSLOT(05) SELECTION_VSLOT(06) SELECTION_VSLOT(07)
	SELECTION_VSLOT(08) SELECTION_VSLOT(09) SELECTION_VSLOT(10) SELECTION_VSLOT(11)
	SELECTION_VSLOT(12) SELECTION_VSLOT(13) SELECTION_VSLOT(14) SELECTION_VSLOT(15)
	SELECTION_VSLOT(16) SELECTION_VSLOT(17) SELECTION_VSLOT(18) SELECTION_VSLOT(19)
	SELECTION_VSLOT(20) SELECTION_VSLOT(21) SELECTION_VSLOT(22) SELECTION_VSLOT(23)
	SELECTION_VSLOT(24) SELECTION_VSLOT(25) SELECTION_VSLOT(26) SELECTION_VSLOT(27)
	SELECTION_VSLOT(28) SELECTION_VSLOT(29) SELECTION_VSLOT(30) SELECTION_VSLOT(31)
	SELECTION_VSLOT(32) SELECTION_VSLOT(33) SELECTION_VSLOT(34) SELECTION_VSLOT(35)
	SELECTION_VSLOT(36) SELECTION_VSLOT(37) SELECTION_VSLOT(38) SELECTION_VSLOT(39)
	SELECTION_VSLOT(40) SELECTION_VSLOT(41) SELECTION_VSLOT(42) SELECTION_VSLOT(43)
	SELECTION_VSLOT(44) SELECTION_VSLOT(45) SELECTION_VSLOT(46) SELECTION_VSLOT(47)
	virtual const SelectionGUICommandView *getGUICommand() const;	// slot 48 (+0xC0)

	Bool isInForceAttackMode() const { return m_forceAttack; }
	Bool isInForceMoveToMode() const { return m_forceMove; }
	Bool isInPreferSelectionMode() const { return m_preferSelection; }

private:
	char m_pad[0x8B8 - 4];
	Bool m_forceAttack;	// +0x8B8
	Bool m_forceMove;	// +0x8B9
	Bool m_preferSelection;	// +0x8BA
};
#define TheSelectionUI ((SelectionInGameUIView *)TheInGameUI)

class GameClient;
extern GameClient *TheGameClient;
class SelectionGameClientView
{
public:
	SELECTION_VSLOT(00) SELECTION_VSLOT(01) SELECTION_VSLOT(02) SELECTION_VSLOT(03)
	SELECTION_VSLOT(04) SELECTION_VSLOT(05) SELECTION_VSLOT(06) SELECTION_VSLOT(07)
	SELECTION_VSLOT(08) SELECTION_VSLOT(09) SELECTION_VSLOT(10) SELECTION_VSLOT(11)
	SELECTION_VSLOT(12) SELECTION_VSLOT(13) SELECTION_VSLOT(14) SELECTION_VSLOT(15)
	SELECTION_VSLOT(16) SELECTION_VSLOT(17)
	virtual Int evaluateContextCommand(Drawable *draw, const Coord3D *pos, Int cmdType);	// slot 18 (+0x48)
};
#define TheSelectionClient ((SelectionGameClientView *)TheGameClient)

Bool contextCommandForNewSelection(const DrawableList *currentlySelectedDrawables,
	const DrawableList *newlySelectedDrawables,
	SelectionInfo *outSelectionInfo,
	Bool selectionIsPoint)
{
	if (!(currentlySelectedDrawables && newlySelectedDrawables && outSelectionInfo))
		return FALSE;

	Bool forceFire = TheSelectionUI->isInForceAttackMode();
	Bool forceMove = TheSelectionUI->isInForceMoveToMode();

	if (forceFire || forceMove) {
		return FALSE;
	}

	Player *localPlayer = ThePlayerList->getLocalPlayer();
	DrawableListCIt it;
	for (it = currentlySelectedDrawables->begin(); it != currentlySelectedDrawables->end(); ++it) {
		if (!(*it)) {
			continue;
		}

		Object *obj = (*it)->getObject();
		if (!obj) {
			continue;
		}

		if (obj->isLocallyControlled()) {
			++outSelectionInfo->currentCountMine;
			if (obj->isKindOf(KINDOF_INFANTRY)) {
				++outSelectionInfo->currentCountMineInfantry;
			} else if (obj->isKindOf(KINDOF_STRUCTURE)) {
				++outSelectionInfo->currentCountMineBuildings;
			}
		} else {
			Relationship rel = localPlayer->getRelationship(obj->getTeam());
			if (rel == ALLIES) {
				++outSelectionInfo->currentCountFriends;
			} else if (rel == ENEMIES) {
				++outSelectionInfo->currentCountEnemies;
			} else if (rel == NEUTRAL) {
				++outSelectionInfo->currentCountCivilians;
			}
		}
	}

	Drawable *newMine = NULL;
	Drawable *newFriendly = NULL;
	Drawable *newEnemy = NULL;
	Drawable *newCivilian = NULL;

	for (it = newlySelectedDrawables->begin(); it != newlySelectedDrawables->end(); ++it) {
		if (!(*it)) {
			continue;
		}

		Object *obj = (*it)->getObject();
		if (!obj) {
			continue;
		}

		if (TheActionManager->canPlayerGarrison(localPlayer, obj, CMD_FROM_PLAYER)) {
			++outSelectionInfo->newCountGarrisonableBuildings;
		}
		if (obj->isKindOf(KINDOF_CRATE)) {
			++outSelectionInfo->newCountCrates;
		}

		if (obj->isLocallyControlled()) {
			++outSelectionInfo->newCountMine;
			newMine = *it;
			if (obj->isKindOf(KINDOF_STRUCTURE)) {
				++outSelectionInfo->newCountMineBuildings;
			}
		} else {
			Relationship rel = localPlayer->getRelationship(obj->getTeam());
			if (rel == ALLIES) {
				newFriendly = *it;
				++outSelectionInfo->newCountFriends;
			} else if (rel == ENEMIES) {
				newEnemy = *it;
				++outSelectionInfo->newCountEnemies;
			} else if (rel == NEUTRAL) {
				newCivilian = *it;
				++outSelectionInfo->newCountCivilians;
			}
		}
	}

	if (outSelectionInfo->currentCountEnemies > 0) {
		// If we have an enemy selected, there are no context sensitive commands
		return FALSE;
	}

	if (outSelectionInfo->currentCountFriends > 0) {
		return FALSE;
	}

	if (outSelectionInfo->currentCountCivilians > 0) {
		return FALSE;
	}

	if (TheGlobalData->m_useAlternateMouse) {
		const SelectionGUICommandView *command = TheSelectionUI->getGUICommand();
		if (!command || command->m_commandType == 10)
			return FALSE;
	}

	if (outSelectionInfo->currentCountMine > 0) {
		if (outSelectionInfo->newCountEnemies > 0) {
			if (outSelectionInfo->newCountEnemies == 1 && selectionIsPoint) {
				return TheSelectionClient->evaluateContextCommand(newEnemy, newEnemy->getPosition(), CONTEXT_EVALUATE_ONLY) != 0;
			}

			return selectionIsPoint;
		}

		if (outSelectionInfo->newCountMine > 0) {
			if (outSelectionInfo->newCountMine == 1 && selectionIsPoint && !TheSelectionUI->isInPreferSelectionMode()) {
				return TheSelectionClient->evaluateContextCommand(newMine, newMine->getPosition(), CONTEXT_EVALUATE_ONLY) != 0;
			}

			return FALSE;
		}

		if (outSelectionInfo->newCountFriends > 0) {
			if (outSelectionInfo->newCountFriends == 1 && selectionIsPoint) {
				return TheSelectionClient->evaluateContextCommand(newFriendly, newFriendly->getPosition(), CONTEXT_EVALUATE_ONLY) != 0;
			}
			return FALSE;
		}

		if (outSelectionInfo->currentCountMineInfantry > 0 && outSelectionInfo->newCountGarrisonableBuildings == 1) {
			return TRUE;
		}

		if (outSelectionInfo->newCountCivilians > 0) {
			if (outSelectionInfo->newCountCivilians == 1 && selectionIsPoint) {
				return TheSelectionClient->evaluateContextCommand(newCivilian, newCivilian->getPosition(), CONTEXT_EVALUATE_ONLY) != 0;
			}
			return FALSE;
		}

		if (outSelectionInfo->newCountCrates > 0) {
			return (outSelectionInfo->newCountCrates == 1 && selectionIsPoint);
		}
	}

	if (outSelectionInfo->currentCountMine == 0) {
		return FALSE;
	}

	return selectionIsPoint;
}
