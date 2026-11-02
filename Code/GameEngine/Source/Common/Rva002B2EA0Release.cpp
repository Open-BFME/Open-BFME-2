// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002B2EA0@Rva002B2EA0@@QAEXXZ @0x002B2EA0 39B
// Conditional release of a prefixed guarded pointer: null or zero-prefix goes
// to rowed operator delete[] 0x0002FD80, a nonzero prefix first calls
// virtual slot 0 with 2 and deletes its return. Evidence: caller 0x002B7529
// (lea ecx+8 no pushes = __thiscall no args); neighbours are /O1.
#include <new>

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
	Rva002B2EA0Item *guardedItem = m_p;
	void *q;
	if (guardedItem) {
		int *prefix = (int *)guardedItem - 1;
		if (*prefix)
			q = guardedItem->v0(2);
		else {
			::operator delete[](prefix);
			q = 0;
		}
	} else {
		q = 0;
	}
	::operator delete[](q);
}
