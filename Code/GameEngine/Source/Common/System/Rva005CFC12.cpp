// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva005CFC12@Rva005D00A6@@UAEXPAVINI@@@Z @0x005CFC12 163B
// Slot 1 of vtable 0x00875374 (class Rva005D00A6): INI parse of two floats via table 0x00875344 then floor(1000x+0.5) to m_8/m_c.
// Evidence: vslot lane slot 1 offset 0x4; donor TU Rva005D00A6Ctor.cpp; callees rowed initFromINI 0x0002DE78 plus IAT floor; BfmeZeroRange 0.0f; 1000.0f at 0x007BE358 and 0.5f at 0x007C26F0 are compiler literals (Rva001DCF82/Rva00285DC5 precedent: extern hoists scale ahead); callers none.
struct FieldParse;
class INI
{
public:
	void initFromINI(void *vals, const struct FieldParse *table);
};

extern "C" __declspec(dllimport) double __cdecl floor(double v);

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline long fast_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

extern const float BfmeZeroRange;
extern float g_00BBB9AC;
extern const struct FieldParse g_00C75344[];

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
	TwoFloats v;
	v.a = g_00BBB9AC;
	v.b = g_00BBB9AC;
	ini->initFromINI(&v, g_00C75344);
	if (v.a >= BfmeZeroRange)
		m_08 = fast_round(fast_floor(v.a * 1000.0f + 0.5f));
	if (v.b >= BfmeZeroRange)
		m_0c = fast_round(fast_floor(v.b * 1000.0f + 0.5f));
}
