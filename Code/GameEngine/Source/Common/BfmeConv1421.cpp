// cl: /Od

#include <string.h>
#pragma intrinsic(memset)

void *bfmeBigAllocPR(unsigned n);
void *bfmeAllocVLV(unsigned n);

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc;

template <>
class __node_alloc<true, 0>
{
private:
	static void *_M_allocate(unsigned int n);
	friend void *::bfmeAllocVLV(unsigned int n);
};
}

struct BfmeHdrVLV
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void *bfmeAllocVLV(unsigned requestedSize)
{
	BfmeHdrVLV *n1;
	unsigned n3;
	unsigned n2;

	n3 = requestedSize + 0x18;
	if (n3 > 0x80)
		n2 = (unsigned)bfmeBigAllocPR(n3);
	else
		n2 = (unsigned)_STL::__node_alloc<true, 0>::_M_allocate(n3);
	n1 = (BfmeHdrVLV *)n2;
	memset(n1, 0xa3, n3);
	n1->m_bfmeTag = 0xdeba;
	n1->m_bfmeVer = 1;
	n1->m_bfmeSize = requestedSize;
	return n1 + 1;
}
