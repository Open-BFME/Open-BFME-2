// cl: /O1 /MD
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

extern "C" int __cdecl atexit(void (__cdecl *)(void));

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

// class-gate: allow AsciiString retail calls the out-of-line folded default ctor at 0x00326BE6; the shared header's inline m_text(0) ctor would store inline instead of emitting that call
class AsciiString
{
public:
	AsciiString();
};

// class-gate: allow UnicodeString retail calls the out-of-line folded default ctor at 0x00326BE6; the shared header's inline empty ctor emits no call
class UnicodeString
{
public:
	UnicodeString();
};

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

class Rva0007EBFB
{
public:
	Rva0007EBFB();
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
void __cdecl rva007B6BF5();
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

extern unsigned g_Va00DDF58C;
extern unsigned g_Va00DDF5B4;
extern unsigned g_Va00DE0878;
extern unsigned g_Va00DE1CCC;
extern unsigned g_Va00DE1CCD;
extern unsigned g_Va00DE2008;
extern unsigned g_Va00DEC008;
extern unsigned g_Va00DEE93C;
extern unsigned g_Va00DFF0C4;
extern unsigned g_Va00E01CF0;
extern unsigned g_Va00E01CF4;
extern unsigned g_Va00E01E40;
extern unsigned g_Va00E02310;
extern unsigned g_Va00E02D90;
extern unsigned g_Va00E02D94;
extern unsigned g_Va00E02E88;
extern unsigned g_Va00E03020;
extern unsigned g_Va00E032E8;
extern unsigned g_Va00E04424;
extern unsigned g_Va00E0447C;
extern unsigned g_Va00E044F0;
extern unsigned g_Va00E048C4;
extern unsigned g_Va00E06634;
extern unsigned g_Va00E06778;
extern unsigned g_Va00E09E60;

struct Rva007ABBB3CtorInits
{
	static void rva007ABBB3();
	static void rva007ABBC9();
	static void rva007ABBE0();
	static void rva007ABCAF();
	static void rva007ABCC5();
	static void rva007AC022();
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
};

// 0x007ABBB3 (22B): ??0INIMacroTable@@QAE@XZ on VA 0x00DDF58C, atexit(0x007B6A6E)
void Rva007ABBB3CtorInits::rva007ABBB3()
{
	( (INIMacroTable *)&g_Va00DDF58C )->INIMacroTable::INIMacroTable();
	atexit( rva007B6A6E );
}

// 0x007ABBC9 (22B): ??0AsciiString@@QAE@XZ on VA 0x00DDF5B4, atexit(0x007B6A5A -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007ABBC9()
{
	( (AsciiString *)&g_Va00DDF5B4 )->AsciiString::AsciiString();
	atexit( rva007B6A5A );
}

// 0x007ABBE0 (22B): ??0AsciiString@@QAE@XZ on VA 0x00DE0878, atexit(0x007B6AA0 -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007ABBE0()
{
	( (AsciiString *)&g_Va00DE0878 )->AsciiString::AsciiString();
	atexit( rva007B6AA0 );
}

// 0x007ABCAF (22B): ??0_Loc_init@ios_base@_STL@@QAE@XZ on VA 0x00DE1CCD, atexit(0x007B6AD2)
void Rva007ABBB3CtorInits::rva007ABCAF()
{
	( (_STL::ios_base::_Loc_init *)&g_Va00DE1CCD )->_STL::ios_base::_Loc_init::_Loc_init();
	atexit( rva007B6AD2 );
}

// 0x007ABCC5 (22B): ??0Init@ios_base@_STL@@QAE@XZ on VA 0x00DE1CCC, atexit(0x007B6ADC)
void Rva007ABBB3CtorInits::rva007ABCC5()
{
	( (_STL::ios_base::Init *)&g_Va00DE1CCC )->_STL::ios_base::Init::Init();
	atexit( rva007B6ADC );
}

// 0x007AC022 (22B): ??0Rva0007EBFB@@QAE@XZ on VA 0x00DE2008, atexit(0x007B6BF5)
void Rva007ABBB3CtorInits::rva007AC022()
{
	( (Rva0007EBFB *)&g_Va00DE2008 )->Rva0007EBFB::Rva0007EBFB();
	atexit( rva007B6BF5 );
}

// 0x007AC880 (22B): ??0?$RefCountPtr@VTextureClass@@@@QAE@XZ on VA 0x00DEC008, atexit(0x007B6E90 -> RefCountPtr<TextureClass> dtor 0x0057098D)
void Rva007ABBB3CtorInits::rva007AC880()
{
	( (RefCountPtr<TextureClass> *)&g_Va00DEC008 )->RefCountPtr<TextureClass>::RefCountPtr();
	atexit( rva007B6E90 );
}

// 0x007ACD72 (22B): ??0AsciiString@@QAE@XZ on VA 0x00DEE93C, atexit(0x007B707A -> AsciiString dtor 0x0048BA39)
void Rva007ABBB3CtorInits::rva007ACD72()
{
	( (AsciiString *)&g_Va00DEE93C )->AsciiString::AsciiString();
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
	( (Rva003818F4 *)&g_Va00E02310 )->Rva003818F4::Rva003818F4();
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
	( (Rva003818F4 *)&g_Va00E02E88 )->Rva003818F4::Rva003818F4();
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
	( (Rva003818F4 *)&g_Va00E04424 )->Rva003818F4::Rva003818F4();
	atexit( rva007B8F08 );
}

// 0x007B3132 (22B): ??0UnicodeString@@QAE@XZ on VA 0x00E0447C, atexit(0x007B8F6D -> UnicodeString dtor 0x005B804E)
void Rva007ABBB3CtorInits::rva007B3132()
{
	( (UnicodeString *)&g_Va00E0447C )->UnicodeString::UnicodeString();
	atexit( rva007B8F6D );
}

// 0x007B33AF (22B): ??0Rva003818F4@@QAE@XZ on VA 0x00E044F0, atexit(0x007B903F)
void Rva007ABBB3CtorInits::rva007B33AF()
{
	( (Rva003818F4 *)&g_Va00E044F0 )->Rva003818F4::Rva003818F4();
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
	( (Rva005D00A6 *)&g_Va00E06634 )->Rva005D00A6::Rva005D00A6();
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
