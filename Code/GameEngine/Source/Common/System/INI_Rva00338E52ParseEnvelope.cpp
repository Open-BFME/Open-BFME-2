// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?Rva00338E52_ParseEnvelope@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338E52, 605 bytes.
// INI FieldParse callback in the INI.cpp run between parseDeathTypeFlags
// (0x00338D91) and parseMappedImage (0x003390B2). Retail FieldParse tables
// reference it for "Envelope" (0x00BCB930, 0x00BF2368) and "FollowTarget"
// (0x00BF2378). It zeroes +0x0C/+0x24 of the store, then reads tokens until
// "End": three opacities through scanReal and five millisecond times through
// the same scale/ceil/__ftol2 shape as parseDurationUnsignedInt. Target-only
// (no Zero Hour counterpart); the callback name stays address-derived.

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	float scanReal(const char *token);
	unsigned int scanUnsignedInt(const char *token);
	static void Rva00338E52_ParseEnvelope(INI *ini, void *instance, void *store, const void *userData);
};

struct Rva00338E52Envelope
{
	float m_initialOpacity;		// +0x00
	float m_peakOpacity;		// +0x04
	float m_sustainOpacity;		// +0x08
	int m_unknown0C;			// +0x0C
	unsigned int m_initialDelay;	// +0x10
	unsigned int m_attackTime;	// +0x14
	unsigned int m_decayTime;	// +0x18
	unsigned int m_sustainTime;	// +0x1C
	unsigned int m_releaseTime;	// +0x20
	int m_unknown24;			// +0x24
};

// Retail value at 0x00DBA4EC owned by INI_parseDurationUnsignedShort.cpp.
extern float g_parseDurationMsecScale;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" int __cdecl strcmp(const char *a, const char *b);

#define MSECS_TO_FRAMES(ini) \
	((unsigned int)ceil(g_parseDurationMsecScale * (float)(ini)->scanUnsignedInt((ini)->getNextToken(NULL))))

// ?Rva00338E52_ParseEnvelope@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00338E52_ParseEnvelope(INI *ini, void *instance, void *store, const void *userData)
{
	Rva00338E52Envelope *env = (Rva00338E52Envelope *)store;
	env->m_unknown0C = 0;
	env->m_unknown24 = 0;

	const char *token;
	while ((token = ini->getNextTokenOrNull(NULL)) != NULL)
	{
		if (strcmp(token, "InitialOpacity") == 0)
			env->m_initialOpacity = ini->scanReal(ini->getNextToken(NULL));
		else if (strcmp(token, "PeakOpacity") == 0)
			env->m_peakOpacity = ini->scanReal(ini->getNextToken(NULL));
		else if (strcmp(token, "SustainOpacity") == 0)
			env->m_sustainOpacity = ini->scanReal(ini->getNextToken(NULL));
		else if (strcmp(token, "AttackTime") == 0)
			env->m_attackTime = MSECS_TO_FRAMES(ini);
		else if (strcmp(token, "DecayTime") == 0)
			env->m_decayTime = MSECS_TO_FRAMES(ini);
		else if (strcmp(token, "SustainTime") == 0)
			env->m_sustainTime = MSECS_TO_FRAMES(ini);
		else if (strcmp(token, "ReleaseTime") == 0)
			env->m_releaseTime = MSECS_TO_FRAMES(ini);
		else if (strcmp(token, "InitialDelay") == 0)
			env->m_initialDelay = MSECS_TO_FRAMES(ini);
		else if (strcmp(token, "End") == 0)
			break;
	}
	(void)instance;
	(void)userData;
}
