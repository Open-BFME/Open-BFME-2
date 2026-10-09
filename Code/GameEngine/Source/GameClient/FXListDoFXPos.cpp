// cl: /Oy- /DNDEBUG /MD /GX-
//
// ?doFXPos@FXList@@QBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
// retail 0x001E296E, 168 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/FXList.cpp,
// FXList::doFXPos): per-bone effect applier walking the nugget list. The
// retail body follows that role with BFME2 additions: an alias-name chain
// resolved through the findFXList row, a disabled-flag early-out, a shroud
// pre-check through the pinned 0x7397F0 thunk, and a per-nugget gate plus a
// consumption flag at +0x144. Virtual slots need no pins.

typedef int Int;

#define NULL 0

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
	float m[12];
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex, const Coord3D *pos) const;
};

extern PartitionManager *TheShroudManager;
// TheShroudManager: matched references place it at VA 0xdfe74c (zero-filled .bss).
PartitionManager * TheShroudManager;

class AsciiString
{
public:
	void *m_data;
};

class FXList;

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

class Player
{
public:
	__declspec(dllimport) __forceinline Int getPlayerIndex() const { return m_playerIndex; }

	char m_pad[0x54];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

	char m_pad[0x10];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	const Coord3D *getPosition() const { return &m_pos; }

	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
	char m_pad38[0x4C4 - (0x38 + sizeof(Coord3D))];
	void *m_shroudClearingBehavior; // +0x4C4
};

class FXNugget
{
public:
	virtual void slot00() = 0;
	virtual void applyEffect(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) = 0;
	virtual void slot0C() = 0;
	virtual bool testNugget(const Object *primary, const Object *secondary) = 0;

	char m_pad[0x140];
	bool m_consumed;
};

struct FXNuggetNode
{
	FXNuggetNode *m_next;
	void *m_reserved;
	FXNugget *m_nugget;
};

class FXList
{
public:
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) const;
	void doFXObj(const Object *primary, const Object *secondary) const;

private:
	void *m_head;
	FXNuggetNode *m_nuggets;
	void *m_unknown8;
	AsciiString m_aliasName;
	bool m_disabled;
	char m_pad11[0x13];
	bool m_hasAlias;
};

// ?doFXPos@FXList@@QBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void FXList::doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) const
{
	const FXList *list = this;
	while (list->m_hasAlias) {
		const char *alias = list->m_aliasName.m_data != NULL ? (const char *)list->m_aliasName.m_data + 8 : "";
		const FXList *found = TheFXListStore->findFXList(alias);
		if (found == NULL)
			break;
		list = found;
	}
	if (!list->m_disabled) {
		if (pos != NULL) {
			int key = ThePlayerList->getLocalPlayer()->getPlayerIndex();
			if (TheShroudManager->getShroudStatusForPlayer(key, pos) != CELLSHROUD_CLEAR)
				return;
		}
	}
	for (FXNuggetNode *node = list->m_nuggets->m_next; node != list->m_nuggets; node = node->m_next) {
		FXNugget *nugget = node->m_nugget;
		if (nugget->testNugget(0, 0)) {
			nugget->applyEffect(pos, mtx, speed, secondary);
			if (nugget->m_consumed)
				return;
		}
	}
}

// ?doFXObj@FXList@@QBEXPBVObject@@0@Z
void FXList::doFXObj(const Object *primary, const Object *secondary) const
{
	const FXList *list = this;
	while (list->m_hasAlias) {
		const char *alias = list->m_aliasName.m_data != NULL ? (const char *)list->m_aliasName.m_data + 8 : "";
		const FXList *found = TheFXListStore->findFXList(alias);
		if (found == NULL)
			break;
		list = found;
	}
	if (!list->m_disabled && primary != NULL) {
		if (primary->m_shroudClearingBehavior != NULL) {
			if (primary->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex()) > 2)
				return;
		} else if (TheShroudManager->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex(), primary->getPosition()) != CELLSHROUD_CLEAR) {
			return;
		}
	}
	for (FXNuggetNode *node = list->m_nuggets->m_next; node != list->m_nuggets; node = node->m_next) {
		FXNugget *nugget = node->m_nugget;
		if (nugget->testNugget(primary, secondary)) {
			nugget->doFXObj(primary, secondary);
			if (nugget->m_consumed)
				return;
		}
	}
}
