// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva00337424Insert@@YAXPAVRva002E9E70@@VRva003371B1@@H@Z @0x00337424 85B sorted insert.
// Evidence: retail 85B EH with __EH_prolog FuncInfo 0x00B7C304; callees rowed copy ctor 0x003372EC and StringBase compare 0x000069D6 plus pin dtor 0x003372B7; callers 0x00337570 and 0x0033786F; prev/next 0x0033738B and 0x00337501 in Rva0033738BCopy.cpp.
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
	~Rva003371B1();
	AsciiString m_name;
	unsigned char _pad[16];
};

void Rva00337424Insert(Rva002E9E70 *pos, Rva003371B1 value, int unused)
{
	Rva002E9E70 *probe = pos - 1;
	while (((const StringBase<char> &)value.m_name).compare((const StringBase<char> &)((Rva002E9E70 *)probe)->m_name) < 0)
	{
		__assume(pos != 0);
		new (pos) Rva002E9E70(*probe);
		pos = probe;
		--probe;
	}
	__assume(pos != 0);
	new (pos) Rva002E9E70(*(const Rva002E9E70 *)&value);
}
