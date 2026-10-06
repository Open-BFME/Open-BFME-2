// cl: /DNDEBUG /MD
//
// ?rva0046274C@SlaughterHordeContain@@UAEXPAXH0@Z, retail 0x0046274C, 57 bytes.
// Virtual slot 81 (offset 0x144) of vtable 0x00848AA0 (class of
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// SlaughterHordeContainCtor.cpp). Clamps the int arg to >=1 into +0xCC via a
// pointer select (int *p = uninit; if/else picks &b or &one; v = *p), copies
// the int at +0x74 of the first pointer arg into +0xC4 and the int at +0x74
// of the second pointer arg into +0xC8. The if/else (no initial p) puts the
// 1 in eax and the named ka local plus m_c4-before-m_cc store order puts p/v
// in eax and ka in edx with the retail cc/c4/c8 store schedule. Evidence:
// vtable slot plus same /O1 flags and class as slots 128/129/82 neighbours;
// no donor hits; no direct callers or callees. Honest address name: class
// plus slot are proven, method identity is not.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

struct Holder0046274C {
	char pad[0x74];
	int key;
};

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1)
	virtual void s20(int); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37) SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s4A(); virtual void s4B();
	virtual void s4C(); virtual void s4D(); virtual void s4E(); virtual void s4F();
	virtual void s50();
	virtual void rva0046274C(void *a, int b, void *c);

	char m_pad04[0xC4 - 4];
	int m_c4;
	int m_c8;
	int m_cc;
};

void SlaughterHordeContain::rva0046274C(void *a, int b, void *c)
{
	int one = 1;
	int *p;
	if (b > 1)
		p = &b;
	else
		p = &one;
	int v = *p;
	m_c4 = ((Holder0046274C *)a)->key;
	m_cc = v;
	m_c8 = ((Holder0046274C *)c)->key;
}
