// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F558, 58 bytes.
// Dedicated frameless TU (twin of INI_parseCoord3D.cpp, two components).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini.cpp,
// INI::parseCoord2D): verbatim X/Y sub-token floats.

#include "../../../../Libraries/Include/Lib/Coord2D.h"

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	float scanReal(const char *token);
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseCoord2D(INI *ini, void *instance, void *store, const void *userData)
{
	Coord2D *theCoord = (Coord2D *)store;
	theCoord->x = ini->scanReal(ini->getNextSubToken("X"));
	theCoord->y = ini->scanReal(ini->getNextSubToken("Y"));
}
