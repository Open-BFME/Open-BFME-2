// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseAngularVelocityReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x003389DD, 44 bytes,
// in the INI.cpp run between clearVeterancyLevelFlag (0x003389AC) and
// parseFXList (0x00338A09). Zero Hour's INI::parseAngularVelocityReal through
// GameCommon.h ConvertAngularVelocityInDegreesPerSecToRadsPerFrame:
// degPerSec * (SECONDS_PER_LOGICFRAME_REAL * RADS_PER_DEGREE). BFME 2 reads the
// seconds-per-frame factor from the 0.2 global at 0x00DBA4F8 (as
// INI_parseVelocityReal.cpp), so the product is formed at run time against
// the PI / 180 literal. Name proven by the FieldParse rows TurretTurnRate /
// TurretPitchRate (0x00C60B90 / 0x00C60BA0), ExitPitchRate and BounceAmount.

#define NULL 0

typedef float Real;

#define PI 3.14159265359f

class INI
{
public:
	const char *getNextToken(const char *seps);
	Real scanReal(const char *token);
	static void parseAngularVelocityReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail 0x00DBA4F8 (0.2), owned by the unit that defines it.
extern Real g_secondsPerLogicFrame;

// ?parseAngularVelocityReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAngularVelocityReal(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	const Real RADS_PER_DEGREE = PI / 180.0f;
	Real degPerSec = ini->scanReal(ini->getNextToken(0));
	*(Real *)store = degPerSec * (g_secondsPerLogicFrame * RADS_PER_DEGREE);
}
