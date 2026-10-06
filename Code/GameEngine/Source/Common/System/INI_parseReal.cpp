// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EFC0, 28 bytes.
// Dedicated frameless TU (twin of INI_parseBool.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseReal): plain float store. Same BFME2 deltas as parseBool
// (explicit NULL seps, member scanReal).

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseReal(INI *ini, void *instance, void *store, const void *userData)
{
	*(float *)store = ini->scanReal(ini->getNextToken(0));
}
