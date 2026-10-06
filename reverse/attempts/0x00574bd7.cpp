// ?rva00574BD7@Rva00574ABB@@QAEPAPAV1@PAPAV1@@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /MD /EHs-c- /Oy-
// ?rva00574BD7@Rva00574ABB@@QAEPAPAV1@PAPAV1@@Z @0x00574BD7 68B via Clone-from-this twin of Rva005CE2A1Create
// Evidence: VTABLE slot 1 of table 0x0086E498 (data_ledger vtable ??_7Rva00574ABB@@6B@);
// new 0x10, vtable 0x0086E498, copy +8/+0xC from this, refcount and out-param store like 0x005CE2A1.
#include <new>

extern const void *const g_00C6E498[];

class Rva00574ABB
{
public:
	struct Payload { int v[2]; };
	virtual ~Rva00574ABB();
	int m_ref; // +4
	Payload m_data; // +8
	Rva00574ABB **rva00574BD7(Rva00574ABB **out);
};

void *__cdecl operator new(unsigned int size);

Rva00574ABB **Rva00574ABB::rva00574BD7(Rva00574ABB **out)
{
	int state;
	__asm { and state, 0 }
	Rva00574ABB *p = (Rva00574ABB *)operator new(0x10);
	if (p != 0) {
		*(void **)p = (void *)g_00C6E498;
		p->m_ref &= 0;
		p->m_data = m_data;
	} else {
		p = 0;
	}
	*out = p;
	if (p != 0)
		p->m_ref++;
	return out;
}
