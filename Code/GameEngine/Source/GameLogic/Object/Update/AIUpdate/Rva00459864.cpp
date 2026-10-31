// cl: /MD
//
// ?rva00459864@Rva00459864@@QAEX_N@Z, retail 0x00459864 95B. Chain via 0x001E42F2.
// Thing at this-0x18 via getDrawable null check then double memset 0x4c tmp
// plus word 0x3f0 at +20 plus rva001E42F2 plus bool arg gating Drawable rva.

// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

#include "../../../../Common/Thing/thing.h"

class Drawable
{
public:
	void rva00274176(bool b);
};

class Rva001E42F2
{
public:
	void rva001E42F2(const int *x);
};

class Rva00459864
{
public:
	void rva00459864(bool flag);
private:
	unsigned char m_pad00[8];
	int m_08;
};

void Rva00459864::rva00459864(bool flag)
{
	Drawable *drawable = (*(Thing **)((char *)this - 0x18))->getDrawable();
	if (drawable == 0)
		return;
	unsigned char tmp[0x4c];
	m_08 = 0;
	memset(tmp, 0, 0x4c);
	memset(tmp, 0, 0x4c);
	*(unsigned short *)(tmp + 20) |= 0x3f0;
	((Rva001E42F2 *)*(Thing **)((char *)this - 0x18))->rva001E42F2((const int *)tmp);
	if (!flag)
		return;
	drawable->rva00274176(false);
}
