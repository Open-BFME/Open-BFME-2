// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva007B6880@@YAXXZ @ 0x007B6880 (10B). Global setter thunk: ecx=&g_Va00DDEB24 then tail-jmp to rowed ?apply@Rva00019EC0DwordImmSetter@@QAEXXZ (0x00019EC0) which sets [ecx],0xBBC8D4. No callers. Prev 0x007B5860 (Rva00CE12FCMutex.cpp) next 0x007B7270 (BfmeConv804.cpp). Honest address name; no donor.
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

// ??1?$VectorClass@UTextureStatisticsStruct@@@@UAE@XZ rowed target for next thunk (67B @0x0012A4D0).
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

