// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005CFC12@Rva005D00A6@@UAEXPAVINI@@@Z @0x005CFC12 163B
// Slot 1 of vtable 0x00875374 (class Rva005D00A6): INI parse of two floats via table 0x00875344 then floor(1000x+0.5) to m_8/m_c.
// Evidence: vslot lane slot 1 offset 0x4; donor TU Rva005D00A6Ctor.cpp; callees rowed initFromINI 0x0002DE78 plus IAT floor; BfmeZeroRange 0.0f; 1000.0f at 0x007BE358 and 0.5f at 0x007C26F0 are compiler literals (Rva001DCF82/Rva00285DC5 precedent: extern hoists scale ahead); callers none.
#include <math.h>

struct FieldParse;
class INI
{
public:
	void initFromINI(void *vals, const struct FieldParse *table);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline long fast_round(float roundValue)
{
	long i;
	__asm {
		fld [roundValue]
		fistp [i]
	}
	return i;
}

extern float g_00BBB9AC;
// Retail's own two-record table, transcribed from .rdata at RVA 0x00875344 (VA
// 0x00C75344, file offset 0x00874744): two parseReal columns into the two longs
// at +0/+4 of the TwoFloats the body above builds, followed by the zero
// terminator. `extern` on the definition keeps the array external.
extern const struct FieldParse g_00C75344[];
const struct FieldParse g_00C75344[] =
{
	{ "StartingAutoResolveBattleMessageDuration", &INI::parseReal, 0, 0 },
	{ "AllEnemiesRetreatedMessageDuration", &INI::parseReal, 0, 4 },
	{ 0, 0, 0, 0 }
};

class Rva005D00A6
{
public:
	virtual void v00();
	virtual void rva005CFC12(INI *ini);
private:
	int m_04;
	int m_08;
	int m_0c;
};

void Rva005D00A6::rva005CFC12(INI *ini)
{
	struct TwoFloats
	{
		float a;
		float b;
	};
	TwoFloats durationSettings;
	durationSettings.a = g_00BBB9AC;
	durationSettings.b = g_00BBB9AC;
	ini->initFromINI(&durationSettings, g_00C75344);
	if (durationSettings.a >= 0.0f)
		m_08 = fast_round(fast_floor(durationSettings.a * 1000.0f + 0.5f));
	if (durationSettings.b >= 0.0f)
		m_0c = fast_round(fast_floor(durationSettings.b * 1000.0f + 0.5f));
}
