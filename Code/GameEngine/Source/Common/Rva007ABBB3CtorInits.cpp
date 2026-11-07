// cl: /MD
//
// More dynamic initializers from the 0x007AB7DA strip of the shape
// Rva007AB81ACtorInits.cpp already recovers: run an already-rowed default
// constructor on a file-scope object, then atexit() its already-rowed cleanup
// thunk. The class named for each call is the one the cleanup thunk proves:
// the folded null-first-word constructor at 0x00326BE6 is spelled
// AsciiString, UnicodeString or RefCountPtr<TextureClass> according to the
// destructor the matching cleanup tail-jumps to. Each is one translation
// unit's compiler-generated initializer; the owning TUs are unrecovered, so
// each keeps an honest address name and its global an address-named extern.

#include <stdlib.h>

namespace ATL
{
	class CAtlBaseModule
	{
	public:
		CAtlBaseModule();
	};
}

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

	template <class T> struct less;
	template <class T> class allocator;
	template <class A, class B> struct pair;
	template <class K, class V, class C, class A> class map
	{
	public:
		map();
	};
}

typedef _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > IntPtrMap;
struct TreeHintOpaque0043671B;
struct BfmePod24;
class AsciiString;
typedef _STL::map<unsigned char, int, _STL::less<unsigned char>, _STL::allocator<_STL::pair<const unsigned char, int> > > ByteIntMap;
typedef _STL::map<AsciiString, TreeHintOpaque0043671B, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, TreeHintOpaque0043671B> > > AsciiHintMap;
typedef _STL::map<int, BfmePod24, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > IntPod24Map;

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class TextureClass;

template <class T> class RefCountPtr
{
public:
	RefCountPtr();
};

class INIMacroTable
{
public:
	INIMacroTable();
};

class Rva003818F4
{
public:
	Rva003818F4();
};

class Rva005114BDHolder
{
public:
	Rva005114BDHolder();
};

class Rva005D00A6
{
public:
	Rva005D00A6();
};

class Rva000F8348
{
public:
	Rva000F8348();
};

class Rva000F9C3C
{
public:
	Rva000F9C3C();
};

class Rva005EA635
{
public:
	Rva005EA635();
};

void __cdecl rva007B6A6E();
void __cdecl rva007B6A5A();
void __cdecl rva007B6AA0();
void __cdecl rva007B6AD2();
void __cdecl rva007B6ADC();
void __cdecl rva007B6E90();
void __cdecl rva007B707A();
void __cdecl rva007B7A19();
void __cdecl rva007B7B8C();
void __cdecl rva007B7B82();
void __cdecl rva007B7C7C();
void __cdecl rva007B7DC7();
void __cdecl rva007B80BF();
void __cdecl rva007B80C9();
void __cdecl rva007B8155();
void __cdecl rva007B823D();
void __cdecl rva007B83A5();
void __cdecl rva007B8F08();
void __cdecl rva007B8F6D();
void __cdecl rva007B903F();
void __cdecl rva007B916C();
void __cdecl rva007B9748();
void __cdecl rva007B9997();
void __cdecl rva007B9B1E();
void __cdecl rva007B7CC3();
void __cdecl rva007B6EAE();
void __cdecl rva007B6EC2();
void __cdecl rva007B7786();
void __cdecl rva007B83B9();
void __cdecl rva007B9071();

extern unsigned BfmeINIMacroTableStorage[8];
extern AsciiString BfmeINICurrentFilename;
extern unsigned g_Va00DE1CCC;
extern unsigned int g_00DE1CCD;
// VA 0x00DEC008: the cross-fade mask texture ScreenCrossFadeFilterUpdateFadeLevel.cpp defines.
class BfmeSrcUDC;
extern BfmeSrcUDC *g_bfmeObjUDC;
// VA 0x00DEE93C: the AsciiString Rva0012CAC3Run.cpp defines.
extern AsciiString g_00DEE93C;
unsigned g_Va00DFF0C4;	// retail RVA 0x009FF0C4 (.bss), defined here
unsigned g_Va00E01CF0;	// retail RVA 0x00A01CF0 (.bss), defined here
unsigned g_Va00E01CF4;	// retail RVA 0x00A01CF4 (.bss), defined here
extern unsigned g_Va00E01E40;
// VA 0x00E02310: the Rva003818B0List Rva0038153BListenerWalks.cpp defines.
class Rva003818B0List;
extern Rva003818B0List g_00E02310;
unsigned g_Va00E02D90;	// retail RVA 0x00A02D90 (.bss), defined here
unsigned g_Va00E02D94;	// retail RVA 0x00A02D94 (.bss), defined here
class Rva002B7250;
extern Rva002B7250 g_registryAtE02E88; // 0x00E02E88, Rva003EF14ADtor.cpp
extern unsigned g_Va00E03020;
unsigned g_Va00E032E8;	// retail RVA 0x00A032E8 (.bss), defined here
// VA 0x00E04424: the Rva002B7250 object Rva004EE5D2Erase.cpp defines.
extern Rva002B7250 g_00E04424;
// VA 0x00E0447C: the UnicodeString AptLobbyScreenInitCallbacks.cpp defines.
extern UnicodeString g_00E0447C;
// VA 0x00E044F0: the Rva002B7250 object Rva004EE5D2Erase.cpp defines.
class Rva002B7250;
extern Rva002B7250 g_00E044F0;
extern unsigned g_Va00E048C4;
// RVA 0x00A06634: retail's constructor 0x005D00A6 (rva007B4A1A below) stores its
// vptr at +0, the base's pair at +4 and 1000 at +8 and +0xC, so the object is 16
// bytes. The ledger records +8 and +0xC as their own globals; the others keep this name.
extern "C" { unsigned int __identifier("?g_Va00E06634@@3IA")[4]; }
extern unsigned g_Va00E06778;
unsigned g_Va00E09E60;	// retail RVA 0x00A09E60 (.bss), defined here
extern unsigned int g_Va00E01E7C;
extern unsigned g_Va00DEC018;
extern unsigned g_Va00DEC080;
extern unsigned g_Va00E032EC;
extern unsigned int g_Va00E04544;

struct Rva007ABBB3CtorInits
{
	static void rva007ABBB3();
	static void rva007ABBC9();
	static void rva007ABBE0();
	static void rva007ABCAF();
	static void rva007ABCC5();
	static void rva007AC880();
	static void rva007ACD72();
	static void rva007AE4ED();
	static void rva007AE937();
	static void rva007AE94D();
	static void rva007AECA4();
	static void rva007AF130();
	static void rva007AF833();
	static void rva007AF849();
	static void rva007AFC26();
	static void rva007AFF72();
	static void rva007B0625();
	static void rva007B301A();
	static void rva007B3132();
	static void rva007B33AF();
	static void rva007B37CE();
	static void rva007B4A1A();
	static void rva007B5181();
	static void rva007B559D();
	static void rva007AED71();
	static void rva007AC8B0();
	static void rva007AC8E0();
	static void rva007ADCAE();
	static void rva007B063B();
	static void rva007B3486();
};

// Each initializer calls its class's default constructor out of line, as
// retail does (AsciiString's is the folded null-first-word body at 0x00326BE6);
// the canonical AsciiString() would otherwise expand to an inline store.
#pragma inline_depth(0)

// 0x007ABBB3 (22B): ??0INIMacroTable@@QAE@XZ on VA 0x00DDF58C, atexit(0x007B6A6E)
void Rva007ABBB3CtorInits::rva007ABBB3()
{
	( (INIMacroTable *)&BfmeINIMacroTableStorage )->INIMacroTable::INIMacroTable();
	atexit( rva007B6A6E );
}

// 0x007ABBC9 (22B): ??0AsciiString@@QAE@XZ on VA 0x00DDF5B4, atexit(0x007B6A5A -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007ABBC9()
{
	( (AsciiString *)&BfmeINICurrentFilename )->AsciiString::AsciiString();
	atexit( rva007B6A5A );
}

// 0x007ABBE0 (22B): ??0AsciiString@@QAE@XZ on VA 0x00DE0878, atexit(0x007B6AA0 -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007ABBE0()
{
	( (AsciiString *)&AsciiString::TheEmptyString )->AsciiString::AsciiString();
	atexit( rva007B6AA0 );
}

// 0x007ABCAF (22B): ??0_Loc_init@ios_base@_STL@@QAE@XZ on VA 0x00DE1CCD, atexit(0x007B6AD2)
void Rva007ABBB3CtorInits::rva007ABCAF()
{
	( (_STL::ios_base::_Loc_init *)&g_00DE1CCD )->_STL::ios_base::_Loc_init::_Loc_init();
	atexit( rva007B6AD2 );
}

// 0x007ABCC5 (22B): ??0Init@ios_base@_STL@@QAE@XZ on VA 0x00DE1CCC, atexit(0x007B6ADC)
void Rva007ABBB3CtorInits::rva007ABCC5()
{
	( (_STL::ios_base::Init *)&g_Va00DE1CCC )->_STL::ios_base::Init::Init();
	atexit( rva007B6ADC );
}

// 0x007AC880 (22B): ??0?$RefCountPtr@VTextureClass@@@@QAE@XZ on VA 0x00DEC008, atexit(0x007B6E90 -> RefCountPtr<TextureClass> dtor 0x0057098D)
void Rva007ABBB3CtorInits::rva007AC880()
{
	( (RefCountPtr<TextureClass> *)&g_bfmeObjUDC )->RefCountPtr<TextureClass>::RefCountPtr();
	atexit( rva007B6E90 );
}

// 0x007ACD72 (22B): ??0AsciiString@@QAE@XZ on VA 0x00DEE93C, atexit(0x007B707A -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007ACD72()
{
	( &g_00DEE93C )->AsciiString::AsciiString();
	atexit( rva007B707A );
}

// 0x007AE4ED (22B): ??0UnicodeString@@QAE@XZ on VA 0x00DFF0C4, atexit(0x007B7A19 -> UnicodeString dtor 0x005B804E)
void Rva007ABBB3CtorInits::rva007AE4ED()
{
	( (UnicodeString *)&g_Va00DFF0C4 )->UnicodeString::UnicodeString();
	atexit( rva007B7A19 );
}

// 0x007AE937 (22B): ??0AsciiString@@QAE@XZ on VA 0x00E01CF0, atexit(0x007B7B8C -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007AE937()
{
	( (AsciiString *)&g_Va00E01CF0 )->AsciiString::AsciiString();
	atexit( rva007B7B8C );
}

// 0x007AE94D (22B): ??0AsciiString@@QAE@XZ on VA 0x00E01CF4, atexit(0x007B7B82 -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007AE94D()
{
	( (AsciiString *)&g_Va00E01CF4 )->AsciiString::AsciiString();
	atexit( rva007B7B82 );
}

// 0x007AECA4 (22B): ??0Init@ios_base@_STL@@QAE@XZ on VA 0x00E01E40, atexit(0x007B7C7C)
void Rva007ABBB3CtorInits::rva007AECA4()
{
	( (_STL::ios_base::Init *)&g_Va00E01E40 )->_STL::ios_base::Init::Init();
	atexit( rva007B7C7C );
}

// 0x007AF130 (22B): ??0Rva003818F4@@QAE@XZ on VA 0x00E02310, atexit(0x007B7DC7)
void Rva007ABBB3CtorInits::rva007AF130()
{
	( (Rva003818F4 *)&g_00E02310 )->Rva003818F4::Rva003818F4();
	atexit( rva007B7DC7 );
}

// 0x007AF833 (22B): ??0AsciiString@@QAE@XZ on VA 0x00E02D90, atexit(0x007B80BF -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007AF833()
{
	( (AsciiString *)&g_Va00E02D90 )->AsciiString::AsciiString();
	atexit( rva007B80BF );
}

// 0x007AF849 (22B): ??0AsciiString@@QAE@XZ on VA 0x00E02D94, atexit(0x007B80C9 -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007AF849()
{
	( (AsciiString *)&g_Va00E02D94 )->AsciiString::AsciiString();
	atexit( rva007B80C9 );
}

// 0x007AFC26 (22B): ??0Rva003818F4@@QAE@XZ on VA 0x00E02E88, atexit(0x007B8155)
void Rva007ABBB3CtorInits::rva007AFC26()
{
	( (Rva003818F4 *)&g_registryAtE02E88 )->Rva003818F4::Rva003818F4();
	atexit( rva007B8155 );
}

// 0x007AFF72 (22B): map<int, void *> default ctor 0x0033C432 on VA 0x00E03020, atexit(0x007B823D)
void Rva007ABBB3CtorInits::rva007AFF72()
{
	( (IntPtrMap *)&g_Va00E03020 )->IntPtrMap::map();
	atexit( rva007B823D );
}

// 0x007B0625 (22B): ??0UnicodeString@@QAE@XZ on VA 0x00E032E8, atexit(0x007B83A5 -> UnicodeString dtor 0x005B804E)
void Rva007ABBB3CtorInits::rva007B0625()
{
	( (UnicodeString *)&g_Va00E032E8 )->UnicodeString::UnicodeString();
	atexit( rva007B83A5 );
}

// 0x007B301A (22B): ??0Rva003818F4@@QAE@XZ on VA 0x00E04424, atexit(0x007B8F08)
void Rva007ABBB3CtorInits::rva007B301A()
{
	( (Rva003818F4 *)&g_00E04424 )->Rva003818F4::Rva003818F4();
	atexit( rva007B8F08 );
}

// 0x007B3132 (22B): ??0UnicodeString@@QAE@XZ on VA 0x00E0447C, atexit(0x007B8F6D -> UnicodeString dtor 0x005B804E)
void Rva007ABBB3CtorInits::rva007B3132()
{
	( &g_00E0447C )->UnicodeString::UnicodeString();
	atexit( rva007B8F6D );
}

// 0x007B33AF (22B): ??0Rva003818F4@@QAE@XZ on VA 0x00E044F0, atexit(0x007B903F)
void Rva007ABBB3CtorInits::rva007B33AF()
{
	( (Rva003818F4 *)&g_00E044F0 )->Rva003818F4::Rva003818F4();
	atexit( rva007B903F );
}

// 0x007B37CE (22B): ??0Rva005114BDHolder@@QAE@XZ on VA 0x00E048C4, atexit(0x007B916C)
void Rva007ABBB3CtorInits::rva007B37CE()
{
	( (Rva005114BDHolder *)&g_Va00E048C4 )->Rva005114BDHolder::Rva005114BDHolder();
	atexit( rva007B916C );
}

// 0x007B4A1A (22B): ??0Rva005D00A6@@QAE@XZ on VA 0x00E06634, atexit(0x007B9748)
void Rva007ABBB3CtorInits::rva007B4A1A()
{
	( (Rva005D00A6 *)__identifier("?g_Va00E06634@@3IA") )->Rva005D00A6::Rva005D00A6();
	atexit( rva007B9748 );
}

// 0x007B5181 (22B): ??0Rva005EA635@@QAE@XZ on VA 0x00E06778, atexit(0x007B9997)
void Rva007ABBB3CtorInits::rva007B5181()
{
	( (Rva005EA635 *)&g_Va00E06778 )->Rva005EA635::Rva005EA635();
	atexit( rva007B9997 );
}

// 0x007B559D (22B): ??0CAtlBaseModule@ATL@@QAE@XZ on VA 0x00E09E60, atexit(0x007B9B1E)
void Rva007ABBB3CtorInits::rva007B559D()
{
	( (ATL::CAtlBaseModule *)&g_Va00E09E60 )->ATL::CAtlBaseModule::CAtlBaseModule();
	atexit( rva007B9B1E );
}

// 0x007AED71 (22B): folded map<unsigned char,int> ctor 0x0033C432 on VA 0x00E01E7C, atexit(0x007B7CC3 -> 0x00362B5A)
void Rva007ABBB3CtorInits::rva007AED71()
{
	( (ByteIntMap *)&g_Va00E01E7C )->ByteIntMap::map();
	atexit( rva007B7CC3 );
}

// 0x007B063B (22B): map<AsciiString,TreeHintOpaque0043671B> ctor 0x00435CE0 on VA 0x00E032EC, atexit(0x007B83B9 -> 0x00435CDB)
void Rva007ABBB3CtorInits::rva007B063B()
{
	( (AsciiHintMap *)&g_Va00E032EC )->AsciiHintMap::map();
	atexit( rva007B83B9 );
}

// 0x007B3486 (22B): map<int,BfmePod24> ctor 0x005011C1 on VA 0x00E04544, atexit(0x007B9071 -> 0x005011AA)
void Rva007ABBB3CtorInits::rva007B3486()
{
	( (IntPod24Map *)&g_Va00E04544 )->IntPod24Map::map();
	atexit( rva007B9071 );
}

// 0x007AC8B0 (22B): unrowed vtable 0x00BCF254 ctor 0x000F8348 (pinned) on VA 0x00DEC018, atexit(0x007B6EAE -> 0x000F82F5)
void Rva007ABBB3CtorInits::rva007AC8B0()
{
	( (Rva000F8348 *)&g_Va00DEC018 )->Rva000F8348::Rva000F8348();
	atexit( rva007B6EAE );
}

// 0x007AC8E0 (22B): unrowed vtable 0x00BCF270 ctor 0x000F9C3C (pinned) on VA 0x00DEC080, atexit(0x007B6EC2 -> 0x000F9BD7)
void Rva007ABBB3CtorInits::rva007AC8E0()
{
	( (Rva000F9C3C *)&g_Va00DEC080 )->Rva000F9C3C::Rva000F9C3C();
	atexit( rva007B6EC2 );
}

#pragma inline_depth()
