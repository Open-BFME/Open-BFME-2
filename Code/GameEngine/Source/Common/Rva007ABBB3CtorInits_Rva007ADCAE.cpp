// cl: /MD
// Split from Rva007ABBB3CtorInits.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

// class-gate: allow AsciiString retail calls the out-of-line folded default ctor at 0x00326BE6; the shared header's inline m_text(0) ctor would store inline instead of emitting that call
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class TextureClass;

template <class T> class RefCountPtr
{
public:
	RefCountPtr();
};

class Rva0023C641 { public: Rva0023C641(); };
class Rva0023DBF9
{
public:
	// Construction is the rowed ??0Rva0023C641, reached by a qualified call.
	__declspec(dllimport) __forceinline Rva0023DBF9() { ((Rva0023C641 *)this)->Rva0023C641::Rva0023C641(); }
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
extern unsigned g_Va00DE0878;
extern unsigned g_Va00DE1CCC;
extern unsigned int g_00DE1CCD;
extern unsigned g_Va00DEE93C;	// retail RVA 0x009EE93C (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00DFF0C4;	// retail RVA 0x009FF0C4 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E01CF0;	// retail RVA 0x00A01CF0 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E01CF4;	// retail RVA 0x00A01CF4 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E01E40;
extern unsigned g_Va00E02D90;	// retail RVA 0x00A02D90 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E02D94;	// retail RVA 0x00A02D94 (.bss), defined in Rva007ABBB3CtorInits.cpp
class Rva002B7250;
extern Rva002B7250 g_registryAtE02E88; // 0x00E02E88, Rva003EF14ADtor.cpp
extern unsigned g_Va00E03020;
extern unsigned g_Va00E032E8;	// retail RVA 0x00A032E8 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E0447C;	// retail RVA 0x00A0447C (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E044F0;	// retail RVA 0x00A044F0 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E048C4;
extern unsigned g_Va00E06634;	// retail RVA 0x00A06634 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned g_Va00E06778;
extern unsigned g_Va00E09E60;	// retail RVA 0x00A09E60 (.bss), defined in Rva007ABBB3CtorInits.cpp
extern unsigned int g_Va00E01E7C;
extern unsigned g_Va00DEC018;
extern unsigned g_Va00DEC080;
extern unsigned char g_00DFE7A8;	// canonical byte owner, Rva003B9EC4.cpp
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































// 0x007ADCAE (22B): unrowed zeroing ctor 0x0023DBF9 (pinned) on VA 0x00DFE7A8, atexit(0x007B7786 -> 0x0023DBC3)
void Rva007ABBB3CtorInits::rva007ADCAE()
{
	( (Rva0023DBF9 *)&g_00DFE7A8 )->Rva0023DBF9::Rva0023DBF9();
	atexit( rva007B7786 );
}
