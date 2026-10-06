// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338BBD, 37 bytes.
// Dedicated frameless TU (same INI verb family as INI_parseAngleReal.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseVelocityReal, via ZH GameCommon.h ConvertVelocityInSecsToFrames):
// scale seconds to frames. BFME2 deltas (all retail-measured): the factor is
// the 0.2 global at 0x9BA4F8 (read by address, DIR32), spelled factor-first
// (retail loads it with fld ahead of the value), and the value flows straight
// from scanReal with no named temp (no intermediate float store). Name proven
// by twenty-one FieldParse tables (Topple InitialVelocityPercent,
// SupplyTruck ... velocity fields).

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
	static void parseVelocityReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail value at 0x009BA4F8 (ZH SECONDS_PER_LOGICFRAME_REAL); owned by
// INI_parseAccelerationReal.cpp, declared here.
extern float g_secondsPerLogicFrame;

// ?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseVelocityReal(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	float val = ini->scanReal(ini->getNextToken(0));
	*(float *)store = g_secondsPerLogicFrame * val;
}
