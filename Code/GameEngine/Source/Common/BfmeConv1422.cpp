// cl: /Od

#include <string.h>
#pragma intrinsic(memset)

void *bfmeBigAllocPR(unsigned n);
void *bfmeSmallAllocPR(unsigned n);

struct BfmeHdrVLW
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void *bfmeAllocVLW(unsigned payloadSize)
{
	BfmeHdrVLW *n1;
	unsigned n3;
	unsigned n2;

	n3 = payloadSize + 0x18;
	if (n3 > 0x80)
		n2 = (unsigned)bfmeBigAllocPR(n3);
	else
		n2 = (unsigned)bfmeSmallAllocPR(n3);
	n1 = (BfmeHdrVLW *)n2;
	memset(n1, 0xa3, n3);
	n1->m_bfmeTag = 0xdeba;
	n1->m_bfmeVer = 1;
	n1->m_bfmeSize = payloadSize;
	return n1 + 1;
}
