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
// whose call 0x00439E0C takes the disguised object.
class GameLogic
{
	char pad[0x38];
	unsigned int m_timestamp;
	char pad3C[0x40 - 0x3C];
	unsigned int m_frame;
	char pad44[0xB4 - 0x44];
	ObjectIdMap m_map;
	char padB5[0x178 - 0xB5];
	Rva00439E0C *m_manager178;

public:
	Object *findObjectByID(ObjectID id);
	Object *getFirstObject();	// 0x0023CAD2
	void destroyObject(Object *obj);	// 0x00242C09
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void rva00376E92(bool first, bool second);	// 0x00376E92
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	Rva00439E0C *getManager178() const { return m_manager178; }
};
