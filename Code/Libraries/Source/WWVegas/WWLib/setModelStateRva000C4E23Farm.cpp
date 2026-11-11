// ?setModelState@W3DScriptedModelDraw@@QAE_NPBUModelConditionInfo@@_NPAX@Z
// ?setModelState@W3DScriptedModelDraw@@QAE_NPBUModelConditionInfo@@_NPAX@Z
// ?setModelState@W3DScriptedModelDraw@@QAE_NPBUModelConditionInfo@@_NPAX@Z
// ?setModelState@W3DScriptedModelDraw@@QAE_NPBUModelConditionInfo@@_NPAX@Z
// W9-O1 bank r2: W3DScriptedModelDraw::setModelState 0xC4E23 (3553 B): 3550 B, nn 40/1110, EH table EXACT, all callees
// resolve. The owned int-return 0/1 query is checked as unsigned char for retail AL tests; no return-type cast or owner rename is required.
// Host: W3DScriptedModelDrawTurretNames.cpp (turretNamesDiffer private EDI/EBX ABI) replacing its source-only caller.
// Sibling guide: W3DHordeModelDrawSetModelState.cpp (0x7A847 matched) - same source family.
// Remaining residue (all register/scheduling): (1) md->m_record8C.text0 test: retail this-form add eax,0x8c (empty()),
// but empty() makes cl CSE the 0x8c constant into EDI and spill the drawable (begin()!=end() used instead, 2 lines);
// (2) debug "not found in drawable" arg scheduling; (3) 2nd C3886 call pushes [edi+0x364] vs retail mov ecx/push ecx;
// (4) track bind: retail md in eax + lea ecx,[eax+0x3c]; 3rd str() result eax vs ours lea edx; (5) shadow block:
// retail info=EDX zero=EAX, ours info=EAX zero=EDX (~14 lines); (6) x87 fld g/fmul field order; (7) m_1C9 store sinks.
// Tried inert: no-local/WB spelling of the shadow test, inverted if, barrier/swap mutation sweep (75), decl moves.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// W3DScriptedModelDraw::setModelState (retail 0x000C4E23, 3553 B, RET 12;
// WorldBuilder 0x00932CA0 W3DScriptedModelDraw::setModelState) and its
// file-static helper turretNamesDiffer (retail 0x000B7E8B, 121 B, RET 0).
//
// turretNamesDiffer: Zero Hour W3DModelDraw.cpp's static turretNamesDiffer is
// the semantic donor: both states must have valid turrets, then the angle and
// pitch name keys of each turret are compared. BFME2 keeps the turrets in a
// vector of 24-byte records at +0xD0 (bounded by both sizes), the valid flag
// is the byte at +0xF5 and MAX_TURRETS is 1 (target facts from the retail and
// WB bodies; the member names are carried from the donor). Retail passes `a`
// in EDI and `b` in EBX: cl 7.1 picks that private convention itself for a
// file-static noinline function.

// Vector and string storage is released through the pinned _STL::free
// (0x00030830); _strnicmp is the CRT import retail calls through its IAT slot.
// The string CRT entry points are imports; the allocator below stays bound
// to the game's _STL::free provider. Take the declarations from the CRT header.
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#pragma pop_macro("_CRTIMP")
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <vector>
#include <string>
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?push_back@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEXABVAsciiStr:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void vector<AsciiString,allocator<AsciiString> >::push_back(AsciiString const &); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$all:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<basic_string<char,char_traits<char>,allocator<char> >,allocator<basic_string<char,char_traits<char>,allocator<char> > > >::push_back(basic_string<char,char_traits<char>,allocator<char> > const &); }
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAVAsciiString@@IV1@@_STL@@YAPAVAsciiString@@PAV1@IABV1@ABU__fal:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> AsciiString * __uninitialized_fill_n<AsciiString *,unsigned int,AsciiString>(AsciiString *,unsigned int,AsciiString const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__find@PAVAsciiString@@PBD@_STL@@YAPAVAsciiString@@PAV1@0ABQBDABUrandom_access_iterator:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> AsciiString * __find<AsciiString *,char const *>(AsciiString *,AsciiString *,char const * const &,random_access_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAVAsciiString@@PAV1@@_STL@@YAPAVAsciiString@@PAV1@00ABU__false_ty:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> AsciiString * __uninitialized_copy<AsciiString *,AsciiString *>(AsciiString *,AsciiString *,AsciiString *,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@IAEXPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<AsciiString,allocator<AsciiString> >::_M_insert_overflow(AsciiString *,AsciiString const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?erase@?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocat:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > * vector<basic_string<char,char_traits<char>,allocator<char> >,allocator<basic_string<char,char_traits<char>,allocator<char> > > >::erase(basic_string<char,char_traits<char>,allocator<char> > *,basic_string<char,char_traits<char>,allocator<char> > *); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<basic_string<char,char_traits<char>,allocator<char> >,allocator<basic_string<char,char_traits<char>,allocator<char> > > >::_M_insert_overflow(basic_string<char,char_traits<char>,allocator<char> > *,basic_string<char,char_traits<char>,allocator<char> > const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > * __uninitialized_fill_n<basic_string<char,char_traits<char>,allocator<char> > *,unsigned int,basic_string<char,char_traits<char>,allocator<char> > >(basic_string<char,char_traits<char>,allocator<char> > *,unsigned int,basic_string<char,char_traits<char>,allocator<char> > const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??4?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV01@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::operator=(basic_string<char,char_traits<char>,allocator<char> > const &); }
// Suppress this TU's non-retail copy of ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> >::basic_string(basic_string<char,char_traits<char>,allocator<char> > const &); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Vector_base<AsciiString,allocator<AsciiString> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??$max@I@_STL@@YAABIABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
#undef free

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int NameKeyType;

enum { MAX_TURRETS = 1 };


typedef _STL::vector<AsciiString> AsciiStringVec;
namespace _STL
{
template <> inline __declspec(noinline) __declspec(nothrow) _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(const allocator<AsciiString> &a)
	: _M_start(0), _M_finish(0), _M_end_of_storage(a, (AsciiString *)0)
{
}
}

struct ShadowInfoRef
{
	char m_pad00[8];
	Int m_08;
};

struct AsciiStringPair
{
	AsciiString first;
	AsciiString second;
};

struct ModelConditionInfo
{
	struct TurretInfo
	{
		NameKeyType m_turretAngleNameKey;
		NameKeyType m_turretPitchNameKey;
		Int m_unknown08[4];
	};

	char m_unknown000[0x58];
	AsciiString m_58;                       // +0x58
	char m_unknown05C[0x64 - 0x5C];
	_STL::vector<AsciiStringPair> m_64;     // +0x64
	char m_unknown070[0x74 - 0x70];
	AsciiString m_74;                       // +0x74
	char m_unknown078[0xD0 - 0x78];
	_STL::vector<TurretInfo> m_turrets;     // +0xD0
	ShadowInfoRef *m_shadowInfo;            // +0xDC
	Int m_shadowE0;                         // +0xE0
	Real m_shadowE4;                        // +0xE4
	Int m_shadowE8;                         // +0xE8
	Real m_shadowEC;                        // +0xEC
	Int m_shadowF0;                         // +0xF0
	Bool m_f4;                              // +0xF4
	Bool m_turretsValid;                    // +0xF5
};

static __declspec(noinline) Bool turretNamesDiffer(const ModelConditionInfo *a, const ModelConditionInfo *b)
{
	if (!a->m_turretsValid || !b->m_turretsValid)
		return true;
	for (Int i = 0; i < MAX_TURRETS; ++i)
	{
		if (i >= a->m_turrets.size() || i >= b->m_turrets.size())
			break;
		if (a->m_turrets[i].m_turretAngleNameKey != b->m_turrets[i].m_turretAngleNameKey ||
			a->m_turrets[i].m_turretPitchNameKey != b->m_turrets[i].m_turretPitchNameKey)
			return true;
	}
	return false;
}

// Rowed in Rva000B4A9F.cpp; its body is repeated here because retail keeps EDX
// across the call (cl knew the callee clobbers only EAX).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva000B4A9F
{
public:
	const char *rva000B4A9F();

private:
	char m_pad00[0x4C];
	const char *m_start4C;
	const char *m_finish50;
};

const char *Rva000B4A9F::rva000B4A9F()
{
	int d = m_finish50 - m_start4C;
	_ReadWriteBarrier();
	if ((d & ~3) == 0)
		return (const char *)&AsciiString::TheEmptyString;
	return m_start4C;
}

static __forceinline bool namesDiffer(const StringBase<char> &a, const StringBase<char> &b) { return a.compare(b) != 0; }

class Rva000B4AB5
{
public:
	const AsciiString *rva000B4AB5(unsigned index);
};

struct BfmeNarrowRecord00079C23
{
	BfmeNarrowRecord00079C23();
	BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23 &o);
	~BfmeNarrowRecord00079C23();
	BfmeNarrowRecord00079C23 &operator=(const BfmeNarrowRecord00079C23 &o);
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text0;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text1;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text2;
	UnsignedInt word0;
	UnsignedInt word1;
};


#define V1(p) virtual void p();
#define V2(p) V1(p##a) V1(p##b)
#define V4(p) V2(p##a) V2(p##b)
#define V8(p) V4(p##a) V4(p##b)
#define V16(p) V8(p##a) V8(p##b)
#define V32(p) V16(p##a) V16(p##b)
#define V64(p) V32(p##a) V32(p##b)

#include "../../../../GameEngine/Source/Common/debug.h"
extern Debug *theDebug;
bool bfmeRva000387C0();
template <typename T> Debug &operator<<(Debug &, const StringBase<T> &);
static __forceinline const char *formatText(const Debug::Format &f) { return (const char *)&f; }

#include "../WWMath/Matrix3DData.h"

class RenderObjClass;
class HAnimClass
{
public:
	virtual void Delete_This();
	Int m_numRefs;
	void Release_Ref() { if ((*(volatile Int *)&m_numRefs -= 1) == 0) Delete_This(); }
};

class RenderObjView
{
public:
	V16(a) V4(b) V1(c)
	virtual void Set_Transform(const Matrix3D &m);                    // +0x54
	V16(d) V4(e) V2(f) V1(g)
	virtual void Set_Animation(HAnimClass *anim, Real frame, Int mode); // +0xB4
	V2(h)
	virtual Int Get_Num_Sub_Objects();                                 // +0xC0
	virtual const char *Get_Sub_Object_Name(Int index);                // +0xC4
	V32(i) V4(j)
	virtual void Set_ObjectScale158(void *data, Int mode);             // +0x158
	V8(k) V4(l) V1(m)
	virtual Int Has_Something190();                                     // +0x190
	V8(n) V4(o)
	virtual void slot1C4(Int on);                                       // +0x1C4
	V1(q)
	virtual void slot1CC(Int on);                                       // +0x1CC
	V1(r)
	virtual void slot1D4(Int value);                                    // +0x1D4
};

class Rva0013101E;
class RenderAsset
{
public:
	static RenderObjClass *CreateRenderObj(const char *name, Real scale, const Rva0013101E &a, AsciiStringVec &b, AsciiStringVec &c, AsciiStringVec &d);
};
RenderObjClass *Rva00137364CreateRenderObj(const char *name, Real scale, const Rva0013101E &a);
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/AnimationAsset.h"

// --- rowed callees, declared under their ledger spellings -------------------
class Rva002793AF { public: void rva002793AF(const AsciiString &name); };
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000BC9B1.h"
void Rva000B5179Apply(void *state, void *arg, void *renderObject);
class Rva000788D3FloatField { public: Real get() const; };
struct Rva000C3886Range;
struct Rva000C3886Obj;
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000C3886.h"
struct Rva00079EA1Element { int m_00; };
namespace _STL
{
template <> Rva00079EA1Element *vector<Rva00079EA1Element, allocator<Rva00079EA1Element> >::erase(Rva00079EA1Element *first, Rva00079EA1Element *last);
}
class Rva000B3348 { public: void rva000B3348(Matrix3D *transform); };
class W3DModelDraw { public: void rva000B7C24(); };
struct SrcArg000C18E3;
class Rva000C18E3 { public: void rva000C18E3(SrcArg000C18E3 *arg); };
class Rva00084206Track { public: char m_pad00[0x38]; void *m_drawable38; };
class Rva00084B18RenderObj;
class Rva00084C05System { public: Rva00084206Track *bind(Rva00084B18RenderObj *robj, Real length, const char *texture, const char *a, const char *b); };
class TerrainTracksRenderObjClassSystem;
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;

class Drawable;
class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_ShadowName;       // +0x00
		Int m_unknown04;
		Int m_type;                     // +0x08
		Real m_sizeX;                   // +0x0C
		Real m_sizeY;                   // +0x10
		Real m_offsetX;                 // +0x14
		Real m_offsetY;                 // +0x18
		Real m_1C;                      // +0x1C
		Real m_20;                      // +0x20
		unsigned char m_24;
		unsigned char m_25;
		unsigned char m_26;
	};
	void setOpacity(Int value);
	void setColor(Int value);
	char m_pad00[4];
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[0x30 - 6];
	unsigned char m_30;
	void enableShadowRender(Bool b) { m_04 = b; }
	void enableShadowInvisible(Bool b) { m_05 = b; }
	void setFlag30(unsigned char b) { m_30 = b; }
};
class Rva00330A37 { public: void rva00330A37(Int a, Int b, Int c, Int d, Int e, Int f, Int g, Int h); };
class Rva000B22B3StateView { public: int rva000B22B3() const; };
class W3DShadowManager { public: Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *info, Drawable *draw); };
extern W3DShadowManager *TheW3DShadowManager;
class Rva000B4653 { public: void *rva000B4653(Int index); };
class Rva0033A5F4 { public: void rva0033A5F4(Int *a, Real *b, Int *c, Real *d, Int *e); };
class Rva000B3E82 { public: void rva000B3E82(unsigned char value); };
#include "../../../../GameEngine/Include/Common/Rva00270260.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView
{
	char m_pad000[0x134];
	UnsignedInt m_134;
	char m_pad138[0x13C - 0x138];
	Bool m_13C;
};
extern Real BfmeClientFramesPerMillisecond;

class W3DDisplayView
{
public:
	V2(a)
	virtual void addRenderObject(RenderObjClass *robj);               // +0x08
};
// VA 0x00DE1B34 is the defined ?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A; this
// unit calls it through its W3DDisplayView view.
class RTS3DScene;
class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

struct ThingTemplateView
{
	const AsciiString &getName() const { return m_name; }
	char m_pad000[0x64];
	AsciiString m_name;                     // +0x64
	char m_pad068[0x90 - 0x68];
	AsciiString m_shadowTexture;            // +0x90
	char m_pad094[0x109 - 0x94];
	unsigned char m_109;                    // +0x109
	char m_pad10A[0x4E8 - 0x10A];
	Real m_shadowSizeX;                     // +0x4E8
	Real m_shadowSizeY;                     // +0x4EC
	Real m_shadowOffsetX;                   // +0x4F0
	Real m_shadowOffsetY;                   // +0x4F4
	char m_pad4F8[0x500 - 0x4F8];
	Real m_shadow500;                       // +0x500
	Real m_shadow504;                       // +0x504
	char m_pad508[0x5E2 - 0x508];
	unsigned short m_shadowType;            // +0x5E2
	char m_pad5E4[0x5ED - 0x5E4];
	unsigned char m_5ED;
	unsigned char m_5EE;
	unsigned char m_5EF;
};

struct DrawableView
{
	ThingTemplateView *getTemplate() const { return m_template; }
	char m_pad000[4];
	ThingTemplateView *m_template;          // +0x004
	char m_pad008[0xA8 - 8];
	Int m_A8;                               // +0x0A8
	char m_pad0AC[0x114 - 0xAC];
	UnsignedInt m_114;                      // +0x114
	char m_pad118[0x248 - 0x118];
	char m_248[0x26C - 0x248];              // +0x248
	UnsignedInt m_26C;                      // +0x26C
	char m_pad270[0x364 - 0x270];
	Int m_364;                              // +0x364
};

struct W3DScriptedModelDrawModuleDataView
{
	char m_pad000[0x30];
	char m_30[0x3C - 0x30];                 // +0x30
	AsciiString m_trackTexture;             // +0x3C
	char m_pad040[0x44 - 0x40];
	AsciiString m_44;                       // +0x44
	AsciiString m_48;                       // +0x48
	char m_pad04C[0x70 - 0x4C];
	_STL::vector<BfmeNarrowRecord00079C23> m_records70;   // +0x70
	struct Elem14 { char m_data[0x14]; };
	_STL::vector<Elem14> m_7C;              // +0x7C
	char m_pad088[0x8C - 0x88];
	BfmeNarrowRecord00079C23 m_record8C;    // +0x8C
	char m_pad0B8[0x128 - 0xB8];
	Bool m_128;
	unsigned char m_129;
	char m_pad12A;
	Bool m_12B;
	char m_pad12C[0x138 - 0x12C];
	Bool m_138;
	char m_pad139[0x15C - 0x139];
	unsigned char m_15C;
	char m_pad15D[0x15F - 0x15D];
	Bool m_15F;
};

class W3DScriptedModelDrawSub0C
{
public:
	V16(a) V8(b) V4(c) V1(d)
	virtual void slot74();                                              // +0x74
};

class W3DScriptedModelDraw
{
public:
	V16(a)
	virtual void setHidden40(Bool hidden);                              // +0x40
	V2(b) V1(c)
	virtual void setTerrainDecal50(Int value);                          // +0x50
	V32(d) V8(e) V2(f)
	virtual void slotFC();                                              // +0xFC

	AsciiString rva000C2E3A(const AsciiString &modelName);
	void rva000C2CBF(Int count, AsciiStringVec *originals, AsciiStringVec *replacements);
	void rva000B5FE6();
	Bool setModelState(const ModelConditionInfo *newState, Bool forceReset, void *arg);

	const W3DScriptedModelDrawModuleDataView *getModuleData() const { return m_moduleData; }
	const W3DScriptedModelDrawModuleDataView *getW3DScriptedModelDrawModuleData() const { return getModuleData(); }

	const W3DScriptedModelDrawModuleDataView *m_moduleData;   // +0x04
	DrawableView *m_drawable;                            // +0x08
	W3DScriptedModelDrawSub0C m_sub0C;                   // +0x0C
	char m_pad010[0x14 - 0x10];
	const ModelConditionInfo *m_curState;                // +0x14
	char m_pad018[0x28 - 0x18];
	char m_28[0x38 - 0x28];                              // +0x28
	_STL::vector<AsciiStringPair> m_38;                  // +0x38
	char m_pad044[0x48 - 0x44];
	Bool m_48;
	Bool m_49;
	Bool m_4A;
	Bool m_4B;
	char m_pad04C[4];
	RenderObjClass *m_renderObject;                      // +0x50
	AsciiString m_54;                                    // +0x54
	Shadow *m_shadow;                                    // +0x58
	char m_pad05C[0x60 - 0x5C];
	Rva00084206Track *m_track;                           // +0x60
	char m_pad064[0x68 - 0x64];
	_STL::vector<Rva00079EA1Element> m_68;               // +0x68
	_STL::vector<Rva00079EA1Element> m_74;               // +0x74
	char m_pad080[0xBC - 0x80];
	Int m_BC;
	Int m_C0;
	char m_pad0C4[0x170 - 0xC4];
	_STL::vector<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > m_170; // +0x170
	char m_pad17C[0x1C9 - 0x17C];
	Bool m_1C9;
	char m_pad1CA[0x2D8 - 0x1CA];
	Bool m_2D8;
	Bool m_2D9;
};

Bool W3DScriptedModelDraw::setModelState(const ModelConditionInfo *newState, Bool forceReset, void *arg)
{
	if ((1 ? (getW3DScriptedModelDrawModuleData()->m_15F && m_BC != 0) : (getW3DScriptedModelDrawModuleData()->m_15F && m_BC != 0)))
		return false;
	if (newState == 0)
		return false;

	((Rva002793AF *)m_drawable)->rva002793AF(newState->m_74);
	if (m_curState == 0 || ((const StringBase<char> &)newState->m_58).compareNoCase((const StringBase<char> &)m_curState->m_58) != 0)
		m_2D8 = true;

	Bool indexChanged = m_BC != m_C0;
	m_BC = m_C0;
	m_2D9 = true;

	if (m_curState != 0 && m_curState == newState && !indexChanged && !forceReset)
		return false;

	if (!(m_drawable->m_114 & 8))
		m_48 = true;

	((Rva000BC9B1 *)this)->rva000BC9B1(true);
	Rva000B5179Apply((void *)newState, arg, m_renderObject);

	Bool newHasHideShow = newState->m_64.size() > 0u;
	Bool curHasHideShow = m_curState ? m_curState->m_64.size() > 0u : false;

	AsciiString modelName;
	if (m_curState != 0
		&& !namesDiffer(*(const StringBase<char> *)((Rva000B4A9F *)newState)->rva000B4A9F(), *(const StringBase<char> *)((Rva000B4A9F *)m_curState)->rva000B4A9F())
		&& !indexChanged
		&& !newHasHideShow
		&& !curHasHideShow
		&& !turretNamesDiffer(newState, m_curState)
		&& !forceReset)
	{
		void *last = (void *)m_drawable->m_364;
		Rva000C3886Range *range = (Rva000C3886Range *)getW3DScriptedModelDrawModuleData()->m_30;
		((Rva000C3886 *)newState)->rva000C3886(m_renderObject, ((const Rva000788D3FloatField *)m_drawable)->get(), range, (Rva000C3886Obj *)arg, last);
	}
	else
	{
		if (!newState->m_f4)
			m_68.clear();

		Bool hadSubObjects = false;
		if (m_renderObject)
			hadSubObjects = ((RenderObjView *)m_renderObject)->Has_Something190() != 0;

		Matrix3D transform;
		((Rva000B3348 *)this)->rva000B3348(&transform);

		DrawableView *draw = m_drawable;
		modelName = rva000C2E3A(*((Rva000B4AB5 *)newState)->rva000B4AB5(draw->m_364));
		Int numReplacements = getW3DScriptedModelDrawModuleData()->m_7C.size();
		Int numRecords = getW3DScriptedModelDrawModuleData()->m_records70.size();
		((StringBase<char> &)m_54).set("");

		if (((const StringBase<char> *)((Rva000B4AB5 *)newState)->rva000B4AB5(draw->m_364))->isEmpty())
		{
			m_renderObject = 0;
		}
		else if ((Bool)((m_drawable->m_26C >> 31) & 1) && !getW3DScriptedModelDrawModuleData()->m_record8C.text0.empty())
		{
			AsciiStringVec originals;
			AsciiStringVec replacements;
			AsciiStringVec extras;
			BfmeNarrowRecord00079C23 record(getW3DScriptedModelDrawModuleData()->m_record8C);
			((StringBase<char> &)m_54).set(record.text0.c_str());
			originals.push_back(AsciiString(record.text0.c_str()));
			if (!record.text1.empty())
				replacements.push_back(AsciiString(record.text1.c_str()));
			m_renderObject = RenderAsset::CreateRenderObj(modelName.str(), ((const Rva000788D3FloatField *)draw)->get(),
				*(const Rva0013101E *)m_28, extras, originals, replacements);
		}
		else if (newHasHideShow || m_38.begin() != m_38.end())
		{
			AsciiStringVec replacements;
			AsciiStringVec originals;
			for (const AsciiStringPair *asciiStringPair = m_38.begin(); asciiStringPair != m_38.end(); ++asciiStringPair)
			{
				originals.push_back(asciiStringPair->first);
				replacements.push_back(asciiStringPair->second);
			}
			for (const AsciiStringPair *q = newState->m_64.begin(); q != newState->m_64.end(); ++q)
			{
				const char *name = q->first.str();
				AsciiString *end = originals.end();
				if (_STL::find(originals.begin(), end, name) == end)
				{
					originals.push_back(q->first);
					replacements.push_back(q->second);
				}
			}
			{
				AsciiStringVec extras;
				m_renderObject = RenderAsset::CreateRenderObj(modelName.str(), ((const Rva000788D3FloatField *)draw)->get(),
					*(const Rva0013101E *)m_28, originals, replacements, extras);
			}
			if (m_renderObject == 0 && bfmeRva000387C0())
			{
				Debug::SkipNext(true);
				theDebug->SkipNext();
				const char *name = modelName.str();
				Debug &report = theDebug->CrashBegin(0, 0, 0);
				report << formatText(Debug::Format("*** ASSET ERROR: Model %s not found!\n", name));
				report.CrashDone(2);
			}
		}
		else if (numReplacements != 0)
		{
			AsciiStringVec originals;
			AsciiStringVec replacements;
			rva000C2CBF(0xFF, &replacements, &originals);
			{
				AsciiStringVec extras;
				m_renderObject = RenderAsset::CreateRenderObj(modelName.str(), ((const Rva000788D3FloatField *)draw)->get(),
					*(const Rva0013101E *)m_28, replacements, originals, extras);
			}
			if (m_renderObject == 0 && bfmeRva000387C0())
			{
				Debug::SkipNext(true);
				theDebug->SkipNext();
				const char *name = modelName.str();
				Debug &report = theDebug->CrashBegin(0, 0, 0);
				report << formatText(Debug::Format("*** ASSET ERROR: Model %s not found!\n", name));
				report.CrashDone(2);
			}
		}
		else if (numRecords > 0)
		{
			Bool found;
			*(volatile Bool *)&found = false;
			BfmeNarrowRecord00079C23 record;
			for (const BfmeNarrowRecord00079C23 *it = getW3DScriptedModelDrawModuleData()->m_records70.begin(); it != getW3DScriptedModelDrawModuleData()->m_records70.end(); ++it)
			{
				BfmeNarrowRecord00079C23 candidate(*it);
				if (((GlobalDataView *)TheWritableGlobalData)->m_134 == candidate.word0)
				{
					found = true;
					record = candidate;
					break;
				}
			}
			AsciiStringVec originals;
			AsciiStringVec replacements;
			AsciiStringVec extras;
			((StringBase<char> &)m_54).set(record.text0.c_str());
			originals.push_back(AsciiString(record.text0.c_str()));
			if (!record.text1.empty())
				replacements.push_back(AsciiString(record.text1.c_str()));
			if (found)
				m_renderObject = RenderAsset::CreateRenderObj(modelName.str(), ((const Rva000788D3FloatField *)draw)->get(),
					*(const Rva0013101E *)m_28, extras, originals, replacements);
			else
				m_renderObject = Rva00137364CreateRenderObj(modelName.str(), ((const Rva000788D3FloatField *)draw)->get(),
					*(const Rva0013101E *)m_28);
		}
		else
		{
			m_renderObject = Rva00137364CreateRenderObj(modelName.str(), ((const Rva000788D3FloatField *)draw)->get(),
				*(const Rva0013101E *)m_28);
			if (m_renderObject == 0 && bfmeRva000387C0())
			{
				Debug::SkipNext(true);
				theDebug->SkipNext();
				(theDebug->CrashBegin(0, 0, 0) << "ASSET ERROR: Model " << (const StringBase<char> &)modelName
					<< " not found in drawable " << (const StringBase<char> &)draw->getTemplate()->getName() << "!").CrashDone(2);
			}
		}

		if (m_renderObject)
		{
			_STL::vector<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > &batNames = m_170;
			batNames.erase(batNames.begin(), batNames.end());
			for (Int i = 0; i < ((RenderObjView *)m_renderObject)->Get_Num_Sub_Objects(); ++i)
			{
				const char *subName = ((RenderObjView *)m_renderObject)->Get_Sub_Object_Name(i);
				if (subName && !::_strnicmp(subName, "BAT_", 4))
					batNames.push_back(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >(subName));
			}
		}

		((W3DModelDraw *)this)->rva000B7C24();
		void *lastObject = (void *)draw->m_364;
		Rva000C3886Range *stateRange = (Rva000C3886Range *)getW3DScriptedModelDrawModuleData()->m_30;
		((Rva000C3886 *)newState)->rva000C3886(m_renderObject, ((const Rva000788D3FloatField *)draw)->get(),
			stateRange, (Rva000C3886Obj *)arg, lastObject);
		((Rva000C18E3 *)this)->rva000C18E3((SrcArg000C18E3 *)arg);

		ThingTemplateView *thingTemplateView = draw->m_template;
		if (thingTemplateView && m_renderObject && (thingTemplateView->m_109 & 5))
			((RenderObjView *)m_renderObject)->slot1C4(1);

		RenderObjClass *robj = m_renderObject;
		if (robj && ((GlobalDataView *)TheWritableGlobalData)->m_13C && m_track == 0 && TheTerrainTracksRenderObjClassSystem
			&& !((const StringBase<char> &)getW3DScriptedModelDrawModuleData()->m_trackTexture).isEmpty())
		{
			m_track = ((Rva00084C05System *)TheTerrainTracksRenderObjClassSystem)->bind((Rva00084B18RenderObj *)robj, 10.0f,
				((const StringBase<char> &)getW3DScriptedModelDrawModuleData()->m_trackTexture).str(),
				((const StringBase<char> &)getW3DScriptedModelDrawModuleData()->m_44).str(),
				((const StringBase<char> &)getW3DScriptedModelDrawModuleData()->m_48).str());
			if (m_track)
				m_track->m_drawable38 = draw;
		}

		ShadowInfoRef *shadowInfo = newState->m_shadowInfo;
		if (shadowInfo && shadowInfo->m_08)
		{
			robj = m_renderObject;
			if (robj && TheW3DShadowManager && !getW3DScriptedModelDrawModuleData()->m_12B)
			{
				m_shadow = TheW3DShadowManager->addShadow(robj, (Shadow::ShadowTypeInfo *)shadowInfo, (Drawable *)draw);
				if (m_shadow)
				{
					m_shadow->enableShadowInvisible(m_49);
					m_shadow->enableShadowRender(m_4A && !m_4B);
					m_shadow->m_30 = 1;
					typedef void (Rva00330A37::*FadeFrames)(UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt);
					if ((unsigned char)((const Rva000B22B3StateView*)m_shadow)->rva000B22B3())
					{
						m_shadow->setOpacity(newState->m_shadowE0);
						(((Rva00330A37 *)m_shadow)->*(FadeFrames)&Rva00330A37::rva00330A37)(0, -1, newState->m_shadowE0,
							(UnsignedInt)(BfmeClientFramesPerMillisecond * newState->m_shadowE4), newState->m_shadowE8, -1,
							(UnsignedInt)(BfmeClientFramesPerMillisecond * newState->m_shadowEC), newState->m_shadowF0);
					}
					else
					{
						m_shadow->setOpacity(newState->m_shadowE8);
					}
				}
			}
		}
		else if (m_renderObject && TheW3DShadowManager && thingTemplateView && thingTemplateView->m_shadowType && !getW3DScriptedModelDrawModuleData()->m_12B)
		{
			Shadow::ShadowTypeInfo info;
			info.m_ShadowName = thingTemplateView->m_shadowTexture;
			info.m_type = thingTemplateView->m_shadowType;
			info.m_sizeX = thingTemplateView->m_shadowSizeX;
			info.m_sizeY = thingTemplateView->m_shadowSizeY;
			info.m_offsetX = thingTemplateView->m_shadowOffsetX;
			info.m_offsetY = thingTemplateView->m_shadowOffsetY;
			info.m_1C = thingTemplateView->m_shadow500;
			info.m_24 = thingTemplateView->m_5ED;
			info.m_25 = 0;
			info.m_26 = 1;
			info.m_20 = thingTemplateView->m_shadow504;
			m_shadow = TheW3DShadowManager->addShadow(m_renderObject, &info, (Drawable *)draw);
			if (m_shadow)
			{
				m_shadow->enableShadowInvisible(m_49);
				m_shadow->enableShadowRender(m_4A && !m_4B);
				m_shadow->setFlag30(thingTemplateView->m_5EF);
				if (thingTemplateView->m_5EE)
					m_shadow->setColor((Int)((Rva000B4653 *)m_28)->rva000B4653(0));
				Int opacity;
				Real fadeIn;
				Int opacity2;
				Real fadeOut;
				Int last;
				((Rva0033A5F4 *)thingTemplateView)->rva0033A5F4(&opacity, &fadeIn, &opacity2, &fadeOut, &last);
				typedef void (Rva00330A37::*FadeFrames)(UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt);
				if ((unsigned char)((const Rva000B22B3StateView*)m_shadow)->rva000B22B3())
				{
					m_shadow->setOpacity(opacity);
					(((Rva00330A37 *)m_shadow)->*(FadeFrames)&Rva00330A37::rva00330A37)(0, -1, opacity, (UnsignedInt)(fadeIn * BfmeClientFramesPerMillisecond), opacity2, -1,
						(UnsignedInt)(fadeOut * BfmeClientFramesPerMillisecond), last);
				}
				else
				{
					m_shadow->setOpacity(opacity2);
				}
			}
		}

		if (m_renderObject && thingTemplateView)
		{
			if (getW3DScriptedModelDrawModuleData()->m_128)
			{
				((RenderObjView *)m_renderObject)->slot1CC(1);
				Int setting = getW3DScriptedModelDrawModuleData()->m_129;
				((RenderObjView *)m_renderObject)->slot1D4(setting);
			}
			rva000B5FE6();
			((Rva000B3E82 *)this)->rva000B3E82(getW3DScriptedModelDrawModuleData()->m_15C);
			((W3DDisplayView *)W3DDisplay::m_3DScene)->addRenderObject(m_renderObject);
			((RenderObjView *)m_renderObject)->Set_ObjectScale158(draw->m_248, 0);
			Int decal = draw->m_A8;
			setTerrainDecal50(decal);
			if (((Rva00270260 *)draw)->rva00270260() || hadSubObjects)
			{
				setHidden40(true);
				m_4A = false;
			}
			((RenderObjView *)m_renderObject)->Set_Transform(transform);
			slotFC();
			if (getW3DScriptedModelDrawModuleData()->m_138)
			{
				AsciiString animName;
				animName.format("%s.%s", modelName.str(), modelName.str());
				HAnimClass *anim = AnimationAsset::GetAnim(animName.str());
				if (anim)
				{
					((RenderObjView *)m_renderObject)->Set_Animation(anim, 0.0f, 1);
					if (--anim->m_numRefs == 0)
						anim->Delete_This();
				}
			}
		}
	}

	m_1C9 = true;
	m_curState = newState;
	if (!m_68.empty() && !m_74.empty())
		m_sub0C.slot74();
	return true;
}
