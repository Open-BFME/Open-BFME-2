// cl: /DNDEBUG /MD
//
// ?rva00462CE1@SlaughterHordeContain@@UAEPAVBfmeObject872Header@@PAV2@H@Z, retail 0x00462CE1, 23 bytes.
// Virtual slot 82 (offset 0x148) of vtable 0x00848AA0 (class of
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// SlaughterHordeContainCtor.cpp). Copies the 16-byte BfmeObject872Header at
// *(this-0x1C)+0x58 into the out pointer via the rowed copy ctor 0x2CF108 and
// returns out; second arg unused but cleaned (ret 8). Caller at 0x0047CB32
// passes the same two args and returns the same out pointer, with the 0x1A4
// copy inline on the bfmeHas1026 path. Evidence: vtable slot plus rowed callee
// plus caller shape. Honest address name: method identity unproven.

class BfmeObject872Header
{
public:
	__declspec(nothrow) BfmeObject872Header(const BfmeObject872Header &other);
};

struct Outer00462CE1 {
	void *m_ptr00;
	char pad04[0x58 - 4];
	BfmeObject872Header m_header58;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1)
	virtual void s20(int); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37) SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void iterateContained(void *func, void *userData, bool reverse);
	virtual void s690(); virtual void s691(); virtual void s692(); virtual void s693();
	virtual void s694(); virtual void s695(); virtual void s696(); virtual void s697();
	virtual void s698(); virtual void s699(); virtual void s69A(); virtual void s69B();
	virtual void s69C();
	virtual BfmeObject872Header *rva00462CE1(BfmeObject872Header *out, int unused);
};

#include <new>

BfmeObject872Header *SlaughterHordeContain::rva00462CE1(BfmeObject872Header *out, int unused)
{
	__assume(out != 0);
	Outer00462CE1 *base = *(Outer00462CE1 **)((char *)this - 0x1c);
	BfmeObject872Header *src = (BfmeObject872Header *)((char *)base + 0x58);
	new (out) BfmeObject872Header(*src);
	return out;
}
