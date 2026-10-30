// cl: /EHsc /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

struct Helper005C4D4B {
	void *m_00;
	AsciiString m_str;
	int m_08;
	int m_0c;
	Helper005C4D4B(void *);
	~Helper005C4D4B() {}
};

struct SubAC005C4B56 {
	char pad[0x60];
	char m_flag60;
};

// Base of the icon sub-object chain: its dtor is the rowed provider
// ??1Rva005C4B1B@@UAE@XZ (OpaqueSingleInheritanceDtors.cpp, 0x5C4B1B), the
// dtor that stores Rva005C4B56's vftable 0xC747B8.  Slot 17 is rowed as
// Rva005C41C9::v17 (0x5C414F); the constructor calls it statically.
class Rva005C4B1B {
public:
	virtual ~Rva005C4B1B();
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual unsigned char v17() = 0;
};

class Rva005C41C9 {
public:
	virtual unsigned char v17();
};

class Rva005C4B56 : public Rva005C4B1B {
public:
	virtual void rva005C4B96(unsigned char);

	char pad_base[0xa8];
	SubAC005C4B56 *m_ac; // +0xac
	void *m_b0;          // +0xb0
	int m_b4;
	int m_b8;

	Rva005C4B56(const Helper005C4D4B &, bool, const int *);
};

struct Rva004E06FBPtrChase32Field {
	int get() const;
};

struct Arg1Host005C4280 {
	char pad[0x38];
	Rva004E06FBPtrChase32Field *m_field38;
};

// 0x002BFFD4 is rowed as Rva002BFF5A::rva002BFFD4 (Rva002BFF5A.cpp).
struct Rva002BFFD4Template;
class Rva002BFF5A {
public:
	void rva002BFFD4(Rva002BFFD4Template *, int, unsigned int);
};
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva005C4230 : public Rva005C4B56 {
public:
	Arg1Host005C4280 *m_bc;
	int m_c0;
	bool m_c4;
	bool m_c5;

	Rva005C4230(void *arg0, Arg1Host005C4280 *host);
	virtual ~Rva005C4230();
};

Rva005C4230::Rva005C4230(void *arg0, Arg1Host005C4280 *host)
	: Rva005C4B56(Helper005C4D4B(arg0), true, 0)
{
	m_c0 = -1;
	m_bc = host;
	m_c4 = true;
	m_c5 = false;
	if (host) {
		if (host->m_field38) {
			m_c0 = host->m_field38->get();
		}
		if (m_ac->m_flag60) {
			((Rva002BFF5A *)TheLivingWorld)->rva002BFFD4((Rva002BFFD4Template *)this, 4, (unsigned int)m_b0);
		}
		rva005C4B96(((Rva005C41C9 *)this)->Rva005C41C9::v17());
	}
}
