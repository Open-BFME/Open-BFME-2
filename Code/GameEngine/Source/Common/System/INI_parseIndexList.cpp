// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EC4E, 31 bytes.
// Dedicated frameless TU (same INI verb family as INI_parseAngleReal.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseIndexList): store the index of the next token in the userData
// name list. BFME2 is the same one-liner through the member scanIndexList
// (pinned at 0x2BD39; BFME2 member-ifies BFME1's static), which throws on a
// miss, so the verb itself has no fail path. Name proven by the
// Locomotor/Weapon/Upgrade/Jet/Horde FieldParse tables.

#define NULL 0

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseIndexList(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	ConstCharPtrArray nameList = (ConstCharPtrArray)userData;
	*(int *)store = ini->scanIndexList(ini->getNextToken(NULL), nameList);
}
