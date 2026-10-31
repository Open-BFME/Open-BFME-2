// cl: /EHsc /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ??0LivingWorldArmyIconSubObject@@QAE@PAXPAXH@Z @0x0056BA07 156B: ctor LivingWorldArmyIconSubObject::LivingWorldArmyIconSubObject(void*,void*,int) via Rva005C4B56(Helper(arg0),1,arg2), sets BC=-1 C0=0 C4=arg1 vtable, then if arg1 calls method_002BFFD4 with 0 and rva005C4B96(rva0056B89F()). Evidence: donor Rva005C4280.cpp Rva005C4230 ctor shape, callee pins Helper005C4D4B Rva005C4B56 method_002BFFD4, rowed rva0056B89F rva005C4B96 releaseBuffer, caller 0x003FE50D.
#include "ascii_string.h"

struct Helper005C4D4B
{
	void *m_00;
	AsciiString m_str;
	int m_08;
	int m_0c;
	Helper005C4D4B(void *);
	~Helper005C4D4B() {}
};

struct SubAC0056B89F
{
	char _00[0x58];
	int m_58;
	unsigned char m_flag5C;
	char _5D;
	unsigned char m_5E;
};

// Base of the icon sub-object chain.  The dtor spelling below is the rowed
// provider ??1Rva005C4B1B@@UAE@XZ (OpaqueSingleInheritanceDtors.cpp, 0x5C4B1B);
// the virtual dtor keeps the constructor's EH states identical to retail.
// The constructor spelling below is the rowed provider
// ??0Rva005C4B56@@QAE@ABUHelper005C4D4B@@_NPBH@Z
// (LivingWorldIconSubObjectCtor.cpp).
class Rva003FCE38
{
public:
	virtual ~Rva003FCE38();
protected:
	AsciiString m_str;
};

class Rva005C4B1B : public Rva003FCE38
{
public:
	virtual ~Rva005C4B1B();
};

class Rva005C4B56 : public Rva005C4B1B
{
public:
	virtual void rva005C4B96(unsigned char);

	char pad_base[0xA4];
	SubAC0056B89F *m_ac;
	void *m_b0;
	int m_b4;
	int m_b8;

	Rva005C4B56(const Helper005C4D4B &, bool, const int *);
};

// 0x002BFFD4 is rowed as Rva002BFF5A::rva002BFFD4 (Rva002BFF5A.cpp).
struct Rva002BFFD4Template;
class Rva002BFF5A
{
public:
	void rva002BFFD4(Rva002BFFD4Template *, int, unsigned int);
	void rva002C004F(const char *name);
};
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Target0056B8D7;
class Visitor0056B984;

struct Holder0056B8D7
{
	Target0056B8D7 *m_ptr;
};

class LivingWorldArmyIconSubObject : public Rva005C4B56
{
public:
	int m_bc;
	unsigned char m_c0;
	char _c1[3];
	Holder0056B8D7 m_c4;

	LivingWorldArmyIconSubObject(void *arg0, void *arg1, int arg2);
	unsigned char rva0056B89F();
	int rva0056B88A();
	bool rva0056B8D7();
	void rva0056B984(Visitor0056B984 *visitor);
	void rva0056B993(Visitor0056B984 *visitor);
};

LivingWorldArmyIconSubObject::LivingWorldArmyIconSubObject(void *arg0, void *arg1, int arg2)
	: Rva005C4B56(Helper005C4D4B(arg0), true, (const int *)arg2)
{
	m_bc = -1;
	m_c0 = 0;
	m_c4.m_ptr = (Target0056B8D7 *)arg1;
	if (arg1) {
		if (m_ac->m_flag5C) {
			((Rva002BFF5A *)TheLivingWorld)->rva002BFFD4((Rva002BFFD4Template *)this, 0, (unsigned int)m_b0);
		}
		rva005C4B96(rva0056B89F());
	}
}
