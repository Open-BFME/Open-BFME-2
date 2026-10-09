// cl: /MD
// ?Rva0070B5D0Check@@YA_NXZ retail 0x0070B5D0 (72B). Validates the Apt string
// pool's saConstant table at 0x00E18388..0x00E18650 (178 EAStringC entries):
// every entry non-empty and strictly ascending by the rowed
// ?compare008B4260@Rva008B4260StringRef@@QBEHABU1@@Z body at 0x006D36C0, with
// the last entry's comparison skipped. The table and its end global are already
// recovered in Rva0070D9F0Shutdown.cpp; this body is address-derived.

class EAStringC
{
public:
	void *m_pData;
	bool IsEmpty() const;
};

struct Rva008B4260StringRef
{
	int compare008B4260(const Rva008B4260StringRef &other) const;
};

extern EAStringC saConstantAtE18388[];
extern EAStringC g_00E18650;

bool Rva0070B5D0Check()
{
	int i = 0;
	EAStringC *p = saConstantAtE18388;
	do
	{
		if (p->IsEmpty())
			return false;
		++i;
		if (i < 0xb2)
		{
			if (((Rva008B4260StringRef *)p)->compare008B4260(*(Rva008B4260StringRef *)(p + 1)) >= 0)
				return false;
		}
		++p;
	} while ((int)p < (int)&g_00E18650);
	return true;
}

// Native B590..B5C6 drains linked nodes at E18370; next+C, virtual slot11
// first, then scalar deleting destructor slot14, and advances saved next.
// WB17727C0 corroborates the deletion loop (its node next differs at10).
class Rva0070B590Node {public:
 virtual void slot0();virtual void slot1();virtual void slot2();
 virtual void slot3();virtual void slot4();virtual void slot5();
 virtual void slot6();virtual void slot7();virtual void slot8();
 virtual void slot9();virtual void slot10();virtual void slot11();
 virtual void slot12();virtual void slot13();virtual ~Rva0070B590Node();
 unsigned flags;void *string;Rva0070B590Node *next;
};
// Reuse the owned pooled AptString free-list provider at E18370.
class Rva006D6D20;
extern Rva006D6D20 *g_AptStringFreeList;
void Rva0070B590Drain() {
 while(g_AptStringFreeList) {
  Rva0070B590Node *next=((Rva0070B590Node *)g_AptStringFreeList)->next;
  ((Rva0070B590Node *)g_AptStringFreeList)->slot11();
  delete (Rva0070B590Node *)g_AptStringFreeList;
  g_AptStringFreeList=(Rva006D6D20 *)next;
 }
}
