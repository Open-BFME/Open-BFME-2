// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?Rva000ABD70Clear@@YAXXZ @0x000ABD70 42B
// Unlock free function that releases a cached virtual object and clears a
// global Dict. Evidence: ret-via-jmp tail to ?clear@Dict@@QAEXXZ, virtual
// slot-0 call with push 0 returning pointer freed via ??3@YAXPAX@Z, and
// dword [eax] nulled with /O1 and-idiom, globals g_00E00940/g_00E00944.

#include "../../../../GameEngine/Include/Common/Dict.h"

struct Inner
{
	virtual void *get(int x);
};

struct Outer
{
	Inner *m_ptr;
};

class BfmeMapObjectListHolder; extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
extern Dict g_Va00E00944;
#define g_00E00944 g_Va00E00944
// ^ g_00E00944 is only an alias of the owned global g_Va00E00944 (ledger names column).

void Rva000ABD70Clear()
{
	Inner *inner = (*(Outer * *)&BfmeTheMapObjectListHolder)->m_ptr;
	if (inner) {
		void *r = inner->get(0);
		::operator delete(r);
		(*(Outer * *)&BfmeTheMapObjectListHolder)->m_ptr = 0;
	}
	return g_00E00944.clear();
}
