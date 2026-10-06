// cl: /Ireference/shims/bfme2_ascii /Ob0
// ?Rva006BE2E0Copy@@YAPAUBfmeElem60@@PAU1@00@Z @0x006BE2E0 129B
// Forward copy of 0x24-byte BfmeElem60 elements, same layout and flags as
// sibling Rva0087EAA0Fill/Copy TUs. AsciiString at +0x1C via rowed
// StringBase<char>::set 0x000366F0 plus trailing bytes at +0x20/+0x21. Called by BfmeVec60::erase
// 0x006BF5AB. Returns dest+n.
#include "ascii_string.h"

struct BfmeCoord60
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoord60 m_10;
	AsciiString m_1C;
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad[2];
};

BfmeElem60 *Rva006BE2E0Copy(BfmeElem60 *first, BfmeElem60 *last, BfmeElem60 *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int m = n;
		do
		{
			dest->m_00 = first->m_00;
			dest->m_04 = first->m_04;
			dest->m_08 = first->m_08;
			dest->m_0C = first->m_0C;
			dest->m_10 = first->m_10;
			((StringBase<char> &)dest->m_1C).set((const StringBase<char> &)first->m_1C);
			dest->m_20 = first->m_20;
			dest->m_21 = first->m_21;
			++first;
			++dest;
		} while (--m);
	}
	return dest;
}
