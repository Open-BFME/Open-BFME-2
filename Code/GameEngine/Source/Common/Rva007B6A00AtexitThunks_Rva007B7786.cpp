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
#include "../../Include/Common/CAtlWinModule.h"
}

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

class Rva005E16DA
{
public:
	virtual ~Rva005E16DA();
};

extern unsigned int g_00DDE0AC;
class Rva00575674;
extern Rva00575674 g_00DFE4C4;	// retail RVA 0x009FE4C4 (.bss), defined in Rva002220DCInit.cpp
extern unsigned char g_00DFE7A8;	// canonical byte owner, Rva003B9EC4.cpp
struct BfmeUiResourceEntryState;
extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
extern int g_00E06734[5];	// data row 0x00A06734 (Rva005E8DB5.cpp)
extern int g_00E06748[5];	// data row 0x00A06748 (Rva005E8DB5.cpp)
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

void __cdecl rva007B9B00();

void __cdecl rva007B9B0A();

void __cdecl rva007B9B14();

void __cdecl rva007B9B1E();

void __cdecl rva007B9B28();

void __cdecl rva007B9BF0();

void __cdecl rva007B9C00();
