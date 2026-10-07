// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004421E1@@UAE@XZ @0x004421E1 211B
// Evidence: chain lane calls 0x57EE5C now rowed; vtable 0x83DD7C at +0; global g_Va00E0333C clear; free +0x3C4 via 0x30830; vector<AsciiString> +0x398 via 0x2CC70; array 8x4 at +0x2F4 via _M 0x629110 with empty dtor at 0xB3FD0; members +0x244 0x57FE6B +0x190 derived Rva0043DAE0 via base 0x57F2DE with vtable 0xC3D95C +0xD0 derived Rva0043DABD via base 0x57EE5C with vtable 0xC3D954 +0x60 0x57E3DB +0x5C ReleaseTreeHintRef 0x7DEEF; base 0x5248D0 pin.
#include <vector>

#include "ascii_string.h"

extern int g_Va00E0333C;
extern "C" void __cdecl free(void *ptr);

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	char m_pad[0x58 - 4];
};

class Rva0057E3DB
{
public:
	virtual ~Rva0057E3DB();
private:
	char m_pad[0x70 - 4];
};

class Rva0057EE5C
{
public:
	virtual ~Rva0057EE5C();
private:
	char m_pad[0xB8 - 4];
};

class Rva0043DABD : public Rva0057EE5C
{
public:
	virtual ~Rva0043DABD() {}
};

class Rva0057F2DE
{
public:
	virtual ~Rva0057F2DE();
private:
	char m_pad[0xB4 - 4];
};

class Rva0043DAE0 : public Rva0057F2DE
{
public:
	virtual ~Rva0043DAE0() {}
};

class Rva0057FE6B
{
public:
	virtual ~Rva0057FE6B();
private:
	char m_pad[0x68 - 4];
};

struct Elem4
{
	int m_x;
	~Elem4();
};

struct Holder5C
{
	TargetRef00217D4C *m_ptr;
	~Holder5C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

struct FreeHolder3C4
{
	char *m_ptr;
	~FreeHolder3C4() { if (m_ptr) free(m_ptr); }
};

class Rva004421E1 : public Rva005248D0
{
public:
	virtual ~Rva004421E1();
private:
	int m_58_gap;
	Holder5C m_5C;
	Rva0057E3DB m_60;
	Rva0043DABD m_D0;
	char m_gap188[0x190 - (0xD0 + 0xB8)];
	Rva0043DAE0 m_190;
	Rva0057FE6B m_244;
	char m_gap2AC[0x2F4 - (0x244 + 0x68)];
	Elem4 m_2F4[8];
	char m_gap314[0x398 - (0x2F4 + 32)];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_398;
	char m_gapVec[0x3C4 - (0x398 + 12)];
	FreeHolder3C4 m_3C4;
};

Rva004421E1::~Rva004421E1()
{
	if (g_Va00E0333C == (int)this)
		g_Va00E0333C = 0;
}
