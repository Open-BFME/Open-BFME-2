// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// Opaque single-member destructors that tail-call the folded AsciiString
// member destructor at 0x0036410, the same shape as Bucket::~Bucket (vtable
// store, this-adjust, tail jump). Each class below is a distinct retail
// vtable whose owner identity is unproven; the member offset is retail
// measured per body. One ledger row per destructor, landed one commit at
// a time; the AsciiStringMember declaration is shared and never defined
// (it resolves to the 0x36410 fold via symbols.csv).

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class Rva00217537
{
public:
	virtual ~Rva00217537();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

Rva00217537::~Rva00217537()
{
}

class Rva0030714F
{
public:
	virtual ~Rva0030714F();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

Rva0030714F::~Rva0030714F()
{
}

class Rva004E156B
{
public:
	virtual ~Rva004E156B();

private:
	AsciiStringMember m_member04;
};

Rva004E156B::~Rva004E156B()
{
}

class Rva004E194E
{
public:
	virtual ~Rva004E194E();

private:
	char m_pad04[8];
	AsciiStringMember m_member0C;
};

Rva004E194E::~Rva004E194E()
{
}

class Rva004FA830
{
public:
	virtual ~Rva004FA830();

private:
	AsciiStringMember m_member04;
};

inline Rva004FA830::~Rva004FA830()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva004FA830DtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva004FA830DtorInlineAnchor()
{
	static_cast<Rva004FA830 *>(0)->Rva004FA830::~Rva004FA830();
}
#pragma inline_depth()

class Rva00538C5F
{
public:
	virtual ~Rva00538C5F();

private:
	AsciiStringMember m_member04;
};

Rva00538C5F::~Rva00538C5F()
{
}

#include "ascii_string.h"

class Rva005C31FB
{
public:
	virtual ~Rva005C31FB();
	Rva005C31FB(int level, const AsciiString &name);
	void rva005C3209();

private:
	int m_level;
	AsciiString m_name;
	bool m_flag0C;
};

// ??0Rva005C31FB@@QAE@HABVAsciiString@@@Z @0x005C31D5 38B: vtable 0x008743F8, level at +4, name copy at +8 via 0x365F0, flag 0 at +0xC.
// Callers at 0x005284F4 0x00528B11 0x005F2856 pass level from GetLevel 0x4128BB plus StringBase temp; new 0x10.
// Sibling dtor at 0x005C31FB plus deleting dtor at 0x005C327F in this TU (/O1 /MD).
Rva005C31FB::Rva005C31FB(int level, const AsciiString &name) : m_level(level), m_name(name), m_flag0C(false)
{
}

Rva005C31FB::~Rva005C31FB()
{
}

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

// ?rva005C3209@Rva005C31FB@@QAEXXZ @0x005C3209 55B: guarded DeleteContent AptCall.
// If flag +0xC is clear return; else pass level +4 and name text +8 (or
// g_Rva0107301CEmptyString when null) with literal "DeleteContent" to rowed
// 0x00524EF4, then clear flag. Evidence: retail cmp/je flag, mov/test/add-8
// string select, pushes to 0x00524EF4, neighbours Rva005C31FB ctor in this TU,
// precedent Rva005C394DGo.cpp, callers 0x005C7954 0x005E0DC0.
void Rva005C31FB::rva005C3209()
{
	if (!m_flag0C)
		return;
	char *t = *(char **)(void *)&m_name;
	const char *s = t ? t + 8 : "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level, s, "DeleteContent");
	m_flag0C = false;
}
