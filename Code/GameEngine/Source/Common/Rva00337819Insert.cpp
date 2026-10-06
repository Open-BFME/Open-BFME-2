// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva00337819Insert@@YAXPAVRva002E9E70@@0VRva003371B1@@H@Z @0x00337819 118B sorted-range insert.
// Evidence: retail 118B EH with __EH_prolog FuncInfo 0x00B7C328; callees rowed StringBase compare 0x000069D6 and Rva002E9E70 copy 0x003372EC and Rva003371B1 copy 0x003371B1 and Rva003377A1Copy 0x003377A1 plus pin dtor 0x003372B7 and just-landed insert 0x00337424; caller 0x00337985.
#include "ascii_string.h"
#include <new.h>

class Rva002E9E70
{
public:
	Rva002E9E70(const Rva002E9E70 &other) throw();
	AsciiString m_name;
	unsigned char m_flag4;
	unsigned char _pad5[3];
	unsigned char m_vec[12];
};

class Rva003371B1
{
public:
	Rva003371B1(const Rva003371B1 &other);
	~Rva003371B1();
	AsciiString m_name;
	unsigned char _pad[16];
};

Rva002E9E70 *Rva003377A1Copy(Rva002E9E70 *first, Rva002E9E70 *last, Rva002E9E70 *result) throw();
void Rva00337424Insert(Rva002E9E70 *pos, Rva003371B1 value, int unused);

void Rva00337819Insert(Rva002E9E70 *first, Rva002E9E70 *last, Rva003371B1 value, int unused)
{
	if (((const StringBase<char> &)value.m_name).compare((const StringBase<char> &)first->m_name) < 0)
	{
		Rva003377A1Copy(first, last, last + 1);
		__assume(first != 0);
		new (first) Rva002E9E70(*(const Rva002E9E70 *)&value);
	}
	else
	{
		Rva00337424Insert(last, value, unused);
	}
}
