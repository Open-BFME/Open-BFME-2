// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00598192@Rva00598192@@QAEHABVAsciiString@@@Z @0x00598192 51B via list count with StringBase compare
// Evidence: thiscall ret4 one AsciiString arg; list at +0x14 with int payloads; payload+0xC AsciiString compared via rowed StringBase<char>::compare 0x000069D6; callers unclaimed 0x00598202 0x0059858C
#include <list>
#include "ascii_string.h"
struct Rva00598192Item
{
	char m_pad00[0xC];
	AsciiString m_name;
};
class Rva00598192
{
public:
	int rva00598192(const AsciiString &key);
private:
	char m_pad00[0x14];
	_STL::list<int> m_list;
};
int Rva00598192::rva00598192(const AsciiString &key)
{
	int count = 0;
	for (_STL::list<int>::iterator it = m_list.begin(); it._M_node != m_list.end()._M_node; ++it) {
		Rva00598192Item *item = (Rva00598192Item *)(int)*it;
		if (item->m_name.compare(key) == 0)
			++count;
	}
	return count;
}
