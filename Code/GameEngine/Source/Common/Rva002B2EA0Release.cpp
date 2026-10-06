// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002B2EA0@Rva002B2EA0@@QAEXXZ @0x002B2EA0 39B
// Conditional release of a prefixed guarded pointer: null or zero-prefix goes
// to rowed operator delete[] 0x0002FD80, a nonzero prefix first calls
// virtual slot 0 with 2 and deletes its return. Evidence: caller 0x002B7529
// (lea ecx+8 no pushes = __thiscall no args); neighbours are /O1.
void __cdecl operator delete[](void *p);

class Rva002B2EA0Item
{
public:
	virtual void *v0(int a);
};

class Rva002B2EA0
{
public:
	void rva002B2EA0();

private:
	Rva002B2EA0Item *m_p;
};

void Rva002B2EA0::rva002B2EA0()
{
	Rva002B2EA0Item *p = m_p;
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
}
