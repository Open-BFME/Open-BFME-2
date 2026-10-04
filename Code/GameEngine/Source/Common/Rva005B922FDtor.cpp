// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"
//
// ??1Rva005B922F@@UAE@XZ @0x005B922F 221B
// Dtor with Apt conditional: stores vtable 0x873B70, if this == g_Va00E06480
// closes two screens via rva00223A94 plus AptOnlineHome InitGadgets via
// _bfme_closeAptScreen, clears global, destroys wide member +0x64, base
// Rva005248D0. Evidence: vtables 0x873B70/0x86DB78, globals g_Va00E06480,
// g_00DD3BC0/C4, TheRva00222A8BTarget, literal AptOnlineHome::InitGadgets,
// callees rowed StringBase PBD 0x37BA0 releaseBuffer D/G plus pin close and
// base dtor, caller deleting dtor 0x005B94E5.
//

void _bfme_closeAptScreen(const AsciiString &);

class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};

class Rva00222A8BTarget : public Rva00223A94
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern int g_Va00E06480;
extern const char *g_00DD3BC0;
extern const char *g_00DD3BC4;

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

private:
	char m_pad[0x58 - 4];
};

class Rva0056DC6B : public Rva005248D0
{
public:
	virtual ~Rva0056DC6B();
};

inline Rva0056DC6B::~Rva0056DC6B()
{
}

class Rva005B922F : public Rva0056DC6B
{
public:
	virtual ~Rva005B922F();

private:
	char m_pad[0x64 - 0x58];
	UnicodeString m_64;
};

Rva005B922F::~Rva005B922F()
{
	if ((int)this == g_Va00E06480) {
		{
			AsciiString s(g_00DD3BC0);
			((Rva00223A94 *)TheRva00222A8BTarget)->rva00223A94(&s);
		}
		{
			AsciiString s(g_00DD3BC4);
			((Rva00223A94 *)TheRva00222A8BTarget)->rva00223A94(&s);
		}
		{
			AsciiString s("AptOnlineHome::InitGadgets");
			_bfme_closeAptScreen(s);
		}
		g_Va00E06480 = 0;
	}
}
