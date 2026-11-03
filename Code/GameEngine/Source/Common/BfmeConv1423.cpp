// cl: /Od

#include <string.h>
#pragma intrinsic(memset)

void bfmeBigFreePM(void *p);

void bfmeFreeVLX(void *p, unsigned n);

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc;

template <>
class __node_alloc<true, 0>
{
private:
	static void _M_deallocate(void *p, unsigned int n);
	friend void ::bfmeFreeVLX(void *p, unsigned int n);
};
}

struct BfmeHdrVLX
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void bfmeFreeVLX(void *allocation, unsigned payloadSize)
{
	BfmeHdrVLX *n1;
	unsigned n2;
	unsigned n3;

	n1 = (BfmeHdrVLX *)((char *)allocation - 0x10);
	for (n2 = (unsigned)n1 + 8; n2 < (unsigned)allocation; ++n2)
	{
	}
	n3 = payloadSize + 0x18;
	for (n2 = (unsigned)allocation + payloadSize; n2 < (unsigned)n1 + n3; ++n2)
	{
	}
	n1->m_bfmeTag = 0xdebd;
	memset(allocation, 0xa3, payloadSize);
	if (n3 > 0x80)
		bfmeBigFreePM(n1);
	else
		_STL::__node_alloc<true, 0>::_M_deallocate(n1, n3);
}
