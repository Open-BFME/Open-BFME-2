#pragma once

// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class Drawable;
class Rva00439E0C;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

// The network code reads the command timestamp at +0x38 and Zero Hour's
// frame counter at +0x40 (ConnectionManager::update 0x004D342A, among others).
// StealthUpdate::disguiseAsObject (0x00373DF0) reads the manager at +0x178
// whose call 0x00439E0C takes the disguised object. The spell store's show
// (finishShowPurchaseScience 0x0043CB48) reads the end flag at +0x6D and
// the game mode at +0x110.
// The object list head is at +0xAC: getFirstObject (0x0023CAD2) returns it and
// prepareLogicForObjectLoad (0x00242C86) walks it inline.
// GameClient::update (0x0023BEE8) reads the byte at +0x125, next to the pause
// byte isGamePaused (0x0023CD97) returns from +0x124, and skips the drawable,
// terrain and display updates while it is set.
class GameLogic
{
	char pad[0x38];
	unsigned int m_timestamp;
	char pad3C[0x40 - 0x3C];
	unsigned int m_frame;
	char pad44[0x6D - 0x44];

public:
	bool m_6d; // +0x6D

private:
	char pad6E[0xAC - 0x6E];
	Object *m_firstObject; // +0xAC, the head getFirstObject returns
	char padB0[0xB4 - 0xB0];
	ObjectIdMap m_map;
	char padB5[0x110 - 0xB5];

public:
	int m_110; // +0x110

private:
	char pad114[0x125 - 0x114];
	bool m_flag125;
	char pad126[0x178 - 0x126];
	Rva00439E0C *m_manager178;

public:
	bool isInMultiplayerGame();	// 0x00042235
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);	// 0x0023CD9E
	Object *findObjectByID(ObjectID id);
	Object *getFirstObject();	// 0x0023CAD2
	void destroyObject(Object *obj);	// 0x00242C09
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void rva00376E92(bool first, bool second);	// 0x00376E92
	unsigned char isGamePaused();	// 0x0023CD97
	void deleteLoadScreen();	// 0x002423E3
	void processDestroyList();	// 0x002413DF
	void prepareLogicForObjectLoad();	// 0x00242C86
	bool getFlag125() const { return m_flag125; }
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	Rva00439E0C *getManager178() const { return m_manager178; }
};
