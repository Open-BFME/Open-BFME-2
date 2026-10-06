// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseDurationUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338B76, 70 bytes.
// Dedicated TU (twin of INI_parseDurationUnsignedInt.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseDurationUnsignedShort): same scale-through-ceil computation,
// narrowed into the store word. BFME2 deltas are the twin's (0.005f global at
// 0xDBA4EC, double ceil import, __ftol2 truncation). Name by family convention
// with the uint twin (same B1 source pair, same retail twin shape).

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	unsigned int scanUnsignedInt(const char *token);
	static void parseDurationUnsignedShort(INI *ini, void *instance, void *store, const void *userData);
};

// Retail value at 0x00DBA4EC; read by address (DIR32) like the landed
// parseDurationReal TU's scale global.
float g_parseDurationMsecScale = 0.005f;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

// ?parseDurationUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseDurationUnsignedShort(INI *ini, void *instance, void *store, const void *userData)
{
	unsigned int val = ini->scanUnsignedInt(ini->getNextToken(0));
	*(unsigned short *)store = (unsigned short)ceil(g_parseDurationMsecScale * (float)val);
	(void)instance;
	(void)userData;
}
