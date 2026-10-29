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

class TerrainFXShaderParameterSourceNamespace
{
public:
	virtual ~TerrainFXShaderParameterSourceNamespace();
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
	virtual ~Rva0057A4E7();
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
unsigned g_Va00DEBC64;	// retail RVA 0x009EBC64 (.bss), defined here
unsigned g_Va00DFE490;	// retail RVA 0x009FE490 (.bss), defined here
unsigned g_Va00DFE49C;	// retail RVA 0x009FE49C (.bss), defined here
class Rva00575674;
extern Rva00575674 g_00DFE4C4;	// retail RVA 0x009FE4C4 (.bss), defined in Rva002220DCInit.cpp
unsigned g_Va00DFE6DC;	// retail RVA 0x009FE6DC (.bss), defined here
unsigned g_Va00DFE940;	// retail RVA 0x009FE940 (.bss), defined here
struct BfmeUiResourceEntryState;
extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
extern unsigned g_Va00DFF030;
unsigned g_Va00DFF0A0;	// retail RVA 0x009FF0A0 (.bss), defined here
unsigned g_Va00DFF0A4;	// retail RVA 0x009FF0A4 (.bss), defined here
extern unsigned g_Va00DFF0C4;
unsigned g_Va00DFF168;	// retail RVA 0x009FF168 (.bss), defined here
extern unsigned g_Va00E022E8;
extern unsigned g_Va00E028C4;
extern unsigned g_Va00E02D68;
extern unsigned g_Va00E02D90;
extern unsigned g_Va00E02D94;
extern unsigned g_Va00E02E70;
extern unsigned g_Va00E02E74;
extern unsigned g_Va00E032E8;
unsigned g_Va00E03324;	// retail RVA 0x00A03324 (.bss), defined here
unsigned g_Va00E03328;	// retail RVA 0x00A03328 (.bss), defined here
unsigned g_Va00E0332C;	// retail RVA 0x00A0332C (.bss), defined here
unsigned g_Va00E03330;	// retail RVA 0x00A03330 (.bss), defined here
unsigned g_Va00E04444;	// retail RVA 0x00A04444 (.bss), defined here
unsigned g_Va00E04448;	// retail RVA 0x00A04448 (.bss), defined here
extern UnicodeString g_00E0447C;	// VA 0x00E0447C, defined in AptLobbyScreenInitCallbacks.cpp
extern unsigned g_Va00E04490;
unsigned g_Va00E048F4;	// retail RVA 0x00A048F4 (.bss), defined here
unsigned g_Va00E048FC;	// retail RVA 0x00A048FC (.bss), defined here
unsigned g_Va00E0494C;	// retail RVA 0x00A0494C (.bss), defined here
unsigned g_Va00E04954;	// retail RVA 0x00A04954 (.bss), defined here
unsigned g_Va00E04964;	// retail RVA 0x00A04964 (.bss), defined here
unsigned g_Va00E04998;	// retail RVA 0x00A04998 (.bss), defined here
unsigned g_Va00E049A0;	// retail RVA 0x00A049A0 (.bss), defined here
unsigned g_Va00E049A4;	// retail RVA 0x00A049A4 (.bss), defined here
extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;
extern unsigned g_Va00E0631C;
unsigned g_Va00E06360;	// retail RVA 0x00A06360 (.bss), defined here
extern unsigned g_Va00E063D4;
unsigned g_Va00E06458;	// retail RVA 0x00A06458 (.bss), defined here
extern unsigned g_Va00E065EC;
extern unsigned g_Va00E06620;
extern unsigned g_Va00E06710;
unsigned g_Va00E06724[4];	// retail RVA 0x00A06724 (.bss), defined here
extern unsigned g_Va00E06734;
extern unsigned g_Va00E06748;
unsigned g_Va00E08D48;	// retail RVA 0x00A08D48 (.bss), defined here
unsigned g_Va00E09E50;	// retail RVA 0x00A09E50 (.bss), defined here
extern unsigned g_Va00E09E60;
extern unsigned GeometryContactSphere;

// ?rva007B6AE7@@YAXXZ @ 0x007B6AE7 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B6AE7()
{
	ATL::CAtlWinModule *receiver = (ATL::CAtlWinModule *)&g_00DDE0AC;
	receiver->Term();
}

// ?rva007B6DFA@@YAXXZ @ 0x007B6DFA (10B): ecx=&g_Va00DEBC64, tail-jump to rowed ??1TerrainFXShaderParameterSourceNamespace@@UAE@XZ (0x000E19A3)
void __cdecl rva007B6DFA()
{
	TerrainFXShaderParameterSourceNamespace *receiver = (TerrainFXShaderParameterSourceNamespace *)&g_Va00DEBC64;
	receiver->TerrainFXShaderParameterSourceNamespace::~TerrainFXShaderParameterSourceNamespace();
}

// ?rva007B76E6@@YAXXZ @ 0x007B76E6 (10B): ecx=&g_Va00DFE490, tail-jump to rowed ?clear@Rva000AD6F4@@QAEXXZ (0x000AD6F4)
void __cdecl rva007B76E6()
{
	Rva000AD6F4 *receiver = (Rva000AD6F4 *)&g_Va00DFE490;
	receiver->clear();
}

// ?rva007B76FA@@YAXXZ @ 0x007B76FA (10B): ecx=&g_Va00DFE49C, tail-jump to rowed ??1Rva00221027@@UAE@XZ (0x00221027)
void __cdecl rva007B76FA()
{
	Rva00221027 *receiver = (Rva00221027 *)&g_Va00DFE49C;
	receiver->Rva00221027::~Rva00221027();
}

// ?rva007B770E@@YAXXZ @ 0x007B770E (10B): ecx=&g_00DFE4C4, tail-jump to rowed ?clear@Rva000AD6F4@@QAEXXZ (0x000AD6F4)
void __cdecl rva007B770E()
{
	Rva000AD6F4 *receiver = (Rva000AD6F4 *)&g_00DFE4C4;
	receiver->clear();
}

// ?rva007B7718@@YAXXZ @ 0x007B7718 (10B): ecx=&g_Va00DFE6DC, tail-jump to rowed ?clear@Rva000AD6F4@@QAEXXZ (0x000AD6F4)
void __cdecl rva007B7718()
{
	Rva000AD6F4 *receiver = (Rva000AD6F4 *)&g_Va00DFE6DC;
	receiver->clear();
}

// ?rva007B7768@@YAXXZ @ 0x007B7768 (10B): ecx=&g_Va00DFE940, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7768()
{
	AsciiString *receiver = (AsciiString *)&g_Va00DFE940;
	receiver->~AsciiString();
}


// ?rva007B789C@@YAXXZ @ 0x007B789C (10B): ecx=&BfmeUiResourceEntryCollectorState, tail-jump to rowed ??1Rva004E5654@@UAE@XZ (0x004E5654)
void __cdecl rva007B789C()
{
	Rva004E5654 *receiver = (Rva004E5654 *)&BfmeUiResourceEntryCollectorState;
	receiver->Rva004E5654::~Rva004E5654();
}

// ?rva007B7979@@YAXXZ @ 0x007B7979 (10B): ecx=&g_Va00DFF030, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7979()
{
	AsciiString *receiver = (AsciiString *)&g_Va00DFF030;
	receiver->~AsciiString();
}

// ?rva007B79FB@@YAXXZ @ 0x007B79FB (10B): ecx=&g_Va00DFF0A0, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B79FB()
{
	AsciiString *receiver = (AsciiString *)&g_Va00DFF0A0;
	receiver->~AsciiString();
}

// ?rva007B7A05@@YAXXZ @ 0x007B7A05 (10B): ecx=&g_Va00DFF0A4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7A05()
{
	AsciiString *receiver = (AsciiString *)&g_Va00DFF0A4;
	receiver->~AsciiString();
}

// ?rva007B7A19@@YAXXZ @ 0x007B7A19 (10B): ecx=&g_Va00DFF0C4, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B7A19()
{
	UnicodeString *receiver = (UnicodeString *)&g_Va00DFF0C4;
	receiver->~UnicodeString();
}

// ?rva007B7AA5@@YAXXZ @ 0x007B7AA5 (10B): ecx=&g_Va00DFF168, tail-jump to rowed ??1PlayerPosition@@QAE@XZ (0x0022D920)
void __cdecl rva007B7AA5()
{
	PlayerPosition *receiver = (PlayerPosition *)&g_Va00DFF168;
	receiver->~PlayerPosition();
}

// ?rva007B7C87@@YAXXZ @ 0x007B7C87 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B7C87()
{
	ATL::CAtlWinModule *receiver = (ATL::CAtlWinModule *)&g_00DDE0AC;
	receiver->Term();
}

// ?rva007B7DB3@@YAXXZ @ 0x007B7DB3 (10B): ecx=&g_Va00E022E8, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7DB3()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E022E8;
	receiver->~AsciiString();
}

// ?rva007B7E49@@YAXXZ @ 0x007B7E49 (10B): ecx=&g_Va00E028C4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B7E49()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E028C4;
	receiver->~AsciiString();
}

// ?rva007B80A1@@YAXXZ @ 0x007B80A1 (10B): ecx=&g_Va00E02D68, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80A1()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E02D68;
	receiver->~AsciiString();
}


// ?rva007B80BF@@YAXXZ @ 0x007B80BF (10B): ecx=&g_Va00E02D90, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80BF()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E02D90;
	receiver->~AsciiString();
}

// ?rva007B80C9@@YAXXZ @ 0x007B80C9 (10B): ecx=&g_Va00E02D94, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B80C9()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E02D94;
	receiver->~AsciiString();
}

// ?rva007B8119@@YAXXZ @ 0x007B8119 (10B): ecx=&g_Va00E02E70, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8119()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E02E70;
	receiver->~AsciiString();
}

// ?rva007B8123@@YAXXZ @ 0x007B8123 (10B): ecx=&g_Va00E02E74, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8123()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E02E74;
	receiver->~AsciiString();
}

// ?rva007B83A5@@YAXXZ @ 0x007B83A5 (10B): ecx=&g_Va00E032E8, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B83A5()
{
	UnicodeString *receiver = (UnicodeString *)&g_Va00E032E8;
	receiver->~UnicodeString();
}

// ?rva007B83EB@@YAXXZ @ 0x007B83EB (10B): ecx=&g_Va00E03324, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B83EB()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E03324;
	receiver->~AsciiString();
}

// ?rva007B83F5@@YAXXZ @ 0x007B83F5 (10B): ecx=&g_Va00E03328, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B83F5()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E03328;
	receiver->~AsciiString();
}

// ?rva007B83FF@@YAXXZ @ 0x007B83FF (10B): ecx=&g_Va00E0332C, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B83FF()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E0332C;
	receiver->~AsciiString();
}

// ?rva007B8409@@YAXXZ @ 0x007B8409 (10B): ecx=&g_Va00E03330, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8409()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E03330;
	receiver->~AsciiString();
}

// ?rva007B8F12@@YAXXZ @ 0x007B8F12 (10B): ecx=&g_Va00E04444, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8F12()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E04444;
	receiver->~AsciiString();
}

// ?rva007B8F1C@@YAXXZ @ 0x007B8F1C (10B): ecx=&g_Va00E04448, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8F1C()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E04448;
	receiver->~AsciiString();
}

// ?rva007B8F6D@@YAXXZ @ 0x007B8F6D (10B): ecx=&g_00E0447C, tail-jump to rowed ??1UnicodeString@@QAE@XZ (0x005B804E)
void __cdecl rva007B8F6D()
{
	UnicodeString *receiver = &g_00E0447C;
	receiver->~UnicodeString();
}

// ?rva007B8FA9@@YAXXZ @ 0x007B8FA9 (10B): ecx=&g_Va00E04490, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B8FA9()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E04490;
	receiver->~AsciiString();
}

// ?rva007B919E@@YAXXZ @ 0x007B919E (10B): ecx=&g_Va00E048F4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B919E()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E048F4;
	receiver->~AsciiString();
}

// ?rva007B91A8@@YAXXZ @ 0x007B91A8 (10B): ecx=&g_Va00E048FC, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B91A8()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E048FC;
	receiver->~AsciiString();
}

// ?rva007B9202@@YAXXZ @ 0x007B9202 (10B): ecx=&g_Va00E0494C, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9202()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E0494C;
	receiver->~AsciiString();
}

// ?rva007B920C@@YAXXZ @ 0x007B920C (10B): ecx=&g_Va00E04964, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B920C()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E04964;
	receiver->~AsciiString();
}

// ?rva007B9216@@YAXXZ @ 0x007B9216 (10B): ecx=&g_Va00E04954, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9216()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E04954;
	receiver->~AsciiString();
}

// ?rva007B9248@@YAXXZ @ 0x007B9248 (10B): ecx=&g_Va00E049A0, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9248()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E049A0;
	receiver->~AsciiString();
}

// ?rva007B9252@@YAXXZ @ 0x007B9252 (10B): ecx=&g_Va00E049A4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B9252()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E049A4;
	receiver->~AsciiString();
}

// ?rva007B927A@@YAXXZ @ 0x007B927A (10B): ecx=&g_Va00E04998, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B927A()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E04998;
	receiver->~AsciiString();
}

// ?rva007B94AA@@YAXXZ @ 0x007B94AA (10B): ecx=&g_Va00E062FC, tail-jump to rowed ??1Rva00574499@@QAE@XZ (0x00574499)
void __cdecl rva007B94AA()
{
	Rva00574499 *receiver = (Rva00574499 *)&g_Va00E062FC;
	receiver->~Rva00574499();
}

// ?rva007B94B4@@YAXXZ @ 0x007B94B4 (10B): ecx=&g_Va00E0630C, tail-jump to rowed ??1Rva00574499@@QAE@XZ (0x00574499)
void __cdecl rva007B94B4()
{
	Rva00574499 *receiver = (Rva00574499 *)&g_Va00E0630C;
	receiver->~Rva00574499();
}

// ?rva007B94C8@@YAXXZ @ 0x007B94C8 (10B): ecx=&g_Va00E0631C, tail-jump to rowed ??1Rva00579731@@UAE@XZ (0x00579731)
void __cdecl rva007B94C8()
{
	Rva00579731 *receiver = (Rva00579731 *)&g_Va00E0631C;
	receiver->Rva00579731::~Rva00579731();
}

// ?rva007B94D2@@YAXXZ @ 0x007B94D2 (10B): ecx=&g_Va00E06360, tail-jump to rowed ??1Rva0057A4E7@@UAE@XZ (0x0057A4E7)
void __cdecl rva007B94D2()
{
	Rva0057A4E7 *receiver = (Rva0057A4E7 *)&g_Va00E06360;
	receiver->Rva0057A4E7::~Rva0057A4E7();
}

// ?rva007B95A4@@YAXXZ @ 0x007B95A4 (10B): ecx=&g_Va00E063D4, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B95A4()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E063D4;
	receiver->~AsciiString();
}

// ?rva007B969E@@YAXXZ @ 0x007B969E (10B): ecx=&g_Va00E06458, tail-jump to rowed ??1AsciiString@@QAE@XZ (0x0048BA39)
void __cdecl rva007B969E()
{
	AsciiString *receiver = (AsciiString *)&g_Va00E06458;
	receiver->~AsciiString();
}

// ?rva007B972A@@YAXXZ @ 0x007B972A (10B): ecx=&g_Va00E065EC, tail-jump to rowed ??1Rva005CB3BE@@QAE@XZ (0x005CB3BE)
void __cdecl rva007B972A()
{
	Rva005CB3BE *receiver = (Rva005CB3BE *)&g_Va00E065EC;
	receiver->~Rva005CB3BE();
}

// ?rva007B9734@@YAXXZ @ 0x007B9734 (10B): ecx=&g_Va00E06620, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9734()
{
	Rva005E16DA *receiver = (Rva005E16DA *)&g_Va00E06620;
	receiver->Rva005E16DA::~Rva005E16DA();
}

// ?rva007B9825@@YAXXZ @ 0x007B9825 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9825()
{
	ATL::CAtlWinModule *receiver = (ATL::CAtlWinModule *)&g_00DDE0AC;
	receiver->Term();
}

// ?rva007B9947@@YAXXZ @ 0x007B9947 (10B): ecx=&g_Va00E06710, tail-jump to rowed ??1Rva005E3DE8@@QAE@XZ (0x005E3DE8)
void __cdecl rva007B9947()
{
	Rva005E3DE8 *receiver = (Rva005E3DE8 *)&g_Va00E06710;
	receiver->~Rva005E3DE8();
}

// ?rva007B9965@@YAXXZ @ 0x007B9965 (10B): ecx=&g_Va00E06724, tail-jump to rowed ??1Rva005E7529@@QAE@XZ (0x005E7529)
void __cdecl rva007B9965()
{
	Rva005E7529 *receiver = (Rva005E7529 *)&g_Va00E06724;
	receiver->~Rva005E7529();
}



// ?rva007B9AB0@@YAXXZ @ 0x007B9AB0 (10B): ecx=&g_Va00E08D48, tail-jump to rowed ??1SimpleFileFactoryClass@@UAE@XZ (0x00613140)
void __cdecl rva007B9AB0()
{
	SimpleFileFactoryClass *receiver = (SimpleFileFactoryClass *)&g_Va00E08D48;
	receiver->SimpleFileFactoryClass::~SimpleFileFactoryClass();
}

// ?rva007B9B00@@YAXXZ @ 0x007B9B00 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9B00()
{
	ATL::CAtlWinModule *receiver = (ATL::CAtlWinModule *)&g_00DDE0AC;
	receiver->Term();
}

// ?rva007B9B0A@@YAXXZ @ 0x007B9B0A (10B): ecx=&g_Va00E09E50, tail-jump to rowed ??1CDCCache@@QAE@XZ (0x00628BC5)
void __cdecl rva007B9B0A()
{
	CDCCache *receiver = (CDCCache *)&g_Va00E09E50;
	receiver->~CDCCache();
}

// ?rva007B9B14@@YAXXZ @ 0x007B9B14 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9B14()
{
	ATL::CAtlWinModule *receiver = (ATL::CAtlWinModule *)&g_00DDE0AC;
	receiver->Term();
}

// ?rva007B9B1E@@YAXXZ @ 0x007B9B1E (10B): ecx=&g_Va00E09E60, tail-jump to rowed ?bfmeGoDXB@BfmeThingDXB@@QAEXXZ (0x00628D20)
void __cdecl rva007B9B1E()
{
	BfmeThingDXB *receiver = (BfmeThingDXB *)&g_Va00E09E60;
	receiver->bfmeGoDXB();
}

// ?rva007B9B28@@YAXXZ @ 0x007B9B28 (10B): ecx=&g_Va00DDE0AC, tail-jump to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1)
void __cdecl rva007B9B28()
{
	ATL::CAtlWinModule *receiver = (ATL::CAtlWinModule *)&g_00DDE0AC;
	receiver->Term();
}

// ?rva007B9BF0@@YAXXZ @ 0x007B9BF0 (10B): ecx=&GeometryContactSphere, tail-jump to rowed ??1GeometryInfo@@UAE@XZ (0x00050B2A)
void __cdecl rva007B9BF0()
{
	GeometryInfo *receiver = (GeometryInfo *)&GeometryContactSphere;
	receiver->GeometryInfo::~GeometryInfo();
}

// ?rva007B9C00@@YAXXZ @ 0x007B9C00 (1B). Empty stub: ret.
void __cdecl rva007B9C00()
{
}
