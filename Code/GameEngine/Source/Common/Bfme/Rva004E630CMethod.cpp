// cl: /MD
// ?rva004E630C@Rva004E630C@@QAEPAXI@Z @ 0x004E630C 28B chain: calls rowed 0x004E624D then flag-guarded operator delete returns this. Callees rowed 0x004E624D and 0x0002FD60.
#include "../../../Include/Common/Rva004E624D.h"
#include <new>
struct Rva004E630C
{
	void *rva004E630C(unsigned int flag);
};
void *Rva004E630C::rva004E630C(unsigned int flag)
{
	((Rva004E624D *)this)->rva004E624D();
	if (flag & 1)
		::operator delete(this);
	return this;
}
