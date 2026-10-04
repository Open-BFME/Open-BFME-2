// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??1Rva00510CC3@@QAE@XZ 68B @0x00510CC3: dtor calls holder clear at +0x24 then member dtor Rva0052413E at +0x14 then member dtor Rva0050EA74 at +0x00 with EH states 1 0 -1. Evidence: rowed callees 0x0050F6AD 0x0052413E 0x0050EA22 plus caller deleting dtor 0x00510CA7 plus layout from Rva0050EA74Ctor 0x14 plus Rva0052413E 0xC plus gap 4.
#include "ascii_string.h"

class Rva0050EA74
{
public:
	virtual ~Rva0050EA74();
private:
	char m_pad[0x14 - 4];
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0xC];
};

class Rva0050F6AD
{
public:
	void rva0050F6AD();
private:
	char m_pad[4];
};

class Rva00510CC3
{
public:
	~Rva00510CC3();
private:
	Rva0050EA74 m_00;
	Rva0052413E m_14;
	char m_pad20[4];
	Rva0050F6AD m_24;
};

Rva00510CC3::~Rva00510CC3()
{
	m_24.rva0050F6AD();
}
