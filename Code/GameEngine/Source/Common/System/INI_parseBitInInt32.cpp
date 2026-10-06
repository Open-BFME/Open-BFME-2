// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002E86C, 41 bytes.
// Dedicated TU (same INI verb family as INI_parseAngleReal.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseBitInInt32): read a Bool token; OR the userData mask into the
// store dword when true, AND out its complement when false. BFME2 is verbatim
// (getNextToken takes an explicit NULL seps here). Name proven by the Weapon
// FieldParse table (AntiAirborneVehicle/AntiGround/... ushort-mask rows).

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	bool scanBool(const char *token);
	static void parseBitInInt32(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitInInt32(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	unsigned int *s = (unsigned int *)store;
	unsigned int mask = (unsigned int)userData;

	if (ini->scanBool(ini->getNextToken(NULL)))
		*s |= mask;
	else
		*s &= ~mask;
}
