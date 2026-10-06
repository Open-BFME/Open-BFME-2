// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002B2EC7@Rva002B2EC7@@QAEXPAUItem002B2EC7@@@Z @0x002B2EC7 57B
// Guarded-pointer setter with same release as 0x002B2EA0: if new differs
// from m_p, release old via prefix rule (virtual slot 0 with 2 or rowed
// delete[] 0x0002FD80, then delete[] result) and store new. Evidence:
// ret 4 one pointer arg; cmp new vs old then je; neighbour /O1.
void __cdecl operator delete[](void *p);

struct Item002B2EC7
{
	virtual void *v0(int a);
};

class Rva002B2EC7
{
public:
	void rva002B2EC7(Item002B2EC7 *v);

private:
	Item002B2EC7 *m_p;
};

void Rva002B2EC7::rva002B2EC7(Item002B2EC7 *v)
{
	Item002B2EC7 *p = m_p;
	if (v != p) {
		void *q;
		if (p) {
			int *prefix = (int *)p - 1;
			if (*prefix)
				q = p->v0(2);
			else {
				::operator delete[](prefix);
				q = 0;
			}
		} else {
			q = 0;
		}
		::operator delete[](q);
		m_p = v;
	}
}
