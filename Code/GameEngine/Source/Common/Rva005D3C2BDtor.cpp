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

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../Include/Common/Rva0052413E.h"

// The retail table at RVA 0x0087598C: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?getDataLength@NetWrapperCommandMsg@@QAEIXZ")();
void __identifier("?rva005D3CCD@Rva005D3B9A@@QAEXH@Z")();
void __identifier("?get@Rva00373C9FByteField@@QBEEXZ")();
void __identifier("?ShowCommandPoints@SelectionUIImpl@StrategicHUD@@QAEXHH@Z")();
void __identifier("?HideCommandPoints@SelectionUIImpl@StrategicHUD@@QAEXXZ")();
void __identifier("?get@Rva00091A25LeaField@@QBEPAXXZ")();
void __identifier("?rva005D3DD5@Rva005D3CA6@@QAEXABUTreeHintRef00217D4C@@@Z")();
void __identifier("?get@Rva00498802ByteField@@QBEEXZ")();
void __identifier("?Show@SelectionUIImpl@StrategicHUD@@QAEXXZ")();
void __identifier("?Hide@SelectionUIImpl@StrategicHUD@@QAEXXZ")();
void __identifier("?rva005D3D97@SelectionUIImpl@StrategicHUD@@QAEXXZ")();
}
extern const void *const g_00C7598C[11] = {
	(const void *)&__identifier("?getDataLength@NetWrapperCommandMsg@@QAEIXZ"), // slot 0 0x0030D377
	(const void *)&__identifier("?rva005D3CCD@Rva005D3B9A@@QAEXH@Z"), // slot 1 0x005D3CCD
	(const void *)&__identifier("?get@Rva00373C9FByteField@@QBEEXZ"), // slot 2 0x00373C9F
	(const void *)&__identifier("?ShowCommandPoints@SelectionUIImpl@StrategicHUD@@QAEXHH@Z"), // slot 3 0x005D39EA
	(const void *)&__identifier("?HideCommandPoints@SelectionUIImpl@StrategicHUD@@QAEXXZ"), // slot 4 0x005D3A55
	(const void *)&__identifier("?get@Rva00091A25LeaField@@QBEPAXXZ"), // slot 5 0x00091A25
	(const void *)&__identifier("?rva005D3DD5@Rva005D3CA6@@QAEXABUTreeHintRef00217D4C@@@Z"), // slot 6 0x005D3DD5
	(const void *)&__identifier("?get@Rva00498802ByteField@@QBEEXZ"), // slot 7 0x00498802
	(const void *)&__identifier("?Show@SelectionUIImpl@StrategicHUD@@QAEXXZ"), // slot 8 0x005D3CFA
	(const void *)&__identifier("?Hide@SelectionUIImpl@StrategicHUD@@QAEXXZ"), // slot 9 0x005D3D4B
	(const void *)&__identifier("?rva005D3D97@SelectionUIImpl@StrategicHUD@@QAEXXZ"), // slot 10 0x005D3D97
};
// The retail table at RVA 0x00875908: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
int __cdecl _purecall(void);
}
extern const void *const g_00C75908[11] = {
	(const void *)&__identifier("_purecall"), // slot 0 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 1 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 3 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 4 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 5 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 6 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 7 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 8 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 9 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 10 0x0003B810
};

class Rva005D3C2BBase
{
public:
	virtual ~Rva005D3C2BBase();
};

inline Rva005D3C2BBase::~Rva005D3C2BBase()
{
	*(const void **)this = g_00C75908;
}

struct Rva005D3C2BReferenceHolder
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva005D3C2BReferenceHolder() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

#include "../../Include/Common/Rva005D3AF2.h"
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

