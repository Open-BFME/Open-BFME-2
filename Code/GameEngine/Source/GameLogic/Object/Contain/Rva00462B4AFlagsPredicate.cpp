// ?rva00462B4A@Rva00462B4A@@QAE_NXZ
// ?rva00462B4A@Rva00462B4A@@QAE_NXZ @0x00462B4A 73B
// Evidence: Native462B4A..462B93 RET0; table43464 near SlaughterHordeContain and owner at secondary minus18. Virtual slot44 returns16B flags value through hidden pointer then zero argument. Real flags return and inline byte test reproduce native MOV SHR TEST. Parent274 and far interface slot45; purpose and original class unknown; full73 bytes exact no pins.
// cl: /O1 /DNDEBUG /MD
// ?rva00462B4A@Rva00462B4A@@QAE_NXZ @0x00462B4A 73B: bool predicate via v_b0 buffer check then parent chain
// Identity: REF table slots (e.g. 0x00843464) with SlaughterHordeContain neighbours; honest address name.
// Evidence: virtual offsets 0xB0/0xB4, returning false/true/forwarded bool.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

struct Buf00462B4A {
	char m_data[0x10];
};

struct Ret00462B4A {
 unsigned m_flags,m_b,m_c,m_d;
 Ret00462B4A(){}
 Ret00462B4A(const Ret00462B4A& x):m_flags(x.m_flags),m_b(x.m_b),m_c(x.m_c),m_d(x.m_d){}
 __forceinline unsigned char test(int i)const {return (unsigned char)(m_flags>>i)&1;}
};

class Other00462B4A {
public:
	SLOT16(o0) SLOT16(o1) SLOT08(o20,o21,o22,o23,o24,o25,o26,o27)
	virtual void o28(); virtual void o29(); virtual void o2A(); virtual void o2B(); virtual void o2C();
	virtual bool v_b4();
};

struct Mid00462B4A {
	char m_pad[0x250];
	Other00462B4A *m_other;
};

struct Parent00462B4A {
	char m_pad[0x274];
	Mid00462B4A *m_mid;
};

class Rva00462B4A {
public:
	SLOT16(s0) SLOT16(s1) SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	virtual void s28(); virtual void s29(); virtual void s2A(); virtual void s2B();
	virtual Ret00462B4A v_b0(int zero);
	bool rva00462B4A();
};

// ?rva00462B4A@Rva00462B4A@@QAE_NXZ
bool Rva00462B4A::rva00462B4A()
{
	if (!v_b0(0).test(1))
		return false;
	Parent00462B4A *outer = *(Parent00462B4A **)((char *)this - 0x18);
	Mid00462B4A *mid = *(Mid00462B4A **)((char *)outer + 0x274);
	if (mid) {
		Other00462B4A *o = *(Other00462B4A **)((char *)mid + 0x250);
		return o->v_b4();
	}
	return true;
}
