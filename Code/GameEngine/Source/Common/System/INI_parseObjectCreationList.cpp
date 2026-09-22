// cl: /O1 /DNDEBUG /MD /GX /Oi-
//
// ?parseObjectCreationList@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338A6F, 30 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseObjectCreationList (Common/INI/INI.cpp): store whatever
// TheObjectCreationListStore (0x00DFDCCC) finds for the token, even NULL.

class ObjectCreationList;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name);
};

extern ObjectCreationListStore *TheObjectCreationListStore;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseObjectCreationList@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseObjectCreationList(INI *ini, void *, void *store, const void *)
{
	*(const ObjectCreationList **)store = TheObjectCreationListStore->findObjectCreationList(ini->getNextToken());
}
