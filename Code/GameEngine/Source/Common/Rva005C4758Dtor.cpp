// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005C4758@@UAE@XZ @0x005C4758 75B: dtor with two AsciiStrings and Rva005C45FE tree member, vtable data 0x008633A0, caller 0x005C473C deleting dtor, prev StrengthenArmy getter
#include "ascii_string.h"

class Rva005C45FE
{
public:
	void *m_header;
	int m_flag;
	void rva005C4667();
	~Rva005C45FE();
};

class Rva005C4758Base
{
public:
	virtual ~Rva005C4758Base();
	AsciiString m_a;
};

inline Rva005C4758Base::~Rva005C4758Base()
{
}

class __declspec(novtable) Rva005C4758 : public Rva005C4758Base
{
public:
	int m_unk08;
	AsciiString m_b;
	Rva005C45FE m_tree;
	~Rva005C4758();
};

Rva005C4758::~Rva005C4758()
{
}
