// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F0D5, 34 bytes.
// Dedicated frameless TU (twin of INI_parseReal.cpp with a scale factor).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseAngleReal): verbatim (degrees to radians). The constant is
// spelled as its exact float value: PI/180.0f rounds to 0.017453292f
// (retail .rdata 0xBBB8D0), and the literal form keeps the fmul against a
// memory constant that the divided form would also fold to.

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
};

const float RADS_PER_DEGREE = 0.017453292f;

// ?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAngleReal(INI *ini, void *instance, void *store, const void *userData)
{
	*(float *)store = ini->scanReal(ini->getNextToken(0)) * RADS_PER_DEGREE;
}
