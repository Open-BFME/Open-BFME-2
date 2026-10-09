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

// Target 003389BD..003389CE/17 is a complete neighboring raw float
// operation after RET3389BC. It forms g_secondsPerLogicFrame * PI/180
// before multiplying the stack float, returning through x87 ST0.
// BFME1 f989 GameCommon.h supplies the angular-conversion expression;
// the original out-of-line helper name remains unknown in BFME2.
Real rva003389bd(Real value)
{
    const Real RADS_PER_DEGREE = PI / 180.0f;
    return value * (g_secondsPerLogicFrame * RADS_PER_DEGREE);
}
