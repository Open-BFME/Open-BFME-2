// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?lookupUnitByValue@Rva00358752Opaque@@QAEPAVObject@@VAsciiString@@@Z
// Retail 0x00358752, 257 bytes. this is the ScriptEngine (named-object
// fields at +0x190B8 and +0x1A114..+0x1A124); the owner keeps the pinned
// opaque name. By-value name lookup behind ScriptEngine::getUnitNamed
// (0x003588E7) and the NAMED_* script actions:
//   "<This Object>"  -> the calling object (+0x1A114), else the condition
//                       object (+0x1A11C);
//   otherwise resolve the name (0x002046C0), look the (resolved, name) pair
//   up in the map at +0x190B8 (find 0x0032C07C) and return the object for
//   the ObjectID at node+0x18; failing that, scan the (name, Object*) vector
//   at +0x1A120..+0x1A124 for an exact name.
// The resolve/key/find helpers are the ones getTeamNamed (0x003584E9) uses.

#include "ascii_string.h"
#include <utility>
#include <vector>

class Object;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id) throw();
};
extern GameLogic *TheGameLogic;

typedef _STL::pair<const AsciiString, AsciiString> Rva00358752KeyPair;

// The rowed two-string key ctor (0x0002C4FD); the key dies through the rowed
// pair<const AsciiString, AsciiString> destructor (0x0002C0C0).
struct Rva0002C4FD
{
	Rva0002C4FD(const StringBase<char> &, const StringBase<char> &);
	~Rva0002C4FD()
	{
		((Rva00358752KeyPair *)this)->~Rva00358752KeyPair();
	}
	char storage[sizeof(Rva00358752KeyPair)];
};

struct TeamMapNode
{
	unsigned char pad[0x18];
	void *value; // +0x18
};

class Rva0032C07COwner
{
public:
	TeamMapNode *find(Rva0002C4FD &key) throw();
	TeamMapNode *m_header;
};

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

struct Rva00358752NamedObject
{
	AsciiString name;
	Object *object;
};

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);

private:
	unsigned char pad_00000[0x190B8];
	Rva0032C07COwner m_namedObjectMap; // +0x190B8
	unsigned char pad_190BC[0x1A114 - 0x190BC];
	Object *m_callingObject; // +0x1A114
	unsigned char pad_1A118[4];
	Object *m_conditionObject; // +0x1A11C
	_STL::vector<Rva00358752NamedObject> m_namedObjects; // +0x1A120
};

Object *Rva00358752Opaque::lookupUnitByValue(AsciiString name)
{
	if (name.compare("<This Object>") == 0) {
		if (m_callingObject)
			return m_callingObject;
		return m_conditionObject;
	}

	{
		AsciiString normalized = ((Rva002046C0Owner *)this)->resolveName(name);
		Rva0002C4FD key(*(const StringBase<char> *)&normalized,
			*(const StringBase<char> *)&name);
		TeamMapNode *node = m_namedObjectMap.find(key);
		if (node != m_namedObjectMap.m_header)
			return TheGameLogic->findObjectByID((ObjectID)(int)node->value);
	}

	for (_STL::vector<Rva00358752NamedObject>::iterator entry = m_namedObjects.begin();
		entry != m_namedObjects.end(); ++entry) {
		if (name.compare(entry->name) == 0)
			return entry->object;
	}
	return 0;
}
