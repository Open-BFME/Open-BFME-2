// ?Rva0045D7E0Notify@@YAXPAXHH@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /MD
// ?Rva0045D7E0Notify@@YAXPAXHH@Z @0x0045D7E0 121B. Free-notify pass over the
// 12 notification vectors of the owner record at +0x58/+0x88/+0xB8 (four
// slots each, stride 0xC per outer iteration), skipping null entries.
// Evidence: every callee in the chain is already rowed -- begin/end pairs are
// read as esi-4/esi -> ?rva001F0410@ObjectCreationList@@QAEXPAX0@Z (0x001F0410),
// esi-0x34/esi-0x30 -> ?rva001E11F8@@QAEXHH@Z (0x001E11F8), and
// esi+0x2C/esi+0x30 -> ?rva002CAC6E@Rva002CA9CA@@QAEXHH@Z (0x002CAC6E);
// neighbours share // cl: /O1 /MD.
//
// The loop counter MUST be `volatile`: without it MSVC coalesces the counter
// onto the dead second-argument slot at [ebp+8] and drops the `push ecx`, so
// the prologue and frame both differ. volatile forces the dedicated [ebp-4]
// slot and the extra callee-saved push that retail has. Two residual encoding
// deltas remain and are recorded in reverse/re_attempts.log.
class ObjectCreationList
{
public:
	void rva001F0410(void *a1, void *a2);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

class Rva002CA9CA
{
public:
	void rva002CAC6E(int a, int b);
};

struct Rva0045D7E0Slot
{
	void **m_begin;
	void **m_end;
	void **m_cap;
};

struct Rva0045D7E0Host
{
	char m_pad[0x58];
	Rva0045D7E0Slot m_a[4];
	Rva0045D7E0Slot m_b[4];
	Rva0045D7E0Slot m_c[4];
};

// ?Rva0045D7E0Notify@@YAXPAXHH@Z present-unmatched
void Rva0045D7E0Notify(void *obj, int a, int b)
{
	volatile int n = 4;
	char *esi = (char *)obj + 0x8C;
	do {
		ObjectCreationList **p1 = *(ObjectCreationList ***)(esi - 4);
		for (; p1 != *(ObjectCreationList ***)(esi); ++p1)
		{
			ObjectCreationList *o = *p1;
			if (o)
				o->rva001F0410((void *)a, (void *)b);
		}
		Rva001E11F8 **p2 = *(Rva001E11F8 ***)(esi - 0x34);
		for (; p2 != *(Rva001E11F8 ***)(esi - 0x30); ++p2)
		{
			Rva001E11F8 *o = *p2;
			if (o)
				o->rva001E11F8(a, b);
		}
		Rva002CA9CA **p3 = *(Rva002CA9CA ***)(esi + 0x2C);
		for (; p3 != *(Rva002CA9CA ***)(esi + 0x30); ++p3)
		{
			Rva002CA9CA *o = *p3;
			if (o)
				o->rva002CAC6E(a, b);
		}
		esi += 0x0C;
	} while (--n != 0);
}