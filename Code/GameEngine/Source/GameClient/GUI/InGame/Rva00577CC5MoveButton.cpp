// cl: /O1 /arch:SSE /MD /EHsc /G7 /Ireference/shims/bfme2_ascii
// Native00577CC5..00577D93 RET16 moves a four-coordinate movie button only
// when an input differs from the retained18/1C/20/24 values. The MoveButton
// literal, scale slot40 and matched314B forwarding call establish the role;
// the original class and method names remain unknown. Nested name records
// are target access views: outer40 -> middle0 -> inner8 counted text.
// Keeping the actual314B forwarding body visible as inline/noinline preserves
// the native delayed f0 store after the name-buffer test. Both bodies verified.
#include "ascii_string.h"
class Rva00222A8BTarget
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7();
	virtual void d8();
	virtual void d9();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual float *getScale();
 int rva00222B19(void*,const char*,const char*,int,const char*,void*,void*,void*,void*);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct InnerBox
{
	char _p0[4];
	void *m_4;
	char *m_8data;
};

struct MidBox
{
	InnerBox *m_0;
};

struct OuterBox
{
	char _p[0x40];
	MidBox *m_40;
};

int __cdecl Rva00577AE9AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, float *pF1, float *pF2, float *pF3, float *pF4);

AsciiString Rva002228E8Get(float val);
AsciiString Rva00222834Get(int val);


static __forceinline const char *GetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

inline __declspec(noinline) int __cdecl Rva00577AE9AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, float *pF1, float *pF2, float *pF3, float *pF4)
{
	return target->rva00222B19(level, prefix, function, 5, GetStr(Rva00222834Get(*pInt)), (void *)GetStr(Rva002228E8Get(*pF1)), (void *)GetStr(Rva002228E8Get(*pF2)), (void *)GetStr(Rva002228E8Get(*pF3)), (void *)GetStr(Rva002228E8Get(*pF4)));
}


class Rva00577CC5
{
public:
	void rva00577CC5(int a0, int a1, int a2, int a3);
private:
	char _p0[8];
	OuterBox *m_8;
	char _pC[4];
	int m_10;
	char _p14[4];
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
};

// ?rva00577CC5@Rva00577CC5@@QAEXHHHH@Z
void Rva00577CC5::rva00577CC5(int a0, int a1, int a2, int a3)
{
	if (a0 != m_18 || a1 != m_1c || a2 != m_20 || a3 != m_24) {
		float *scale = TheRva00222A8BTarget->getScale();
		float f3 = (float)a3 * scale[1];
		float f2 = (float)a2 * scale[0];
		float f1 = (float)a1 * scale[1];
		float f0 = (float)a0 * scale[0];
		InnerBox *box = m_8->m_40->m_0;
		char *raw = *(char **)((char *)box + 8);
		const char *s;
		if (raw)
			s = raw + 8;
		else
			s = "";
		Rva00577AE9AptCall(TheRva00222A8BTarget, box->m_4, s, "MoveButton", &m_10, &f0, &f1, &f2, &f3);
		m_18 = a0;
		m_1c = a1;
		m_20 = a2;
		m_24 = a3;
	}
}
