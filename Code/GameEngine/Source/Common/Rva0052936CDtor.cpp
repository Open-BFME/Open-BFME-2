// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva0052936C@@QAE@XZ @0x0052936C 103B
// Evidence: destructor shape via rowed callees 0x00528B98 0x00036410 0x00524436 0x0052413E plus array ??_M count 6 size 0x14 at +0x64; callers 0x00529A62 0x00529B40; neighbours Rva00529130Setter/DispDwordFieldGetters.
#include "ascii_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0x0C];
};

class Rva00524436
{
public:
	~Rva00524436();
private:
	char m_pad[0x18];
};

class Rva00528B98
{
public:
	void rva00528B98();
private:
	void *m_owner;
	bool m_flag04;
	char m_pad[3];
};

struct Holder38
{
	Rva00528B98 m_inner;
// ??1Holder38@@QAE@XZ present-unmatched
	~Holder38() { m_inner.rva00528B98(); }
};

struct ArrayElem
{
	AsciiString m_str;
	char m_pad[0x10];
// ??1ArrayElem@@QAE@XZ present-unmatched
	~ArrayElem() {}
};

class Rva0052936C
{
public:
	~Rva0052936C();
private:
	char m_pad00[8];
	Rva0052413E m_08;
	Rva00524436 m_14;
	char m_pad2C[8];
	AsciiString m_34;
	Holder38 m_38;
	char m_pad40[0x24];
	ArrayElem m_64[6];
};

Rva0052936C::~Rva0052936C() {}
