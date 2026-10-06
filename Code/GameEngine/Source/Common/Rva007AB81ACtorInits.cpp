// cl: /MD
//
// Dynamic initializers from the 0x007AB7DA strip that run an already-rowed
// default constructor (or in-place init member) on a file-scope object, then
// atexit() its already-rowed cleanup thunk: ATL's _AtlWinModule per including
// TU, STLport's ios_base::Init / _Loc_init sentries, SortingRenderStateStruct
// and single-copy globals. Each is one translation unit's compiler-generated
// initializer; the owning TUs are unrecovered, so each keeps an honest address
// name and its global an address-named extern.

extern "C" int __cdecl atexit(void (__cdecl *)(void));

namespace ATL
{
	class CAtlWinModule
	{
	public:
		CAtlWinModule();
	};
}

class Rva00019EB0VTableInstall
{
public:
	Rva00019EB0VTableInstall *init();
};

class Rva000910D8VTableInstall
{
public:
	Rva000910D8VTableInstall *init();
};

class SortingRenderStateStruct
{
public:
	SortingRenderStateStruct();
};

class SegLineRendererClass
{
public:
	SegLineRendererClass();
};

class BfmeDualVtableReleaseDtor
{
public:
	BfmeDualVtableReleaseDtor();
};

class Rva002150CE
{
public:
	Rva002150CE *rva002150CE();
};

class Rva005CB35A
{
public:
	Rva005CB35A();
};

class Rva005E74CF
{
public:
	Rva005E74CF();
};

class SimpleFileFactoryClass
{
public:
	SimpleFileFactoryClass();
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
void __cdecl rva007B7C87();
void __cdecl rva007B972A();
void __cdecl rva007B9825();
void __cdecl rva007B9806();
void __cdecl rva007B9810();
void __cdecl rva007B9965();
void __cdecl rva007B9AB0();
void __cdecl rva007B9B00();
void __cdecl rva007B9B14();
void __cdecl rva007B9B28();

extern unsigned int g_00DDE070;
extern unsigned int g_00DDE071;
extern unsigned int g_00DDE0AC;
extern unsigned g_Va00DDEB24;
extern unsigned g_Va00DE4878;
extern unsigned g_Va00DEDC80;
extern unsigned g_Va00DEE5D8;
extern unsigned int g_Va009F6F30;
extern unsigned g_Va00DFE180;
extern unsigned g_Va00DFE1E8;
extern unsigned g_Va00DFE280;
extern unsigned g_Va00E065EC;
extern unsigned g_Va00E06664;
extern unsigned g_Va00E06665;
extern unsigned g_Va00E06724;
extern unsigned g_Va00E08D48;

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
	static void rva007AEC78();
	static void rva007B494C();
	static void rva007B4C22();
	static void rva007B4C38();
	static void rva007B4C4E();
	static void rva007B506A();
	static void rva007B54F0();
	static void rva007B5558();
	static void rva007B5587();
	static void rva007B55B3();
};

// ?rva007AB81A@Rva007AB81ACtorInits@@SAXXZ @ 0x007AB81A (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B686F)
void Rva007AB81ACtorInits::rva007AB81A()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B686F );
}

// ?rva007AB830@Rva007AB81ACtorInits@@SAXXZ @ 0x007AB830 (22B): ??0_Loc_init@ios_base@_STL@@QAE@XZ on VA 0x00DDE071, atexit(0x007B685A)
void Rva007AB81ACtorInits::rva007AB830()
{
	( (_STL::ios_base::_Loc_init *)&g_00DDE071 )->_STL::ios_base::_Loc_init::_Loc_init();
	atexit( rva007B685A );
}

// ?rva007AB846@Rva007AB81ACtorInits@@SAXXZ @ 0x007AB846 (22B): ??0Init@ios_base@_STL@@QAE@XZ on VA 0x00DDE070, atexit(0x007B6864)
void Rva007AB81ACtorInits::rva007AB846()
{
	( (_STL::ios_base::Init *)&g_00DDE070 )->_STL::ios_base::Init::Init();
	atexit( rva007B6864 );
}

// ?rva007AB8A0@Rva007AB81ACtorInits@@SAXXZ @ 0x007AB8A0 (22B): ?init@Rva00019EB0VTableInstall@@QAEPAV1@XZ on VA 0x00DDEB24, atexit(0x007B6880)
void Rva007AB81ACtorInits::rva007AB8A0()
{
	( (Rva00019EB0VTableInstall *)&g_Va00DDEB24 )->init();
	atexit( rva007B6880 );
}

// ?rva007ABC99@Rva007AB81ACtorInits@@SAXXZ @ 0x007ABC99 (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B6AE7)
void Rva007AB81ACtorInits::rva007ABC99()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B6AE7 );
}

// ?rva007AC15D@Rva007AB81ACtorInits@@SAXXZ @ 0x007AC15D (22B): ?init@Rva000910D8VTableInstall@@QAEPAV1@XZ on VA 0x00DE4878, atexit(0x007B6C3E)
void Rva007AB81ACtorInits::rva007AC15D()
{
	( (Rva000910D8VTableInstall *)&g_Va00DE4878 )->init();
	atexit( rva007B6C3E );
}

// ?rva007ACC00@Rva007AB81ACtorInits@@SAXXZ @ 0x007ACC00 (22B): ??0SortingRenderStateStruct@@QAE@XZ on VA 0x00DEDC80, atexit(0x007B6FC0)
void Rva007AB81ACtorInits::rva007ACC00()
{
	( (SortingRenderStateStruct *)&g_Va00DEDC80 )->SortingRenderStateStruct::SortingRenderStateStruct();
	atexit( rva007B6FC0 );
}

// ?rva007ACC20@Rva007AB81ACtorInits@@SAXXZ @ 0x007ACC20 (22B): ??0SortingRenderStateStruct@@QAE@XZ on VA 0x00DEE5D8, atexit(0x007B6FD0)
void Rva007AB81ACtorInits::rva007ACC20()
{
	( (SortingRenderStateStruct *)&g_Va00DEE5D8 )->SortingRenderStateStruct::SortingRenderStateStruct();
	atexit( rva007B6FD0 );
}

// ?rva007ACE30@Rva007AB81ACtorInits@@SAXXZ @ 0x007ACE30 (22B): ??0SegLineRendererClass@@QAE@XZ on VA 0x00DF6F30, atexit(0x007B71C0)
void Rva007AB81ACtorInits::rva007ACE30()
{
	( (SegLineRendererClass *)&g_Va009F6F30 )->SegLineRendererClass::SegLineRendererClass();
	atexit( rva007B71C0 );
}

// ?rva007AD7DD@Rva007AB81ACtorInits@@SAXXZ @ 0x007AD7DD (22B): ??0BfmeDualVtableReleaseDtor@@QAE@XZ on VA 0x00DFE180, atexit(0x007B75E2)
void Rva007AB81ACtorInits::rva007AD7DD()
{
	( (BfmeDualVtableReleaseDtor *)&g_Va00DFE180 )->BfmeDualVtableReleaseDtor::BfmeDualVtableReleaseDtor();
	atexit( rva007B75E2 );
}

// ?rva007AD9BC@Rva007AB81ACtorInits@@SAXXZ @ 0x007AD9BC (22B): ?rva002150CE@Rva002150CE@@QAEPAV1@XZ on VA 0x00DFE1E8, atexit(0x007B763C)
void Rva007AB81ACtorInits::rva007AD9BC()
{
	( (Rva002150CE *)&g_Va00DFE1E8 )->rva002150CE();
	atexit( rva007B763C );
}

// ?rva007AD9D2@Rva007AB81ACtorInits@@SAXXZ @ 0x007AD9D2 (22B): ?rva002150CE@Rva002150CE@@QAEPAV1@XZ on VA 0x00DFE280, atexit(0x007B7632)
void Rva007AB81ACtorInits::rva007AD9D2()
{
	( (Rva002150CE *)&g_Va00DFE280 )->rva002150CE();
	atexit( rva007B7632 );
}

// ?rva007AEC78@Rva007AB81ACtorInits@@SAXXZ @ 0x007AEC78 (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B7C87)
void Rva007AB81ACtorInits::rva007AEC78()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B7C87 );
}

// ?rva007B494C@Rva007AB81ACtorInits@@SAXXZ @ 0x007B494C (22B): ??0Rva005CB35A@@QAE@XZ on VA 0x00E065EC, atexit(0x007B972A)
void Rva007AB81ACtorInits::rva007B494C()
{
	( (Rva005CB35A *)&g_Va00E065EC )->Rva005CB35A::Rva005CB35A();
	atexit( rva007B972A );
}

// ?rva007B4C22@Rva007AB81ACtorInits@@SAXXZ @ 0x007B4C22 (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B9825)
void Rva007AB81ACtorInits::rva007B4C22()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B9825 );
}

// ?rva007B4C38@Rva007AB81ACtorInits@@SAXXZ @ 0x007B4C38 (22B): ??0_Loc_init@ios_base@_STL@@QAE@XZ on VA 0x00E06665, atexit(0x007B9806)
void Rva007AB81ACtorInits::rva007B4C38()
{
	( (_STL::ios_base::_Loc_init *)&g_Va00E06665 )->_STL::ios_base::_Loc_init::_Loc_init();
	atexit( rva007B9806 );
}

// ?rva007B4C4E@Rva007AB81ACtorInits@@SAXXZ @ 0x007B4C4E (22B): ??0Init@ios_base@_STL@@QAE@XZ on VA 0x00E06664, atexit(0x007B9810)
void Rva007AB81ACtorInits::rva007B4C4E()
{
	( (_STL::ios_base::Init *)&g_Va00E06664 )->_STL::ios_base::Init::Init();
	atexit( rva007B9810 );
}

// ?rva007B506A@Rva007AB81ACtorInits@@SAXXZ @ 0x007B506A (22B): ??0Rva005E74CF@@QAE@XZ on VA 0x00E06724, atexit(0x007B9965)
void Rva007AB81ACtorInits::rva007B506A()
{
	( (Rva005E74CF *)&g_Va00E06724 )->Rva005E74CF::Rva005E74CF();
	atexit( rva007B9965 );
}

// ?rva007B54F0@Rva007AB81ACtorInits@@SAXXZ @ 0x007B54F0 (22B): ??0SimpleFileFactoryClass@@QAE@XZ on VA 0x00E08D48, atexit(0x007B9AB0)
void Rva007AB81ACtorInits::rva007B54F0()
{
	( (SimpleFileFactoryClass *)&g_Va00E08D48 )->SimpleFileFactoryClass::SimpleFileFactoryClass();
	atexit( rva007B9AB0 );
}

// ?rva007B5558@Rva007AB81ACtorInits@@SAXXZ @ 0x007B5558 (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B9B00)
void Rva007AB81ACtorInits::rva007B5558()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B9B00 );
}

// ?rva007B5587@Rva007AB81ACtorInits@@SAXXZ @ 0x007B5587 (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B9B14)
void Rva007AB81ACtorInits::rva007B5587()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B9B14 );
}

// ?rva007B55B3@Rva007AB81ACtorInits@@SAXXZ @ 0x007B55B3 (22B): ??0CAtlWinModule@ATL@@QAE@XZ on VA 0x00DDE0AC, atexit(0x007B9B28)
void Rva007AB81ACtorInits::rva007B55B3()
{
	( (ATL::CAtlWinModule *)&g_00DDE0AC )->ATL::CAtlWinModule::CAtlWinModule();
	atexit( rva007B9B28 );
}
