// cl: /MD
// Split from Rva007AB81ACtorInits.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Dynamic initializers from the 0x007AB7DA strip that run an already-rowed
// default constructor (or in-place init member) on a file-scope object, then
// atexit() its already-rowed cleanup thunk: ATL's _AtlWinModule per including
// TU, STLport's ios_base::Init / _Loc_init sentries, SortingRenderStateStruct
// and single-copy globals. Each is one translation unit's compiler-generated
// initializer; the owning TUs are unrecovered, so each keeps an honest address
// name and its global an address-named extern.

#include <stdlib.h>
namespace ATL
{
#include "../../Include/Common/CAtlWinModule.h"
}

#include "../../Include/Common/SortingRenderStateStruct.h"

class BfmeDualVtableReleaseDtor
{
public:
	BfmeDualVtableReleaseDtor();
};

class Rva0030ADED
{
public:
	Rva0030ADED();
};

class Rva00214E02
{
public:
	Rva00214E02();
};

class Rva005E74CF
{
public:
	Rva005E74CF();
};

namespace _STL
{
	class ios_base
	{
	public:
		class _Loc_init
		{
		public:
			_Loc_init();
		};
		class Init
		{
		public:
			Init();
		};
	};
}

void __cdecl rva007B686F();
void __cdecl rva007B685A();
void __cdecl rva007B6864();
void __cdecl rva007B6880();
void __cdecl rva007B6AE7();
void __cdecl rva007B6C3E();
void __cdecl rva007B6FC0();
void __cdecl rva007B6FD0();
void __cdecl rva007B71C0();
void __cdecl rva007B75E2();
void __cdecl rva007B763C();
void __cdecl rva007B7632();
void __cdecl rva007B7AF5();
void __cdecl rva007B7AFF();
void __cdecl rva007B7C87();
void __cdecl rva007B972A();
void __cdecl rva007B9825();
void __cdecl rva007B9806();
void __cdecl rva007B9810();
void __cdecl rva007B9965();
void __cdecl rva007B9B00();
void __cdecl rva007B9B14();
void __cdecl rva007B9B28();

extern unsigned int g_00DDE070;
extern unsigned int g_00DDE071;
extern unsigned int g_00DDE0AC;
// VA 0x00DEE5D8 is dx8wrapper.cpp's protected
// ?render_state@DX8Wrapper@@1URenderStateStruct@@A, reached as a friend of
// the canonical DX8Wrapper header instead of a second datum at its address.
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
// VA 0x00DFE180 is ScriptEngine_init.cpp's TheFXParticleEditor.
extern BfmeDualVtableReleaseDtor TheFXParticleEditor;
extern Rva0030ADED TheFireSettings;			// 0x00DFF4F8 (Rva007B6880Thunks.cpp)
extern Rva0030ADED TheFireSettingsSaved;		// 0x00DFF4B8
extern Rva00214E02 TheCloudEffectSettings;		// 0x00DFE280 (Rva007B6880Thunks.cpp)
extern Rva00214E02 TheCloudEffectSettingsSaved;	// 0x00DFE1E8
extern unsigned int g_00E06664;
// VA 0x00E06665: the one-byte STLport `static ios_base::_Loc_init _LocInit;`
// sentry that <fstream>/<iostream> declare per TU, beside the ios_base::Init
// sentry g_00E06664 at 0x00E06664. Its home TU is a file-local static no other
// unit can name, so the storage is defined here, in its initializer's unit,
// under the ledger's spelling for the address (?g_00E06665@@3...); the
// initializer below runs the rowed _Loc_init ctor on it.
unsigned char g_00E06665;
extern unsigned g_Va00E06724[4];

struct Rva007AB81ACtorInits
{
	static void rva007AB81A();
	static void rva007AB830();
	static void rva007AB846();
	static void rva007AB8A0();
	static void rva007ABC99();
	static void rva007AC15D();
	static void rva007ACC00();
	static void rva007ACC20();
	static void rva007ACE30();
	static void rva007AD7DD();
	static void rva007AD9BC();
	static void rva007AD9D2();
	static void rva007AE79E();
	static void rva007AE7B4();
	static void rva007AEC78();
	static void rva007B494C();
	static void rva007B4C22();
	static void rva007B4C38();
	static void rva007B4C4E();
	static void rva007B506A();
	static void rva007B5558();
	static void rva007B5587();
	static void rva007B55B3();
};








// ?rva007ACC20@Rva007AB81ACtorInits@@SAXXZ @ 0x007ACC20 (22B): ??0SortingRenderStateStruct@@QAE@XZ on VA 0x00DEE5D8, atexit(0x007B6FD0)
void Rva007AB81ACtorInits::rva007ACC20()
{
	( (SortingRenderStateStruct *)&DX8Wrapper::render_state )->SortingRenderStateStruct::SortingRenderStateStruct();
	atexit( rva007B6FD0 );
}


// ?rva007AD7DD@Rva007AB81ACtorInits@@SAXXZ @ 0x007AD7DD (22B): ??0BfmeDualVtableReleaseDtor@@QAE@XZ on VA 0x00DFE180, atexit(0x007B75E2)
void Rva007AB81ACtorInits::rva007AD7DD()
{
	( &TheFXParticleEditor )->BfmeDualVtableReleaseDtor::BfmeDualVtableReleaseDtor();
	atexit( rva007B75E2 );
}








// ?rva007B4C38@Rva007AB81ACtorInits@@SAXXZ @ 0x007B4C38 (22B): ??0_Loc_init@ios_base@_STL@@QAE@XZ on VA 0x00E06665, atexit(0x007B9806)
void Rva007AB81ACtorInits::rva007B4C38()
{
	( (_STL::ios_base::_Loc_init *)&g_00E06665 )->_STL::ios_base::_Loc_init::_Loc_init();
	atexit( rva007B9806 );
}

// ?rva007B4C4E@Rva007AB81ACtorInits@@SAXXZ @ 0x007B4C4E (22B): ??0Init@ios_base@_STL@@QAE@XZ on VA 0x00E06664, atexit(0x007B9810)
void Rva007AB81ACtorInits::rva007B4C4E()
{
	( (_STL::ios_base::Init *)&g_00E06664 )->_STL::ios_base::Init::Init();
	atexit( rva007B9810 );
}

// ?rva007B506A@Rva007AB81ACtorInits@@SAXXZ @ 0x007B506A (22B): ??0Rva005E74CF@@QAE@XZ on VA 0x00E06724, atexit(0x007B9965)
void Rva007AB81ACtorInits::rva007B506A()
{
	( (Rva005E74CF *)&g_Va00E06724 )->Rva005E74CF::Rva005E74CF();
	atexit( rva007B9965 );
}



