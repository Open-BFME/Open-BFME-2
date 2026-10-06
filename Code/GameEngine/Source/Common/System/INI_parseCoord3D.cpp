// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F507, 81 bytes.
// Dedicated frameless TU (twin of INI_parseReal.cpp, three components).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini.cpp,
// INI::parseCoord3D): verbatim X/Y/Z sub-token floats. Unlocked by the
// getNextSubToken row at 0x002E06B.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	float scanReal(const char *token);
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseCoord3D(INI *ini, void *instance, void *store, const void *userData)
{
	Coord3D *theCoord = (Coord3D *)store;
	theCoord->x = ini->scanReal(ini->getNextSubToken("X"));
	theCoord->y = ini->scanReal(ini->getNextSubToken("Y"));
	theCoord->z = ini->scanReal(ini->getNextSubToken("Z"));
}
