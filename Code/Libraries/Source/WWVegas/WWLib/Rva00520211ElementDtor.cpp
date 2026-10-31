// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode /I.
//
// ??1Rva00520211Element@@QAE@XZ
// RVA 0x0051FB52 size 135. The byte-verified vector helpers at 0x5200F4,
// 0x52010D and 0x520211 advance by 0x50; this is an 80-byte element view.
// Target calls show cleanup at +0x44/+0x38/+0x2C, then opaque subobject
// destructors at +0x20/+0x14, AsciiString teardown at +0x0C, and the pinned
// wide-string teardown at +0x04. The three pointer owners and two opaque
// subobject identities are only field-level reconstructions, not application
// identity claims.

#include "ascii_string.h"

class BfmeWideString000543F5
{
public:
	~BfmeWideString000543F5();

private:
	char *m_text;
};

class Rva0039C151Subobject
{
public:
	~Rva0039C151Subobject();

private:
	char m_pad[12];
};

class Rva004EE501Subobject
{
public:
	~Rva004EE501Subobject();

private:
	char m_pad[12];
};

void __cdecl Rva00030830GameFree(void *);

struct Rva00520211FreeOwner
{
	void *m_block;
	int m_unused04;
	int m_unused08;

	~Rva00520211FreeOwner()
	{
		if (m_block != 0)
			Rva00030830GameFree(m_block);
	}
};

// Native destroy/fill helpers advance by 0x50; field identities stay opaque.
struct Rva00520211Element
{
	int m_unknown00;
	BfmeWideString000543F5 m_wide04;
	int m_unknown08;
	AsciiString m_ascii0C;
	int m_unknown10;
	Rva0039C151Subobject m_subobject14;
	Rva004EE501Subobject m_subobject20;
	Rva00520211FreeOwner m_owned2C;
	Rva00520211FreeOwner m_owned38;
	Rva00520211FreeOwner m_owned44;
	Rva00520211Element(const Rva00520211Element &);
	Rva00520211Element &operator=(const Rva00520211Element &);
	~Rva00520211Element();
};

Rva00520211Element::~Rva00520211Element()
{
}
