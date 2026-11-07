// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0StructureToppleUpdateModuleData@@QAE@XZ, retail 0x00257A5E, 256 bytes.
// Interim (crash-prevention, 2026-11-07): the class derives from the canonical
// ModuleData, so this constructor installs ??_7StructureToppleUpdateModuleData@@6B@ (retail 0x00BF43A8,
// 31 ModuleData slots) instead of a one-byte placeholder, and the unwind destroys
// the base through ModuleData's rowed destructor 0x0049B47C. ModuleFactory.cpp,
// first in link order, still emits a Zero Hour 8-slot copy of that name beside
// the rowed deleting destructor it owns (0x00257B5E, displaced in tu_map), so the
// real link's vtable bridge places retail's table until a TU approval lets the
// ??_G leave ModuleFactory.cpp (LINK-625).
// StructureTopple data ctor. Donor is ZH
// StructureToppleUpdate.h (same member order and values) with BFME2
// changes: DieMuxData member at +8 constructed through its rowed init at
// 0x004CE534, an extra float at +0x48 (0.06), the damage-flags word as -1
// at +0x4C, and an extra float at +0xB8. Total size 0xBC matches the
// friend_newModuleData `new 0xBC`.
//
// Layout: ModuleData +0..+7, DieMuxData +8 (0x30, opaque: retail issues no
// member-construction calls for it, only init), delays +0x38/+0x3C,
// integrity +0x40 (0.1), decay +0x44, unk48 +0x48 (0.06), unk4C +0x4C (-1
// via the or-idiom), five FXList nulls +0x50..+0x60, crushing weapon
// string +0x64 (zero-init then set("")), burst delays +0x68/+0x6C,
// OCLVec m_ocls[3] +0x70 (3 12B vectors through ehvecctor 0x629512; the
// element setup/teardown immediates are DIR32 slots the patcher copies
// from retail per the CrushDie precedent), oclCount triple +0x94 (1,1,1
// via unrolled pointer stores), fxbones +0xA0 (8B FXBoneInfo, E16 base
// plus erase-clear through rowed 0x207F0D), angleFX +0xAC (8B
// AngleFXInfo, E16 base plus erase-clear through the Pod8 alias at
// 0x3FA4DB), trailer float +0xB8.
//
// Schedule notes: the DieMux init call sits at the member-construction
// position, so the member is modeled with an inline default ctor that
// forwards to init (no separate construction call exists in retail). The
// scalar stores, the weapon set, the oclCount stores and the two erases
// are body statements (ProductionUpdate erase-begin-end idiom for both;
// named reference for fxbones to home the base, direct for angleFX).
// The ModuleData base (out-of-line destructor) carries unwindability for
// EH states 0/1/4; the vector bases arm none.

// Preserve STLport's out-of-line pointer-copy wrapper.
#include "../../../../../../vendor/stlport/stl/_algobase.h"
#include <vector>
// Suppress this TU's non-retail copy of ??1?$vector@UFXBoneInfo@@V?$allocator@UFXBoneInfo@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct FXBoneInfo;
namespace _STL { template <> vector<FXBoneInfo,allocator<FXBoneInfo> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct AngleFXInfo;
namespace _STL { template <> vector<AngleFXInfo,allocator<AngleFXInfo> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$vector@PBVObjectCreationList@@V?$allocator@PBVObjectCreationList@@@_STL@@@_STL@@QAE@X:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ObjectCreationList;
namespace _STL { template <> vector<ObjectCreationList const *,allocator<ObjectCreationList const *> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@PBVObjectCreationList@@V?$allocator@PBVObjectCreationList@@@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ObjectCreationList;
namespace _STL { template <> _Vector_base<ObjectCreationList const *,allocator<ObjectCreationList const *> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct AngleFXInfo;
namespace _STL { template <> _Vector_base<AngleFXInfo,allocator<AngleFXInfo> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UFXBoneInfo@@V?$allocator@UFXBoneInfo@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct FXBoneInfo;
namespace _STL { template <> _Vector_base<FXBoneInfo,allocator<FXBoneInfo> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UFXBoneInfo@@@_STL@@QBEXPAUFXBoneInfo@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct FXBoneInfo;
namespace _STL { template <> void allocator<FXBoneInfo>::deallocate(FXBoneInfo *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVObjectCreationList@@@_STL@@QBEXPAPBVObjectCreationList@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ObjectCreationList;
namespace _STL { template <> void allocator<ObjectCreationList const *>::deallocate(ObjectCreationList const * *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UAngleFXInfo@@@_STL@@QBEXPAUAngleFXInfo@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct AngleFXInfo;
namespace _STL { template <> void allocator<AngleFXInfo>::deallocate(AngleFXInfo *, size_t) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct FXBoneInfo
{
	~FXBoneInfo();
	AsciiString m_boneName;
	const void *m_particleSystemTemplate;
};

struct AngleFXInfo
{
	float m_angle;
	const void *m_fxList;
};

class ObjectCreationList;

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

enum
{
	ST_PHASE_COUNT = 3,
};

#include "../../../../Include/Common/ModuleData.h"

// The native angle-vector erase calls the existing 8-byte range-erase
// owner at 0x003FA4DB. Bind that call to its rowed spelling; the AngleFXInfo
// specialization emitted elsewhere does not reproduce that body.
struct BfmePod8 { int words[2]; };

namespace _STL
{
template <> BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *, BfmePod8 *);
template <> __declspec(dllimport) __forceinline AngleFXInfo *
vector<AngleFXInfo>::erase(AngleFXInfo *first, AngleFXInfo *last)
{
	return (AngleFXInfo *)((vector<BfmePod8> *)this)->erase(
		(BfmePod8 *)first, (BfmePod8 *)last);
}

// Declared-only explicit specializations: keep the calls external (the
// FXBoneInfo erase resolves to its rowed true name; the two _Vector_base
// ctors and the AngleFXInfo erase resolve through twin/alias pins) and
// throwing (retail arms EH states around the later calls only).
template <>
_Vector_base<FXBoneInfo, allocator<FXBoneInfo> >::_Vector_base(
	const allocator<FXBoneInfo> &storage) throw();
template <>
_Vector_base<AngleFXInfo, allocator<AngleFXInfo> >::_Vector_base(
	const allocator<AngleFXInfo> &storage) throw();
template <>
vector<FXBoneInfo, allocator<FXBoneInfo> >::iterator
vector<FXBoneInfo, allocator<FXBoneInfo> >::erase(
	vector<FXBoneInfo, allocator<FXBoneInfo> >::iterator first,
	vector<FXBoneInfo, allocator<FXBoneInfo> >::iterator last);
// Retail range erase calls the pointer-copy wrapper out of line.
template <> __declspec(noinline) inline AngleFXInfo *
__copy_ptrs<AngleFXInfo *, AngleFXInfo *>(AngleFXInfo *first, AngleFXInfo *last,
    AngleFXInfo *result, const __false_type &)
{
    return __copy(first, last, result, random_access_iterator_tag(), (int *)0);
}

}

class StructureToppleUpdateModuleData : public ModuleData
{
public:
	StructureToppleUpdateModuleData();
	virtual ~StructureToppleUpdateModuleData();

private:
	DieMuxData m_dieMuxData; // +8
	Int m_minToppleDelay; // +0x38
	Int m_maxToppleDelay; // +0x3C
	float m_structuralIntegrity; // +0x40
	float m_structuralDecay; // +0x44
	float m_toppleAccelerationFactor; // +0x48
	Int m_damageFXTypes; // +0x4C
	void *m_toppleStartFXList; // +0x50
	void *m_toppleDelayFXList; // +0x54
	void *m_toppleDoneFXList; // +0x58
	void *m_toppleFXList; // +0x5C
	void *m_crushingFXList; // +0x60
	AsciiString m_crushingWeaponName; // +0x64
	Int m_minToppleBurstDelay; // +0x68
	Int m_maxToppleBurstDelay; // +0x6C
	_STL::vector<const ObjectCreationList *,
		_STL::allocator<const ObjectCreationList *> > m_ocls[3]; // +0x70
	Int m_oclCount[3]; // +0x94
	_STL::vector<FXBoneInfo, _STL::allocator<FXBoneInfo> > m_fxbones; // +0xA0
	_STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> > m_angleFX; // +0xAC
	float m_forceToppleAngle; // +0xB8
};

// ??0StructureToppleUpdateModuleData@@QAE@XZ @0x00257A5E
inline StructureToppleUpdateModuleData::StructureToppleUpdateModuleData()
	: m_crushingWeaponName()
{
	m_minToppleDelay = 0;
	m_maxToppleDelay = 0;
	m_structuralIntegrity = 0.1f;
	m_damageFXTypes = -1;
	m_minToppleBurstDelay = 0;
	m_maxToppleBurstDelay = 0;
	m_structuralDecay = 0.0f;
	m_toppleStartFXList = 0;
	m_toppleDelayFXList = 0;
	m_toppleFXList = 0;
	m_toppleDoneFXList = 0;
	m_crushingFXList = 0;
	m_crushingWeaponName.set("");
	m_toppleAccelerationFactor = 0.06f;
	m_forceToppleAngle = -9.87654f;
	for (int i = 0; i < ST_PHASE_COUNT; ++i)
		m_oclCount[i] = 1;
	_STL::vector<FXBoneInfo, _STL::allocator<FXBoneInfo> > &bones = m_fxbones;
	bones.erase(bones.begin(), bones.end());
	_STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> > &angleBones = m_angleFX;
	angleBones.erase(angleBones.begin(), angleBones.end());
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeStructureToppleUpdateModuleDataInlineAnchor@@YAXPAVStructureToppleUpdateModuleData@@@Z absent-from-retail
void _bfmeStructureToppleUpdateModuleDataInlineAnchor(StructureToppleUpdateModuleData *structureToppleUpdateModuleData)
{
    structureToppleUpdateModuleData->StructureToppleUpdateModuleData::StructureToppleUpdateModuleData();
}
#pragma inline_depth()
