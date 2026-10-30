// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// Split from Rva007B6A00AtexitThunks.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
extern unsigned g_Va00DEBC64;	// retail RVA 0x009EBC64 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00DFE490;	// retail RVA 0x009FE490 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00DFE49C;	// retail RVA 0x009FE49C (.bss), defined in Rva007B6A00AtexitThunks.cpp
class Rva00575674;
extern Rva00575674 g_00DFE4C4;	// retail RVA 0x009FE4C4 (.bss), defined in Rva002220DCInit.cpp
extern unsigned g_Va00DFE6DC;	// retail RVA 0x009FE6DC (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned char g_00DFE7A8;	// canonical byte owner, Rva003B9EC4.cpp
extern unsigned g_Va00DFE940;	// retail RVA 0x009FE940 (.bss), defined in Rva007B6A00AtexitThunks.cpp
struct BfmeUiResourceEntryState;
extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
extern unsigned g_Va00DFF030;
extern unsigned g_Va00DFF0A0;	// retail RVA 0x009FF0A0 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00DFF0A4;	// retail RVA 0x009FF0A4 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00DFF0C4;
extern unsigned g_Va00DFF168;	// retail RVA 0x009FF168 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E022E8;
extern unsigned g_Va00E028C4;
extern unsigned g_Va00E02D68;
extern unsigned g_Va00E02D90;
extern unsigned g_Va00E02D94;
extern unsigned g_Va00E02E70;
extern unsigned g_Va00E02E74;
extern unsigned g_Va00E032E8;
extern unsigned g_Va00E03324;	// retail RVA 0x00A03324 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E03328;	// retail RVA 0x00A03328 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E0332C;	// retail RVA 0x00A0332C (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E03330;	// retail RVA 0x00A03330 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E04444;	// retail RVA 0x00A04444 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E04448;	// retail RVA 0x00A04448 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E04490;
extern unsigned g_Va00E0494C;	// retail RVA 0x00A0494C (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E04954;	// retail RVA 0x00A04954 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E04964;	// retail RVA 0x00A04964 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E04998;	// retail RVA 0x00A04998 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E049A0;	// retail RVA 0x00A049A0 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E049A4;	// retail RVA 0x00A049A4 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;
extern unsigned g_Va00E0631C;
extern unsigned g_Va00E06360;	// retail RVA 0x00A06360 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E063D4;
extern unsigned g_Va00E06458;	// retail RVA 0x00A06458 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E065EC;
extern unsigned g_Va00E06620;
extern unsigned g_Va00E06710;
extern unsigned g_Va00E06724[4];	// retail RVA 0x00A06724 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern int g_00E06734;	// data row 0x00A06734 (Rva005E8DB5.cpp)
extern int g_00E06748;	// data row 0x00A06748 (Rva005E8DB5.cpp)
extern unsigned g_Va00E08D48;	// retail RVA 0x00A08D48 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E09E50;	// retail RVA 0x00A09E50 (.bss), defined in Rva007B6A00AtexitThunks.cpp
extern unsigned g_Va00E09E60;
extern unsigned GeometryContactSphere;

void __cdecl rva007B6DFA();

void __cdecl rva007B76E6();

void __cdecl rva007B76FA();

void __cdecl rva007B770E();

void __cdecl rva007B7718();

void __cdecl rva007B7768();


// ?rva007B7786@@YAXXZ @ 0x007B7786 (10B): ecx=&g_Va00DFE7A8, tail-jump to rowed ??1Rva0023DBC3@@QAE@XZ (0x0023DBC3)
void __cdecl rva007B7786()
{
	Rva0023DBC3 *p = (Rva0023DBC3 *)&g_00DFE7A8;
	p->~Rva0023DBC3();
}
void __cdecl rva007B789C();

void __cdecl rva007B7979();

void __cdecl rva007B79FB();

void __cdecl rva007B7A05();

void __cdecl rva007B7A19();

void __cdecl rva007B7AA5();

void __cdecl rva007B7C87();

void __cdecl rva007B7DB3();

void __cdecl rva007B7E49();

void __cdecl rva007B80A1();

void __cdecl rva007B80BF();

void __cdecl rva007B80C9();

void __cdecl rva007B8119();

void __cdecl rva007B8123();

void __cdecl rva007B83A5();

void __cdecl rva007B83EB();

void __cdecl rva007B83F5();

void __cdecl rva007B83FF();

void __cdecl rva007B8409();

void __cdecl rva007B8F12();

void __cdecl rva007B8F1C();

void __cdecl rva007B8F6D();

void __cdecl rva007B8FA9();

void __cdecl rva007B919E();

void __cdecl rva007B91A8();

void __cdecl rva007B9202();

void __cdecl rva007B920C();

void __cdecl rva007B9216();

void __cdecl rva007B9248();

void __cdecl rva007B9252();

void __cdecl rva007B927A();

void __cdecl rva007B94AA();

void __cdecl rva007B94B4();

void __cdecl rva007B94C8();

void __cdecl rva007B94D2();

void __cdecl rva007B95A4();

void __cdecl rva007B969E();

void __cdecl rva007B972A();

void __cdecl rva007B9734();

void __cdecl rva007B9825();

void __cdecl rva007B9947();

void __cdecl rva007B9965();


// ?rva007B9979@@YAXXZ @ 0x007B9979 (10B): ecx=&g_00E06734, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9979()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_00E06734;
	p->Rva005E16DA::~Rva005E16DA();
}

// ?rva007B9983@@YAXXZ @ 0x007B9983 (10B): ecx=&g_00E06748, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9983()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_00E06748;
	p->Rva005E16DA::~Rva005E16DA();
}
void __cdecl rva007B9AB0();

void __cdecl rva007B9B00();

void __cdecl rva007B9B0A();

void __cdecl rva007B9B14();

void __cdecl rva007B9B1E();

void __cdecl rva007B9B28();

void __cdecl rva007B9BF0();

void __cdecl rva007B9C00();
