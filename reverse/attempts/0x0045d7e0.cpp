// ?Rva0045D7E0Notify@@YAXPAXHH@Z
// partial score=0.98 date=2026-10-04
// cl: /O1 /MD
//
// ?Rva0045D7E0Notify@@YAXPAXHH@Z retail 0x0045D7E0 121B.
// Free notify over 12 vectors at +0x58/+0x88/+0xB8 (4 each stride 0xC).
// Evidence: chain lane all callees rowed; begin/end pairs per iteration
// (esi-4/esi -> ObjectCreationList 0x001F0410, esi-0x34/esi-0x30 ->
// Rva001E11F8 0x001E11F8, esi+0x2C/esi+0x30 -> Rva002CA9CA 0x002CAC6E);
// neighbours share // cl: /O1 /MD.
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
	int n = 4;
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
