// cl: /MD
// ?Rva000B5179Apply@@YAXPAXPAXPAX@Z 0x000B5179 97B evidence: leaf via rowed 0x000B304B; outer 6 buckets at +0xA4 stride 0xC end at +0xB0 flags at +0xF6 bit 8 at +0xF4 inner stride 0x3C check +8
#include "../../Include/Common/Rva000B304B.h"

struct Elem000B5179
{
	char _p00[8];
	int m08;
	char _rest[0x3C - 12];
};

struct Bucket000B5179
{
	char _p00[4];
	Elem000B5179 *m_begin;
	Elem000B5179 *m_end;
};

struct Cont000B5179
{
	char _p00[0xA8];
	Bucket000B5179 m_buckets[6];
	char _pF0[0xF4 - 0xF0];
	unsigned char mF4;
};

struct Flags000B5179
{
	char _p00[0xF6];
	unsigned char m_flags[6];
};

void Rva000B5179Apply(void *a1_, void *a2_, void *a3_)
{
	Flags000B5179 *flags = (Flags000B5179 *)a1_;
	Cont000B5179 *container = (Cont000B5179 *)a2_;
	void *provider = a3_;
	if (flags == 0 || container == 0 || provider == 0)
		return;
	if ((container->mF4 & 8) == 0)
		return;
	Elem000B5179 **ppEnd = &container->m_buckets[0].m_end;
	for (int i = 0; i < 6; i++, ppEnd = (Elem000B5179 **)((char *)ppEnd + 0xC)) {
		if (flags->m_flags[i] != 0) {
			Elem000B5179 *beg = *(ppEnd - 1);
			for (Elem000B5179 *elems = beg; elems != *ppEnd; ++elems) {
				if (elems->m08 != 0)
					((Rva000B304B *)elems)->setMuzzleFlashHidden(provider, true);
			}
		}
	}
}
