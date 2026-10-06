// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002ECAF, 31 bytes.
// Dedicated frameless TU (twin of INI_parseIndexList.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseLookupList): store the value of the next token in the userData
// lookup list. BFME2 is the same one-liner through the member scanLookupList
// (pinned at 0x2BD85; BFME2 member-ifies BFME1's static), which throws on a
// miss, so the verb itself has no fail path. Name proven by the
// ObjectCreationList/DeliverPayload/AssistedTargeting FieldParse tables.

#define NULL 0

struct LookupListRec
{
	const char *name;
	int value;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanLookupList(const char *token, const LookupListRec *lookupList);
	static void parseLookupList(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseLookupList(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	const LookupListRec *lookupList = (const LookupListRec *)userData;
	*(int *)store = ini->scanLookupList(ini->getNextToken(NULL), lookupList);
}
