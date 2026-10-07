// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
//
// More 10-byte atexit cleanup thunks from the 0x007B68xx..0x007B9xxx strip, the
// companions of Rva007B6880Thunks.cpp (kept in a separate unit so concurrent
// work on that file does not collide). Each is ecx = &global then a tail jump
// to an already-rowed destructor or cleanup member: the compiler-generated
// cleanup a translation unit registers for a file-scope object. Many are
// per-TU copies of header-level objects (AsciiString keys, ATL's
// _AtlWinModule, FX default infos). The owning TUs are unrecovered, so each
// keeps an honest address name and its global an address-named extern.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Include/Common/Rva00041004Lock.h"

namespace ATL
{
	class CAtlWinModule
	{
	public:
		void Term();
	};
}

class BfmeStringTailRecord144
{
public:
	virtual ~BfmeStringTailRecord144();
};

class Rva000E19A3
{
public:
	virtual ~Rva000E19A3();
};

class Rva00049C38ADwordImmSetter
{
public:
	void apply();
};

class Rva000AD6F4
{
public:
	void clear();
};

class Rva00221027
{
public:
	virtual ~Rva00221027();
};

class Rva0023DBC3
{
public:
	~Rva0023DBC3();
};

namespace FXParticleSystem
{
	class OutwardEmissionVelocityInfo
	{
	public:
		virtual ~OutwardEmissionVelocityInfo();
	};
}

class Rva004E5654
{
public:
	virtual ~Rva004E5654();
};

class PlayerPosition
{
public:
	~PlayerPosition();
};

class Rva002390CB
{
public:
	~Rva002390CB();
};

class Rva00574499
{
public:
	~Rva00574499();
};

class Rva00579731
{
public:
	virtual ~Rva00579731();
};

class Rva0057A4E7
{
public:
	~Rva0057A4E7();
};

class Rva0005970E6DwordImmSetter
{
public:
	void apply();
};

class Rva005CB3BE
{
public:
	~Rva005CB3BE();
};

class Rva005E16DA
{
public:
	virtual ~Rva005E16DA();
};

class Rva005E3DE8
{
public:
	~Rva005E3DE8();
};

class Rva005E7529
{
public:
	~Rva005E7529();
};

class SimpleFileFactoryClass
{
public:
	virtual ~SimpleFileFactoryClass();
};

class CDCCache
{
public:
	~CDCCache();
};

class BfmeThingDXB
{
public:
	void bfmeGoDXB();
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
};

extern unsigned int g_00DDE0AC;
extern unsigned g_Va00DE1DC0;
extern unsigned g_Va00DEBC64;
extern unsigned g_Va00DEBCA0;
extern unsigned g_Va00DFE3E8;
extern unsigned g_Va00DFE420;
extern unsigned g_Va00DFE440;
extern unsigned g_Va00DFE448;
extern unsigned g_Va00DFE490;
extern unsigned g_Va00DFE49C;
extern unsigned g_Va00DFE4C4;
extern unsigned g_Va00DFE6DC;
extern unsigned g_Va00DFE72C;
extern unsigned g_Va00DFE7A8;
extern unsigned g_Va00DFE940;
extern unsigned g_Va00DFED90;
extern unsigned g_Va00DFED9C;
extern unsigned g_Va00DFEDA8;
extern unsigned g_Va00DFEDB4;
extern unsigned g_Va00DFEDC0;
extern unsigned g_Va00DFEDCC;
extern unsigned g_Va00DFEDD8;
extern unsigned g_Va00DFEDFC;
extern unsigned g_Va00DFEE20;
extern unsigned g_Va00DFF030;
extern unsigned g_Va00DFF044;
extern unsigned g_Va00DFF048;
extern unsigned g_Va00DFF050;
extern unsigned g_Va00DFF054;
extern unsigned g_Va00DFF05C;
extern unsigned g_Va00DFF060;
extern unsigned g_Va00DFF0A0;
extern unsigned g_Va00DFF0A4;
extern unsigned g_Va00DFF0C4;
extern unsigned g_Va00DFF168;
extern unsigned g_Va00E02040;
extern unsigned g_Va00E020C8;
extern unsigned g_Va00E02158;
extern unsigned g_Va00E021F8;
extern unsigned g_Va00E022A8;
extern unsigned g_Va00E022AC;
extern unsigned g_Va00E022C4;
extern unsigned g_Va00E022E8;
extern unsigned g_Va00E028C4;
extern unsigned g_Va00E02D68;
extern unsigned g_Va00E02D70;
extern unsigned g_Va00E02D90;
extern unsigned g_Va00E02D94;
extern unsigned g_Va00E02E70;
extern unsigned g_Va00E02E74;
extern unsigned g_Va00E03080;
extern unsigned g_Va00E030E4;
extern unsigned g_Va00E03238;
extern unsigned g_Va00E032E8;
extern unsigned g_Va00E03318;
extern unsigned g_Va00E03324;
extern unsigned g_Va00E03328;
extern unsigned g_Va00E0332C;
extern unsigned g_Va00E03330;
extern unsigned g_Va00E04444;
extern unsigned g_Va00E04448;
extern unsigned g_Va00E0445C;
extern unsigned g_Va00E0447C;
extern unsigned g_Va00E04490;
extern unsigned g_Va00E048F4;
extern unsigned g_Va00E048FC;
extern unsigned g_Va00E0494C;
extern unsigned g_Va00E04954;
extern unsigned g_Va00E04964;
extern unsigned g_Va00E0498C;
extern unsigned g_Va00E04998;
extern unsigned g_Va00E049A0;
extern unsigned g_Va00E049A4;
extern unsigned g_Va00E05E00;
extern unsigned g_Va00E05E04;
extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;
extern unsigned g_Va00E0631C;
extern unsigned g_Va00E06360;
extern unsigned g_Va00E063B8;
extern unsigned g_Va00E063C0;
extern unsigned g_Va00E063D4;
extern unsigned g_Va00E06458;
extern unsigned g_Va00E065EC;
extern unsigned g_Va00E06620;
extern unsigned g_Va00E06710;
extern unsigned g_Va00E06724;
extern unsigned g_Va00E06734;
extern unsigned g_Va00E06748;
extern unsigned g_Va00E08D48;
extern unsigned g_Va00E09E50;
extern unsigned g_Va00E09E60;
extern unsigned g_Va00E0C150;
extern unsigned g_Va00E176A0;

// ?rva007B6AE7@@YAXXZ @ 0x007B6AE7 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B6AE7()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	p->Term();
}

// ?rva007B6B05@@YAXXZ @ 0x007B6B05 (10B): ecx=&g_Va00DE1DC0, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B6B05()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00DE1DC0;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B6DFA@@YAXXZ @ 0x007B6DFA (10B): ecx=&g_Va00DEBC64, tail-jump to rowed ??1Rva000E19A3@@UAE@XZ (0x000E19A3)
void __cdecl rva007B6DFA()
{
	Rva000E19A3 *p = (Rva000E19A3 *)&g_Va00DEBC64;
	p->Rva000E19A3::~Rva000E19A3();
}

// ?rva007B6E36@@YAXXZ @ 0x007B6E36 (10B): ecx=&g_Va00DEBCA0, tail-jump to rowed ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ (0x0049C38A)
void __cdecl rva007B6E36()
{
	Rva00049C38ADwordImmSetter *p = (Rva00049C38ADwordImmSetter *)&g_Va00DEBCA0;
	p->apply();
}

// ?rva007B7650@@YAXXZ @ 0x007B7650 (10B): ecx=&g_Va00DFE3E8, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7650()
{
	AsciiString *p = (AsciiString *)&g_Va00DFE3E8;
	p->~AsciiString();
}

// ?rva007B766E@@YAXXZ @ 0x007B766E (10B): ecx=&g_Va00DFE440, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B766E()
{
	AsciiString *p = (AsciiString *)&g_Va00DFE440;
	p->~AsciiString();
}

// ?rva007B7678@@YAXXZ @ 0x007B7678 (10B): ecx=&g_Va00DFE448, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7678()
{
	AsciiString *p = (AsciiString *)&g_Va00DFE448;
	p->~AsciiString();
}

// ?rva007B76AA@@YAXXZ @ 0x007B76AA (10B): ecx=&g_Va00DFE420, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B76AA()
{
	AsciiString *p = (AsciiString *)&g_Va00DFE420;
	p->~AsciiString();
}

// ?rva007B76E6@@YAXXZ @ 0x007B76E6 (10B): ecx=&g_Va00DFE490, tail-jump to rowed ?clear@Rva000AD6F4@@QAEXXZ (0x000AD6F4)
void __cdecl rva007B76E6()
{
	Rva000AD6F4 *p = (Rva000AD6F4 *)&g_Va00DFE490;
	p->clear();
}

// ?rva007B76FA@@YAXXZ @ 0x007B76FA (10B): ecx=&g_Va00DFE49C, tail-jump to rowed ??1Rva00221027@@UAE@XZ (0x00221027)
void __cdecl rva007B76FA()
{
	Rva00221027 *p = (Rva00221027 *)&g_Va00DFE49C;
	p->Rva00221027::~Rva00221027();
}

// ?rva007B770E@@YAXXZ @ 0x007B770E (10B): ecx=&g_Va00DFE4C4, tail-jump to rowed ?clear@Rva000AD6F4@@QAEXXZ (0x000AD6F4)
void __cdecl rva007B770E()
{
	Rva000AD6F4 *p = (Rva000AD6F4 *)&g_Va00DFE4C4;
	p->clear();
}

// ?rva007B7718@@YAXXZ @ 0x007B7718 (10B): ecx=&g_Va00DFE6DC, tail-jump to rowed ?clear@Rva000AD6F4@@QAEXXZ (0x000AD6F4)
void __cdecl rva007B7718()
{
	Rva000AD6F4 *p = (Rva000AD6F4 *)&g_Va00DFE6DC;
	p->clear();
}

// ?rva007B7736@@YAXXZ @ 0x007B7736 (10B): ecx=&g_Va00DFE72C, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B7736()
{
	UnicodeString *p = (UnicodeString *)&g_Va00DFE72C;
	p->~UnicodeString();
}

// ?rva007B7768@@YAXXZ @ 0x007B7768 (10B): ecx=&g_Va00DFE940, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7768()
{
	AsciiString *p = (AsciiString *)&g_Va00DFE940;
	p->~AsciiString();
}

// ?rva007B7786@@YAXXZ @ 0x007B7786 (10B): ecx=&g_Va00DFE7A8, tail-jump to rowed ??1Rva0023DBC3@@QAE@XZ (0x0023DBC3)
void __cdecl rva007B7786()
{
	Rva0023DBC3 *p = (Rva0023DBC3 *)&g_Va00DFE7A8;
	p->~Rva0023DBC3();
}

// ?rva007B7842@@YAXXZ @ 0x007B7842 (10B): ecx=&g_Va00DFED9C, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B7842()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFED9C;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B784C@@YAXXZ @ 0x007B784C (10B): ecx=&g_Va00DFEDA8, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B784C()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFEDA8;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B7856@@YAXXZ @ 0x007B7856 (10B): ecx=&g_Va00DFEDB4, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B7856()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFEDB4;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B7860@@YAXXZ @ 0x007B7860 (10B): ecx=&g_Va00DFEDC0, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B7860()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFEDC0;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B786A@@YAXXZ @ 0x007B786A (10B): ecx=&g_Va00DFEDCC, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B786A()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFEDCC;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B7874@@YAXXZ @ 0x007B7874 (10B): ecx=&g_Va00DFEDD8, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B7874()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFEDD8;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B787E@@YAXXZ @ 0x007B787E (10B): ecx=&g_Va00DFED90, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B787E()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00DFED90;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B789C@@YAXXZ @ 0x007B789C (10B): ecx=&g_Va00DFEDFC, tail-jump to rowed ??1Rva004E5654@@UAE@XZ (0x004E5654)
void __cdecl rva007B789C()
{
	Rva004E5654 *p = (Rva004E5654 *)&g_Va00DFEDFC;
	p->Rva004E5654::~Rva004E5654();
}

// ?rva007B78A6@@YAXXZ @ 0x007B78A6 (10B): ecx=&g_Va00DFEE20, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B78A6()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00DFEE20;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B7979@@YAXXZ @ 0x007B7979 (10B): ecx=&g_Va00DFF030, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7979()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF030;
	p->~AsciiString();
}

// ?rva007B798D@@YAXXZ @ 0x007B798D (10B): ecx=&g_Va00DFF044, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B798D()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF044;
	p->~AsciiString();
}

// ?rva007B7997@@YAXXZ @ 0x007B7997 (10B): ecx=&g_Va00DFF048, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7997()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF048;
	p->~AsciiString();
}

// ?rva007B79A1@@YAXXZ @ 0x007B79A1 (10B): ecx=&g_Va00DFF050, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B79A1()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF050;
	p->~AsciiString();
}

// ?rva007B79AB@@YAXXZ @ 0x007B79AB (10B): ecx=&g_Va00DFF054, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B79AB()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF054;
	p->~AsciiString();
}

// ?rva007B79B5@@YAXXZ @ 0x007B79B5 (10B): ecx=&g_Va00DFF05C, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B79B5()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF05C;
	p->~AsciiString();
}

// ?rva007B79BF@@YAXXZ @ 0x007B79BF (10B): ecx=&g_Va00DFF060, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B79BF()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF060;
	p->~AsciiString();
}

// ?rva007B79FB@@YAXXZ @ 0x007B79FB (10B): ecx=&g_Va00DFF0A0, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B79FB()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF0A0;
	p->~AsciiString();
}

// ?rva007B7A05@@YAXXZ @ 0x007B7A05 (10B): ecx=&g_Va00DFF0A4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7A05()
{
	AsciiString *p = (AsciiString *)&g_Va00DFF0A4;
	p->~AsciiString();
}

// ?rva007B7A19@@YAXXZ @ 0x007B7A19 (10B): ecx=&g_Va00DFF0C4, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B7A19()
{
	UnicodeString *p = (UnicodeString *)&g_Va00DFF0C4;
	p->~UnicodeString();
}

// ?rva007B7AA5@@YAXXZ @ 0x007B7AA5 (10B): ecx=&g_Va00DFF168, tail-jump to rowed ??1PlayerPosition@@QAE@XZ (0x0022D920)
void __cdecl rva007B7AA5()
{
	PlayerPosition *p = (PlayerPosition *)&g_Va00DFF168;
	p->~PlayerPosition();
}

// ?rva007B7C87@@YAXXZ @ 0x007B7C87 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B7C87()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	p->Term();
}

// ?rva007B7D27@@YAXXZ @ 0x007B7D27 (10B): ecx=&g_Va00E02040, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B7D27()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00E02040;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B7D31@@YAXXZ @ 0x007B7D31 (10B): ecx=&g_Va00E020C8, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B7D31()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00E020C8;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B7D3B@@YAXXZ @ 0x007B7D3B (10B): ecx=&g_Va00E02158, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B7D3B()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00E02158;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B7D45@@YAXXZ @ 0x007B7D45 (10B): ecx=&g_Va00E021F8, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B7D45()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00E021F8;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B7D77@@YAXXZ @ 0x007B7D77 (10B): ecx=&g_Va00E022A8, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7D77()
{
	AsciiString *p = (AsciiString *)&g_Va00E022A8;
	p->~AsciiString();
}

// ?rva007B7D81@@YAXXZ @ 0x007B7D81 (10B): ecx=&g_Va00E022AC, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7D81()
{
	AsciiString *p = (AsciiString *)&g_Va00E022AC;
	p->~AsciiString();
}

// ?rva007B7D95@@YAXXZ @ 0x007B7D95 (10B): ecx=&g_Va00E022C4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7D95()
{
	AsciiString *p = (AsciiString *)&g_Va00E022C4;
	p->~AsciiString();
}

// ?rva007B7DB3@@YAXXZ @ 0x007B7DB3 (10B): ecx=&g_Va00E022E8, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7DB3()
{
	AsciiString *p = (AsciiString *)&g_Va00E022E8;
	p->~AsciiString();
}

// ?rva007B7E49@@YAXXZ @ 0x007B7E49 (10B): ecx=&g_Va00E028C4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7E49()
{
	AsciiString *p = (AsciiString *)&g_Va00E028C4;
	p->~AsciiString();
}

// ?rva007B80A1@@YAXXZ @ 0x007B80A1 (10B): ecx=&g_Va00E02D68, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80A1()
{
	AsciiString *p = (AsciiString *)&g_Va00E02D68;
	p->~AsciiString();
}

// ?rva007B80B5@@YAXXZ @ 0x007B80B5 (10B): ecx=&g_Va00E02D70, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80B5()
{
	AsciiString *p = (AsciiString *)&g_Va00E02D70;
	p->~AsciiString();
}

// ?rva007B80BF@@YAXXZ @ 0x007B80BF (10B): ecx=&g_Va00E02D90, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80BF()
{
	AsciiString *p = (AsciiString *)&g_Va00E02D90;
	p->~AsciiString();
}

// ?rva007B80C9@@YAXXZ @ 0x007B80C9 (10B): ecx=&g_Va00E02D94, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80C9()
{
	AsciiString *p = (AsciiString *)&g_Va00E02D94;
	p->~AsciiString();
}

// ?rva007B8119@@YAXXZ @ 0x007B8119 (10B): ecx=&g_Va00E02E70, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8119()
{
	AsciiString *p = (AsciiString *)&g_Va00E02E70;
	p->~AsciiString();
}

// ?rva007B8123@@YAXXZ @ 0x007B8123 (10B): ecx=&g_Va00E02E74, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8123()
{
	AsciiString *p = (AsciiString *)&g_Va00E02E74;
	p->~AsciiString();
}

// ?rva007B8265@@YAXXZ @ 0x007B8265 (10B): ecx=&g_Va00E03080, tail-jump to rowed ??1Rva002390CB@@QAE@XZ (0x004C9F38)
void __cdecl rva007B8265()
{
	Rva002390CB *p = (Rva002390CB *)&g_Va00E03080;
	p->~Rva002390CB();
}

// ?rva007B8283@@YAXXZ @ 0x007B8283 (10B): ecx=&g_Va00E030E4, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B8283()
{
	UnicodeString *p = (UnicodeString *)&g_Va00E030E4;
	p->~UnicodeString();
}

// ?rva007B8369@@YAXXZ @ 0x007B8369 (10B): ecx=&g_Va00E03238, tail-jump to rowed ??1BfmeStringTailRecord144@@UAE@XZ (0x002D9A43)
void __cdecl rva007B8369()
{
	BfmeStringTailRecord144 *p = (BfmeStringTailRecord144 *)&g_Va00E03238;
	p->BfmeStringTailRecord144::~BfmeStringTailRecord144();
}

// ?rva007B83A5@@YAXXZ @ 0x007B83A5 (10B): ecx=&g_Va00E032E8, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B83A5()
{
	UnicodeString *p = (UnicodeString *)&g_Va00E032E8;
	p->~UnicodeString();
}

// ?rva007B83E1@@YAXXZ @ 0x007B83E1 (10B): ecx=&g_Va00E03318, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B83E1()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00E03318;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B83EB@@YAXXZ @ 0x007B83EB (10B): ecx=&g_Va00E03324, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B83EB()
{
	AsciiString *p = (AsciiString *)&g_Va00E03324;
	p->~AsciiString();
}

// ?rva007B83F5@@YAXXZ @ 0x007B83F5 (10B): ecx=&g_Va00E03328, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B83F5()
{
	AsciiString *p = (AsciiString *)&g_Va00E03328;
	p->~AsciiString();
}

// ?rva007B83FF@@YAXXZ @ 0x007B83FF (10B): ecx=&g_Va00E0332C, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B83FF()
{
	AsciiString *p = (AsciiString *)&g_Va00E0332C;
	p->~AsciiString();
}

// ?rva007B8409@@YAXXZ @ 0x007B8409 (10B): ecx=&g_Va00E03330, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8409()
{
	AsciiString *p = (AsciiString *)&g_Va00E03330;
	p->~AsciiString();
}

// ?rva007B8F12@@YAXXZ @ 0x007B8F12 (10B): ecx=&g_Va00E04444, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8F12()
{
	AsciiString *p = (AsciiString *)&g_Va00E04444;
	p->~AsciiString();
}

// ?rva007B8F1C@@YAXXZ @ 0x007B8F1C (10B): ecx=&g_Va00E04448, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8F1C()
{
	AsciiString *p = (AsciiString *)&g_Va00E04448;
	p->~AsciiString();
}

// ?rva007B8F26@@YAXXZ @ 0x007B8F26 (10B): ecx=&g_Va00E0445C, tail-jump to rowed ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ (0x0049B47C)
void __cdecl rva007B8F26()
{
	FXParticleSystem::OutwardEmissionVelocityInfo *p = (FXParticleSystem::OutwardEmissionVelocityInfo *)&g_Va00E0445C;
	p->FXParticleSystem::OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo();
}

// ?rva007B8F6D@@YAXXZ @ 0x007B8F6D (10B): ecx=&g_Va00E0447C, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B8F6D()
{
	UnicodeString *p = (UnicodeString *)&g_Va00E0447C;
	p->~UnicodeString();
}

// ?rva007B8FA9@@YAXXZ @ 0x007B8FA9 (10B): ecx=&g_Va00E04490, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8FA9()
{
	AsciiString *p = (AsciiString *)&g_Va00E04490;
	p->~AsciiString();
}

// ?rva007B919E@@YAXXZ @ 0x007B919E (10B): ecx=&g_Va00E048F4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B919E()
{
	AsciiString *p = (AsciiString *)&g_Va00E048F4;
	p->~AsciiString();
}

// ?rva007B91A8@@YAXXZ @ 0x007B91A8 (10B): ecx=&g_Va00E048FC, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B91A8()
{
	AsciiString *p = (AsciiString *)&g_Va00E048FC;
	p->~AsciiString();
}

// ?rva007B9202@@YAXXZ @ 0x007B9202 (10B): ecx=&g_Va00E0494C, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9202()
{
	AsciiString *p = (AsciiString *)&g_Va00E0494C;
	p->~AsciiString();
}

// ?rva007B920C@@YAXXZ @ 0x007B920C (10B): ecx=&g_Va00E04964, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B920C()
{
	AsciiString *p = (AsciiString *)&g_Va00E04964;
	p->~AsciiString();
}

// ?rva007B9216@@YAXXZ @ 0x007B9216 (10B): ecx=&g_Va00E04954, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9216()
{
	AsciiString *p = (AsciiString *)&g_Va00E04954;
	p->~AsciiString();
}

// ?rva007B9248@@YAXXZ @ 0x007B9248 (10B): ecx=&g_Va00E049A0, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9248()
{
	AsciiString *p = (AsciiString *)&g_Va00E049A0;
	p->~AsciiString();
}

// ?rva007B9252@@YAXXZ @ 0x007B9252 (10B): ecx=&g_Va00E049A4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9252()
{
	AsciiString *p = (AsciiString *)&g_Va00E049A4;
	p->~AsciiString();
}

// ?rva007B9270@@YAXXZ @ 0x007B9270 (10B): ecx=&g_Va00E0498C, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9270()
{
	AsciiString *p = (AsciiString *)&g_Va00E0498C;
	p->~AsciiString();
}

// ?rva007B927A@@YAXXZ @ 0x007B927A (10B): ecx=&g_Va00E04998, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B927A()
{
	AsciiString *p = (AsciiString *)&g_Va00E04998;
	p->~AsciiString();
}

// ?rva007B92B6@@YAXXZ @ 0x007B92B6 (10B): ecx=&g_Va00E05E00, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B92B6()
{
	UnicodeString *p = (UnicodeString *)&g_Va00E05E00;
	p->~UnicodeString();
}

// ?rva007B92C0@@YAXXZ @ 0x007B92C0 (10B): ecx=&g_Va00E05E04, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B92C0()
{
	UnicodeString *p = (UnicodeString *)&g_Va00E05E04;
	p->~UnicodeString();
}

// ?rva007B94AA@@YAXXZ @ 0x007B94AA (10B): ecx=&g_Va00E062FC, tail-jump to rowed ??1Rva00574499@@QAE@XZ (0x00574499)
void __cdecl rva007B94AA()
{
	Rva00574499 *p = (Rva00574499 *)&g_Va00E062FC;
	p->~Rva00574499();
}

// ?rva007B94B4@@YAXXZ @ 0x007B94B4 (10B): ecx=&g_Va00E0630C, tail-jump to rowed ??1Rva00574499@@QAE@XZ (0x00574499)
void __cdecl rva007B94B4()
{
	Rva00574499 *p = (Rva00574499 *)&g_Va00E0630C;
	p->~Rva00574499();
}

// ?rva007B94C8@@YAXXZ @ 0x007B94C8 (10B): ecx=&g_Va00E0631C, tail-jump to rowed ??1Rva00579731@@UAE@XZ (0x00579731)
void __cdecl rva007B94C8()
{
	Rva00579731 *p = (Rva00579731 *)&g_Va00E0631C;
	p->Rva00579731::~Rva00579731();
}

// ?rva007B94D2@@YAXXZ @ 0x007B94D2 (10B): ecx=&g_Va00E06360, tail-jump to rowed ??1Rva0057A4E7@@QAE@XZ (0x0057A4E7)
void __cdecl rva007B94D2()
{
	Rva0057A4E7 *p = (Rva0057A4E7 *)&g_Va00E06360;
	p->~Rva0057A4E7();
}

// ?rva007B957C@@YAXXZ @ 0x007B957C (10B): ecx=&g_Va00E063B8, tail-jump to rowed ?apply@Rva0005970E6DwordImmSetter@@QAEXXZ (0x005970E6)
void __cdecl rva007B957C()
{
	Rva0005970E6DwordImmSetter *p = (Rva0005970E6DwordImmSetter *)&g_Va00E063B8;
	p->apply();
}

// ?rva007B9586@@YAXXZ @ 0x007B9586 (10B): ecx=&g_Va00E063C0, tail-jump to rowed ?apply@Rva0005970E6DwordImmSetter@@QAEXXZ (0x005970E6)
void __cdecl rva007B9586()
{
	Rva0005970E6DwordImmSetter *p = (Rva0005970E6DwordImmSetter *)&g_Va00E063C0;
	p->apply();
}

// ?rva007B95A4@@YAXXZ @ 0x007B95A4 (10B): ecx=&g_Va00E063D4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B95A4()
{
	AsciiString *p = (AsciiString *)&g_Va00E063D4;
	p->~AsciiString();
}

// ?rva007B969E@@YAXXZ @ 0x007B969E (10B): ecx=&g_Va00E06458, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B969E()
{
	AsciiString *p = (AsciiString *)&g_Va00E06458;
	p->~AsciiString();
}

// ?rva007B972A@@YAXXZ @ 0x007B972A (10B): ecx=&g_Va00E065EC, tail-jump to rowed ??1Rva005CB3BE@@QAE@XZ (0x005CB3BE)
void __cdecl rva007B972A()
{
	Rva005CB3BE *p = (Rva005CB3BE *)&g_Va00E065EC;
	p->~Rva005CB3BE();
}

// ?rva007B9734@@YAXXZ @ 0x007B9734 (10B): ecx=&g_Va00E06620, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9734()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_Va00E06620;
	p->Rva005E16DA::~Rva005E16DA();
}

// ?rva007B9825@@YAXXZ @ 0x007B9825 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9825()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	p->Term();
}

// ?rva007B9947@@YAXXZ @ 0x007B9947 (10B): ecx=&g_Va00E06710, tail-jump to rowed ??1Rva005E3DE8@@QAE@XZ (0x005E3DE8)
void __cdecl rva007B9947()
{
	Rva005E3DE8 *p = (Rva005E3DE8 *)&g_Va00E06710;
	p->~Rva005E3DE8();
}

// ?rva007B9965@@YAXXZ @ 0x007B9965 (10B): ecx=&g_Va00E06724, tail-jump to rowed ??1Rva005E7529@@QAE@XZ (0x005E7529)
void __cdecl rva007B9965()
{
	Rva005E7529 *p = (Rva005E7529 *)&g_Va00E06724;
	p->~Rva005E7529();
}

// ?rva007B9979@@YAXXZ @ 0x007B9979 (10B): ecx=&g_Va00E06734, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9979()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_Va00E06734;
	p->Rva005E16DA::~Rva005E16DA();
}

// ?rva007B9983@@YAXXZ @ 0x007B9983 (10B): ecx=&g_Va00E06748, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9983()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_Va00E06748;
	p->Rva005E16DA::~Rva005E16DA();
}

// ?rva007B9AB0@@YAXXZ @ 0x007B9AB0 (10B): ecx=&g_Va00E08D48, tail-jump to rowed ??1SimpleFileFactoryClass@@UAE@XZ (0x00613140)
void __cdecl rva007B9AB0()
{
	SimpleFileFactoryClass *p = (SimpleFileFactoryClass *)&g_Va00E08D48;
	p->SimpleFileFactoryClass::~SimpleFileFactoryClass();
}

// ?rva007B9B00@@YAXXZ @ 0x007B9B00 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9B00()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	p->Term();
}

// ?rva007B9B0A@@YAXXZ @ 0x007B9B0A (10B): ecx=&g_Va00E09E50, tail-jump to rowed ??1CDCCache@@QAE@XZ (0x00628BC5)
void __cdecl rva007B9B0A()
{
	CDCCache *p = (CDCCache *)&g_Va00E09E50;
	p->~CDCCache();
}

// ?rva007B9B14@@YAXXZ @ 0x007B9B14 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9B14()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	p->Term();
}

// ?rva007B9B1E@@YAXXZ @ 0x007B9B1E (10B): ecx=&g_Va00E09E60, tail-jump to rowed ?bfmeGoDXB@BfmeThingDXB@@QAEXXZ (0x00628D20)
void __cdecl rva007B9B1E()
{
	BfmeThingDXB *p = (BfmeThingDXB *)&g_Va00E09E60;
	p->bfmeGoDXB();
}

// ?rva007B9B28@@YAXXZ @ 0x007B9B28 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9B28()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	p->Term();
}

// ?rva007B9BF0@@YAXXZ @ 0x007B9BF0 (10B): ecx=&g_Va00E0C150, tail-jump to rowed ??1GeometryInfo@@UAE@XZ (0x00050B2A)
void __cdecl rva007B9BF0()
{
	GeometryInfo *p = (GeometryInfo *)&g_Va00E0C150;
	p->GeometryInfo::~GeometryInfo();
}

// ?rva007B9C00@@YAXXZ @ 0x007B9C00 (1B). Empty stub: ret.
void __cdecl rva007B9C00()
{
}

// ?rva007B9C20@@YAXXZ @ 0x007B9C20 (10B): ecx=&g_Va00E176A0, tail-jump to rowed ??1Rva00041004@@UAE@XZ (0x00040FE5)
void __cdecl rva007B9C20()
{
	Rva00041004 *p = (Rva00041004 *)&g_Va00E176A0;
	p->Rva00041004::~Rva00041004();
}
