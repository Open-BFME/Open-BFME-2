// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva005D2B2F@Rva005D25F2@@QAEXHM@Z @0x005D2B2F 165B: virtual slot 4 offset 0x10 of vtable 0x00875800.
// Evidence: (idx+1)*0x1C array like sibling Rva005D2664, timeGetTime plus floor plus fast_round fistp,
// Fire 0x00525338 with SetFlashEffectState plus _show/_hide plus GetStr of AsciiString at +8,
// globals g_00BBE358 g_Va007C26F0 TheRva00222A8BTarget, x87 blocker needs inline asm fast_round.
#include "ascii_string.h"
#define inline static inline
#include <math.h>
#undef inline

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) double __cdecl floor(double);

extern float g_00BBE358;
// g_00BBE358: matched references place it at VA 0xbbe358 (retail .rdata value 1000.0f).
float g_00BBE358 = 1000.0f;


class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);

__forceinline const char *GetStr005D2B2F(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

static __forceinline long fast_round005D2B2F(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct Elem005D2B2F
{
	char m_pad00[0x14];
	unsigned long m_14;
	int m_18;
};

class Rva005D25F2
{
public:
	void rva005D2B2F(int idx, float val);
private:
	void *m_vtbl00;
	void *m_04;
	AsciiString m_08;
	char m_pad0C[0x10];
	Elem005D2B2F m_1C[6];
};

void Rva005D25F2::rva005D2B2F(int idx, float val)
{
	Elem005D2B2F *e = (Elem005D2B2F *)((char *)this + (idx + 1) * 0x1C);
	int old = e->m_18;
	unsigned long t = timeGetTime();
	float vv = *(const volatile float *)&val;
	float s = vv * g_00BBE358;
	e->m_14 = t;
	s = s + 0.5f;
	double d = floor(s);
	float f = (float)d;
	int ni = fast_round005D2B2F(f);
	e->m_18 = ni;
	if (old == 0) {
		if (ni == 0)
			return;
		Rva00525338Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_04, GetStr005D2B2F(m_08), "SetFlashEffectState", &idx, (void *)"_show");
	} else {
		if (ni != 0)
			return;
		Rva00525338Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_04, GetStr005D2B2F(m_08), "SetFlashEffectState", &idx, (void *)"_hide");
	}
}
