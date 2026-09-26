// cl: /O1 /DNDEBUG /MD /GX-
// Rva004C8F94_ParseSpawnObject (retail 0x004C8F94, 67 bytes). Reads a
// required first token through the rowed getNextToken at 0x002DF97, then
// loops OrNull tokens through the rowed getNextTokenOrNull at 0x002DEED:
// each resolves through the pinned findObjectCreationList at 0x001F07B8
// on TheObjectCreationListStore, stashed in the dead instance slot (the
// instance pointer is already consumed into the vector base) and pushed
// through the rowed vector<ModuleData>::push_back fold at 0x004DFCB0 onto
// the vector at instance +0x14 (the element rides the 4B-pointer fold;
// the store really holds ObjectCreationList pointers). Serves the
// SpawnObject entry of the table at 0x85EA10 (sibling FX plus ReloadTime).
// The callback name stays address-derived; the owning struct is BFME2-new
// (no BFME1 donor).

class ModuleData
{
};

class ObjectCreationList
{
};

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name);
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	static void Rva004C8F94_ParseSpawnObject(INI *ini, void *instance, void *store, const void *userData);
};

extern ObjectCreationListStore *TheObjectCreationListStore;

// ?Rva004C8F94_ParseSpawnObject@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004C8F94_ParseSpawnObject(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (token == 0)
		return;
	_STL::vector<const ModuleData *> *vec = (_STL::vector<const ModuleData *> *)((char *)instance + 0x14);
	do {
		instance = (void *)TheObjectCreationListStore->findObjectCreationList(token);
		vec->push_back((const ModuleData *&)instance);
		token = ini->getNextTokenOrNull(0);
	} while (token != 0);
}
