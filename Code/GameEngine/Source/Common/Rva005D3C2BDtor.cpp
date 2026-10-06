// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva005D3C2B@@UAE@XZ
// Banked 123-byte virtual destructor at RVA 0x005D3C2B; no original application class name asserted.
// Target: Ghidra [0x005D3C2B,0x005D3CA6), RET0; constructor 0x005D3E06
// stores the same derived table 0x00C7598C. Rowed owner reset 0x0057873E
// deletes this object. Native member cleanup proves AsciiString +8, 12-byte
// Rva0052413E +0xC, reference holders +0x1C/+0x24 and the conditional flag +0x30.
// Cleanup calls 0x005D3AF2,0x005D3B9A,0x0007DEEF,0x0052413E,0x00036410
// have full rowed bodies. Base table store is 0x00C75908.
// Structural guide: verified sibling Rva005794EDDtor.cpp; member positions
// above come from this target, not from that sibling. Volatile accesses retain
// the observed vptr-store/flag-test order; they do not assert donor qualifiers.
// Both-volatile trial passes explain_mismatch for all 123 bytes, but the
// address-named vtable externs have no established linkable definitions.
// Do not land until those providers and the complete dependency gate pass.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0xC];
};

extern const void *const g_00C7598C[];
extern const void *const g_00C75908[];

class Rva005D3C2BBase
{
public:
	virtual ~Rva005D3C2BBase();
};

// ??1Rva005D3C2BBase@@UAE@XZ present-unmatched
inline Rva005D3C2BBase::~Rva005D3C2BBase()
{
	*(const void **)this = g_00C75908;
}

struct Rva005D3C2BReferenceHolder
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva005D3C2BReferenceHolder() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva005D3AF2 {public: void rva005D3AF2();};
class Rva005D3B9A {public: void rva005D3B9A();};
class __declspec(novtable) Rva005D3C2B : public Rva005D3C2BBase
{
public:
	virtual ~Rva005D3C2B();
	
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	void *m_18;
 Rva005D3C2BReferenceHolder m_1C;
 int m_20;
 Rva005D3C2BReferenceHolder m_24;
 int m_28,m_2C;
 volatile bool m_30;
};

Rva005D3C2B::~Rva005D3C2B()
{
	*(const void *volatile *)this = g_00C7598C;
 if(m_30) {
  ((Rva005D3AF2*)this)->rva005D3AF2();
  ((Rva005D3B9A*)this)->rva005D3B9A();
 }
}

