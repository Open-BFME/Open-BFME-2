// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseInt@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EF56, 28 bytes.
// Dedicated frameless TU (twin of INI_parseBool.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseInt): plain integer store. Same BFME2 deltas as parseBool
// (explicit NULL seps, member scanInt).

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseInt@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseInt(INI *ini, void *instance, void *store, const void *userData)
{
	*(int *)store = ini->scanInt(ini->getNextToken(0));
}
