// cl: /DNDEBUG /MD
//
// ?rva00462516@SlaughterHordeContain@@QAEXPAX0PAUDamageInfoInput00462516@@@Z, retail 0x00462516, 72 bytes.
// Gap between 0x00462504 (slot 63) and 0x0046255E in
// SlaughterHordeContainRva004625BB.cpp. Third arg is DamageInfoInput (m_damageType
// at +0x10, m_amount at +0x20, m_kill at +0x24): when type is neither 0xE nor 8,
// zeroes amount/kill, else when kill==1 forwards first arg plus 0 to slot 41
// (offset 0xA4). Evidence: gap TU plus call at 0x00479C22 plus DamageInfoInput
// layout plus virtual offset. Honest address name: method identity unproven.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

struct DamageInfoInput00462516 {
	char pad00[0x10];
	int m_damageType;
	char pad14[0x20 - 0x14];
	float m_amount;
	bool m_kill;
};

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1)
	virtual void s20(int); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(void *a, int b); virtual void s2A(); virtual void s2B(); virtual void s2C(); virtual void s2D(); virtual void s2E(); virtual void s2F();
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37) SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F);
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void iterateContained(void *func, void *userData, bool reverse);
	SLOT16(s69) SLOT16(s6A) SLOT16(s6B)
	SLOT08(s6C0,s6C1,s6C2,s6C3,s6C4,s6C5,s6C6,s6C7)
	virtual void s6D0(); virtual void s6D1(); virtual void s6D2();
	void rva00462516(void *a, void *b, DamageInfoInput00462516 *info);
};

void SlaughterHordeContain::rva00462516(void *a, void *b, DamageInfoInput00462516 *info)
{
	if (!a)
		return;
	if (!b)
		return;
	if (!info)
		return;
	if (info->m_damageType == 0xE || info->m_damageType == 8) {
		if (info->m_kill != 1)
			return;
		s29(a, 0);
	} else {
		info->m_amount = 0.0f;
		info->m_kill = false;
	}
}
