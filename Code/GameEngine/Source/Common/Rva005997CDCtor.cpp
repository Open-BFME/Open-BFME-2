// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// stlport
//
// ??0Rva005997CD@@QAE@H@Z @0x00599784 73B
// Ctor of Rva005997CD (dtor at 0x005997CD): two list<int> at +0/+4 via rowed
// List_base ctor 0x004EC36C, AsciiString at +8 zeroed, int at +0xC from arg,
// bool at +0x10 false, returns this. Evidence: abuts dtor, same members,
// EH_prolog plus List_base twice, ret-4 single int arg, 1 caller.
#include <list>
#include "ascii_string.h"

class Rva005997CD
{
public:
	Rva005997CD(int x);
	~Rva005997CD();
private:
	_STL::list<int> m_list0;
	_STL::list<int> m_list1;
	AsciiString m_str;
	int m_val;
	bool m_flag;
};

Rva005997CD::Rva005997CD(int x) : m_val(x), m_flag(false)
{
}
