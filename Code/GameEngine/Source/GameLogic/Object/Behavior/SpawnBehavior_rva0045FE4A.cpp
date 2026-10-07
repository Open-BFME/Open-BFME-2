// ?rva0045FE4A@SpawnBehavior@@UAEHP6AHPAVObject@@PAX@Z1@Z
// Walk the spawn-ID list at this+0x20, resolve each entry through
// TheGameLogic->findObjectByID, drop nulls and entries failing the 0x004A1828
// filter, and run the callback on the survivors. Returns 0 on the first
// callback false, else 1. Identity: the slot at 0x00842598 of the
// SpawnBehavior sub-object vftable at +0x2C (spawn IDs +0x4C = this +0x20).
// The name is address-derived.
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4; MSVC calls the out-of-line copy 0x00049DC5, and only the
// inline declaration gives retail's register assignment.
// cl: /O1 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_OBJECT_ID)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0xB4];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

struct Rva004A1828Owner;
int Rva004A1828Get(struct Rva004A1828Owner *owner);

typedef int (__cdecl *Rva0045FE4ACallback)(Object *obj, void *data);

class SpawnBehavior
{
public:
	virtual int rva0045FE4A(Rva0045FE4ACallback func, void *data);

private:
	unsigned char m_pad04[0x20 - 0x04];
	_STL::list<ObjectID> m_spawnIDs;
};

int SpawnBehavior::rva0045FE4A(Rva0045FE4ACallback func, void *data)
{
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj && Rva004A1828Get((struct Rva004A1828Owner *)obj))
		{
			if (!func(obj, data))
				return 0;
		}
	}
	return 1;
}