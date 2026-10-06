// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6C79@Rva002E6C79@@QAEHXZ @0x002E6C79 20B.
// Honest address name: unclaimed __thiscall double null-checked ptr-chase.
// Byte-exact model: mov eax [ecx] test je to shared false tail then
// mov eax [eax+8] test je to same tail then mov eax [eax+0x30] ret.
// Evidence: 10 callers e.g. 0x002EE1D9 0x002F35DB 0x0052DCEF in UNCLAIMED
// 0x002EE1C7 0x002F35AF 0x0052DC97 which derefs return as pointer pair;
// callees none; prev 0x002E6C4D in Rva002E6C4DGet.cpp and next 0x002E6DC4
// in Rva002E6DC4Check.cpp share /O1 frameless shape; flags /O1 from
// single-chase siblings Rva002E6B06 and Rva002E6AF3.

class Rva002E6C79
{
public:
	int rva002E6C79();
	void *m_ptr;
};

struct Rva002E6C79Mid
{
	char m_pad[8];
	void *m_8;
};

struct Rva002E6C79Inner
{
	char m_pad[0x30];
	int m_30;
};

int Rva002E6C79::rva002E6C79()
{
	if (m_ptr != 0) {
		Rva002E6C79Mid *mid = (Rva002E6C79Mid *)m_ptr;
		if (mid->m_8 != 0)
			return ((Rva002E6C79Inner *)mid->m_8)->m_30;
	}
	return 0;
}
