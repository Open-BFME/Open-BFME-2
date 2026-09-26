// cl: /O1 /DNDEBUG /MD
//
// ?rva004625BB@SlaughterHordeContain@@UAE_NPAXH@Z, retail 0x004625BB, 53 bytes.
// Virtual slot 128 (offset 0x200) of vtable 0x00848AA0 (class of
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// SlaughterHordeContainCtor.cpp). Wrapper over slot 68 (offset 0x110)
// iterateContained: builds a 9-byte user struct {first arg, second arg,
// bool out}, passes the retail callback at 0x0046258C plus the struct plus
// true to the slot-68 virtual, then returns out == false (xor, cmp, sete).
// Evidence: vtable slots 128/129 share the same slot-68 caller shape (129 is
// the void twin at 0x004625F0 pushing 0x004625AA), push-imm 0x86258c plus
// call [eax+0x110] plus leave/ret-8 shape, no direct callees (DIR32-masked
// callback, virtual iterate needs no row). Honest address name: class plus
// slot are proven, method identity is not.

class Object;
typedef void (__cdecl *ContainIterateFunc)(Object *obj, void *userData);

void iterCallback0046258C(Object *obj, void *userData);
void iterCallback004625AA(Object *obj, void *userData);

struct Coord3D0046255E {
	float x;
	float y;
	float z;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1)
	virtual void s20(int); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37) SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,rva00462504);
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
	SLOT16(s69) SLOT16(s6A) SLOT16(s6B)
	SLOT08(s6C0,s6C1,s6C2,s6C3,s6C4,s6C5,s6C6,s6C7)
	virtual void s6D0(); virtual void s6D1(); virtual void s6D2();
	virtual bool rva004625BB(void *a, int b);
	virtual void rva004625F0(void *a);
	void rva0046255E(const Coord3D0046255E *pos);

	char m_pad9C[0x9C];
	Coord3D0046255E m_posA0;
	bool m_flagAC;
	char m_padAD[0xC1 - 0xAD];
	bool m_flagC1;
};

struct IterateUser004625BB {
	void *a;
	int b;
	bool flag;
};

struct IterateUser004625F0 {
	int zero;
	void *a;
	bool flag;
};

bool SlaughterHordeContain::rva004625BB(void *a, int b)
{
	IterateUser004625BB user;
	user.b = b;
	user.a = a;
	user.flag = false;
	iterateContained(iterCallback0046258C, &user, true);
	return user.flag == false;
}

// ?rva004625F0@SlaughterHordeContain@@UAEXPAX@Z, retail 0x004625F0, 43 bytes.
// Virtual slot 129 (offset 0x204) of vtable 0x00848AA0, void twin of slot 128:
// zeroes the first user DWORD, stores the single arg as the second DWORD,
// passes the retail callback at 0x004625AA plus the struct plus true to the
// slot-68 virtual. Same flags and class as slot 128, no direct callees.
// Honest address name: class plus slot are proven, method identity is not.
void SlaughterHordeContain::rva004625F0(void *a)
{
	IterateUser004625F0 user;
	user.zero = 0;
	user.a = a;
	user.flag = false;
	iterateContained(iterCallback004625AA, &user, true);
}

// ?rva0046255E@SlaughterHordeContain@@QAEXPBUCoord3D0046255E@@@Z, retail 0x0046255E, 27 bytes.
// 12-byte copy from the single pointer arg to +0xA0 plus flag at +0xAC set to
// 1 (push esi/edi, lea edi [ecx+0xA0], three movsd, flag). Same /O1 flags and
// class as slots 128/129; no callees. Shape matches OpenContain::setRallyPoint
// (m_rallyPoint plus exists) but identity is unproven, so honest address name.
void SlaughterHordeContain::rva0046255E(const Coord3D0046255E *pos)
{
	m_posA0 = *pos;
	m_flagAC = true;
}

// ?rva00462504@SlaughterHordeContain@@UAEXXZ, retail 0x00462504, 18 bytes.
// Virtual slot 63 (offset 0xFC) of vtable 0x00848AA0: clears the byte at
// +0xC1 then forwards constant 2 to slot 32 (offset 0x80). Same /O1 flags
// and class as slots 128/129/62CE1 neighbours; virtual call needs no row.
// Honest address name: class plus slot are proven, method identity is not.
void SlaughterHordeContain::rva00462504()
{
	m_flagC1 = false;
	s20(2);
}
