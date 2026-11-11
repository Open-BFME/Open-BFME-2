// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0055CE92Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABUVec001F8810@@@Z at 0x0055CE92 size 24
// Evidence: chain lane via 0x001F89E2; conditional Vec write skipping zero IsZero 0x0055CCEF on +0x14 then tail-jmp Write; neighbours are parsers in same dir.

namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	void _M_put_nowiden(char const *s);
	void _M_put_char(char c);
};
}

#include "../../Include/Common/Vec001F8810.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

int Rva0055CCEFIsZero(const RGBColor &color);
void Rva001F89E2Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Vec001F8810 &value);

void Rva0055CE92Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Vec001F8810 &value)
{
	if ((unsigned char)Rva0055CCEFIsZero(reinterpret_cast<const RGBColor &>(value)))
		return;
	Rva001F89E2Write(os, pad, key, value);
}
