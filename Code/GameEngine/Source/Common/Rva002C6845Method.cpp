// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002C6845@Rva002C6845@@QAEXXZ @0x002C6845 52B
// Leaf with pinned name; skips when flag at +0x168 set, otherwise refreshes via rowed 0x004EBF93, runs rowed 0x002C5F65 on object at +0x164, then sets byte at +4 of that object when global +0x85D flag set.
// Evidence: pin name, caller 0x004E9507, callees rowed, prev/next same dir with /O1.
class Rva004EBF93
{
public:
	void rva004EBF93();
};

class Rva002C5F65
{
public:
	void rva002C5F65();
};

class Rva002A8F24;
extern Rva002A8F24 *g_00DFEEF8;

class Rva002C6845
{
public:
	void rva002C6845();
private:
	char m_pad00[0x164];
	void *m_ptr164;
	unsigned char m_flag168;
};

void Rva002C6845::rva002C6845()
{
	if (m_flag168)
		return;
	((Rva004EBF93 *)this)->rva004EBF93();
	char *base = (char *)this + 0x164;
	Rva002C5F65 *p = *(Rva002C5F65 **)base;
	p->rva002C5F65();
	if (((unsigned char *)g_00DFEEF8)[0x85D] == 0)
		return;
	Rva002C5F65 *q = *(Rva002C5F65 **)base;
	((unsigned char *)q)[4] = 1;
}
