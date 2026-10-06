// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002E0D02Get@@YAHPAURva002E0D02Arg@@@Z @ 0x002E0D02 100B sum via indexed get.
// Evidence: neighbours Rva002E0CD4Get plus Rva002E0D66Method share /O1; rowed get@Rva0040CB2CIndexedField 0x0040CB2C plus EBP frame plus and-mem-zero plus sar-3 so /O1; ret is cdecl 1 arg; unblocks 0x005235D5 plus 0x005D13E2.
struct Entry8
{
	int first;
	void *second;
};
class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
	char m_pad[0x40];
	Entry8 *m_begin;
	Entry8 *m_end;
};
struct Mid78Holder
{
	char m_pad[0x78];
	Rva0040CB2CIndexedField *m_78;
};
struct Elem
{
	Mid78Holder *m_ptr;
};
struct Pair1B8
{
	Elem *m_1B8;
	Elem *m_1BC;
};
struct Rva002E0D02Arg
{
	char m_pad[0x1B8];
	Pair1B8 m_pair;
};
int __cdecl Rva002E0D02Get(Rva002E0D02Arg *arg)
{
	Pair1B8 *p = &arg->m_pair;
	Elem *end = p->m_1BC;
	Elem *b = p->m_1B8;
	int total = 0;
	if (b != end) {
		do {
			Rva0040CB2CIndexedField *f = b->m_ptr->m_78;
			int cnt = (int)((char *)f->m_end - (char *)f->m_begin) >> 3;
			int i = 0;
			if (cnt > 0) {
				do {
					int v = f->get(i);
					total += *(int *)((char *)v + 0x90);
					++i;
				} while (i < cnt);
			}
			b = (Elem *)((char *)b + 4);
		} while (b != end);
	}
	return total;
}
