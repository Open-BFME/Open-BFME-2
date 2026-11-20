#include "../../Include/Common/Rva0023C641Storage.h"
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



template <class T> class RefCountPtr
{
public:
	RefCountPtr();
};

#include "../../Include/GameLogic/Rva0023C641.h"
class Rva0023DBF9
{
public:
	// Construction is the rowed ??0Rva0023C641, reached by a qualified call.
	__declspec(dllimport) __forceinline Rva0023DBF9() { ((Rva0023C641 *)this)->Rva0023C641::Rva0023C641(); }
};


























void __cdecl rva007B7786();




class Rva002B7250;
extern Rva002B7250 g_registryAtE02E88; // 0x00E02E88, Rva003EF14ADtor.cpp


struct Rva007ABBB3CtorInits
{
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
