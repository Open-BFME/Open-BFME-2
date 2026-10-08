// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva007B6880@@YAXXZ @ 0x007B6880 (10B). Global setter thunk: ecx=&g_Va00DDEB24 then tail-jmp to rowed ?apply@Rva00019EC0DwordImmSetter@@QAEXXZ (0x00019EC0) which sets [ecx],0xBBC8D4. No callers. Prev 0x007B5860 (Rva00CE12FCMutex.cpp) next 0x007B7270 (BfmeConv804.cpp). Honest address name; no donor.
extern "C" const void *const vtbl_00CE3934[];  // ??_7Rva00669510@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE3934=??_7Rva00669510@@6B@")

extern "C" const void *const vtbl_00CE36A0[];  // ??_7Rva006680E0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE36A0=??_7Rva006680E0@@6B@")

extern "C" const void *const vtbl_00CE3168[];  // ??_7Rva006655B0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE3168=??_7Rva006655B0@@6B@")

class Rva00019EC0DwordImmSetter
{
public:
	void apply();
};

extern unsigned g_Va00DDEB24;
// g_Va00DDEB24: matched references place it at VA 0xddeb24 (zero-filled .bss).
unsigned int g_Va00DDEB24;

void __cdecl rva007B6880()
{
	Rva00019EC0DwordImmSetter *p = (Rva00019EC0DwordImmSetter *)&g_Va00DDEB24;
	return p->apply();
}

// ?clear@Rva0009990D@@QAEXXZ pin-only target for next thunk (26B @0x0009990D).
class Rva0009990D
{
public:
	void clear();
};

extern unsigned g_Va009E5DF8;
// g_Va009E5DF8: matched references place it at VA 0xde5df8 (zero-filled .bss).
unsigned int g_Va009E5DF8;

// ?rva007B6C9B@@YAXXZ @ 0x007B6C9B (10B). Global clear thunk: ecx=&g_Va009E5DF8 then tail-jmp to pinned ?clear@Rva0009990D@@QAEXXZ (0x0009990D). No callers. Prev is our 0x007B6880 row in this TU. Honest address name.
void __cdecl rva007B6C9B()
{
	Rva0009990D *p = (Rva0009990D *)&g_Va009E5DF8;
	return p->clear();
}

class CriticalSectionClass
{
public:
	~CriticalSectionClass();
};

extern unsigned g_Va00DE4B34;

// ?rva007B6C66@@YAXXZ @ 0x007B6C66 (10B). Global CriticalSectionClass dtor thunk: ecx=&g_Va00DE4B34 then tail-jmp to rowed ??1CriticalSectionClass@@QAE@XZ (0x00613B10).
void __cdecl rva007B6C66()
{
	CriticalSectionClass *p = (CriticalSectionClass *)&g_Va00DE4B34;
	return p->~CriticalSectionClass();
}

class MutexClass
{
public:
	~MutexClass();
};

extern unsigned g_Va00DE5DA0;

// ?rva007B6C70@@YAXXZ @ 0x007B6C70 (10B). Global MutexClass dtor thunk: ecx=&g_Va00DE5DA0 then tail-jmp to rowed ??1MutexClass@@QAE@XZ (0x00613A20).
void __cdecl rva007B6C70()
{
	MutexClass *p = (MutexClass *)&g_Va00DE5DA0;
	return p->~MutexClass();
}

// ?Free_String@StringClass@@AAEXXZ rowed target for next thunks (0x00610A40).
class StringClass
{
	friend void __cdecl rva007B7050();
	friend void __cdecl rva007B7070();
private:
	void Free_String();
};

extern unsigned g_Va009EE91C;
// ?g_Va009EE91C@@3IA: the global at this VA is ?texture_statistics_string@@3VStringClass@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va009EE91C@@3IA=?texture_statistics_string@@3VStringClass@@A")
extern unsigned g_Va009EE938;
// g_Va009EE938: matched references place it at VA 0xdee938 (zero-filled .bss).
unsigned int g_Va009EE938;

// ?rva007B7050@@YAXXZ @ 0x007B7050 (10B). Global Free_String thunk: ecx=&g_Va009EE91C then tail-jmp to rowed ?Free_String@StringClass@@AAEXXZ (0x00610A40). No callers. Prev is our 0x007B6C9B row in this TU. Honest address name.
void __cdecl rva007B7050()
{
	StringClass *p = (StringClass *)&g_Va009EE91C;
	return p->Free_String();
}

// ?rva007B7070@@YAXXZ @ 0x007B7070 (10B). Global Free_String thunk: ecx=&g_Va009EE938 then tail-jmp to rowed ?Free_String@StringClass@@AAEXXZ (0x00610A40). No callers. Same target as 0x007B7050, different global. Honest address name.
void __cdecl rva007B7070()
{
	StringClass *p = (StringClass *)&g_Va009EE938;
	return p->Free_String();
}

struct TextureStatisticsStruct;
template<class T>
class VectorClass
{
public:
	virtual ~VectorClass();
};



extern unsigned g_Va009EE920;
// g_Va009EE920: matched references place it at VA 0xdee920 (zero-filled .bss).
unsigned int g_Va009EE920;

// ?rva007B7060@@YAXXZ @ 0x007B7060 (10B). Global VectorClass dtor thunk: ecx=&g_Va009EE920 then tail-jmp to rowed ??1?$VectorClass@UTextureStatisticsStruct@@@@UAE@XZ (0x0012A4D0). No callers. Prev 0x007B7050 next 0x007B7070 in this TU. Honest address name.
void __cdecl rva007B7060()
{
	VectorClass<TextureStatisticsStruct> *p = (VectorClass<TextureStatisticsStruct> *)&g_Va009EE920;
	return p->VectorClass<TextureStatisticsStruct>::~VectorClass();
}

// ??1AsciiString@@QAE@XZ rowed target for next thunk (5B @0x0048BA39, ICF with StringBase clear/dtor).
#include "ascii_string.h"

extern unsigned g_Va00DE0878;
extern unsigned g_Va00DDF5B4;
extern unsigned g_Va00DEAF18;

// ?rva007B6A5A@@YAXXZ @ 0x007B6A5A (10B). Global AsciiString dtor thunk: ecx=&g_Va00DDF5B4 then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39). No callers. Honest address name.
void __cdecl rva007B6A5A()
{
	AsciiString *p = (AsciiString *)&g_Va00DDF5B4;
	return p->~AsciiString();
}

// ?rva007B6AA0@@YAXXZ @ 0x007B6AA0 (10B). Global AsciiString dtor thunk: ecx=&g_Va00DE0878 then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39). No callers. Prev is our 0x007B7070 row in this TU (same page). Honest address name.
void __cdecl rva007B6AA0()
{
	AsciiString *p = (AsciiString *)&g_Va00DE0878;
	return p->~AsciiString();
}

// ?rva007B6CFF@@YAXXZ @ 0x007B6CFF (10B). Global AsciiString dtor thunk: ecx=&g_Va00DEAF18 then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39).
void __cdecl rva007B6CFF()
{
	AsciiString *p = (AsciiString *)&g_Va00DEAF18;
	return p->~AsciiString();
}

namespace _STL
{
template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class CharT, class Alloc>
class _String_base
{
public:
	~_String_base();
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	~basic_string();
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StlNarrowString;
typedef _STL::_String_base<char, _STL::allocator<char> > StlNarrowStringBase;

extern unsigned g_Va00DDEB2C;
extern unsigned g_Va00DDEF08;
extern unsigned g_Va00DDEEFC;
extern unsigned g_Va00DDEF14;
extern unsigned g_Va00DDEEE4;
extern unsigned g_Va00DDEF38;
extern unsigned g_Va00DDEEF0;
extern unsigned g_Va00DDEF20;
extern unsigned g_Va00DDEF2C;

// ?rva007B68C0@@YAXXZ @ 0x007B68C0 (10B). Global string dtor thunk: ecx=&g_Va00DDEB2C then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B68C0()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DDEB2C;
	return p->~basic_string();
}

// ?rva007B6A00@@YAXXZ @ 0x007B6A00 (10B). Global string base dtor thunk: ecx=&g_Va00DDEEF0 then tail-jmp to rowed ??1?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAE@XZ (0x0000B3C0).
void __cdecl rva007B6A00()
{
	StlNarrowStringBase *p = (StlNarrowStringBase *)&g_Va00DDEEF0;
	return p->~_String_base();
}

// ?rva007B6A10@@YAXXZ @ 0x007B6A10 (10B). Global string base dtor thunk: ecx=&g_Va00DDEF20 then tail-jmp to rowed ??1?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAE@XZ (0x0000B3C0).
void __cdecl rva007B6A10()
{
	StlNarrowStringBase *p = (StlNarrowStringBase *)&g_Va00DDEF20;
	return p->~_String_base();
}

// ?rva007B6A40@@YAXXZ @ 0x007B6A40 (10B). Global string base dtor thunk: ecx=&g_Va00DDEF2C then tail-jmp to rowed ??1?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAE@XZ (0x0000B3C0).
void __cdecl rva007B6A40()
{
	StlNarrowStringBase *p = (StlNarrowStringBase *)&g_Va00DDEF2C;
	return p->~_String_base();
}

// ?rva007B69D0@@YAXXZ @ 0x007B69D0 (10B). Global string dtor thunk: ecx=&g_Va00DDEF08 then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B69D0()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DDEF08;
	return p->~basic_string();
}

// ?rva007B69E0@@YAXXZ @ 0x007B69E0 (10B). Global string dtor thunk: ecx=&g_Va00DDEEFC then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B69E0()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DDEEFC;
	return p->~basic_string();
}

// ?rva007B69F0@@YAXXZ @ 0x007B69F0 (10B). Global string dtor thunk: ecx=&g_Va00DDEF14 then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B69F0()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DDEF14;
	return p->~basic_string();
}

// ?rva007B6A20@@YAXXZ @ 0x007B6A20 (10B). Global string dtor thunk: ecx=&g_Va00DDEEE4 then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B6A20()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DDEEE4;
	return p->~basic_string();
}

// ?rva007B6A30@@YAXXZ @ 0x007B6A30 (10B). Global string dtor thunk: ecx=&g_Va00DDEF38 then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B6A30()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DDEF38;
	return p->~basic_string();
}

// ??1SortingRenderStateStruct@@QAE@XZ rowed target for next thunks (184B @0x0011C5C0).
class SortingRenderStateStruct
{
public:
	~SortingRenderStateStruct();
};

extern unsigned g_Va00DEDC80;
// g_Va00DEDC80: matched references place it at VA 0xdedc80 (zero-filled .bss).
unsigned int g_Va00DEDC80;
extern unsigned ScreenCurrentShader;

// ?rva007B6FC0@@YAXXZ @ 0x007B6FC0 (10B). Global SortingRenderStateStruct dtor thunk: ecx=&g_Va00DEDC80 then tail-jmp to rowed ??1SortingRenderStateStruct@@QAE@XZ (0x0011C5C0). No callers. Same page. Honest address name.
void __cdecl rva007B6FC0()
{
	SortingRenderStateStruct *p = (SortingRenderStateStruct *)&g_Va00DEDC80;
	return p->~SortingRenderStateStruct();
}

// ?rva007B6FD0@@YAXXZ @ 0x007B6FD0 (10B). Global SortingRenderStateStruct dtor thunk: ecx=&ScreenCurrentShader then tail-jmp to rowed ??1SortingRenderStateStruct@@QAE@XZ (0x0011C5C0). No callers. Same target as 0x007B6FC0, different global. Honest address name.
void __cdecl rva007B6FD0()
{
	SortingRenderStateStruct *p = (SortingRenderStateStruct *)&ScreenCurrentShader;
	return p->~SortingRenderStateStruct();
}

// ??1SegLineRendererClass@@QAE@XZ rowed target for next thunk (0x001911C0).
class SegLineRendererClass
{
public:
	~SegLineRendererClass();
};

extern unsigned g_Va009F6F30;
// g_Va009F6F30: matched references place it at VA 0xdf6f30 (zero-filled .bss).
unsigned int g_Va009F6F30;

// ?rva007B71C0@@YAXXZ @ 0x007B71C0 (10B). Global SegLineRenderer dtor thunk: ecx=&g_Va009F6F30 then tail-jmp to rowed ??1SegLineRendererClass@@QAE@XZ (0x001911C0). No callers. Prev is our 0x007B6FD0 row in this TU (same page). Honest address name.
// The deleting-dtor COMDAT copy this TU emits must match part_buf.cpp's /O2-style (add esp,4) copy, while the file stays /O1 for the other thunks: pragma on the caller controls the compiler-generated ??_G.
#pragma optimize("t", on)
void __cdecl rva007B71C0()
{
	SegLineRendererClass *p = (SegLineRendererClass *)&g_Va009F6F30;
	return p->~SegLineRendererClass();
}
#pragma optimize("", on)

class EvacuateDamage
{
public:
	virtual ~EvacuateDamage();
};

extern unsigned g_Va00DDF58C;

// ?rva007B6A6E@@YAXXZ @ 0x007B6A6E (10B). Global EvacuateDamage dtor thunk: ecx=&g_Va00DDF58C then tail-jmp to rowed ??1EvacuateDamage@@UAE@XZ (0x0002CD7B).
void __cdecl rva007B6A6E()
{
	EvacuateDamage *p = (EvacuateDamage *)&g_Va00DDF58C;
	return p->EvacuateDamage::~EvacuateDamage();
}

#include "../../Include/Common/Rva00041004Lock.h"

extern unsigned g_Va00DE0850;
extern unsigned g_Va00DE0828;

// ?rva007B6A80@@YAXXZ @ 0x007B6A80 (10B). Global Rva00041004 dtor thunk: ecx=&g_Va00DE0850 then tail-jmp to rowed ??1Rva00041004@@UAE@XZ (0x00040FE5).
void __cdecl rva007B6A80()
{
	Rva00041004 *p = (Rva00041004 *)&g_Va00DE0850;
	return p->Rva00041004::~Rva00041004();
}

// ?rva007B6A90@@YAXXZ @ 0x007B6A90 (10B). Global Rva00041004 dtor thunk: ecx=&g_Va00DE0828 then tail-jmp to rowed ??1Rva00041004@@UAE@XZ (0x00040FE5).
void __cdecl rva007B6A90()
{
	Rva00041004 *p = (Rva00041004 *)&g_Va00DE0828;
	return p->Rva00041004::~Rva00041004();
}

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
};

extern unsigned g_Va00DE1D00;
extern unsigned g_Va00DE1D60;

// ?rva007B6B19@@YAXXZ @ 0x007B6B19 (10B). Global GeometryInfo dtor thunk: ecx=&g_Va00DE1D00 then tail-jmp to rowed ??1GeometryInfo@@UAE@XZ (0x00050B2A).
void __cdecl rva007B6B19()
{
	GeometryInfo *p = (GeometryInfo *)&g_Va00DE1D00;
	return p->GeometryInfo::~GeometryInfo();
}

// ?rva007B6B23@@YAXXZ @ 0x007B6B23 (10B). Global GeometryInfo dtor thunk: ecx=&g_Va00DE1D60 then tail-jmp to rowed ??1GeometryInfo@@UAE@XZ (0x00050B2A).
void __cdecl rva007B6B23()
{
	GeometryInfo *p = (GeometryInfo *)&g_Va00DE1D60;
	return p->GeometryInfo::~GeometryInfo();
}

class Rva0090088
{
public:
	virtual ~Rva0090088();
};

extern unsigned g_Va00DE2084;

// ?rva007B6C2A@@YAXXZ @ 0x007B6C2A (10B). Global Rva0090088 dtor thunk: ecx=&g_Va00DE2084 then tail-jmp to rowed ??1Rva0090088@@UAE@XZ (0x00090088).
void __cdecl rva007B6C2A()
{
	Rva0090088 *p = (Rva0090088 *)&g_Va00DE2084;
	return p->Rva0090088::~Rva0090088();
}

class Rva00090771DwordImmSetter
{
public:
	void apply();
};

extern unsigned g_Va00DE4878;

// ?rva007B6C3E@@YAXXZ @ 0x007B6C3E (10B). Global Rva00090771DwordImmSetter thunk: ecx=&g_Va00DE4878 then tail-jmp to rowed ?apply@Rva00090771DwordImmSetter@@QAEXXZ (0x00090771).
void __cdecl rva007B6C3E()
{
	Rva00090771DwordImmSetter *p = (Rva00090771DwordImmSetter *)&g_Va00DE4878;
	return p->apply();
}

class Rva001EAF7B
{
public:
	bool rva001EAF7B();
};

extern unsigned g_Va00DA60E8;

// ?rva007B6850@@YAXXZ @ 0x007B6850 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6850()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6AAA@@YAXXZ @ 0x007B6AAA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6AAA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6AB4@@YAXXZ @ 0x007B6AB4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6AB4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6ABE@@YAXXZ @ 0x007B6ABE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6ABE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6AF1@@YAXXZ @ 0x007B6AF1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6AF1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6AFB@@YAXXZ @ 0x007B6AFB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6AFB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B0F@@YAXXZ @ 0x007B6B0F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B0F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B2D@@YAXXZ @ 0x007B6B2D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B2D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B4B@@YAXXZ @ 0x007B6B4B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B4B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B55@@YAXXZ @ 0x007B6B55 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B55()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B5F@@YAXXZ @ 0x007B6B5F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B5F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B69@@YAXXZ @ 0x007B6B69 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B69()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B7D@@YAXXZ @ 0x007B6B7D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B7D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B87@@YAXXZ @ 0x007B6B87 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B87()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6B9B@@YAXXZ @ 0x007B6B9B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B9B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6BA5@@YAXXZ @ 0x007B6BA5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6BA5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6BAF@@YAXXZ @ 0x007B6BAF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6BAF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6BCD@@YAXXZ @ 0x007B6BCD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6BCD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6BD7@@YAXXZ @ 0x007B6BD7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6BD7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6BEB@@YAXXZ @ 0x007B6BEB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6BEB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6BFF@@YAXXZ @ 0x007B6BFF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6BFF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C09@@YAXXZ @ 0x007B6C09 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C09()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C16@@YAXXZ @ 0x007B6C16 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C16()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C20@@YAXXZ @ 0x007B6C20 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C20()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C34@@YAXXZ @ 0x007B6C34 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C34()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C48@@YAXXZ @ 0x007B6C48 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C48()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C52@@YAXXZ @ 0x007B6C52 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C52()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6C5C@@YAXXZ @ 0x007B6C5C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6C5C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CA5@@YAXXZ @ 0x007B6CA5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CA5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CB9@@YAXXZ @ 0x007B6CB9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CB9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CC3@@YAXXZ @ 0x007B6CC3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CC3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CCD@@YAXXZ @ 0x007B6CCD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CCD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CD7@@YAXXZ @ 0x007B6CD7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CD7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CEB@@YAXXZ @ 0x007B6CEB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CEB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6CF5@@YAXXZ @ 0x007B6CF5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6CF5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D13@@YAXXZ @ 0x007B6D13 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D13()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D31@@YAXXZ @ 0x007B6D31 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D31()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D3B@@YAXXZ @ 0x007B6D3B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D3B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D45@@YAXXZ @ 0x007B6D45 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D45()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D4F@@YAXXZ @ 0x007B6D4F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D4F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D59@@YAXXZ @ 0x007B6D59 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D59()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D63@@YAXXZ @ 0x007B6D63 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D63()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D6D@@YAXXZ @ 0x007B6D6D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D6D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D77@@YAXXZ @ 0x007B6D77 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D77()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D81@@YAXXZ @ 0x007B6D81 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D81()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D8B@@YAXXZ @ 0x007B6D8B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D8B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D95@@YAXXZ @ 0x007B6D95 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D95()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6D9F@@YAXXZ @ 0x007B6D9F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6D9F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DAA@@YAXXZ @ 0x007B6DAA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DAA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DB4@@YAXXZ @ 0x007B6DB4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DB4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DBE@@YAXXZ @ 0x007B6DBE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DBE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DC8@@YAXXZ @ 0x007B6DC8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DC8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DD2@@YAXXZ @ 0x007B6DD2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DD2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DDC@@YAXXZ @ 0x007B6DDC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DDC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DE6@@YAXXZ @ 0x007B6DE6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DE6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6DF0@@YAXXZ @ 0x007B6DF0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6DF0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E04@@YAXXZ @ 0x007B6E04 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E04()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E0E@@YAXXZ @ 0x007B6E0E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E0E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E22@@YAXXZ @ 0x007B6E22 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E22()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E2C@@YAXXZ @ 0x007B6E2C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E2C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E40@@YAXXZ @ 0x007B6E40 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E40()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E4A@@YAXXZ @ 0x007B6E4A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E4A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E68@@YAXXZ @ 0x007B6E68 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E68()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E86@@YAXXZ @ 0x007B6E86 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E86()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6E9A@@YAXXZ @ 0x007B6E9A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6E9A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6EA4@@YAXXZ @ 0x007B6EA4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6EA4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ rowed target for next thunk (0x000F1D19).
class Curve3DClass
{
public:
	class KeyClass;
};

template<class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

extern unsigned g_00DEBE0C;
// g_00DEBE0C: packet annotates VA 0x00DEBE0C (data RVA 0x009EBE0C), no name yet.

// ?rva007B6E54@@YAXXZ @ 0x007B6E54 (10B). Global DynamicVectorClass dtor thunk: ecx=&g_00DEBE0C then tail-jmp to rowed ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ (0x000F1D19). No callers. Between 0x007B6E4A and 0x007B6E68. Honest address name.
void __cdecl rva007B6E54()
{
	DynamicVectorClass<Curve3DClass::KeyClass> *p = (DynamicVectorClass<Curve3DClass::KeyClass> *)&g_00DEBE0C;
	return p->DynamicVectorClass<Curve3DClass::KeyClass>::~DynamicVectorClass();
}

// ?rva007B6EB8@@YAXXZ @ 0x007B6EB8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6EB8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6ECC@@YAXXZ @ 0x007B6ECC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6ECC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6EE0@@YAXXZ @ 0x007B6EE0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6EE0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6EFE@@YAXXZ @ 0x007B6EFE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6EFE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F1C@@YAXXZ @ 0x007B6F1C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F1C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F28@@YAXXZ @ 0x007B6F28 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F28()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F32@@YAXXZ @ 0x007B6F32 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F32()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F3E@@YAXXZ @ 0x007B6F3E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F3E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F48@@YAXXZ @ 0x007B6F48 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F48()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F52@@YAXXZ @ 0x007B6F52 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F52()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F66@@YAXXZ @ 0x007B6F66 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F66()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F70@@YAXXZ @ 0x007B6F70 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F70()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F7A@@YAXXZ @ 0x007B6F7A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F7A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6F84@@YAXXZ @ 0x007B6F84 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6F84()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6FA2@@YAXXZ @ 0x007B6FA2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6FA2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B6FAC@@YAXXZ @ 0x007B6FAC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6FAC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

extern unsigned g_Va00DEAF20;
extern unsigned g_Va00DEC290;
extern unsigned g_Va00DEC3B8;
extern unsigned g_Va00DEE93C;

// ?rva007B6D09@@YAXXZ @ 0x007B6D09 (10B). Global AsciiString dtor thunk: ecx=&g_Va00DEAF20 then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39).
void __cdecl rva007B6D09()
{
	AsciiString *p = (AsciiString *)&g_Va00DEAF20;
	return p->~AsciiString();
}

// ?rva007B6F5C@@YAXXZ @ 0x007B6F5C (10B). Global AsciiString dtor thunk: ecx=&g_Va00DEC290 then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39).
void __cdecl rva007B6F5C()
{
	AsciiString *p = (AsciiString *)&g_Va00DEC290;
	return p->~AsciiString();
}

// ?rva007B6F98@@YAXXZ @ 0x007B6F98 (10B). Global AsciiString dtor thunk: ecx=&g_Va00DEC3B8 then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39).
void __cdecl rva007B6F98()
{
	AsciiString *p = (AsciiString *)&g_Va00DEC3B8;
	return p->~AsciiString();
}

// ?rva007B707A@@YAXXZ @ 0x007B707A (10B). Global AsciiString dtor thunk: ecx=&g_Va00DEE93C then tail-jmp to rowed ??1AsciiString@@QAE@XZ (0x0048BA39).
void __cdecl rva007B707A()
{
	AsciiString *p = (AsciiString *)&g_Va00DEE93C;
	return p->~AsciiString();
}

extern unsigned g_Va00DEC390;
extern unsigned g_Va00DF2984;

// ?rva007B6F8E@@YAXXZ @ 0x007B6F8E (10B). Global Rva00041004 dtor thunk: ecx=&g_Va00DEC390 then tail-jmp to rowed ??1Rva00041004@@UAE@XZ (0x00040FE5).
void __cdecl rva007B6F8E()
{
	Rva00041004 *p = (Rva00041004 *)&g_Va00DEC390;
	return p->Rva00041004::~Rva00041004();
}

// ?rva007B70AB@@YAXXZ @ 0x007B70AB (10B). Global Rva00041004 dtor thunk: ecx=&g_Va00DF2984 then tail-jmp to rowed ??1Rva00041004@@UAE@XZ (0x00040FE5).
void __cdecl rva007B70AB()
{
	Rva00041004 *p = (Rva00041004 *)&g_Va00DF2984;
	return p->Rva00041004::~Rva00041004();
}

extern unsigned g_Va00DB424C;

// ?rva007B6B91@@YAXXZ @ 0x007B6B91 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DB424C then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B6B91()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DB424C;
	p->rva001EAF7B();
}

extern unsigned g_Va00DEBE24;
extern unsigned g_Va00DF3648;
extern unsigned g_Va00DF3660;

// ?rva007B6E5E@@YAXXZ @ 0x007B6E5E (10B). Global DynamicVectorClass dtor thunk: ecx=&g_Va00DEBE24 then tail-jmp to rowed ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ (0x000F1D19).
void __cdecl rva007B6E5E()
{
	DynamicVectorClass<Curve3DClass::KeyClass> *p = (DynamicVectorClass<Curve3DClass::KeyClass> *)&g_Va00DEBE24;
	return p->DynamicVectorClass<Curve3DClass::KeyClass>::~DynamicVectorClass();
}

// ?rva007B7190@@YAXXZ @ 0x007B7190 (10B). Global DynamicVectorClass dtor thunk: ecx=&g_Va00DF3648 then tail-jmp to rowed ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ (0x000F1D19).
void __cdecl rva007B7190()
{
	DynamicVectorClass<Curve3DClass::KeyClass> *p = (DynamicVectorClass<Curve3DClass::KeyClass> *)&g_Va00DF3648;
	return p->DynamicVectorClass<Curve3DClass::KeyClass>::~DynamicVectorClass();
}

// ?rva007B71A0@@YAXXZ @ 0x007B71A0 (10B). Global DynamicVectorClass dtor thunk: ecx=&g_Va00DF3660 then tail-jmp to rowed ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ (0x000F1D19).
void __cdecl rva007B71A0()
{
	DynamicVectorClass<Curve3DClass::KeyClass> *p = (DynamicVectorClass<Curve3DClass::KeyClass> *)&g_Va00DF3660;
	return p->DynamicVectorClass<Curve3DClass::KeyClass>::~DynamicVectorClass();
}

class TextureClass;

template <class T>
class RefCountPtr
{
public:
	~RefCountPtr();
};

extern unsigned g_Va00DEC008;
extern unsigned g_Va00DF2974;
extern unsigned g_Va00DF297C;

// ?rva007B6E90@@YAXXZ @ 0x007B6E90 (10B). Global RefCountPtr<TextureClass> dtor thunk: ecx=&g_Va00DEC008 then tail-jmp to rowed ??1?$RefCountPtr@VTextureClass@@@@QAE@XZ (0x0017098D).
void __cdecl rva007B6E90()
{
	RefCountPtr<TextureClass> *p = (RefCountPtr<TextureClass> *)&g_Va00DEC008;
	return p->~RefCountPtr();
}

// ?rva007B70B5@@YAXXZ @ 0x007B70B5 (10B). Global RefCountPtr<TextureClass> dtor thunk: ecx=&g_Va00DF2974 then tail-jmp to rowed ??1?$RefCountPtr@VTextureClass@@@@QAE@XZ (0x0017098D).
void __cdecl rva007B70B5()
{
	RefCountPtr<TextureClass> *p = (RefCountPtr<TextureClass> *)&g_Va00DF2974;
	return p->~RefCountPtr();
}

// ?rva007B70BF@@YAXXZ @ 0x007B70BF (10B). Global RefCountPtr<TextureClass> dtor thunk: ecx=&g_Va00DF297C then tail-jmp to rowed ??1?$RefCountPtr@VTextureClass@@@@QAE@XZ (0x0017098D).
void __cdecl rva007B70BF()
{
	RefCountPtr<TextureClass> *p = (RefCountPtr<TextureClass> *)&g_Va00DF297C;
	return p->~RefCountPtr();
}

// ?rva007B751A@@YAXXZ @ 0x007B751A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B751A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7524@@YAXXZ @ 0x007B7524 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7524()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B752E@@YAXXZ @ 0x007B752E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B752E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7538@@YAXXZ @ 0x007B7538 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7538()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7542@@YAXXZ @ 0x007B7542 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7542()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B754C@@YAXXZ @ 0x007B754C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B754C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7560@@YAXXZ @ 0x007B7560 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7560()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B756A@@YAXXZ @ 0x007B756A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B756A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7574@@YAXXZ @ 0x007B7574 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7574()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B757E@@YAXXZ @ 0x007B757E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B757E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7592@@YAXXZ @ 0x007B7592 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7592()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B75B0@@YAXXZ @ 0x007B75B0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B75B0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B75BA@@YAXXZ @ 0x007B75BA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B75BA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B75CE@@YAXXZ @ 0x007B75CE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B75CE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B75D8@@YAXXZ @ 0x007B75D8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B75D8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B75EC@@YAXXZ @ 0x007B75EC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B75EC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7600@@YAXXZ @ 0x007B7600 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7600()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7614@@YAXXZ @ 0x007B7614 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7614()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B761E@@YAXXZ @ 0x007B761E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B761E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7628@@YAXXZ @ 0x007B7628 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7628()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7646@@YAXXZ @ 0x007B7646 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7646()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B76D2@@YAXXZ @ 0x007B76D2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B76D2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B76F0@@YAXXZ @ 0x007B76F0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B76F0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7722@@YAXXZ @ 0x007B7722 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7722()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B772C@@YAXXZ @ 0x007B772C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B772C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B774A@@YAXXZ @ 0x007B774A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B774A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7754@@YAXXZ @ 0x007B7754 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7754()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7772@@YAXXZ @ 0x007B7772 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7772()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7790@@YAXXZ @ 0x007B7790 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7790()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B779A@@YAXXZ @ 0x007B779A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B779A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B77A4@@YAXXZ @ 0x007B77A4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B77A4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B77AE@@YAXXZ @ 0x007B77AE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B77AE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B77C3@@YAXXZ @ 0x007B77C3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B77C3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B77CE@@YAXXZ @ 0x007B77CE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B77CE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B77E2@@YAXXZ @ 0x007B77E2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B77E2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B77FC@@YAXXZ @ 0x007B77FC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B77FC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7806@@YAXXZ @ 0x007B7806 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7806()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7838@@YAXXZ @ 0x007B7838 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7838()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7888@@YAXXZ @ 0x007B7888 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7888()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B78B0@@YAXXZ @ 0x007B78B0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B78B0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B78CE@@YAXXZ @ 0x007B78CE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B78CE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B78D8@@YAXXZ @ 0x007B78D8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B78D8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B78E2@@YAXXZ @ 0x007B78E2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B78E2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B78F6@@YAXXZ @ 0x007B78F6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B78F6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B790A@@YAXXZ @ 0x007B790A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B790A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7914@@YAXXZ @ 0x007B7914 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7914()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B791E@@YAXXZ @ 0x007B791E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B791E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7928@@YAXXZ @ 0x007B7928 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7928()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7932@@YAXXZ @ 0x007B7932 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7932()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B793C@@YAXXZ @ 0x007B793C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B793C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7946@@YAXXZ @ 0x007B7946 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7946()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7950@@YAXXZ @ 0x007B7950 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7950()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B795A@@YAXXZ @ 0x007B795A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B795A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7964@@YAXXZ @ 0x007B7964 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7964()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B79C9@@YAXXZ @ 0x007B79C9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B79C9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B79D3@@YAXXZ @ 0x007B79D3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B79D3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B79DD@@YAXXZ @ 0x007B79DD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B79DD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B79E7@@YAXXZ @ 0x007B79E7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B79E7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B79F1@@YAXXZ @ 0x007B79F1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B79F1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// The observed 24-byte ScienceStore pool is owned by Rva002E8548Pool.cpp.
class Rva002E8548;
extern Rva002E8548 g_Va00DB9440;

// ?rva007B75C4@@YAXXZ @ 0x007B75C4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DB9440 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B). No callers. Honest address name.
void __cdecl rva007B75C4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DB9440;
	p->rva001EAF7B();
}

// The observed 24-byte pool is owned by Rva002E8548Pool.cpp.
class Rva002E8548;
extern Rva002E8548 g_Va00DBD4C8;

// ?rva007B7A37@@YAXXZ @ 0x007B7A37 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DBD4C8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B). No callers. Honest address name.
void __cdecl rva007B7A37()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DBD4C8;
	p->rva001EAF7B();
}

extern unsigned g_Va00DBD4B0;
unsigned int g_Va00DBD4B0;

// ?rva007B7A41@@YAXXZ @ 0x007B7A41 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DBD4B0 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B). No callers. Honest address name.
void __cdecl rva007B7A41()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DBD4B0;
	p->rva001EAF7B();
}

// ?rva007B7A0F@@YAXXZ @ 0x007B7A0F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7A0F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7A23@@YAXXZ @ 0x007B7A23 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7A23()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7A2D@@YAXXZ @ 0x007B7A2D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7A2D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7A4B@@YAXXZ @ 0x007B7A4B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7A4B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7A73@@YAXXZ @ 0x007B7A73 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7A73()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7AAF@@YAXXZ @ 0x007B7AAF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7AAF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7AB9@@YAXXZ @ 0x007B7AB9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7AB9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7AC3@@YAXXZ @ 0x007B7AC3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7AC3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7AEB@@YAXXZ @ 0x007B7AEB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7AEB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7B1E@@YAXXZ @ 0x007B7B1E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7B1E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7B32@@YAXXZ @ 0x007B7B32 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7B32()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7B3C@@YAXXZ @ 0x007B7B3C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7B3C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7B46@@YAXXZ @ 0x007B7B46 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7B46()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7B78@@YAXXZ @ 0x007B7B78 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7B78()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7B96@@YAXXZ @ 0x007B7B96 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7B96()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BA0@@YAXXZ @ 0x007B7BA0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BA0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BAA@@YAXXZ @ 0x007B7BAA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BAA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BB4@@YAXXZ @ 0x007B7BB4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BB4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BD2@@YAXXZ @ 0x007B7BD2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BD2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BDC@@YAXXZ @ 0x007B7BDC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BDC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BE6@@YAXXZ @ 0x007B7BE6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BE6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BF0@@YAXXZ @ 0x007B7BF0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BF0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7BFA@@YAXXZ @ 0x007B7BFA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7BFA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C0E@@YAXXZ @ 0x007B7C0E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C0E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C18@@YAXXZ @ 0x007B7C18 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C18()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C22@@YAXXZ @ 0x007B7C22 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C22()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C2C@@YAXXZ @ 0x007B7C2C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C2C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C36@@YAXXZ @ 0x007B7C36 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C36()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C4A@@YAXXZ @ 0x007B7C4A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C4A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C54@@YAXXZ @ 0x007B7C54 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C54()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C5E@@YAXXZ @ 0x007B7C5E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C5E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C68@@YAXXZ @ 0x007B7C68 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C68()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C91@@YAXXZ @ 0x007B7C91 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C91()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7C9B@@YAXXZ @ 0x007B7C9B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7C9B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7CA5@@YAXXZ @ 0x007B7CA5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7CA5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7CB9@@YAXXZ @ 0x007B7CB9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7CB9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7CCD@@YAXXZ @ 0x007B7CCD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7CCD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7CE1@@YAXXZ @ 0x007B7CE1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7CE1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7CEB@@YAXXZ @ 0x007B7CEB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7CEB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7CFF@@YAXXZ @ 0x007B7CFF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7CFF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D09@@YAXXZ @ 0x007B7D09 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D09()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D13@@YAXXZ @ 0x007B7D13 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D13()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D1D@@YAXXZ @ 0x007B7D1D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D1D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D4F@@YAXXZ @ 0x007B7D4F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D4F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D63@@YAXXZ @ 0x007B7D63 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D63()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D6D@@YAXXZ @ 0x007B7D6D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D6D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D8B@@YAXXZ @ 0x007B7D8B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D8B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7D9F@@YAXXZ @ 0x007B7D9F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7D9F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7DA9@@YAXXZ @ 0x007B7DA9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7DA9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7DBD@@YAXXZ @ 0x007B7DBD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7DBD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7DE5@@YAXXZ @ 0x007B7DE5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7DE5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7DEF@@YAXXZ @ 0x007B7DEF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7DEF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7DF9@@YAXXZ @ 0x007B7DF9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7DF9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}










// ?rva007B7E03@@YAXXZ @ 0x007B7E03 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E03()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E17@@YAXXZ @ 0x007B7E17 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E17()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E2B@@YAXXZ @ 0x007B7E2B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E2B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E35@@YAXXZ @ 0x007B7E35 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E35()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E53@@YAXXZ @ 0x007B7E53 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E53()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E5D@@YAXXZ @ 0x007B7E5D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E5D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E67@@YAXXZ @ 0x007B7E67 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E67()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E71@@YAXXZ @ 0x007B7E71 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E71()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E7B@@YAXXZ @ 0x007B7E7B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E7B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B7E85@@YAXXZ @ 0x007B7E85 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B7E85()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B806F@@YAXXZ @ 0x007B806F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B806F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8079@@YAXXZ @ 0x007B8079 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8079()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8083@@YAXXZ @ 0x007B8083 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8083()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B808D@@YAXXZ @ 0x007B808D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B808D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8097@@YAXXZ @ 0x007B8097 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8097()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B80AB@@YAXXZ @ 0x007B80AB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B80AB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

extern void *g_00DB6200;
extern char g_00BD23B4;
// g_00DB6200: packet annotates VA 0x009B6200 (data), no name yet.
// g_00BD23B4: packet annotates VA 0x007D23B4 (data), no name yet.

// ?Rva007B7090Set@@YAXXZ @ 0x007B7090 (11B). Global pointer store: g_00DB6200 = &g_00BD23B4 (mov [0xDB6200],0xBD23B4; ret). No callers. Between 0x007B707A and 0x007B70AB. Honest address name.
void __cdecl Rva007B7090Set()
{
	g_00DB6200 = &g_00BD23B4;
}

class BfmeDualVtableReleaseDtor
{
public:
	virtual ~BfmeDualVtableReleaseDtor();
};

extern unsigned g_00DFE180;
// g_00DFE180: packet annotates VA 0x009FE180 (data), no name yet.

// ?rva007B75E2@@YAXXZ @ 0x007B75E2 (10B). Global BfmeDualVtableReleaseDtor dtor thunk: ecx=&g_00DFE180 then tail-jmp to rowed ??1BfmeDualVtableReleaseDtor@@UAE@XZ (0x00203629). No callers. Between 0x007B75D8 and 0x007B75EC. Honest address name.
void __cdecl rva007B75E2()
{
	BfmeDualVtableReleaseDtor *p = (BfmeDualVtableReleaseDtor *)&g_00DFE180;
	return p->BfmeDualVtableReleaseDtor::~BfmeDualVtableReleaseDtor();
}

namespace _STL
{
template <typename T, typename A>
class vector
{
public:
	~vector();
};
}

extern unsigned g_00DFE174;
// g_00DFE174: packet annotates VA 0x009FE174 (data), no name yet.

// ?rva007B75F6@@YAXXZ @ 0x007B75F6 (10B). Global vector<AsciiString> dtor thunk: ecx=&g_00DFE174 then tail-jmp to rowed ??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ (0x0002CC70). No callers. Between 0x007B75EC and 0x007B7600. Honest address name.
void __cdecl rva007B75F6()
{
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > *p = (_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)&g_00DFE174;
	return p->_STL::vector<AsciiString, _STL::allocator<AsciiString> >::~vector();
}

extern unsigned g_00DFE1AC;
// g_00DFE1AC: packet annotates VA 0x009FE1AC (data), no name yet.

// ?rva007B760A@@YAXXZ @ 0x007B760A (10B). Global basic_string<char> dtor thunk: ecx=&g_00DFE1AC then tail-jmp to rowed BasicStringCharDtor_dup (0x0007FAB3 object ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ). No callers. Between 0x007B7600 and 0x007B7614. Honest address name.
void __cdecl rva007B760A()
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p = (_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)&g_00DFE1AC;
	return p->_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::~basic_string();
}

class Open2Dtor40B830
{
public:
	~Open2Dtor40B830();
};

extern unsigned g_00DFE280;
// g_00DFE280: packet annotates VA 0x009FE280 (data), no name yet.

// ?rva007B7632@@YAXXZ @ 0x007B7632 (10B). Global Open2Dtor40B830 dtor thunk: ecx=&g_00DFE280 then tail-jmp to rowed ??1Open2Dtor40B830@@QAE@XZ (0x00215101). No callers. Between 0x007B7628 and 0x007B7646. Honest address name.
void __cdecl rva007B7632()
{
	Open2Dtor40B830 *p = (Open2Dtor40B830 *)&g_00DFE280;
	return p->Open2Dtor40B830::~Open2Dtor40B830();
}

extern unsigned g_00DFE1E8;
// g_00DFE1E8: packet annotates VA 0x009FE1E8 (data), no name yet.

// ?rva007B763C@@YAXXZ @ 0x007B763C (10B). Global Open2Dtor40B830 dtor thunk: ecx=&g_00DFE1E8 then tail-jmp to rowed ??1Open2Dtor40B830@@QAE@XZ (0x00215101). No callers. Between 0x007B7632 and 0x007B7646. Honest address name.
void __cdecl rva007B763C()
{
	Open2Dtor40B830 *p = (Open2Dtor40B830 *)&g_00DFE1E8;
	return p->Open2Dtor40B830::~Open2Dtor40B830();
}

extern unsigned g_00DFE358;
// g_00DFE358: packet annotates VA 0x00DFE358 (data RVA 0x009FE358), no name yet.

// ?rva007B76DC@@YAXXZ @ 0x007B76DC (10B). Global basic_string<char> dtor thunk: ecx=&g_00DFE358 then tail-jmp to rowed BasicStringCharDtor_dup (0x0007FAB3 object ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ). No callers. Between 0x007B76D2 and 0x007B76F0. Honest address name.
void __cdecl rva007B76DC()
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p = (_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)&g_00DFE358;
	return p->_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::~basic_string();
}

extern unsigned g_00DFEA44;
// g_00DFEA44: packet annotates VA 0x00DFEA44 (data RVA 0x009FEA44), no name yet.

// ?rva007B77B9@@YAXXZ @ 0x007B77B9 (10B). Global basic_string<char> dtor thunk: ecx=&g_00DFEA44 then tail-jmp to rowed BasicStringCharDtor_dup (0x0007FAB3 object ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ). No callers. Between 0x007B77AE and 0x007B77C3. Honest address name.
void __cdecl rva007B77B9()
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p = (_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)&g_00DFEA44;
	return p->_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::~basic_string();
}

extern unsigned g_00E01CF4;
// g_00E01CF4: packet annotates VA 0x00E01CF4 (data RVA 0x00A01CF4), no name yet.

// ?rva007B7B82@@YAXXZ @ 0x007B7B82 (10B). Global StringBase<char> clear thunk: ecx=&g_00E01CF4 then tail-jmp to rowed ?clear@?$StringBase@D@@QAEXXZ (0x0048BA39). No callers. Between 0x007B7B78 and 0x007B7B96. Honest address name.
void __cdecl rva007B7B82()
{
	StringBase<char> *p = (StringBase<char> *)&g_00E01CF4;
	return p->clear();
}

extern unsigned g_00E01CF0;
// g_00E01CF0: packet annotates VA 0x00E01CF0 (data RVA 0x00A01CF0), no name yet.

// ?rva007B7B8C@@YAXXZ @ 0x007B7B8C (10B). Global StringBase<char> clear thunk: ecx=&g_00E01CF0 then tail-jmp to rowed ?clear@?$StringBase@D@@QAEXXZ (0x0048BA39). No callers. Between 0x007B7B82 and 0x007B7B96. Honest address name.
void __cdecl rva007B7B8C()
{
	StringBase<char> *p = (StringBase<char> *)&g_00E01CF0;
	return p->clear();
}

extern void *g_00DB620C;
// g_00DB620C: packet annotates VA 0x009B620C (data), no name yet. Value is &g_00BD23B4 (VA 0x007D23B4, already extern above).

// ?Rva007B70A0Set@@YAXXZ @ 0x007B70A0 (11B). Global pointer store: g_00DB620C = &g_00BD23B4 (mov [0xDB620C],0xBD23B4; ret). No callers. Between 0x007B7090 and 0x007B70AB. Honest address name.
void __cdecl Rva007B70A0Set()
{
	g_00DB620C = &g_00BD23B4;
}

class ModuleData;
// g_vec00200D38: packet annotates VA 0x00DDF580 (data RVA 0x009DF580) with extern name in use ?g_vec00200D38@@3V?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@A (vector<const ModuleData*> from Rva00200D38Ctor.cpp). Retail thunk calls BasicStringCharDtor_dup on it; cast preserves bytes.
extern _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > g_vec00200D38;

// ?rva007B6A64@@YAXXZ @ 0x007B6A64 (10B). Global basic_string<char> dtor thunk on vector global address: ecx=&g_vec00200D38 then tail-jmp to rowed BasicStringCharDtor_dup (0x0007FAB3 object ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ). No callers. Between 0x007B6A40 and 0x007B6A5A. Honest address name.
void __cdecl rva007B6A64()
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p = (_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)&g_vec00200D38;
	return p->_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::~basic_string();
}

// ?rva007B80D3@@YAXXZ @ 0x007B80D3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B80D3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B80DD@@YAXXZ @ 0x007B80DD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B80DD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B80E7@@YAXXZ @ 0x007B80E7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B80E7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B815F@@YAXXZ @ 0x007B815F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B815F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B816B@@YAXXZ @ 0x007B816B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B816B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B819D@@YAXXZ @ 0x007B819D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B819D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81A7@@YAXXZ @ 0x007B81A7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81A7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81B1@@YAXXZ @ 0x007B81B1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81B1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81BB@@YAXXZ @ 0x007B81BB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81BB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81C5@@YAXXZ @ 0x007B81C5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81C5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81CF@@YAXXZ @ 0x007B81CF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81CF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81D9@@YAXXZ @ 0x007B81D9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81D9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81E3@@YAXXZ @ 0x007B81E3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81E3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B81ED@@YAXXZ @ 0x007B81ED (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B81ED()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B820B@@YAXXZ @ 0x007B820B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B820B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8215@@YAXXZ @ 0x007B8215 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8215()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8251@@YAXXZ @ 0x007B8251 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8251()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B825B@@YAXXZ @ 0x007B825B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B825B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B826F@@YAXXZ @ 0x007B826F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B826F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8279@@YAXXZ @ 0x007B8279 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8279()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B828D@@YAXXZ @ 0x007B828D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B828D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8297@@YAXXZ @ 0x007B8297 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8297()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B82A1@@YAXXZ @ 0x007B82A1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B82A1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B82AB@@YAXXZ @ 0x007B82AB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B82AB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B82B5@@YAXXZ @ 0x007B82B5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B82B5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B82F1@@YAXXZ @ 0x007B82F1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B82F1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B82FB@@YAXXZ @ 0x007B82FB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B82FB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8305@@YAXXZ @ 0x007B8305 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8305()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B830F@@YAXXZ @ 0x007B830F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B830F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8319@@YAXXZ @ 0x007B8319 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8319()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B832D@@YAXXZ @ 0x007B832D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B832D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8337@@YAXXZ @ 0x007B8337 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8337()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8341@@YAXXZ @ 0x007B8341 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8341()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8355@@YAXXZ @ 0x007B8355 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8355()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B835F@@YAXXZ @ 0x007B835F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B835F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8373@@YAXXZ @ 0x007B8373 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8373()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8387@@YAXXZ @ 0x007B8387 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8387()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8391@@YAXXZ @ 0x007B8391 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8391()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B83AF@@YAXXZ @ 0x007B83AF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B83AF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B83C3@@YAXXZ @ 0x007B83C3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B83C3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B83CD@@YAXXZ @ 0x007B83CD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B83CD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B83D7@@YAXXZ @ 0x007B83D7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B83D7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8413@@YAXXZ @ 0x007B8413 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8413()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B841D@@YAXXZ @ 0x007B841D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B841D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8427@@YAXXZ @ 0x007B8427 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8427()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8431@@YAXXZ @ 0x007B8431 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8431()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8445@@YAXXZ @ 0x007B8445 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8445()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8459@@YAXXZ @ 0x007B8459 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8459()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B846D@@YAXXZ @ 0x007B846D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B846D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8477@@YAXXZ @ 0x007B8477 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8477()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B848B@@YAXXZ @ 0x007B848B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B848B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8495@@YAXXZ @ 0x007B8495 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8495()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B849F@@YAXXZ @ 0x007B849F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B849F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84A9@@YAXXZ @ 0x007B84A9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84A9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84B3@@YAXXZ @ 0x007B84B3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84B3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84BD@@YAXXZ @ 0x007B84BD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84BD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84C7@@YAXXZ @ 0x007B84C7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84C7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84D1@@YAXXZ @ 0x007B84D1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84D1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84DB@@YAXXZ @ 0x007B84DB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84DB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84E5@@YAXXZ @ 0x007B84E5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84E5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B84EF@@YAXXZ @ 0x007B84EF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B84EF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8503@@YAXXZ @ 0x007B8503 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8503()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B850D@@YAXXZ @ 0x007B850D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B850D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8517@@YAXXZ @ 0x007B8517 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8517()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8521@@YAXXZ @ 0x007B8521 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8521()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B852B@@YAXXZ @ 0x007B852B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B852B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8535@@YAXXZ @ 0x007B8535 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8535()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B853F@@YAXXZ @ 0x007B853F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B853F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8549@@YAXXZ @ 0x007B8549 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8549()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8553@@YAXXZ @ 0x007B8553 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8553()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B855D@@YAXXZ @ 0x007B855D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B855D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8567@@YAXXZ @ 0x007B8567 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8567()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8571@@YAXXZ @ 0x007B8571 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8571()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B857B@@YAXXZ @ 0x007B857B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B857B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8586@@YAXXZ @ 0x007B8586 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8586()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B859A@@YAXXZ @ 0x007B859A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B859A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85A4@@YAXXZ @ 0x007B85A4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85A4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85AE@@YAXXZ @ 0x007B85AE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85AE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85C2@@YAXXZ @ 0x007B85C2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85C2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85CC@@YAXXZ @ 0x007B85CC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85CC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85D6@@YAXXZ @ 0x007B85D6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85D6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85E3@@YAXXZ @ 0x007B85E3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85E3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85ED@@YAXXZ @ 0x007B85ED (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85ED()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B85F7@@YAXXZ @ 0x007B85F7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B85F7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8601@@YAXXZ @ 0x007B8601 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8601()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B860B@@YAXXZ @ 0x007B860B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B860B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8615@@YAXXZ @ 0x007B8615 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8615()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B861F@@YAXXZ @ 0x007B861F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B861F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8629@@YAXXZ @ 0x007B8629 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8629()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8633@@YAXXZ @ 0x007B8633 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8633()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B863D@@YAXXZ @ 0x007B863D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B863D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8647@@YAXXZ @ 0x007B8647 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8647()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8651@@YAXXZ @ 0x007B8651 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8651()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B865B@@YAXXZ @ 0x007B865B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B865B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8665@@YAXXZ @ 0x007B8665 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8665()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B866F@@YAXXZ @ 0x007B866F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B866F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8679@@YAXXZ @ 0x007B8679 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8679()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8683@@YAXXZ @ 0x007B8683 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8683()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B868D@@YAXXZ @ 0x007B868D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B868D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86A1@@YAXXZ @ 0x007B86A1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86A1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86AB@@YAXXZ @ 0x007B86AB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86AB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86B5@@YAXXZ @ 0x007B86B5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86B5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86BF@@YAXXZ @ 0x007B86BF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86BF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86C9@@YAXXZ @ 0x007B86C9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86C9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86D3@@YAXXZ @ 0x007B86D3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86D3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86DD@@YAXXZ @ 0x007B86DD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86DD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86E7@@YAXXZ @ 0x007B86E7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86E7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86F1@@YAXXZ @ 0x007B86F1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86F1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B86FB@@YAXXZ @ 0x007B86FB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B86FB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8705@@YAXXZ @ 0x007B8705 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8705()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B870F@@YAXXZ @ 0x007B870F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B870F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8719@@YAXXZ @ 0x007B8719 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8719()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8723@@YAXXZ @ 0x007B8723 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8723()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B872D@@YAXXZ @ 0x007B872D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B872D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8737@@YAXXZ @ 0x007B8737 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8737()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8741@@YAXXZ @ 0x007B8741 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8741()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B874B@@YAXXZ @ 0x007B874B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B874B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8755@@YAXXZ @ 0x007B8755 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8755()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B875F@@YAXXZ @ 0x007B875F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B875F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8773@@YAXXZ @ 0x007B8773 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8773()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B877D@@YAXXZ @ 0x007B877D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B877D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8787@@YAXXZ @ 0x007B8787 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8787()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8791@@YAXXZ @ 0x007B8791 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8791()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B879B@@YAXXZ @ 0x007B879B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B879B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87A5@@YAXXZ @ 0x007B87A5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87A5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87AF@@YAXXZ @ 0x007B87AF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87AF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87B9@@YAXXZ @ 0x007B87B9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87B9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87C3@@YAXXZ @ 0x007B87C3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87C3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87CD@@YAXXZ @ 0x007B87CD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87CD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87D7@@YAXXZ @ 0x007B87D7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87D7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87E1@@YAXXZ @ 0x007B87E1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87E1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87EB@@YAXXZ @ 0x007B87EB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87EB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87F5@@YAXXZ @ 0x007B87F5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87F5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B87FF@@YAXXZ @ 0x007B87FF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B87FF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8809@@YAXXZ @ 0x007B8809 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8809()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8813@@YAXXZ @ 0x007B8813 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8813()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8827@@YAXXZ @ 0x007B8827 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8827()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8831@@YAXXZ @ 0x007B8831 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8831()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B883B@@YAXXZ @ 0x007B883B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B883B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8845@@YAXXZ @ 0x007B8845 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8845()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B884F@@YAXXZ @ 0x007B884F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B884F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8859@@YAXXZ @ 0x007B8859 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8859()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8863@@YAXXZ @ 0x007B8863 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8863()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B886D@@YAXXZ @ 0x007B886D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B886D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8877@@YAXXZ @ 0x007B8877 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8877()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8881@@YAXXZ @ 0x007B8881 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8881()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B888B@@YAXXZ @ 0x007B888B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B888B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8895@@YAXXZ @ 0x007B8895 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8895()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B889F@@YAXXZ @ 0x007B889F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B889F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88A9@@YAXXZ @ 0x007B88A9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88A9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88B3@@YAXXZ @ 0x007B88B3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88B3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88BD@@YAXXZ @ 0x007B88BD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88BD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88C7@@YAXXZ @ 0x007B88C7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88C7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88DB@@YAXXZ @ 0x007B88DB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88DB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88E5@@YAXXZ @ 0x007B88E5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88E5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88EF@@YAXXZ @ 0x007B88EF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88EF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B88F9@@YAXXZ @ 0x007B88F9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B88F9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8903@@YAXXZ @ 0x007B8903 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8903()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B890D@@YAXXZ @ 0x007B890D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B890D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8917@@YAXXZ @ 0x007B8917 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8917()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8921@@YAXXZ @ 0x007B8921 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8921()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B892B@@YAXXZ @ 0x007B892B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B892B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8935@@YAXXZ @ 0x007B8935 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8935()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B893F@@YAXXZ @ 0x007B893F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B893F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8949@@YAXXZ @ 0x007B8949 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8949()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8953@@YAXXZ @ 0x007B8953 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8953()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B895D@@YAXXZ @ 0x007B895D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B895D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8967@@YAXXZ @ 0x007B8967 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8967()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8971@@YAXXZ @ 0x007B8971 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8971()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B897B@@YAXXZ @ 0x007B897B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B897B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8985@@YAXXZ @ 0x007B8985 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8985()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B898F@@YAXXZ @ 0x007B898F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B898F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8999@@YAXXZ @ 0x007B8999 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8999()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89A3@@YAXXZ @ 0x007B89A3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89A3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89AD@@YAXXZ @ 0x007B89AD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89AD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89B7@@YAXXZ @ 0x007B89B7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89B7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89CB@@YAXXZ @ 0x007B89CB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89CB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89D5@@YAXXZ @ 0x007B89D5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89D5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89DF@@YAXXZ @ 0x007B89DF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89DF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89E9@@YAXXZ @ 0x007B89E9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89E9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89F3@@YAXXZ @ 0x007B89F3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89F3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B89FD@@YAXXZ @ 0x007B89FD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B89FD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A07@@YAXXZ @ 0x007B8A07 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A07()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A11@@YAXXZ @ 0x007B8A11 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A11()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A1B@@YAXXZ @ 0x007B8A1B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A1B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A25@@YAXXZ @ 0x007B8A25 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A25()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A2F@@YAXXZ @ 0x007B8A2F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A2F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A39@@YAXXZ @ 0x007B8A39 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A39()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A43@@YAXXZ @ 0x007B8A43 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A43()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A4D@@YAXXZ @ 0x007B8A4D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A4D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A57@@YAXXZ @ 0x007B8A57 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A57()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A61@@YAXXZ @ 0x007B8A61 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A61()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A6B@@YAXXZ @ 0x007B8A6B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A6B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A75@@YAXXZ @ 0x007B8A75 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A75()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A7F@@YAXXZ @ 0x007B8A7F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A7F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A89@@YAXXZ @ 0x007B8A89 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A89()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A93@@YAXXZ @ 0x007B8A93 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A93()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8A9D@@YAXXZ @ 0x007B8A9D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8A9D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AA7@@YAXXZ @ 0x007B8AA7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AA7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AB1@@YAXXZ @ 0x007B8AB1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AB1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8ABB@@YAXXZ @ 0x007B8ABB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8ABB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AC5@@YAXXZ @ 0x007B8AC5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AC5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8ACF@@YAXXZ @ 0x007B8ACF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8ACF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AD9@@YAXXZ @ 0x007B8AD9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AD9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AE3@@YAXXZ @ 0x007B8AE3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AE3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AED@@YAXXZ @ 0x007B8AED (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AED()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8AF7@@YAXXZ @ 0x007B8AF7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8AF7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B01@@YAXXZ @ 0x007B8B01 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B01()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B0B@@YAXXZ @ 0x007B8B0B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B0B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B15@@YAXXZ @ 0x007B8B15 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B15()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B1F@@YAXXZ @ 0x007B8B1F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B1F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B29@@YAXXZ @ 0x007B8B29 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B29()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B33@@YAXXZ @ 0x007B8B33 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B33()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B3D@@YAXXZ @ 0x007B8B3D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B3D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B47@@YAXXZ @ 0x007B8B47 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B47()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B51@@YAXXZ @ 0x007B8B51 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B51()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B5B@@YAXXZ @ 0x007B8B5B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B5B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B65@@YAXXZ @ 0x007B8B65 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B65()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B6F@@YAXXZ @ 0x007B8B6F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B6F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B79@@YAXXZ @ 0x007B8B79 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B79()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B83@@YAXXZ @ 0x007B8B83 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B83()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B8D@@YAXXZ @ 0x007B8B8D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B8D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8B97@@YAXXZ @ 0x007B8B97 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8B97()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BA1@@YAXXZ @ 0x007B8BA1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BA1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BAB@@YAXXZ @ 0x007B8BAB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BAB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BB5@@YAXXZ @ 0x007B8BB5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BB5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BBF@@YAXXZ @ 0x007B8BBF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BBF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BC9@@YAXXZ @ 0x007B8BC9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BC9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BD3@@YAXXZ @ 0x007B8BD3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BD3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BDD@@YAXXZ @ 0x007B8BDD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BDD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BE7@@YAXXZ @ 0x007B8BE7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BE7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BF1@@YAXXZ @ 0x007B8BF1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BF1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8BFB@@YAXXZ @ 0x007B8BFB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8BFB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C05@@YAXXZ @ 0x007B8C05 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C05()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C0F@@YAXXZ @ 0x007B8C0F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C0F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C19@@YAXXZ @ 0x007B8C19 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C19()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C23@@YAXXZ @ 0x007B8C23 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C23()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C2D@@YAXXZ @ 0x007B8C2D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C2D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C37@@YAXXZ @ 0x007B8C37 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C37()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C41@@YAXXZ @ 0x007B8C41 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C41()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C4B@@YAXXZ @ 0x007B8C4B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C4B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C55@@YAXXZ @ 0x007B8C55 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C55()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C5F@@YAXXZ @ 0x007B8C5F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C5F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C69@@YAXXZ @ 0x007B8C69 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C69()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C73@@YAXXZ @ 0x007B8C73 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C73()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C87@@YAXXZ @ 0x007B8C87 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C87()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C91@@YAXXZ @ 0x007B8C91 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C91()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8C9B@@YAXXZ @ 0x007B8C9B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8C9B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CA5@@YAXXZ @ 0x007B8CA5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CA5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CAF@@YAXXZ @ 0x007B8CAF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CAF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CB9@@YAXXZ @ 0x007B8CB9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CB9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CC3@@YAXXZ @ 0x007B8CC3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CC3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CCD@@YAXXZ @ 0x007B8CCD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CCD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CD7@@YAXXZ @ 0x007B8CD7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CD7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CE1@@YAXXZ @ 0x007B8CE1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CE1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CEB@@YAXXZ @ 0x007B8CEB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CEB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CF5@@YAXXZ @ 0x007B8CF5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CF5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8CFF@@YAXXZ @ 0x007B8CFF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8CFF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D09@@YAXXZ @ 0x007B8D09 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D09()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D13@@YAXXZ @ 0x007B8D13 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D13()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D1D@@YAXXZ @ 0x007B8D1D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D1D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D27@@YAXXZ @ 0x007B8D27 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D27()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D31@@YAXXZ @ 0x007B8D31 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D31()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D3B@@YAXXZ @ 0x007B8D3B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D3B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D45@@YAXXZ @ 0x007B8D45 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D45()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D4F@@YAXXZ @ 0x007B8D4F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D4F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D59@@YAXXZ @ 0x007B8D59 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D59()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D63@@YAXXZ @ 0x007B8D63 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D63()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D6D@@YAXXZ @ 0x007B8D6D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D6D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D77@@YAXXZ @ 0x007B8D77 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D77()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D81@@YAXXZ @ 0x007B8D81 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D81()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D8B@@YAXXZ @ 0x007B8D8B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D8B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D95@@YAXXZ @ 0x007B8D95 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D95()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8D9F@@YAXXZ @ 0x007B8D9F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8D9F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DA9@@YAXXZ @ 0x007B8DA9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DA9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DB3@@YAXXZ @ 0x007B8DB3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DB3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DBD@@YAXXZ @ 0x007B8DBD (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DBD()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DC7@@YAXXZ @ 0x007B8DC7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DC7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DD1@@YAXXZ @ 0x007B8DD1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DD1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DDB@@YAXXZ @ 0x007B8DDB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DDB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DE5@@YAXXZ @ 0x007B8DE5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DE5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DEF@@YAXXZ @ 0x007B8DEF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DEF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8DF9@@YAXXZ @ 0x007B8DF9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8DF9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E03@@YAXXZ @ 0x007B8E03 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E03()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E0D@@YAXXZ @ 0x007B8E0D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E0D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E17@@YAXXZ @ 0x007B8E17 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E17()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E21@@YAXXZ @ 0x007B8E21 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E21()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E2B@@YAXXZ @ 0x007B8E2B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E2B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E35@@YAXXZ @ 0x007B8E35 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E35()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E3F@@YAXXZ @ 0x007B8E3F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E3F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E49@@YAXXZ @ 0x007B8E49 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E49()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E53@@YAXXZ @ 0x007B8E53 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E53()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E5D@@YAXXZ @ 0x007B8E5D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E5D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E67@@YAXXZ @ 0x007B8E67 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E67()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E71@@YAXXZ @ 0x007B8E71 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E71()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E7B@@YAXXZ @ 0x007B8E7B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E7B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E85@@YAXXZ @ 0x007B8E85 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E85()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E8F@@YAXXZ @ 0x007B8E8F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E8F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8E9A@@YAXXZ @ 0x007B8E9A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8E9A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EAE@@YAXXZ @ 0x007B8EAE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EAE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EB8@@YAXXZ @ 0x007B8EB8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EB8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EC2@@YAXXZ @ 0x007B8EC2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EC2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8ECC@@YAXXZ @ 0x007B8ECC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8ECC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EE0@@YAXXZ @ 0x007B8EE0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EE0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EEA@@YAXXZ @ 0x007B8EEA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EEA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EF4@@YAXXZ @ 0x007B8EF4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EF4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8EFE@@YAXXZ @ 0x007B8EFE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8EFE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F30@@YAXXZ @ 0x007B8F30 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F30()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F3A@@YAXXZ @ 0x007B8F3A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F3A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F45@@YAXXZ @ 0x007B8F45 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F45()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F4F@@YAXXZ @ 0x007B8F4F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F4F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F59@@YAXXZ @ 0x007B8F59 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F59()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F63@@YAXXZ @ 0x007B8F63 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F63()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F77@@YAXXZ @ 0x007B8F77 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F77()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F81@@YAXXZ @ 0x007B8F81 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F81()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F8B@@YAXXZ @ 0x007B8F8B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F8B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8F95@@YAXXZ @ 0x007B8F95 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8F95()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FB3@@YAXXZ @ 0x007B8FB3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FB3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FC7@@YAXXZ @ 0x007B8FC7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FC7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FD1@@YAXXZ @ 0x007B8FD1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FD1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FDB@@YAXXZ @ 0x007B8FDB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FDB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FE5@@YAXXZ @ 0x007B8FE5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FE5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FEF@@YAXXZ @ 0x007B8FEF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FEF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B8FF9@@YAXXZ @ 0x007B8FF9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B8FF9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B900D@@YAXXZ @ 0x007B900D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B900D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9017@@YAXXZ @ 0x007B9017 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9017()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9021@@YAXXZ @ 0x007B9021 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9021()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B902B@@YAXXZ @ 0x007B902B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B902B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9053@@YAXXZ @ 0x007B9053 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9053()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B905D@@YAXXZ @ 0x007B905D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B905D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9067@@YAXXZ @ 0x007B9067 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9067()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B907B@@YAXXZ @ 0x007B907B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B907B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9085@@YAXXZ @ 0x007B9085 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9085()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B908F@@YAXXZ @ 0x007B908F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B908F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B909A@@YAXXZ @ 0x007B909A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B909A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90A4@@YAXXZ @ 0x007B90A4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90A4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90AE@@YAXXZ @ 0x007B90AE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90AE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90B8@@YAXXZ @ 0x007B90B8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90B8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90C2@@YAXXZ @ 0x007B90C2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90C2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90CC@@YAXXZ @ 0x007B90CC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90CC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90D6@@YAXXZ @ 0x007B90D6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90D6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90E0@@YAXXZ @ 0x007B90E0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90E0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90EA@@YAXXZ @ 0x007B90EA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90EA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90F4@@YAXXZ @ 0x007B90F4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90F4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B90FE@@YAXXZ @ 0x007B90FE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B90FE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9108@@YAXXZ @ 0x007B9108 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9108()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9112@@YAXXZ @ 0x007B9112 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9112()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B911C@@YAXXZ @ 0x007B911C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B911C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9126@@YAXXZ @ 0x007B9126 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9126()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9130@@YAXXZ @ 0x007B9130 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9130()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B913A@@YAXXZ @ 0x007B913A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B913A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9144@@YAXXZ @ 0x007B9144 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9144()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B914E@@YAXXZ @ 0x007B914E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B914E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9158@@YAXXZ @ 0x007B9158 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9158()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9176@@YAXXZ @ 0x007B9176 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9176()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9180@@YAXXZ @ 0x007B9180 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9180()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B918A@@YAXXZ @ 0x007B918A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B918A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9194@@YAXXZ @ 0x007B9194 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9194()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B91B2@@YAXXZ @ 0x007B91B2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B91B2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B91BC@@YAXXZ @ 0x007B91BC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B91BC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B91C6@@YAXXZ @ 0x007B91C6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B91C6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B91D0@@YAXXZ @ 0x007B91D0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B91D0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B91DA@@YAXXZ @ 0x007B91DA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B91DA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B91EE@@YAXXZ @ 0x007B91EE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B91EE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B922A@@YAXXZ @ 0x007B922A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B922A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9234@@YAXXZ @ 0x007B9234 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9234()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B923E@@YAXXZ @ 0x007B923E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B923E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9284@@YAXXZ @ 0x007B9284 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9284()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B928E@@YAXXZ @ 0x007B928E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B928E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92AC@@YAXXZ @ 0x007B92AC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92AC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92CA@@YAXXZ @ 0x007B92CA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92CA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92D4@@YAXXZ @ 0x007B92D4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92D4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92DE@@YAXXZ @ 0x007B92DE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92DE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92E8@@YAXXZ @ 0x007B92E8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92E8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92F2@@YAXXZ @ 0x007B92F2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92F2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B92FC@@YAXXZ @ 0x007B92FC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B92FC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9306@@YAXXZ @ 0x007B9306 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9306()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9310@@YAXXZ @ 0x007B9310 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9310()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B931A@@YAXXZ @ 0x007B931A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B931A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9324@@YAXXZ @ 0x007B9324 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9324()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B932E@@YAXXZ @ 0x007B932E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B932E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9338@@YAXXZ @ 0x007B9338 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9338()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9342@@YAXXZ @ 0x007B9342 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9342()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B934C@@YAXXZ @ 0x007B934C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B934C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9356@@YAXXZ @ 0x007B9356 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9356()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9360@@YAXXZ @ 0x007B9360 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9360()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B936A@@YAXXZ @ 0x007B936A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B936A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9374@@YAXXZ @ 0x007B9374 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9374()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B937E@@YAXXZ @ 0x007B937E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B937E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9392@@YAXXZ @ 0x007B9392 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9392()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B939C@@YAXXZ @ 0x007B939C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B939C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B93A6@@YAXXZ @ 0x007B93A6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B93A6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B93B0@@YAXXZ @ 0x007B93B0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B93B0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B93BA@@YAXXZ @ 0x007B93BA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B93BA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B93C4@@YAXXZ @ 0x007B93C4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B93C4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B93CE@@YAXXZ @ 0x007B93CE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B93CE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B93D8@@YAXXZ @ 0x007B93D8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B93D8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B943C@@YAXXZ @ 0x007B943C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B943C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9446@@YAXXZ @ 0x007B9446 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9446()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9450@@YAXXZ @ 0x007B9450 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9450()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9464@@YAXXZ @ 0x007B9464 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9464()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B946E@@YAXXZ @ 0x007B946E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B946E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9478@@YAXXZ @ 0x007B9478 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9478()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9482@@YAXXZ @ 0x007B9482 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9482()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B948C@@YAXXZ @ 0x007B948C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B948C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9496@@YAXXZ @ 0x007B9496 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9496()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B94A0@@YAXXZ @ 0x007B94A0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B94A0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B94BE@@YAXXZ @ 0x007B94BE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B94BE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B94DC@@YAXXZ @ 0x007B94DC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B94DC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B94E6@@YAXXZ @ 0x007B94E6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B94E6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B94F0@@YAXXZ @ 0x007B94F0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B94F0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B94FA@@YAXXZ @ 0x007B94FA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B94FA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9504@@YAXXZ @ 0x007B9504 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9504()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B950E@@YAXXZ @ 0x007B950E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B950E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9518@@YAXXZ @ 0x007B9518 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9518()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9522@@YAXXZ @ 0x007B9522 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9522()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B952C@@YAXXZ @ 0x007B952C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B952C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9536@@YAXXZ @ 0x007B9536 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9536()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9540@@YAXXZ @ 0x007B9540 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9540()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B954A@@YAXXZ @ 0x007B954A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B954A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9554@@YAXXZ @ 0x007B9554 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9554()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B955E@@YAXXZ @ 0x007B955E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B955E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9568@@YAXXZ @ 0x007B9568 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9568()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9572@@YAXXZ @ 0x007B9572 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9572()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9590@@YAXXZ @ 0x007B9590 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9590()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B959A@@YAXXZ @ 0x007B959A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B959A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95AE@@YAXXZ @ 0x007B95AE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95AE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95B8@@YAXXZ @ 0x007B95B8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95B8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95C2@@YAXXZ @ 0x007B95C2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95C2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95CC@@YAXXZ @ 0x007B95CC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95CC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95D6@@YAXXZ @ 0x007B95D6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95D6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95E0@@YAXXZ @ 0x007B95E0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95E0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95F4@@YAXXZ @ 0x007B95F4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95F4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B95FE@@YAXXZ @ 0x007B95FE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B95FE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9608@@YAXXZ @ 0x007B9608 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9608()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9612@@YAXXZ @ 0x007B9612 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9612()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9626@@YAXXZ @ 0x007B9626 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9626()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B963A@@YAXXZ @ 0x007B963A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B963A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B964E@@YAXXZ @ 0x007B964E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B964E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9658@@YAXXZ @ 0x007B9658 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9658()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9676@@YAXXZ @ 0x007B9676 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9676()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

extern unsigned g_00E06444;
// g_00E06444: packet annotates VA 0x00E06444 (data RVA 0x00A06444), no name yet.

// ?rva007B9680@@YAXXZ @ 0x007B9680 (10B). Global StringBase<char> clear thunk: ecx=&g_00E06444 then tail-jmp to rowed ?clear@?$StringBase@D@@QAEXXZ (0x0048BA39). No callers. Between 0x007B9676 and 0x007B9694. Honest address name.
void __cdecl rva007B9680()
{
	StringBase<char> *p = (StringBase<char> *)&g_00E06444;
	return p->clear();
}

extern unsigned g_00E06448;
// g_00E06448: packet annotates VA 0x00E06448 (data RVA 0x00A06448), no name yet.

// ?rva007B968A@@YAXXZ @ 0x007B968A (10B). Global StringBase<char> clear thunk: ecx=&g_00E06448 then tail-jmp to rowed ?clear@?$StringBase@D@@QAEXXZ (0x0048BA39). No callers. Between 0x007B9680 and 0x007B9694. Honest address name.
void __cdecl rva007B968A()
{
	StringBase<char> *p = (StringBase<char> *)&g_00E06448;
	return p->clear();
}

// ?rva007B9694@@YAXXZ @ 0x007B9694 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9694()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B96A8@@YAXXZ @ 0x007B96A8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B96A8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B96B2@@YAXXZ @ 0x007B96B2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B96B2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

class QueuedDownload;
namespace _STL { template <class T, class A = allocator<T> > class list { public: ~list(); }; }
extern unsigned g_Va00E0657C;
unsigned int g_Va00E0657C;

// ?rva007B96BC@@YAXXZ @ 0x007B96BC (10B). Global list dtor thunk: ecx=&g_Va00E0657C then tail-jmp to rowed ??1?$list@VQueuedDownload@@V?$allocator@VQueuedDownload@@@_STL@@@_STL@@QAE@XZ (0x005BD5EE). No callers. Between 0x007B96B2 and 0x007B96C6. Honest address name.
void __cdecl rva007B96BC()
{
	_STL::list<QueuedDownload> *p = (_STL::list<QueuedDownload> *)&g_Va00E0657C;
	return p->~list();
}

// ?rva007B96C6@@YAXXZ @ 0x007B96C6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B96C6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B96D0@@YAXXZ @ 0x007B96D0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B96D0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B96DA@@YAXXZ @ 0x007B96DA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B96DA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B96E4@@YAXXZ @ 0x007B96E4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B96E4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9716@@YAXXZ @ 0x007B9716 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9716()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B973E@@YAXXZ @ 0x007B973E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B973E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

class Rva005E9F7B
{
public:
	virtual ~Rva005E9F7B();
};

extern unsigned g_00E06634;
// g_00E06634: packet annotates VA 0x00E06634 (data), no name yet.

// ?rva007B9748@@YAXXZ @ 0x007B9748 (10B). Global Rva005E9F7B dtor thunk: ecx=&g_00E06634 then tail-jmp to pinned ??1Rva005E9F7B@@UAE@XZ (0x005E9F7B). No callers. Between 0x007B973E and 0x007B9752. Honest address name.
void __cdecl rva007B9748()
{
	Rva005E9F7B *p = (Rva005E9F7B *)&g_00E06634;
	return p->Rva005E9F7B::~Rva005E9F7B();
}

// ?rva007B9752@@YAXXZ @ 0x007B9752 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9752()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B975C@@YAXXZ @ 0x007B975C (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B975C()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9766@@YAXXZ @ 0x007B9766 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9766()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9770@@YAXXZ @ 0x007B9770 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9770()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B977A@@YAXXZ @ 0x007B977A (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B977A()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9784@@YAXXZ @ 0x007B9784 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9784()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B978E@@YAXXZ @ 0x007B978E (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B978E()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9798@@YAXXZ @ 0x007B9798 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9798()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97A2@@YAXXZ @ 0x007B97A2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97A2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97AC@@YAXXZ @ 0x007B97AC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97AC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97B6@@YAXXZ @ 0x007B97B6 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97B6()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97C0@@YAXXZ @ 0x007B97C0 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97C0()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97CA@@YAXXZ @ 0x007B97CA (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97CA()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97D4@@YAXXZ @ 0x007B97D4 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97D4()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97DE@@YAXXZ @ 0x007B97DE (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97DE()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97E8@@YAXXZ @ 0x007B97E8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97E8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97F2@@YAXXZ @ 0x007B97F2 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97F2()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B97FC@@YAXXZ @ 0x007B97FC (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B97FC()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B981B@@YAXXZ @ 0x007B981B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B981B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9839@@YAXXZ @ 0x007B9839 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9839()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B984D@@YAXXZ @ 0x007B984D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B984D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9857@@YAXXZ @ 0x007B9857 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9857()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9861@@YAXXZ @ 0x007B9861 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9861()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B986B@@YAXXZ @ 0x007B986B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B986B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9875@@YAXXZ @ 0x007B9875 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9875()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B987F@@YAXXZ @ 0x007B987F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B987F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9889@@YAXXZ @ 0x007B9889 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9889()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9893@@YAXXZ @ 0x007B9893 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9893()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B989D@@YAXXZ @ 0x007B989D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B989D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98A7@@YAXXZ @ 0x007B98A7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98A7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98B1@@YAXXZ @ 0x007B98B1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98B1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98BB@@YAXXZ @ 0x007B98BB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98BB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98C5@@YAXXZ @ 0x007B98C5 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98C5()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98CF@@YAXXZ @ 0x007B98CF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98CF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98D9@@YAXXZ @ 0x007B98D9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98D9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98E3@@YAXXZ @ 0x007B98E3 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98E3()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98ED@@YAXXZ @ 0x007B98ED (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98ED()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B98F7@@YAXXZ @ 0x007B98F7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B98F7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9901@@YAXXZ @ 0x007B9901 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9901()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B990B@@YAXXZ @ 0x007B990B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B990B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9915@@YAXXZ @ 0x007B9915 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9915()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B991F@@YAXXZ @ 0x007B991F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B991F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9929@@YAXXZ @ 0x007B9929 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9929()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9933@@YAXXZ @ 0x007B9933 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9933()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9951@@YAXXZ @ 0x007B9951 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9951()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B995B@@YAXXZ @ 0x007B995B (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B995B()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B996F@@YAXXZ @ 0x007B996F (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B996F()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B99A1@@YAXXZ @ 0x007B99A1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B99A1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B99AB@@YAXXZ @ 0x007B99AB (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B99AB()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B99BF@@YAXXZ @ 0x007B99BF (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B99BF()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B99C9@@YAXXZ @ 0x007B99C9 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B99C9()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B99E7@@YAXXZ @ 0x007B99E7 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B99E7()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B99F1@@YAXXZ @ 0x007B99F1 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B99F1()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9A19@@YAXXZ @ 0x007B9A19 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9A19()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9A2D@@YAXXZ @ 0x007B9A2D (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9A2D()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B9CA8@@YAXXZ @ 0x007B9CA8 (10B). Global Rva001EAF7B thunk: ecx=&g_Va00DA60E8 then tail-jmp to rowed ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ (0x001EAF7B).
void __cdecl rva007B9CA8()
{
	Rva001EAF7B *p = (Rva001EAF7B *)&g_Va00DA60E8;
	p->rva001EAF7B();
}

// ?rva007B686F@@YAXXZ @ 0x007B686F (10B). Global CAtlWinModule thunk: ecx=&g_00DDE0AC then tail-jmp to rowed ?Term@CAtlWinModule@ATL@@QAEXXZ (0x00006AF1).
namespace ATL
{
class CAtlWinModule
{
public:
	void Term();
};
}

extern unsigned g_00DDE0AC;
unsigned int g_00DDE0AC;

void __cdecl rva007B686F()
{
	ATL::CAtlWinModule *p = (ATL::CAtlWinModule *)&g_00DDE0AC;
	return p->Term();
}

// ?rva007B685A@@YAXXZ @ 0x007B685A (10B). Global locale uninitialize thunk: ecx=&g_00DDE071 then tail-jmp to pinned ?rva00007670@Rva00007670@@QAEXXZ (0x00007670 twin of rowed ?_S_uninitialize@locale@_STL@@SAXXZ). Evidence: callees 0x00007670; same 10B mov ecx jmp shape as neighbours 0x007B6850 0x007B686F. Honest address names.
class Rva00007670
{
public:
	void rva00007670();
};

extern unsigned g_00DDE071;
unsigned int g_00DDE071;

void __cdecl rva007B685A()
{
	Rva00007670 *p = (Rva00007670 *)&g_00DDE071;
	return p->rva00007670();
}

// ?rva007B6864@@YAXXZ @ 0x007B6864 (10B). Global ios_base Init dtor thunk: ecx=&g_00DDE070 then tail-jmp to rowed ??1Init@ios_base@_STL@@QAE@XZ (0x00015E70). Evidence: callees 0x00015E70; same 10B mov ecx jmp shape as neighbours 0x007B685A 0x007B686F. Honest address names.
namespace _STL
{
class ios_base
{
public:
	class Init
	{
	public:
		~Init();
	};
};
}

extern unsigned g_00DDE070;
unsigned int g_00DDE070;

void __cdecl rva007B6864()
{
	_STL::ios_base::Init *p = (_STL::ios_base::Init *)&g_00DDE070;
	return p->~Init();
}

extern unsigned g_00E06665;
// g_00E06665: packet annotates VA 0x00E06665 (data RVA 0x00A06665), no name yet.

// ?rva007B9806@@YAXXZ @ 0x007B9806 (10B). Global locale uninitialize thunk: ecx=&g_00E06665 then tail-jmp to pinned ?rva00007670@Rva00007670@@QAEXXZ (0x00007670 twin of rowed ?_S_uninitialize@locale@_STL@@SAXXZ). No callers. Between 0x007B97FC and 0x007B981B. Honest address name.
void __cdecl rva007B9806()
{
	Rva00007670 *p = (Rva00007670 *)&g_00E06665;
	return p->rva00007670();
}

extern unsigned g_00E06664;
// g_00E06664: packet annotates VA 0x00E06664 (data RVA 0x00A06664), no name yet.

// ?rva007B9810@@YAXXZ @ 0x007B9810 (10B). Global ios_base Init dtor thunk: ecx=&g_00E06664 then tail-jmp to rowed ??1Init@ios_base@_STL@@QAE@XZ (0x00015E70). No callers. Between 0x007B9806 and 0x007B981B. Honest address name.
void __cdecl rva007B9810()
{
	_STL::ios_base::Init *p = (_STL::ios_base::Init *)&g_00E06664;
	return p->~Init();
}

// ?rva007B981A@@YAXXZ @ 0x007B981A (1B). Empty stub: ret.
void __cdecl rva007B981A()
{
}

class LightEnvironmentClass
{
public:
	~LightEnvironmentClass();
};

extern unsigned g_Va00A1F2B8;
unsigned int g_Va00A1F2B8;

// ?rva007B9CB2@@YAXXZ @ 0x007B9CB2 (10B). Global dtor thunk: ecx=&g_Va00A1F2B8 then tail-jmp to rowed 0x0069E440.
void __cdecl rva007B9CB2()
{
	LightEnvironmentClass *p = (LightEnvironmentClass *)&g_Va00A1F2B8;
	return p->~LightEnvironmentClass();
}

extern unsigned g_Va00A1F4E8;
unsigned int g_Va00A1F4E8;

// ?rva007B9CC0@@YAXXZ @ 0x007B9CC0 (10B). Global SegLineRendererClass dtor thunk: ecx=&g_Va00A1F4E8 then tail-jmp to rowed ??1SegLineRendererClass@@QAE@XZ (0x001911C0).
#pragma optimize("t", on)
void __cdecl rva007B9CC0()
{
	SegLineRendererClass *p = (SegLineRendererClass *)&g_Va00A1F4E8;
	return p->~SegLineRendererClass();
}
#pragma optimize("", on)

extern unsigned g_Va00DE1CCC;
unsigned int g_Va00DE1CCC;

// ?rva007B6ADC@@YAXXZ @ 0x007B6ADC (10B). Global ios_base::Init dtor thunk: ecx=&g_Va00DE1CCC then tail-jmp to rowed ??1Init@ios_base@_STL@@QAE@XZ (0x00015E70).
void __cdecl rva007B6ADC()
{
	_STL::ios_base::Init *p = (_STL::ios_base::Init *)&g_Va00DE1CCC;
	return p->~Init();
}



class RenderObjClass
{
public:
	virtual void Update_Sub_Object_Transforms();
};

extern unsigned g_Va00DE5E50;
unsigned int g_Va00DE5E50;

// ?rva007B6CAF@@YAXXZ @ 0x007B6CAF (10B). Global RenderObjClass dtor thunk: ecx=&g_Va00DE5E50 then tail-jmp to rowed 0x0069E440.
void __cdecl rva007B6CAF()
{
	RenderObjClass *p = (RenderObjClass *)&g_Va00DE5E50;
	return p->RenderObjClass::Update_Sub_Object_Transforms();
}

extern unsigned g_Va00DF3410;
unsigned int g_Va00DF3410;

// ?rva007B70E0@@YAXXZ @ 0x007B70E0 (10B). Global RenderObjClass dtor thunk: ecx=&g_Va00DF3410 then tail-jmp to rowed 0x0069E440.
void __cdecl rva007B70E0()
{
	RenderObjClass *p = (RenderObjClass *)&g_Va00DF3410;
	return p->RenderObjClass::Update_Sub_Object_Transforms();
}


extern unsigned g_00E01E41;
// g_00E01E41: packet annotates VA 0x00E01E41 (data), no name yet.

// ?rva007B7C72@@YAXXZ @ 0x007B7C72 (10B). Global locale uninitialize thunk: ecx=&g_00E01E41 then tail-jmp to pinned ?rva00007670@Rva00007670@@QAEXXZ (0x00007670 twin of rowed ?_S_uninitialize@locale@_STL@@SAXXZ). No callers. Between 0x007B7C68 and 0x007B7C7C. Honest address name.
void __cdecl rva007B7C72()
{
	Rva00007670 *p = (Rva00007670 *)&g_00E01E41;
	return p->rva00007670();
}

extern unsigned g_Va00E01E40;
unsigned int g_Va00E01E40;

// ?rva007B7C7C@@YAXXZ @ 0x007B7C7C (10B). Global ios_base::Init dtor thunk: ecx=&g_Va00E01E40 then tail-jmp to rowed ??1Init@ios_base@_STL@@QAE@XZ (0x00015E70).
void __cdecl rva007B7C7C()
{
	_STL::ios_base::Init *p = (_STL::ios_base::Init *)&g_Va00E01E40;
	return p->~Init();
}


struct BfmeContainerRecord00048139;
extern unsigned g_Va00DE1CAC;
unsigned int g_Va00DE1CAC;

// ?rva007B6AC8@@YAXXZ @ 0x007B6AC8 (10B). Global vector<BfmeContainerRecord00048139> dtor thunk: ecx=&g_Va00DE1CAC then tail-jmp to rowed ??1?$vector@UBfmeContainerRecord00048139@@V?$allocator@UBfmeContainerRecord00048139@@@_STL@@@_STL@@QAE@XZ (0x0004B193).
void __cdecl rva007B6AC8()
{
	_STL::vector<BfmeContainerRecord00048139, _STL::allocator<BfmeContainerRecord00048139> > *p = (_STL::vector<BfmeContainerRecord00048139, _STL::allocator<BfmeContainerRecord00048139> > *)&g_Va00DE1CAC;
	return p->_STL::vector<BfmeContainerRecord00048139, _STL::allocator<BfmeContainerRecord00048139> >::~vector();
}

extern unsigned g_00DE1CCD;
unsigned int g_00DE1CCD;

// ?rva007B6AD2@@YAXXZ @ 0x007B6AD2 (10B). Global locale uninitialize thunk: ecx=&g_00DE1CCD then tail-jmp to pinned ?rva00007670@Rva00007670@@QAEXXZ (0x00007670 twin of rowed ?_S_uninitialize@locale@_STL@@SAXXZ). Between 0x007B6AC8 and 0x007B6ADC. Honest address name.
void __cdecl rva007B6AD2()
{
	Rva00007670 *p = (Rva00007670 *)&g_00DE1CCD;
	return p->rva00007670();
}

extern unsigned g_Va00E09DBC;
unsigned int g_Va00E09DBC;

// ?rva007B9AD0@@YAXXZ @ 0x007B9AD0 (10B). Global string dtor thunk: ecx=&g_Va00E09DBC then tail-jmp to rowed ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ (0x00142D70).
void __cdecl rva007B9AD0()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E09DBC;
	return p->~basic_string();
}

struct Rva001D28F0Element;
extern unsigned g_Va00E0ABB4;
unsigned int g_Va00E0ABB4;

// ?rva007B9BC0@@YAXXZ @ 0x007B9BC0 (10B). Global vector<Rva001D28F0Element> dtor thunk: ecx=&g_Va00E0ABB4 then tail-jmp to rowed ??1?$vector@URva001D28F0Element@@V?$allocator@URva001D28F0Element@@@_STL@@@_STL@@QAE@XZ (0x00689DB0).
void __cdecl rva007B9BC0()
{
	_STL::vector<Rva001D28F0Element, _STL::allocator<Rva001D28F0Element> > *p = (_STL::vector<Rva001D28F0Element, _STL::allocator<Rva001D28F0Element> > *)&g_Va00E0ABB4;
	return p->_STL::vector<Rva001D28F0Element, _STL::allocator<Rva001D28F0Element> >::~vector();
}

// ?rva007B9BD0@@YAXXZ @ 0x007B9BD0 (1B). Empty stub: ret.
void __cdecl rva007B9BD0()
{
}

extern unsigned g_Va00DDC00C;
unsigned int g_Va00DDC00C;

// ?rva007B9BE0@@YAXXZ @ 0x007B9BE0 (10B). Global StringBase<char> releaseBuffer thunk: ecx=&g_Va00DDC00C then tail-jmp to rowed ?releaseBuffer@?$StringBase@D@@AAEXXZ (0x00036410).
void __cdecl rva007B9BE0()
{
	AsciiString *p = (AsciiString *)&g_Va00DDC00C;
	return p->~AsciiString();
}

extern unsigned g_Va00DF6F98;
unsigned int g_Va00DF6F98;

// ?rva007B7253@@YAXXZ @ 0x007B7253 (10B). Global DynamicVectorClass<Curve3DClass::KeyClass> dtor thunk: ecx=&g_Va00DF6F98 then tail-jmp to rowed ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ (0x000F1D19).
void __cdecl rva007B7253()
{
	DynamicVectorClass<Curve3DClass::KeyClass> *p = (DynamicVectorClass<Curve3DClass::KeyClass> *)&g_Va00DF6F98;
	return p->DynamicVectorClass<Curve3DClass::KeyClass>::~DynamicVectorClass();
}

extern unsigned g_Va00DF6FB0;
unsigned int g_Va00DF6FB0;

// ?rva007B725D@@YAXXZ @ 0x007B725D (10B). Global DynamicVectorClass<Curve3DClass::KeyClass> dtor thunk: ecx=&g_Va00DF6FB0 then tail-jmp to rowed ??1?$DynamicVectorClass@VKeyClass@Curve3DClass@@@@UAE@XZ (0x000F1D19).
void __cdecl rva007B725D()
{
	DynamicVectorClass<Curve3DClass::KeyClass> *p = (DynamicVectorClass<Curve3DClass::KeyClass> *)&g_Va00DF6FB0;
	return p->DynamicVectorClass<Curve3DClass::KeyClass>::~DynamicVectorClass();
}




extern unsigned g_Va00E02FB0;
unsigned int g_Va00E02FB0;

// ?rva007B8201@@YAXXZ @ 0x007B8201 (10B). Global vector<AsciiString> dtor thunk: ecx=&g_Va00E02FB0 then tail-jmp to rowed ??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ (0x0002CC70).
void __cdecl rva007B8201()
{
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > *p = (_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)&g_Va00E02FB0;
	return p->_STL::vector<AsciiString, _STL::allocator<AsciiString> >::~vector();
}

namespace _STL
{
template <class T, class Alloc>
class deque
{
public:
	~deque();
};
}

struct BfmeE12;
extern unsigned g_Va00E031A8;
unsigned int g_Va00E031A8;

// ?rva007B82E7@@YAXXZ @ 0x007B82E7 (10B). Global deque<BfmeE12> dtor thunk: ecx=&g_Va00E031A8 then tail-jmp to rowed ??1?$deque@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAE@XZ (0x005858F3).
void __cdecl rva007B82E7()
{
	_STL::deque<BfmeE12, _STL::allocator<BfmeE12> > *p = (_STL::deque<BfmeE12, _STL::allocator<BfmeE12> > *)&g_Va00E031A8;
	return p->~deque();
}





namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultModuleTag;

template <class TAG>
class ConcreteModuleClass
{
public:
	~ConcreteModuleClass();
};
}

extern unsigned g_Va00E048C4;
unsigned int g_Va00E048C4;

extern unsigned g_Va00E060A4;
unsigned int g_Va00E060A4;

typedef FXParticleSystem::ConcreteModuleClass<FXParticleSystem::DefaultModuleTag<0> > GenericConcreteModuleClass;

// ?rva007B916C@@YAXXZ @ 0x007B916C (10B). Global ConcreteModuleClass dtor thunk: ecx=&g_Va00E048C4 then tail-jmp to rowed ??1?@V?@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ (0x0057C03B).
void __cdecl rva007B916C()
{
	GenericConcreteModuleClass *p = (GenericConcreteModuleClass *)&g_Va00E048C4;
	return p->~ConcreteModuleClass();
}

// ?rva007B93E2@@YAXXZ @ 0x007B93E2 (10B). Global ConcreteModuleClass dtor thunk: ecx=&g_Va00E060A4 then tail-jmp to rowed ??1?@V?@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ (0x0057C03B).
void __cdecl rva007B93E2()
{
	GenericConcreteModuleClass *p = (GenericConcreteModuleClass *)&g_Va00E060A4;
	return p->~ConcreteModuleClass();
}

extern unsigned g_Va00DE1E54;
unsigned int g_Va00DE1E54;

void __cdecl rva007B6B37()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DE1E54;
	return p->~basic_string();
}

extern unsigned g_Va00DF29A8;
unsigned int g_Va00DF29A8;

void __cdecl rva007B70C9()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DF29A8;
	return p->~basic_string();
}

extern unsigned g_Va00DFEC84;
unsigned int g_Va00DFEC84;

void __cdecl rva007B782E()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DFEC84;
	return p->~basic_string();
}

extern unsigned g_Va00DFF134;
unsigned int g_Va00DFF134;

void __cdecl rva007B7A7D()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00DFF134;
	return p->~basic_string();
}

extern unsigned g_Va00E02310;
unsigned int g_Va00E02310;

void __cdecl rva007B7DC7()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E02310;
	return p->~basic_string();
}

extern unsigned g_Va00E02E88;
unsigned int g_Va00E02E88;

void __cdecl rva007B8155()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E02E88;
	return p->~basic_string();
}

extern unsigned g_Va00E04424;
unsigned int g_Va00E04424;

void __cdecl rva007B8F08()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E04424;
	return p->~basic_string();
}

extern unsigned g_Va00E04484;
unsigned int g_Va00E04484;

void __cdecl rva007B8F9F()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E04484;
	return p->~basic_string();
}

extern unsigned g_Va00E04494;
unsigned int g_Va00E04494;

void __cdecl rva007B8FBD()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E04494;
	return p->~basic_string();
}

extern unsigned g_Va00E044F0;
unsigned int g_Va00E044F0;

void __cdecl rva007B903F()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E044F0;
	return p->~basic_string();
}

extern unsigned g_Va00E04920;
unsigned int g_Va00E04920;

void __cdecl rva007B91E4()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E04920;
	return p->~basic_string();
}

// Opaque-class views for the global teardown thunks below. The destructors
// are declared only; symbols.csv pins them to 0x001F4B01, 0x001FBD17 and
// 0x001FBF4D (see OpaqueScalarDeletingDtorsB03.cpp and VectorDeletingDtorsV05.cpp).
class Rva001F4B01
{
public:
	virtual ~Rva001F4B01();
};
class Rva001FBD17
{
public:
	virtual ~Rva001FBD17();
};
class Rva001FBF4D
{
public:
	virtual ~Rva001FBF4D();
};

extern unsigned g_Va00DFDD0C;
unsigned int g_Va00DFDD0C;

// ?rva007B7588@@YAXXZ @ 0x007B7588 (10B). Global Rva001F4B01 dtor thunk: ecx=&g_Va00DFDD0C then tail-jmp to pinned ??1Rva001F4B01@@UAE@XZ (0x001F4B01; scalar deleting dtor 0x001F4B47, vtable 0x00BE171C#0). No callers. Honest address name.
void __cdecl rva007B7588()
{
	Rva001F4B01 *p = (Rva001F4B01 *)&g_Va00DFDD0C;
	return p->Rva001F4B01::~Rva001F4B01();
}

extern unsigned g_Va00DFDD60;
unsigned int g_Va00DFDD60;

// ?rva007B759C@@YAXXZ @ 0x007B759C (10B). Global Rva001FBD17 dtor thunk: ecx=&g_Va00DFDD60 then tail-jmp to pinned ??1Rva001FBD17@@UAE@XZ (0x001FBD17; scalar deleting dtor 0x001FC17F, vtable 0x00BE1A10#0). No callers. Honest address name.
void __cdecl rva007B759C()
{
	Rva001FBD17 *p = (Rva001FBD17 *)&g_Va00DFDD60;
	return p->Rva001FBD17::~Rva001FBD17();
}

extern unsigned g_Va00DFDF40;
unsigned int g_Va00DFDF40;

// ?rva007B75A6@@YAXXZ @ 0x007B75A6 (10B). Global Rva001FBF4D dtor thunk: ecx=&g_Va00DFDF40 then tail-jmp to pinned ??1Rva001FBF4D@@UAE@XZ (0x001FBF4D; vector deleting dtor 0x001FC052, element 0xD4, vtable 0x00BE1A28#0). No callers. Honest address name.
void __cdecl rva007B75A6()
{
	Rva001FBF4D *p = (Rva001FBF4D *)&g_Va00DFDF40;
	return p->Rva001FBF4D::~Rva001FBF4D();
}

// Faction-set tree teardown view for the thunks below. The destructor is
// declared only; symbols.csv pins it to the jmp stub 0x00059068, which jumps
// to the rowed FactionSetTree dtor (0x000589BE, MapMetaDataCopy.cpp).
class Rva00059068Tree
{
public:
	~Rva00059068Tree();
};

extern unsigned g_Va00DE1E78;
unsigned int g_Va00DE1E78;

// ?rva007B6B41@@YAXXZ @ 0x007B6B41 (10B). Faction-set tree teardown: ecx=&g_Va00DE1E78 then tail-jmp to the 0x00059068 stub for the rowed FactionSetTree dtor (0x000589BE). No callers. Honest address name.
void __cdecl rva007B6B41()
{
	Rva00059068Tree *p = (Rva00059068Tree *)&g_Va00DE1E78;
	return p->~Rva00059068Tree();
}

extern unsigned g_Va00DEAF30;
unsigned int g_Va00DEAF30;

// ?rva007B6D1D@@YAXXZ @ 0x007B6D1D (10B). Faction-set tree teardown: ecx=&g_Va00DEAF30 then tail-jmp to the 0x00059068 stub for the rowed FactionSetTree dtor (0x000589BE). No callers. Honest address name.
void __cdecl rva007B6D1D()
{
	Rva00059068Tree *p = (Rva00059068Tree *)&g_Va00DEAF30;
	return p->~Rva00059068Tree();
}

extern unsigned g_Va00DEAF3C;
unsigned int g_Va00DEAF3C;

// ?rva007B6D27@@YAXXZ @ 0x007B6D27 (10B). Faction-set tree teardown: ecx=&g_Va00DEAF3C then tail-jmp to the 0x00059068 stub for the rowed FactionSetTree dtor (0x000589BE). No callers. Honest address name.
void __cdecl rva007B6D27()
{
	Rva00059068Tree *p = (Rva00059068Tree *)&g_Va00DEAF3C;
	return p->~Rva00059068Tree();
}

extern unsigned g_Va00DEBFD8;
unsigned int g_Va00DEBFD8;

// ?rva007B6E72@@YAXXZ @ 0x007B6E72 (10B). Faction-set tree teardown: ecx=&g_Va00DEBFD8 then tail-jmp to the 0x00059068 stub for the rowed FactionSetTree dtor (0x000589BE). No callers. Honest address name.
void __cdecl rva007B6E72()
{
	Rva00059068Tree *p = (Rva00059068Tree *)&g_Va00DEBFD8;
	return p->~Rva00059068Tree();
}

extern unsigned g_Va00DEBFE4;
unsigned int g_Va00DEBFE4;

// ?rva007B6E7C@@YAXXZ @ 0x007B6E7C (10B). Faction-set tree teardown: ecx=&g_Va00DEBFE4 then tail-jmp to the 0x00059068 stub for the rowed FactionSetTree dtor (0x000589BE). No callers. Honest address name.
void __cdecl rva007B6E7C()
{
	Rva00059068Tree *p = (Rva00059068Tree *)&g_Va00DEBFE4;
	return p->~Rva00059068Tree();
}

// Minimal Dict view for the teardown below. releaseData stays private so the
// call mangles as the rowed ?releaseData@Dict@@AAEXXZ (0x0031339C); the thunk
// is friended. Layout follows Rva00329D0EDtor.cpp.
class Dict
{
	struct DictPairData
	{
		unsigned short m_refCount;
		unsigned short m_numPairsAllocated;
		unsigned short m_numPairsUsed;
	};

	void releaseData();
	friend void __cdecl rva007B7B14();

	DictPairData *m_data;
};

extern unsigned g_Va00E00944;
unsigned int g_Va00E00944;

// ?rva007B7B14@@YAXXZ @ 0x007B7B14 (10B). Global Dict teardown: ecx=&g_Va00E00944 then tail-jmp to rowed ?releaseData@Dict@@AAEXXZ (0x0031339C). No callers. Honest address name.
void __cdecl rva007B7B14()
{
	Dict *p = (Dict *)&g_Va00E00944;
	return p->releaseData();
}

// Minimal Rva00200667 view for the two teardowns below. The destructor is
// declared only; symbols.csv pins ??1Rva00200667@@QAE@XZ to 0x00200667
// (see FamilyDeletingDtors11.cpp).
class Rva00200667
{
public:
	~Rva00200667();
};

extern unsigned g_Va00DE6194;
unsigned int g_Va00DE6194;

// ?rva007B6CE1@@YAXXZ @ 0x007B6CE1 (10B). Global Rva00200667 dtor thunk: ecx=&g_Va00DE6194 then tail-jmp to pinned ??1Rva00200667@@QAE@XZ (0x00200667; deleting dtor 0x002821B3). No callers. Honest address name.
void __cdecl rva007B6CE1()
{
	Rva00200667 *p = (Rva00200667 *)&g_Va00DE6194;
	return p->~Rva00200667();
}

extern unsigned g_Va00E0362C;
unsigned int g_Va00E0362C;

// ?rva007B8590@@YAXXZ @ 0x007B8590 (10B). Global Rva00200667 dtor thunk: ecx=&g_Va00E0362C then tail-jmp to pinned ??1Rva00200667@@QAE@XZ (0x00200667; deleting dtor 0x002821B3). No callers. Honest address name.
void __cdecl rva007B8590()
{
	Rva00200667 *p = (Rva00200667 *)&g_Va00E0362C;
	return p->~Rva00200667();
}

extern unsigned g_Va00DFF144;
unsigned int g_Va00DFF144;

// ?rva007B7A87@@YAXXZ @ 0x007B7A87 (10B). Global Rva00200667 dtor thunk: ecx=&g_Va00DFF144 then tail-jmp to pinned ??1Rva00200667@@QAE@XZ (0x00200667; deleting dtor 0x002821B3). No callers. Honest address name.
void __cdecl rva007B7A87()
{
	Rva00200667 *p = (Rva00200667 *)&g_Va00DFF144;
	return p->~Rva00200667();
}

extern unsigned g_Va00DFF148;
unsigned int g_Va00DFF148;

// ?rva007B7A91@@YAXXZ @ 0x007B7A91 (10B). Global Rva00200667 dtor thunk: ecx=&g_Va00DFF148 then tail-jmp to pinned ??1Rva00200667@@QAE@XZ (0x00200667; deleting dtor 0x002821B3). No callers. Honest address name.
void __cdecl rva007B7A91()
{
	Rva00200667 *p = (Rva00200667 *)&g_Va00DFF148;
	return p->~Rva00200667();
}


// Tree-destructor stub teardown views for the thunks below. Each destructor
// is declared only; symbols.csv pins it to its jmp stub, which jumps to a
// tree-dtor-family body (rowed: 0x00410C7B dup, 0x00410CB9 tree dtor).
class Rva004110B4Tree
{
public:
	~Rva004110B4Tree();
};
class Rva004110B9Tree
{
public:
	~Rva004110B9Tree();
};
class Rva004110BETree
{
public:
	~Rva004110BETree();
};
class Rva00411453Tree
{
public:
	~Rva00411453Tree();
};

extern unsigned g_Va00E02FE4;
unsigned int g_Va00E02FE4;

// ?rva007B821F@@YAXXZ @ 0x007B821F (10B). Tree teardown: ecx=&g_Va00E02FE4 then tail-jmp to the 0x004110B4 stub for a tree-dtor-family body (0x00410C42, same prologue as the rowed family). No callers. Honest address name.
void __cdecl rva007B821F()
{
	Rva004110B4Tree *p = (Rva004110B4Tree *)&g_Va00E02FE4;
	return p->~Rva004110B4Tree();
}

extern unsigned g_Va00E02FF8;
unsigned int g_Va00E02FF8;

// ?rva007B8229@@YAXXZ @ 0x007B8229 (10B). Tree teardown: ecx=&g_Va00E02FF8 then tail-jmp to the 0x004110B9 stub for the rowed dup_00410c7b body (0x00410C7B). No callers. Honest address name.
void __cdecl rva007B8229()
{
	Rva004110B9Tree *p = (Rva004110B9Tree *)&g_Va00E02FF8;
	return p->~Rva004110B9Tree();
}

extern unsigned g_Va00E0300C;
unsigned int g_Va00E0300C;

// ?rva007B8233@@YAXXZ @ 0x007B8233 (10B). Tree teardown: ecx=&g_Va00E0300C then tail-jmp to the 0x004110B9 stub for the rowed dup_00410c7b body (0x00410C7B). No callers. Honest address name.
void __cdecl rva007B8233()
{
	Rva004110B9Tree *p = (Rva004110B9Tree *)&g_Va00E0300C;
	return p->~Rva004110B9Tree();
}

extern unsigned g_Va00E03020;
unsigned int g_Va00E03020;

// ?rva007B823D@@YAXXZ @ 0x007B823D (10B). Tree teardown: ecx=&g_Va00E03020 then tail-jmp to the 0x004110BE stub for the rowed tree dtor (0x00410CB9). No callers. Honest address name.
void __cdecl rva007B823D()
{
	Rva004110BETree *p = (Rva004110BETree *)&g_Va00E03020;
	return p->~Rva004110BETree();
}

extern unsigned g_Va00E02FD0;
unsigned int g_Va00E02FD0;

// ?rva007B8247@@YAXXZ @ 0x007B8247 (10B). Tree teardown: ecx=&g_Va00E02FD0 then tail-jmp to the 0x00411453 stub for a tree-dtor-family body (0x004111CC, same prologue as the rowed family). No callers. Honest address name.
void __cdecl rva007B8247()
{
	Rva00411453Tree *p = (Rva00411453Tree *)&g_Va00E02FD0;
	return p->~Rva00411453Tree();
}

// CategoryModuleClass dtor teardown view for the six thunks below. The
// destructor is declared only; symbols.csv pins it to 0x0057C03B, where the
// rowed CategoryModuleClass<$N> dtors (FXParticleSystem.cpp) are folded.
// Which instantiation each global holds is unproven.
class Rva0057C03BModule
{
public:
	~Rva0057C03BModule();
};

extern unsigned g_Va00E06228;
unsigned int g_Va00E06228;

// ?rva007B9400@@YAXXZ @ 0x007B9400 (10B). CategoryModuleClass dtor teardown: ecx=&g_Va00E06228 then tail-jmp to the folded family at 0x0057C03B. No callers. Honest address name.
void __cdecl rva007B9400()
{
	Rva0057C03BModule *p = (Rva0057C03BModule *)&g_Va00E06228;
	return p->~Rva0057C03BModule();
}

extern unsigned g_Va00E06240;
unsigned int g_Va00E06240;

// ?rva007B940A@@YAXXZ @ 0x007B940A (10B). CategoryModuleClass dtor teardown: ecx=&g_Va00E06240 then tail-jmp to the folded family at 0x0057C03B. No callers. Honest address name.
void __cdecl rva007B940A()
{
	Rva0057C03BModule *p = (Rva0057C03BModule *)&g_Va00E06240;
	return p->~Rva0057C03BModule();
}

extern unsigned g_Va00E06258;
unsigned int g_Va00E06258;

// ?rva007B9414@@YAXXZ @ 0x007B9414 (10B). CategoryModuleClass dtor teardown: ecx=&g_Va00E06258 then tail-jmp to the folded family at 0x0057C03B. No callers. Honest address name.
void __cdecl rva007B9414()
{
	Rva0057C03BModule *p = (Rva0057C03BModule *)&g_Va00E06258;
	return p->~Rva0057C03BModule();
}

extern unsigned g_Va00E06270;
unsigned int g_Va00E06270;

// ?rva007B941E@@YAXXZ @ 0x007B941E (10B). CategoryModuleClass dtor teardown: ecx=&g_Va00E06270 then tail-jmp to the folded family at 0x0057C03B. No callers. Honest address name.
void __cdecl rva007B941E()
{
	Rva0057C03BModule *p = (Rva0057C03BModule *)&g_Va00E06270;
	return p->~Rva0057C03BModule();
}

extern unsigned g_Va00E06284;
unsigned int g_Va00E06284;

// ?rva007B9428@@YAXXZ @ 0x007B9428 (10B). CategoryModuleClass dtor teardown: ecx=&g_Va00E06284 then tail-jmp to the folded family at 0x0057C03B. No callers. Honest address name.
void __cdecl rva007B9428()
{
	Rva0057C03BModule *p = (Rva0057C03BModule *)&g_Va00E06284;
	return p->~Rva0057C03BModule();
}

extern unsigned g_Va00E06298;
unsigned int g_Va00E06298;

// ?rva007B9432@@YAXXZ @ 0x007B9432 (10B). CategoryModuleClass dtor teardown: ecx=&g_Va00E06298 then tail-jmp to the folded family at 0x0057C03B. No callers. Honest address name.
void __cdecl rva007B9432()
{
	Rva0057C03BModule *p = (Rva0057C03BModule *)&g_Va00E06298;
	return p->~Rva0057C03BModule();
}

// Minimal Rva005C47A3 view for the four thunks below. The destructor is
// declared only; symbols.csv already pins ??1Rva005C47A3@@UAE@XZ to
// 0x005C47A3 (scalar deleting dtor 0x005C43E7).
class Rva005C47A3
{
public:
	virtual ~Rva005C47A3();
};

extern unsigned g_Va00E04500;
unsigned int g_Va00E04500;

// ?rva007B9035@@YAXXZ @ 0x007B9035 (10B). Global Rva005C47A3 dtor thunk: ecx=&g_Va00E04500 then tail-jmp to pinned ??1Rva005C47A3@@UAE@XZ (0x005C47A3). No callers. Honest address name.
void __cdecl rva007B9035()
{
	Rva005C47A3 *p = (Rva005C47A3 *)&g_Va00E04500;
	return p->Rva005C47A3::~Rva005C47A3();
}

extern unsigned g_Va00E065B4;
unsigned int g_Va00E065B4;

// ?rva007B96EE@@YAXXZ @ 0x007B96EE (10B). Global Rva005C47A3 dtor thunk: ecx=&g_Va00E065B4 then tail-jmp to pinned ??1Rva005C47A3@@UAE@XZ (0x005C47A3). No callers. Honest address name.
void __cdecl rva007B96EE()
{
	Rva005C47A3 *p = (Rva005C47A3 *)&g_Va00E065B4;
	return p->Rva005C47A3::~Rva005C47A3();
}

extern unsigned g_Va00E065B8;
unsigned int g_Va00E065B8;

// ?rva007B96F8@@YAXXZ @ 0x007B96F8 (10B). Global Rva005C47A3 dtor thunk: ecx=&g_Va00E065B8 then tail-jmp to pinned ??1Rva005C47A3@@UAE@XZ (0x005C47A3). No callers. Honest address name.
void __cdecl rva007B96F8()
{
	Rva005C47A3 *p = (Rva005C47A3 *)&g_Va00E065B8;
	return p->Rva005C47A3::~Rva005C47A3();
}

extern unsigned g_Va00E065BC;
unsigned int g_Va00E065BC;

// ?rva007B9702@@YAXXZ @ 0x007B9702 (10B). Global Rva005C47A3 dtor thunk: ecx=&g_Va00E065BC then tail-jmp to pinned ??1Rva005C47A3@@UAE@XZ (0x005C47A3). No callers. Honest address name.
void __cdecl rva007B9702()
{
	Rva005C47A3 *p = (Rva005C47A3 *)&g_Va00E065BC;
	return p->Rva005C47A3::~Rva005C47A3();
}

extern unsigned g_Va00E062D8;
unsigned int g_Va00E062D8;

// ?rva007B945A@@YAXXZ @ 0x007B945A (10B). Global Rva00200667 dtor thunk: ecx=&g_Va00E062D8 then tail-jmp to pinned ??1Rva00200667@@QAE@XZ (0x00200667; deleting dtor 0x002821B3). No callers. Honest address name.
void __cdecl rva007B945A()
{
	Rva00200667 *p = (Rva00200667 *)&g_Va00E062D8;
	return p->~Rva00200667();
}

extern unsigned g_Va00E06654;
unsigned int g_Va00E06654;

// ?rva007B982F@@YAXXZ @ 0x007B982F (10B). Global basic_string<char> dtor thunk: ecx=&g_Va00E06654 then tail-jmp to rowed BasicStringCharDtor_dup (0x0007FAB3 object ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ). No callers. Honest address name.
void __cdecl rva007B982F()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E06654;
	return p->~basic_string();
}

extern unsigned g_Va00E06670;
unsigned int g_Va00E06670;

// ?rva007B9843@@YAXXZ @ 0x007B9843 (10B). Global basic_string<char> dtor thunk: ecx=&g_Va00E06670 then tail-jmp to rowed BasicStringCharDtor_dup (0x0007FAB3 object ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ). No callers. Honest address name.
void __cdecl rva007B9843()
{
	StlNarrowString *p = (StlNarrowString *)&g_Va00E06670;
	return p->~basic_string();
}

// Opaque-class view for the thunk below. The destructor is declared only;
// symbols.csv pins ??1Rva005F00FB@@UAE@XZ to 0x005F00FB
// (see OpaqueScalarDeletingDtorsB17.cpp).
class Rva005F00FB
{
public:
	virtual ~Rva005F00FB();
};

extern unsigned g_Va00E0669C;
unsigned int g_Va00E0669C;

// ?rva007B993D@@YAXXZ @ 0x007B993D (10B). Global Rva005E9F7B dtor thunk: ecx=&g_Va00E0669C then tail-jmp to pinned ??1Rva005E9F7B@@UAE@XZ (0x005E9F7B; scalar deleting dtor 0x005EA68B). No callers. Honest address name.
void __cdecl rva007B993D()
{
	Rva005E9F7B *p = (Rva005E9F7B *)&g_Va00E0669C;
	return p->Rva005E9F7B::~Rva005E9F7B();
}

extern unsigned g_Va00E06778;
unsigned int g_Va00E06778;

// ?rva007B9997@@YAXXZ @ 0x007B9997 (10B). Global Rva005E9F7B dtor thunk: ecx=&g_Va00E06778 then tail-jmp to pinned ??1Rva005E9F7B@@UAE@XZ (0x005E9F7B; scalar deleting dtor 0x005EA68B). No callers. Honest address name.
void __cdecl rva007B9997()
{
	Rva005E9F7B *p = (Rva005E9F7B *)&g_Va00E06778;
	return p->Rva005E9F7B::~Rva005E9F7B();
}

extern unsigned g_Va00E06858;
unsigned int g_Va00E06858;

// ?rva007B99B5@@YAXXZ @ 0x007B99B5 (10B). Global Rva005F00FB dtor thunk: ecx=&g_Va00E06858 then tail-jmp to pinned ??1Rva005F00FB@@UAE@XZ (0x005F00FB; scalar deleting dtor 0x005F02C4). No callers. Honest address name.
void __cdecl rva007B99B5()
{
	Rva005F00FB *p = (Rva005F00FB *)&g_Va00E06858;
	return p->Rva005F00FB::~Rva005F00FB();
}

// Construction-thunk view for the six thunks below. MSVC emits no dynamic
// initializer for a global whose constructor is undefined in this TU
// (verified with a minimal TU), so these thunks reproduce the
// compiler-generated dynamic-initializer shape (mov ecx,OFFSET + tail-jmp to
// the rowed ctor) through an init alias pinned in symbols.csv. The six
// globals hold Rva00552F2E objects (see Rva00552F2EHelpers.cpp).
struct Rva00552F2EInit
{
	void init();
};

extern unsigned g_Va00E06484;
unsigned int g_Va00E06484;

// ?rva007B474C@@YAXXZ @ 0x007B474C (10B). Rva00552F2E construction thunk: ecx=&g_Va00E06484 then tail-jmp to rowed ??0Rva00552F2E@@QAE@XZ (0x00552F2E) via init alias. No callers. Honest address name.
void __cdecl rva007B474C()
{
	Rva00552F2EInit *p = (Rva00552F2EInit *)&g_Va00E06484;
	return p->init();
}

extern unsigned g_Va00E064A4;
unsigned int g_Va00E064A4;

// ?rva007B4756@@YAXXZ @ 0x007B4756 (10B). Rva00552F2E construction thunk: ecx=&g_Va00E064A4 then tail-jmp to rowed ??0Rva00552F2E@@QAE@XZ (0x00552F2E) via init alias. No callers. Honest address name.
void __cdecl rva007B4756()
{
	Rva00552F2EInit *p = (Rva00552F2EInit *)&g_Va00E064A4;
	return p->init();
}

extern unsigned g_Va00E064C4;
unsigned int g_Va00E064C4;

// ?rva007B4760@@YAXXZ @ 0x007B4760 (10B). Rva00552F2E construction thunk: ecx=&g_Va00E064C4 then tail-jmp to rowed ??0Rva00552F2E@@QAE@XZ (0x00552F2E) via init alias. No callers. Honest address name.
void __cdecl rva007B4760()
{
	Rva00552F2EInit *p = (Rva00552F2EInit *)&g_Va00E064C4;
	return p->init();
}

extern unsigned g_Va00E064E4;
unsigned int g_Va00E064E4;

// ?rva007B476A@@YAXXZ @ 0x007B476A (10B). Rva00552F2E construction thunk: ecx=&g_Va00E064E4 then tail-jmp to rowed ??0Rva00552F2E@@QAE@XZ (0x00552F2E) via init alias. No callers. Honest address name.
void __cdecl rva007B476A()
{
	Rva00552F2EInit *p = (Rva00552F2EInit *)&g_Va00E064E4;
	return p->init();
}

extern unsigned g_Va00E06504;
unsigned int g_Va00E06504;

// ?rva007B4774@@YAXXZ @ 0x007B4774 (10B). Rva00552F2E construction thunk: ecx=&g_Va00E06504 then tail-jmp to rowed ??0Rva00552F2E@@QAE@XZ (0x00552F2E) via init alias. No callers. Honest address name.
void __cdecl rva007B4774()
{
	Rva00552F2EInit *p = (Rva00552F2EInit *)&g_Va00E06504;
	return p->init();
}

extern unsigned g_Va00E06524;
unsigned int g_Va00E06524;

// ?rva007B477E@@YAXXZ @ 0x007B477E (10B). Rva00552F2E construction thunk: ecx=&g_Va00E06524 then tail-jmp to rowed ??0Rva00552F2E@@QAE@XZ (0x00552F2E) via init alias. No callers. Honest address name.
void __cdecl rva007B477E()
{
	Rva00552F2EInit *p = (Rva00552F2EInit *)&g_Va00E06524;
	return p->init();
}

// CPUDetectInitClass construction view for the thunk below. The rowed ctor
// (0x006130C0, cpudetect.cpp) is defined in its own TU, so this thunk
// reproduces the compiler-generated dynamic-initializer shape through an
// init alias pinned in symbols.csv. The global holds a CPUDetectInitClass.
struct CPUDetectInitThunk
{
	void init();
};

extern unsigned g_Va00E08D38;
unsigned int g_Va00E08D38;

// ?rva007B54E0@@YAXXZ @ 0x007B54E0 (10B). CPUDetectInitClass construction thunk: ecx=&g_Va00E08D38 then tail-jmp to rowed ??0CPUDetectInitClass@@QAE@XZ (0x006130C0) via init alias. No callers. Honest address name.
void __cdecl rva007B54E0()
{
	CPUDetectInitThunk *p = (CPUDetectInitThunk *)&g_Va00E08D38;
	return p->init();
}

extern unsigned g_Va00E02C48;
unsigned int g_Va00E02C48;

// ?rva007B3EB4@@YAXXZ @ 0x007B3EB4 (11B). Global store thunk: g_Va00E02C48 = 0x00E02C40 then ret. The stored value is 8 below the global's own address; purpose unproven. No callers. Honest address name.
void __cdecl rva007B3EB4()
{
	g_Va00E02C48 = 0x00E02C40;
}

extern unsigned g_Va00E02C4C;
unsigned int g_Va00E02C4C;

// ?rva007B3EBF@@YAXXZ @ 0x007B3EBF (11B). Global store thunk: g_Va00E02C4C = 0x00E02C44 then ret. The stored value is 8 below the global's own address; purpose unproven. No callers. Honest address name.
void __cdecl rva007B3EBF()
{
	g_Va00E02C4C = 0x00E02C44;
}

// Opaque-class view for the thunk below. The destructor is declared only;
// symbols.csv pins ??1Rva007EC44@@UAE@XZ to 0x007EC44 (opaque SEH dtor, vptr
// 0xBC6F80; called by the rowed scalar deleting dtor 0x007EC87).
class Rva007EC44
{
public:
	virtual ~Rva007EC44();
};

extern unsigned g_Va00DE2008;
unsigned int g_Va00DE2008;

// ?rva007B6BF5@@YAXXZ @ 0x007B6BF5 (10B). Global Rva007EC44 dtor thunk: ecx=&g_Va00DE2008 then tail-jmp to pinned ??1Rva007EC44@@UAE@XZ (0x007EC44). No callers. Honest address name.
void __cdecl rva007B6BF5()
{
	Rva007EC44 *p = (Rva007EC44 *)&g_Va00DE2008;
	return p->Rva007EC44::~Rva007EC44();
}

// FrustumClass construction view for the thunk below. The rowed ctor
// (0x000F0F5B, FrustumCtorO1.cpp) is defined in its own TU, so this thunk
// reproduces the compiler-generated dynamic-initializer shape through an
// init alias pinned in symbols.csv. The global holds a FrustumClass.
struct FrustumInitThunk
{
	void init();
};

extern unsigned g_Va00DEBD00;
unsigned int g_Va00DEBD00;

// ?rva007AC7F5@@YAXXZ @ 0x007AC7F5 (10B). FrustumClass construction thunk: ecx=&g_Va00DEBD00 then tail-jmp to rowed ??0FrustumClass@@QAE@XZ (0x000F0F5B) via init alias. No callers. Honest address name.
void __cdecl rva007AC7F5()
{
	FrustumInitThunk *p = (FrustumInitThunk *)&g_Va00DEBD00;
	return p->init();
}

// Opaque-class view for the thunk below. The destructor is declared only;
// symbols.csv pins ??1Rva007A4E6@@QAE@XZ to 0x007A4E6 (101B EH dtor: frees
// members at +0x10/+0x1C via 0x00030830, clears +0xC via rowed 0x000799D0,
// destroys +0 via rowed tree dtor 0x00079E55; non-virtual, no vftable store).
class Rva007A4E6
{
public:
	~Rva007A4E6();
};

extern unsigned g_Va00DE1FC8;
unsigned int g_Va00DE1FC8;

// ?rva007B6BE1@@YAXXZ @ 0x007B6BE1 (10B). Global Rva007A4E6 dtor thunk: ecx=&g_Va00DE1FC8 then tail-jmp to pinned ??1Rva007A4E6@@QAE@XZ (0x007A4E6). No callers. Honest address name.
void __cdecl rva007B6BE1()
{
	Rva007A4E6 *p = (Rva007A4E6 *)&g_Va00DE1FC8;
	return p->~Rva007A4E6();
}

extern unsigned g_Va00DD828C;
unsigned int g_Va00DD828C;

// ?rva007B9B90@@YAXXZ @ 0x007B9B90 (11B). Vftable store thunk: g_Va00DD828C = 0x00CE3168 (vftable stored as slot 10 by the rowed ??_GRva006655B0 deleting dtor) then ret. No callers. Honest address name.
void __cdecl rva007B9B90()
{
	g_Va00DD828C = ((unsigned int)vtbl_00CE3168);
}

extern unsigned g_Va00DD8314;
unsigned int g_Va00DD8314;

// ?rva007B9BA0@@YAXXZ @ 0x007B9BA0 (11B). Vftable store thunk: g_Va00DD8314 = 0x00CE36A0 (vftable stored as slot 10 by the rowed ??_GRva006680E0 deleting dtor) then ret. No callers. Honest address name.
void __cdecl rva007B9BA0()
{
	g_Va00DD8314 = ((unsigned int)vtbl_00CE36A0);
}

extern unsigned g_Va00DD83B4;
unsigned int g_Va00DD83B4;

// ?rva007B9BB0@@YAXXZ @ 0x007B9BB0 (11B). Vftable store thunk: g_Va00DD83B4 = 0x00CE3934 (vftable stored as slot 10 by the rowed ??_GRva00669510 deleting dtor) then ret. No callers. Honest address name.
void __cdecl rva007B9BB0()
{
	g_Va00DD83B4 = ((unsigned int)vtbl_00CE3934);
}

// Opaque-class view for the thunk below. The destructor is declared only;
// symbols.csv / functions.csv pins ??1Rva004E5A24@@UAE@XZ to 0x000FB86C.
class Rva004E5A24
{
public:
	virtual ~Rva004E5A24();
};

extern unsigned g_Va00DEC174;
unsigned int g_Va00DEC174;

// ?rva007B6EF4@@YAXXZ @ 0x007B6EF4 (10B). Global Rva004E5A24 dtor thunk: ecx=&g_Va00DEC174 then tail-jmp to rowed ??1Rva004E5A24@@UAE@XZ (0x000FB86C). No callers. Honest address name.
void __cdecl rva007B6EF4()
{
	Rva004E5A24 *p = (Rva004E5A24 *)&g_Va00DEC174;
	return p->Rva004E5A24::~Rva004E5A24();
}

class Rva000E6387
{
public:
	virtual ~Rva000E6387();
};

extern unsigned g_Va00DEBC98;
unsigned int g_Va00DEBC98;

// ?rva007B6E18@@YAXXZ @ 0x007B6E18 (10B). Global Rva000E6387 dtor thunk: ecx=&g_Va00DEBC98 then tail-jmp to pinned ??1Rva000E6387@@UAE@XZ (0x000E6387). No callers. Honest address name.
void __cdecl rva007B6E18()
{
	Rva000E6387 *p = (Rva000E6387 *)&g_Va00DEBC98;
	return p->Rva000E6387::~Rva000E6387();
}

class Gen_uwm_00357cd9
{
public:
	~Gen_uwm_00357cd9();
};

extern unsigned g_Va00E02838;
unsigned int g_Va00E02838;

// ?rva007B7E3F@@YAXXZ @ 0x007B7E3F (10B). Global Gen_uwm_00357cd9 dtor thunk: ecx=&g_Va00E02838 then tail-jmp to pinned ??1Gen_uwm_00357cd9@@QAE@XZ (0x00357CD9). No callers. Honest address name.
void __cdecl rva007B7E3F()
{
	Gen_uwm_00357cd9 *p = (Gen_uwm_00357cd9 *)&g_Va00E02838;
	return p->~Gen_uwm_00357cd9();
}

extern unsigned g_Va00DDEF54;
unsigned int g_Va00DDEF54;

// ?rva007B6A50@@YAXXZ @ 0x007B6A50 (10B). Global locale uninitialize thunk: ecx=&g_Va00DDEF54 then tail-jmp to pinned ?rva00007670@Rva00007670@@QAEXXZ (0x00007670). No callers. Honest address name.
void __cdecl rva007B6A50()
{
	Rva00007670 *p = (Rva00007670 *)&g_Va00DDEF54;
	return p->rva00007670();
}

class Rva00422CE9Tree
{
public:
	~Rva00422CE9Tree();
};

extern unsigned g_Va00E03168;
unsigned int g_Va00E03168;

// ?rva007B82D3@@YAXXZ @ 0x007B82D3 (10B). Tree teardown: ecx=&g_Va00E03168 then tail-jmp to the 0x00422CE9 stub for tree dtor ??1Rva00421BF7@@QAE@XZ (0x0042263D). No callers. Honest address name.
void __cdecl rva007B82D3()
{
	Rva00422CE9Tree *p = (Rva00422CE9Tree *)&g_Va00E03168;
	return p->~Rva00422CE9Tree();
}

class Rva00422CEETree
{
public:
	~Rva00422CEETree();
};

extern unsigned g_Va00E0319C;
unsigned int g_Va00E0319C;

// ?rva007B82DD@@YAXXZ @ 0x007B82DD (10B). Tree teardown: ecx=&g_Va00E0319C then tail-jmp to the 0x00422CEE stub for tree dtor ??1Rva00421C24@@QAE@XZ (0x00422675). No callers. Honest address name.
void __cdecl rva007B82DD()
{
	Rva00422CEETree *p = (Rva00422CEETree *)&g_Va00E0319C;
	return p->~Rva00422CEETree();
}

class Rva0030AF8FAudioEventRTS
{
public:
	~Rva0030AF8FAudioEventRTS();
};

extern unsigned g_Va00DFF4F8;
unsigned int g_Va00DFF4F8;

// ?rva007B7AF5@@YAXXZ @ 0x007B7AF5 (10B). Global AudioEventRTS dtor thunk: ecx=&g_Va00DFF4F8 then tail-jmp to pinned ??1Rva0030AF8FAudioEventRTS@@QAE@XZ (0x0030AF8F). No callers. Honest address name.
void __cdecl rva007B7AF5()
{
	Rva0030AF8FAudioEventRTS *p = (Rva0030AF8FAudioEventRTS *)&g_Va00DFF4F8;
	return p->~Rva0030AF8FAudioEventRTS();
}

extern unsigned g_Va00DFF4B8;
unsigned int g_Va00DFF4B8;

// ?rva007B7AFF@@YAXXZ @ 0x007B7AFF (10B). Global AudioEventRTS dtor thunk: ecx=&g_Va00DFF4B8 then tail-jmp to pinned ??1Rva0030AF8FAudioEventRTS@@QAE@XZ (0x0030AF8F). No callers. Honest address name.
void __cdecl rva007B7AFF()
{
	Rva0030AF8FAudioEventRTS *p = (Rva0030AF8FAudioEventRTS *)&g_Va00DFF4B8;
	return p->~Rva0030AF8FAudioEventRTS();
}

// Native7B89C1 loads ECX with E03CE0; separate from7B8590's E0362C.
extern unsigned g_Va00E03CE0;
unsigned int g_Va00E03CE0;

class Rva004ABE53Dtor
{
public:
	~Rva004ABE53Dtor();
};

// ?rva007B89C1@@YAXXZ @ 0x007B89C1 (10B). Global dtor thunk: ecx=&g_Va00E03CE0 then tail-jmp to pinned ??1Rva004ABE53Dtor@@QAE@XZ (0x004ABE53). No callers. Honest address name.
void __cdecl rva007B89C1()
{
	Rva004ABE53Dtor *p = (Rva004ABE53Dtor *)&g_Va00E03CE0;
	return p->~Rva004ABE53Dtor();
}

class AptActionInterpreter
{
public:
	~AptActionInterpreter();
};

extern unsigned g_Va00E182E0;
unsigned int g_Va00E182E0;

// ?rva007B9C50@@YAXXZ @ 0x007B9C50 (10B). Global AptActionInterpreter dtor thunk: ecx=&g_Va00E182E0 then tail-jmp to pinned ??1AptActionInterpreter@@QAE@XZ (0x006FE9C0). No callers. Honest address name.
void __cdecl rva007B9C50()
{
	AptActionInterpreter *p = (AptActionInterpreter *)&g_Va00E182E0;
	return p->~AptActionInterpreter();
}

class Rva000FC5AADtor
{
public:
	~Rva000FC5AADtor();
};

extern unsigned g_Va00DEC1CC;
unsigned int g_Va00DEC1CC;

// ?rva007B6F08@@YAXXZ @ 0x007B6F08 (10B). Global dtor thunk: ecx=&g_Va00DEC1CC then tail-jmp to pinned ??1Rva000FC5AADtor@@QAE@XZ (0x000FC5AA). No callers. Honest address name.
void __cdecl rva007B6F08()
{
	Rva000FC5AADtor *p = (Rva000FC5AADtor *)&g_Va00DEC1CC;
	return p->~Rva000FC5AADtor();
}

extern unsigned g_Va00DEC1DC;
unsigned int g_Va00DEC1DC;

// ?rva007B6F12@@YAXXZ @ 0x007B6F12 (10B). Global dtor thunk: ecx=&g_Va00DEC1DC then tail-jmp to pinned ??1Rva000FC5AADtor@@QAE@XZ (0x000FC5AA). No callers. Honest address name.
void __cdecl rva007B6F12()
{
	Rva000FC5AADtor *p = (Rva000FC5AADtor *)&g_Va00DEC1DC;
	return p->~Rva000FC5AADtor();
}

class Rva000F82F5Dtor
{
public:
	~Rva000F82F5Dtor();
};

extern unsigned g_Va00DEC018;
unsigned int g_Va00DEC018;

// ?rva007B6EAE@@YAXXZ @ 0x007B6EAE (10B). Global dtor thunk: ecx=&g_Va00DEC018 then tail-jmp to pinned ??1Rva000F82F5Dtor@@QAE@XZ (0x000F82F5). No callers. Honest address name.
void __cdecl rva007B6EAE()
{
	Rva000F82F5Dtor *p = (Rva000F82F5Dtor *)&g_Va00DEC018;
	return p->~Rva000F82F5Dtor();
}

class Rva000F9BD7Dtor
{
public:
	~Rva000F9BD7Dtor();
};

extern unsigned g_Va00DEC080;
unsigned int g_Va00DEC080;

// ?rva007B6EC2@@YAXXZ @ 0x007B6EC2 (10B). Global dtor thunk: ecx=&g_Va00DEC080 then tail-jmp to pinned ??1Rva000F9BD7Dtor@@QAE@XZ (0x000F9BD7). No callers. Honest address name.
void __cdecl rva007B6EC2()
{
	Rva000F9BD7Dtor *p = (Rva000F9BD7Dtor *)&g_Va00DEC080;
	return p->~Rva000F9BD7Dtor();
}

class Rva000FA7E8Dtor
{
public:
	~Rva000FA7E8Dtor();
};

extern unsigned g_Va00DEC0E0;
unsigned int g_Va00DEC0E0;

// ?rva007B6ED6@@YAXXZ @ 0x007B6ED6 (10B). Global dtor thunk: ecx=&g_Va00DEC0E0 then tail-jmp to pinned ??1Rva000FA7E8Dtor@@QAE@XZ (0x000FA7E8). No callers. Honest address name.
void __cdecl rva007B6ED6()
{
	Rva000FA7E8Dtor *p = (Rva000FA7E8Dtor *)&g_Va00DEC0E0;
	return p->~Rva000FA7E8Dtor();
}

class Rva000FB85DDtor
{
public:
	~Rva000FB85DDtor();
};

extern unsigned g_Va00DEC140;
unsigned int g_Va00DEC140;

// ?rva007B6EEA@@YAXXZ @ 0x007B6EEA (10B). Global dtor thunk: ecx=&g_Va00DEC140 then tail-jmp to pinned ??1Rva000FB85DDtor@@QAE@XZ (0x000FB85D). No callers. Honest address name.
void __cdecl rva007B6EEA()
{
	Rva000FB85DDtor *p = (Rva000FB85DDtor *)&g_Va00DEC140;
	return p->~Rva000FB85DDtor();
}

class Rva00136768Dtor
{
public:
	~Rva00136768Dtor();
};

extern unsigned g_Va00DF29B4;
unsigned int g_Va00DF29B4;

// ?rva007B70D3@@YAXXZ @ 0x007B70D3 (10B). Global dtor thunk: ecx=&g_Va00DF29B4 then tail-jmp to pinned ??1Rva00136768Dtor@@QAE@XZ (0x00136768). No callers. Honest address name.
void __cdecl rva007B70D3()
{
	Rva00136768Dtor *p = (Rva00136768Dtor *)&g_Va00DF29B4;
	return p->~Rva00136768Dtor();
}

class Rva0007C632Dtor
{
public:
	~Rva0007C632Dtor();
};

extern unsigned g_Va00DF6F10;
unsigned int g_Va00DF6F10;

// ?rva007B71AA@@YAXXZ @ 0x007B71AA (10B). Global dtor thunk: ecx=&g_Va00DF6F10 then tail-jmp to pinned ??1Rva0007C632Dtor@@QAE@XZ (0x0007C632). No callers. Honest address name.
void __cdecl rva007B71AA()
{
	Rva0007C632Dtor *p = (Rva0007C632Dtor *)&g_Va00DF6F10;
	return p->~Rva0007C632Dtor();
}

class Rva002213C0Dtor
{
public:
	~Rva002213C0Dtor();
};

extern unsigned g_Va00DFE4AC;
unsigned int g_Va00DFE4AC;

// ?rva007B7704@@YAXXZ @ 0x007B7704 (10B). Global dtor thunk: ecx=&g_Va00DFE4AC then tail-jmp to pinned ??1Rva002213C0Dtor@@QAE@XZ (0x002213C0). No callers. Honest address name.
void __cdecl rva007B7704()
{
	Rva002213C0Dtor *p = (Rva002213C0Dtor *)&g_Va00DFE4AC;
	return p->~Rva002213C0Dtor();
}

class Rva003ED94FDtor
{
public:
	~Rva003ED94FDtor();
};

extern unsigned g_Va00DFEC74;
unsigned int g_Va00DFEC74;

// ?rva007B7810@@YAXXZ @ 0x007B7810 (10B). Global dtor thunk: ecx=&g_Va00DFEC74 then tail-jmp to pinned ??1Rva003ED94FDtor@@QAE@XZ (0x003ED94F). No callers. Honest address name.
void __cdecl rva007B7810()
{
	Rva003ED94FDtor *p = (Rva003ED94FDtor *)&g_Va00DFEC74;
	return p->~Rva003ED94FDtor();
}

class Rva00301621Dtor
{
public:
	~Rva00301621Dtor();
};

extern unsigned g_Va00DFF14C;
unsigned int g_Va00DFF14C;

// ?rva007B7A9B@@YAXXZ @ 0x007B7A9B (10B). Global dtor thunk: ecx=&g_Va00DFF14C then tail-jmp to pinned ??1Rva00301621Dtor@@QAE@XZ (0x00301621). No callers. Honest address name.
void __cdecl rva007B7A9B()
{
	Rva00301621Dtor *p = (Rva00301621Dtor *)&g_Va00DFF14C;
	return p->~Rva00301621Dtor();
}

class Rva0030A0FCDtor
{
public:
	~Rva0030A0FCDtor();
};

extern unsigned g_Va00DFF494;
unsigned int g_Va00DFF494;

// ?rva007B7AE1@@YAXXZ @ 0x007B7AE1 (10B). Global dtor thunk: ecx=&g_Va00DFF494 then tail-jmp to pinned ??1Rva0030A0FCDtor@@QAE@XZ (0x0030A0FC). No callers. Honest address name.
void __cdecl rva007B7AE1()
{
	Rva0030A0FCDtor *p = (Rva0030A0FCDtor *)&g_Va00DFF494;
	return p->~Rva0030A0FCDtor();
}

class Rva002B905DDtor
{
public:
	~Rva002B905DDtor();
};

extern unsigned g_Va00E032DC;
unsigned int g_Va00E032DC;

// ?rva007B839B@@YAXXZ @ 0x007B839B (10B). Global dtor thunk: ecx=&g_Va00E032DC then tail-jmp to pinned ??1Rva002B905DDtor@@QAE@XZ (0x002B905D). No callers. Honest address name.
void __cdecl rva007B839B()
{
	Rva002B905DDtor *p = (Rva002B905DDtor *)&g_Va00E032DC;
	return p->~Rva002B905DDtor();
}

class Rva00435CDBDtor
{
public:
	~Rva00435CDBDtor();
};

extern unsigned g_Va00E032EC;
unsigned int g_Va00E032EC;

// ?rva007B83B9@@YAXXZ @ 0x007B83B9 (10B). Global dtor thunk: ecx=&g_Va00E032EC then tail-jmp to pinned ??1Rva00435CDBDtor@@QAE@XZ (0x00435CDB). No callers. Honest address name.
void __cdecl rva007B83B9()
{
	Rva00435CDBDtor *p = (Rva00435CDBDtor *)&g_Va00E032EC;
	return p->~Rva00435CDBDtor();
}

class Rva00502D03Dtor
{
public:
	~Rva00502D03Dtor();
};

extern unsigned g_Va00E04508;
unsigned int g_Va00E04508;

// ?rva007B9049@@YAXXZ @ 0x007B9049 (10B). Global dtor thunk: ecx=&g_Va00E04508 then tail-jmp to pinned ??1Rva00502D03Dtor@@QAE@XZ (0x00502D03). No callers. Honest address name.
void __cdecl rva007B9049()
{
	Rva00502D03Dtor *p = (Rva00502D03Dtor *)&g_Va00E04508;
	return p->~Rva00502D03Dtor();
}

class Rva005011AADtor
{
public:
	~Rva005011AADtor();
};

extern unsigned g_Va00E04544;
unsigned int g_Va00E04544;

// ?rva007B9071@@YAXXZ @ 0x007B9071 (10B). Global dtor thunk: ecx=&g_Va00E04544 then tail-jmp to pinned ??1Rva005011AADtor@@QAE@XZ (0x005011AA). No callers. Honest address name.
void __cdecl rva007B9071()
{
	Rva005011AADtor *p = (Rva005011AADtor *)&g_Va00E04544;
	return p->~Rva005011AADtor();
}

class Rva00524CC1Dtor
{
public:
	~Rva00524CC1Dtor();
};

extern unsigned g_Va00E04938;
unsigned int g_Va00E04938;

// ?rva007B91F8@@YAXXZ @ 0x007B91F8 (10B). Global dtor thunk: ecx=&g_Va00E04938 then tail-jmp to pinned ??1Rva00524CC1Dtor@@QAE@XZ (0x00524CC1). No callers. Honest address name.
void __cdecl rva007B91F8()
{
	Rva00524CC1Dtor *p = (Rva00524CC1Dtor *)&g_Va00E04938;
	return p->~Rva00524CC1Dtor();
}

class Rva0052B7B3Dtor
{
public:
	~Rva0052B7B3Dtor();
};

extern unsigned g_Va00E049B4;
unsigned int g_Va00E049B4;

// ?rva007B9298@@YAXXZ @ 0x007B9298 (10B). Global dtor thunk: ecx=&g_Va00E049B4 then tail-jmp to pinned ??1Rva0052B7B3Dtor@@QAE@XZ (0x0052B7B3). No callers. Honest address name.
void __cdecl rva007B9298()
{
	Rva0052B7B3Dtor *p = (Rva0052B7B3Dtor *)&g_Va00E049B4;
	return p->~Rva0052B7B3Dtor();
}

namespace _STL
{
template <class T, class A>
class _List_base
{
public:
	~_List_base();

private:
	void *m_header;
};
}

class Rva00207F08Dtor : public _STL::_List_base<AsciiString, _STL::allocator<AsciiString> >
{
public:
	~Rva00207F08Dtor();
};

Rva00207F08Dtor::~Rva00207F08Dtor()
{
}

extern unsigned g_Va00E065E4;
unsigned int g_Va00E065E4;

// ?rva007B9720@@YAXXZ @ 0x007B9720 (10B). Global dtor thunk: ecx=&g_Va00E065E4 then tail-jmp to pinned ??1Rva00207F08Dtor@@QAE@XZ (0x00207F08). No callers. Honest address name.
void __cdecl rva007B9720()
{
	Rva00207F08Dtor *p = (Rva00207F08Dtor *)&g_Va00E065E4;
	return p->~Rva00207F08Dtor();
}

class Rva002859EADtor
{
public:
	~Rva002859EADtor();
};

extern unsigned g_Va00DE1E98;
unsigned int g_Va00DE1E98;

// ?rva007B6B73@@YAXXZ @ 0x007B6B73 (10B). Global dtor thunk: ecx=&g_Va00DE1E98 then tail-jmp to pinned ??1Rva002859EADtor@@QAE@XZ (0x002859EA). No callers. Honest address name.
void __cdecl rva007B6B73()
{
	Rva002859EADtor *p = (Rva002859EADtor *)&g_Va00DE1E98;
	return p->~Rva002859EADtor();
}

extern unsigned g_Va00DFEC94;
unsigned int g_Va00DFEC94;

// ?rva007B781A@@YAXXZ @ 0x007B781A (10B). Global dtor thunk: ecx=&g_Va00DFEC94 then tail-jmp to pinned ??1Rva002859EADtor@@QAE@XZ (0x002859EA). No callers. Honest address name.
void __cdecl rva007B781A()
{
	Rva002859EADtor *p = (Rva002859EADtor *)&g_Va00DFEC94;
	return p->~Rva002859EADtor();
}

extern unsigned g_Va00DFECA8;
unsigned int g_Va00DFECA8;

// ?rva007B7824@@YAXXZ @ 0x007B7824 (10B). Global dtor thunk: ecx=&g_Va00DFECA8 then tail-jmp to pinned ??1Rva002859EADtor@@QAE@XZ (0x002859EA). No callers. Honest address name.
void __cdecl rva007B7824()
{
	Rva002859EADtor *p = (Rva002859EADtor *)&g_Va00DFECA8;
	return p->~Rva002859EADtor();
}

class Rva003615E5Dtor
{
public:
	~Rva003615E5Dtor();
};

extern unsigned g_Va00E01E68;
unsigned int g_Va00E01E68;

// ?rva007B7CAF@@YAXXZ @ 0x007B7CAF (10B). Global dtor thunk: ecx=&g_Va00E01E68 then tail-jmp to pinned ??1Rva003615E5Dtor@@QAE@XZ (0x003615E5). No callers. Honest address name.
void __cdecl rva007B7CAF()
{
	Rva003615E5Dtor *p = (Rva003615E5Dtor *)&g_Va00E01E68;
	return p->~Rva003615E5Dtor();
}

class Rva00362B5ADtor
{
public:
	~Rva00362B5ADtor();
};

extern unsigned g_Va00E01E7C;
unsigned int g_Va00E01E7C;

// ?rva007B7CC3@@YAXXZ @ 0x007B7CC3 (10B). Global dtor thunk: ecx=&g_Va00E01E7C then tail-jmp to pinned ??1Rva00362B5ADtor@@QAE@XZ (0x00362B5A). No callers. Honest address name.
void __cdecl rva007B7CC3()
{
	Rva00362B5ADtor *p = (Rva00362B5ADtor *)&g_Va00E01E7C;
	return p->~Rva00362B5ADtor();
}

extern unsigned g_Va00E01E94;
unsigned int g_Va00E01E94;

// ?rva007B7CD7@@YAXXZ @ 0x007B7CD7 (10B). Global dtor thunk: ecx=&g_Va00E01E94 then tail-jmp to pinned ??1Rva002859EADtor@@QAE@XZ (0x002859EA). No callers. Honest address name.
void __cdecl rva007B7CD7()
{
	Rva002859EADtor *p = (Rva002859EADtor *)&g_Va00E01E94;
	return p->~Rva002859EADtor();
}

class Rva003ED94ADtor
{
public:
	~Rva003ED94ADtor();
};

extern unsigned g_Va00E02E50;
unsigned int g_Va00E02E50;

// ?rva007B80F1@@YAXXZ @ 0x007B80F1 (10B). Global dtor thunk: ecx=&g_Va00E02E50 then tail-jmp to pinned ??1Rva003ED94ADtor@@QAE@XZ (0x003ED94A). No callers. Honest address name.
void __cdecl rva007B80F1()
{
	Rva003ED94ADtor *p = (Rva003ED94ADtor *)&g_Va00E02E50;
	return p->~Rva003ED94ADtor();
}

class Rva003B55F9Dtor
{
public:
	~Rva003B55F9Dtor();
};

extern unsigned g_Va00E03174;
unsigned int g_Va00E03174;

// ?rva007B82C9@@YAXXZ @ 0x007B82C9 (10B). Global dtor thunk: ecx=&g_Va00E03174 then tail-jmp to pinned ??1Rva003B55F9Dtor@@QAE@XZ (0x003B55F9). No callers. Honest address name.
void __cdecl rva007B82C9()
{
	Rva003B55F9Dtor *p = (Rva003B55F9Dtor *)&g_Va00E03174;
	return p->~Rva003B55F9Dtor();
}

extern unsigned g_Va00E049D8;
unsigned int g_Va00E049D8;

// ?rva007B92A2@@YAXXZ @ 0x007B92A2 (10B). Global dtor thunk: ecx=&g_Va00E049D8 then tail-jmp to pinned ??1Rva002859EADtor@@QAE@XZ (0x002859EA). No callers. Honest address name.
void __cdecl rva007B92A2()
{
	Rva002859EADtor *p = (Rva002859EADtor *)&g_Va00E049D8;
	return p->~Rva002859EADtor();
}

extern unsigned g_Va00E06E60;
unsigned int g_Va00E06E60;

// ?rva007B9A37@@YAXXZ @ 0x007B9A37 (10B). Global dtor thunk: ecx=&g_Va00E06E60 then tail-jmp to pinned ??1Rva003B55F9Dtor@@QAE@XZ (0x003B55F9). No callers. Honest address name.
void __cdecl rva007B9A37()
{
	Rva003B55F9Dtor *p = (Rva003B55F9Dtor *)&g_Va00E06E60;
	return p->~Rva003B55F9Dtor();
}

// CameraMarker-layout view for the thunk below. The destructor is declared
// only; symbols.csv pins ??1Rva00523EC0Marker@@QAE@XZ to 0x0029D7C2 whose
// identical bytes serve this teardown (ICF; rowed as ??1CameraMarker).
class Rva00523EC0Marker
{
public:
	~Rva00523EC0Marker();
};

// ?rva00523EC0@Rva00523EC0@@QAEXXZ @0x00523EC0 8B member dtor forwarder to
// pinned ??1Rva00523EC0Marker@@QAE@XZ (0x0029D7C2). No callers. Honest
// address name.
class Rva00523EC0
{
public:
	void rva00523EC0();
private:
	char m_pad[4];
	Rva00523EC0Marker *m_member;
};
void Rva00523EC0::rva00523EC0()
{
	return m_member->~Rva00523EC0Marker();
}

// Rva005C392A view for the thunk below. The method is declared only and
// resolves to the rowed ?rva005C392A@Rva005C392A@@QAEXXZ (0x005C392A, 8B
// vtable slot in VslotSmallBodiesAE.cpp); declared here (not defined) so the
// tailcall is preserved.
class Rva005C392A
{
public:
	void rva005C392A();
};

// ?rva00567782@Rva00567782@@QAEXXZ @0x00567782 8B member forwarder to rowed
// ?rva005C392A@Rva005C392A@@QAEXXZ (0x005C392A). No callers. Honest address name.
class Rva00567782
{
public:
	void rva00567782();
private:
	char m_pad[8];
	Rva005C392A *m_member;
};
void Rva00567782::rva00567782()
{
	return m_member->rva005C392A();
}

