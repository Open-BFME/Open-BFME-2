// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338B30, 70 bytes.
// Dedicated TU (same INI verb family as INI_parseDurationReal.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseDurationUnsignedInt): scan an unsigned int, scale milliseconds to
// frames through ceil. BFME2 deltas (all retail-measured): the scale is the
// TU-local 0.005f global read from 0xDBA4EC (same global the landed
// parseDurationReal TU cites), the ceil is the double msvcr71 import (IAT
// slot 0xBBA578; the value spills as a qword first), and the truncation rides
// the pinned __ftol2 helper. Name proven by seventy-five FieldParse tables
// (RespawnTime/BuildTime/... millisecond fields).

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	unsigned int scanUnsignedInt(const char *token);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

// Retail value at 0x00DBA4EC owned by INI_parseDurationUnsignedShort.cpp;
// declared here so uses keep the same name without a second definition.
extern float g_parseDurationMsecScale;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

// ?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData)
{
	unsigned int val = ini->scanUnsignedInt(ini->getNextToken(0));
	*(unsigned int *)store = (unsigned int)ceil(g_parseDurationMsecScale * (float)val);
	(void)instance;
	(void)userData;
}
