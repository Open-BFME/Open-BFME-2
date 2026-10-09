// cl: /DNDEBUG /MD
//
// INI::parseDurationReal, retail 0x00338B0A (38 bytes).
// ZH INI.cpp: duration in msec scaled by a const-global multiplier, inlined
// here as val * scale with the scale read from memory (fld + fmul st(1)).
// Retail reads 0.005f at 0x00DBA4EC; the getNextToken/scanReal callees are
// already pinned. Upstream name of the scale global not recovered, so it is
// TU-local with the retail value cited.

class INI
{
public:
	const char *getNextToken(const char *separators);
	float scanReal(const char *token);
	static void parseDurationReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail value at 0x00DBA4EC; read by address (DIR32) like other globals.
extern float g_parseDurationMsecScale;

void INI::parseDurationReal(INI *ini, void *instance, void *store, const void *userData)
{
	float val = ini->scanReal(ini->getNextToken(0));
	*(float *)store = g_parseDurationMsecScale * val;
	(void)instance;
	(void)userData;
}

// BFME1 f989 GameCommon.h ConvertDurationFromMsecsToFrames is the
// reference expression. Retail uses the established mutable duration
// factor above: 00203521..0020352C/11 after RET203520, one stack float,
// fld factor / fmul argument / RET0, ST0 result. Original name unknown.
float rva00203521(float value)
{
    return g_parseDurationMsecScale * value;
}
