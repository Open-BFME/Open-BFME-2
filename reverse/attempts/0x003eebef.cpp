// ?rva003EEBEF@Rva003EEBEF@@QAEXH@Z
// partial score=0.9375333885972184 date=2026-10-09
// ?rva003EEBEF@Rva003EEBEF@@QAEXH@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD
// ?rva003EEBEF@Rva003EEBEF@@QAEXH@Z 0x003EEBEF 116B
// Evidence: finish from stash 0.93; gate on holder+0x2c then loop over 0x14-stride array calling rowed 0x0020EAF6 and rowed 0x003EE84A; prev 0x003EEBC4 next 0x003EEE64 same TU.
typedef int Int;
class Rva0020E89C;
class Rva0020E90FView
{
public:
	char m_pad[0x2d];
};
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
	char m_pad00[8];
	Rva0020E90FView *m_holder;
};
class Rva002BA8F1Logic
{
public:
	char m_pad00[0xB0];
	Rva0020EAF6View *m_B0;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva003EEBEFElem
{
	char m_pad00[4];
	Int m_index;
	Int m_arg;
	char m_pad08[0x14 - 12];
};
struct Rva003EEBEFArg
{
	char m_pad00[0x3c];
	Rva003EEBEFElem *m_begin;
	Rva003EEBEFElem *m_end;
};
class Rva003EE84A
{
public:
	void rva003EE84A(Int a, Int b);
};
class Rva003EEBEF
{
public:
	void rva003EEBEF(Int p);
};
// ?rva003EEBEF@Rva003EEBEF@@QAEXH@Z present-unmatched
void Rva003EEBEF::rva003EEBEF(Int p)
{
	Rva0020E90FView *holder = ((Rva002BA8F1Logic*)TheLivingWorldLogic)->m_B0->m_holder;
	void *gate;
	if(holder) gate=(char*)holder+0x2c;
	else gate=0;
	if (gate == 0)
		return;
	Rva003EEBEFArg *arg = (Rva003EEBEFArg *)p;
	int count = (int)(((char *)arg->m_end - (char *)arg->m_begin) / 0x14);
	if (count <= 0)
		return;
	int offset = 0;
	int remaining = count;
	do {
		int index = *(int *)(offset + (unsigned int)arg->m_begin + 4);
		Rva0020E89C *found = ((Rva002BA8F1Logic*)TheLivingWorldLogic)->m_B0->rva0020EAF6(index);
		((Rva003EE84A *)this)->rva003EE84A((Int)found, (Int)((char *)arg->m_begin + offset + 8));
		offset += 0x14;
		--remaining;
	} while (remaining != 0);
}
