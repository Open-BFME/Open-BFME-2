// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00399165@CastleMemberBehavior@@UAEXPBVDict@@@Z, retail 0x00399165..
// 0x0039922D (200 bytes, EH, RET 4): slot 45 of CastleMemberBehavior's
// +0x0C interface table, so it runs on that subobject and reads the owning
// object at +0x08 (-4 here). Given a property dictionary, a castle piece
// reads its objectBaseName (rowed Dict::getAsciiString, pinned
// StaticNameKey::key) and, when it is present, walks TheGameLogic's object
// list (rowed getFirstObject; name at +0x88, next at +0x8C) for the object of
// that name (rowed AsciiString compare). That object's CastleBehavior (rowed
// Object::findModule with the rowed CastleBehavior key 0x003955DA) registers
// this piece's object (rowed registerOwnedObject) and its +0x34 state becomes
// 4. WorldBuilder's twin (0x00EC2940) is unnamed, so the slot keeps an
// address-derived name.

#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_objectBaseName;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists = 0) const;
};

class Module;
class CastleMemberBehavior;

class Object
{
	friend class CastleMemberBehavior;

public:
	const AsciiString &getName() const { return m_name; }
	Object *getNextObject() const { return m_next; }

protected:
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad00[0x88];
	AsciiString m_name;						// +0x88
	Object *m_next;							// +0x8C
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
	void registerOwnedObject(Object *obj);

	unsigned char m_pad00[0x34];
	int m_state34;							// +0x34
};

class ModuleData;

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	Object *getObject() const { return m_object; }

	const ModuleData *m_moduleData;			// +0x04
	Object *m_object;						// +0x08
};

class BehaviorModuleInterface
{
public:
#define V(n) virtual void b##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44)
#undef V
	virtual void rva00399165(const Dict *properties);	// slot 45
};

class CastleMemberBehavior : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual void rva00399165(const Dict *properties);
};

void CastleMemberBehavior::rva00399165(const Dict *properties)
{
	if (!properties)
		return;
	bool exists = false;
	AsciiString baseName = properties->getAsciiString(TheKey_objectBaseName, &exists);
	if (!exists)
		return;
	Object *obj;
	for (obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
		if (obj->getName().compare(baseName) == 0)
			break;
	if (obj)
	{
		CastleBehavior *castle = (CastleBehavior *)obj->findModule(CastleBehavior::rva0003955DA());
		if (castle && getObject())
		{
			castle->registerOwnedObject(getObject());
			castle->m_state34 = 4;
		}
	}
}
