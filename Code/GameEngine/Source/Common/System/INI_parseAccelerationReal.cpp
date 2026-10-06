// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseAccelerationReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338BE3, 43 bytes.
// Dedicated frameless TU (twin of INI_parseVelocityReal.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseAccelerationReal, via ZH GameCommon.h
// ConvertAccelerationInSecsToFrames): scale seconds-squared to frames-squared
// through the squared factor. BFME2 deltas (all retail-measured): the 0.2
// global at 0x9BA4F8 is squared at runtime (two fld/fmul pairs, never folded
// to 0.04, so the factor stays a mutable global), the product leads
// factor-first ahead of the scanReal value, and the value flows straight from
// scanReal with no named temp. Name by family convention with the velocity
// twin (same B1 source pair, same retail twin shape, six table refs).

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
	static void parseAccelerationReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail value at 0x009BA4F8 (ZH SECONDS_PER_LOGICFRAME_REAL); read by
// address (DIR32) like the duration scale global.
float g_secondsPerLogicFrame = 0.2f;

// ?parseAccelerationReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAccelerationReal(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	float val = ini->scanReal(ini->getNextToken(0));
	*(float *)store = (g_secondsPerLogicFrame * g_secondsPerLogicFrame) * val;
}
