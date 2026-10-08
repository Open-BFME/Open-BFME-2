// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseBool@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002E850, 28 bytes.
// Dedicated frameless TU (same INI scanner family as INI_scanBool.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseBool): store the macro-expanded yes/no token as a bool. BFME2
// deltas: getNextToken takes an explicit NULL separator set, and scanBool is
// a member (thiscall through ini, not a static). The callee cleanup is
// load-bearing: getNextToken pops its own separator argument (ret 4), so the
// second ini load still reads [esp+4]; scanBool does not, so the store load
// reads [esp+0xC].

class INI
{
public:
	const char *getNextToken(const char *seps);
	bool scanBool(const char *token);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseBool@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBool(INI *ini, void *instance, void *store, const void *userData)
{
	*(bool *)store = ini->scanBool(ini->getNextToken(0));
}
