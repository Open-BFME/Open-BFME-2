// cl: /Ob0
// ??0Rva0044BD34@@QAE@PBURva004C5DD0Pair@@@Z @0x0044BD34 31B
// Ctor forwarding its Pair arg to the rowed Rva004C5DD0 copy ctor at +8,
// after storing vtable VA 0x00C3EDEC (data RVA 0x0083EDEC) and zeroing +4.
// Evidence: rowed callee copy ctor 0x0044BD00; vtable g_00C3EDEC; caller 0x0044BECE;
// landing unblocks 0x0044BEB9; neighbours Rva004C5DD0Set.cpp / Rva004C5EF0Handle.cpp.
// The retail table at RVA 0x0083EDEC: 2 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0044BE1DRecord@@QAEPAXI@Z")();
void __identifier("?rva0044BD53@Rva0044BD53@@QAEXH@Z")();
}
extern const void *const g_00C3EDEC[2] = {
	(const void *)&__identifier("??_GRva0044BE1DRecord@@QAEPAXI@Z"), // slot 0 0x0044BE1D
	(const void *)&__identifier("?rva0044BD53@Rva0044BD53@@QAEXH@Z"), // slot 1 0x0044BD53
};

#include "../../Include/Common/Rva004C5DD0Ref.h"

#include "../../Include/Common/Rva004C5DD0Pair.h"

#include "../../Include/Common/Rva004C5DD0.h"

struct Rva004C5DD0Slot
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;
};

class __declspec(novtable) Rva0044BD34
{
public:
	explicit Rva0044BD34(const Rva004C5DD0Pair *p);

private:
	const void *m_vptr;
	int m_04;
	Rva004C5DD0Slot m_08;
};

Rva0044BD34::Rva0044BD34(const Rva004C5DD0Pair *p)
{
	*(const void **)this = g_00C3EDEC;
	m_04 = 0;
	((Rva004C5DD0 *)&m_08)->Rva004C5DD0::Rva004C5DD0(*(const Rva004C5DD0 *)p);
}
