// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0DynamicPortalBehaviourModuleData@@QAE@XZ, retail 0x0046142A (261 bytes).
// DynamicPortal wall-portal data over the rowed Rva00253487Base base
// ctor (0x253487, 0x118 base): NumberOfBones at +0x118 is zero,
// BonePrefix at +0x11C is an inline-null AsciiString cleared through the
// folded clear at 0x00036410 (Image clear-after-null precedent),
// WayPoint at +0x120 is an 8B-element vector built through the folded
// Vector_base at 0x00211E58 and cleared through erase at 0x003FA4DB
// (OCL clear-lowers-to-erase precedent). Link at +0x12C holds 12B owner
// records: native cleanup78A8E5 and companion destructor461602 call the
// verified Link vector destructor4613EB (element clearer3F29F8). WallBoundsMesh at +0x138 copies TheEmptyString, GenerateNow
// at +0x13C and AllowEnemies at +0x13D are false, AboveWall at +0x140 is -1,
// TopAttackPos at +0x144 is zero, TopAttackRadius at +0x150 is 5.0f,
// ActivationDelaySeconds at +0x154 is 0.0f, and DestroyedDamageTimeoutMS at
// +0x158 builds through the opaque 0x3623E5 pin with one 28B FixedStorage
// temp from the prototype at 0x00DFEFA4 fed through applyFilter at
// 0x00362120 (CallHelp single-storage precedent). Own table 0x00C42A38
// anchors these fields; the DynamicPortalBehaviour data factory at 0x0024B4B3
// news 0x15C with this ctor pinned as sole caller. The implicit vtable
// store targets 0x00C42930; base and derived dtors stay declared-only.
// The native call at +0xA8 targets StringBase<char>::set(copy), not the
// C-string assignment wrapper at 0x65B8. Its argument is the empty
// AsciiString object at 0x00DE0878, not a C-string literal. Scalar defaults ride the
// init-list (the init region schedules ahead of the implicit filter
// construction, which is how those stores land before the filter call with
// no cross-call motion); TopAttackPos stays a body statement through a
// pointer local, which is what emits retail's lea-plus-indirect zero stores.
#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

// 8B INI-list element (erase at 0x3FA4DB is the 8B-element build);
// WayPoint parser46133B is unclaimed, so its two scalar fields stay neutral.
struct DynamicPortalWayPoint
{
	int m_first;
	int m_second;
};

// Same partial element layout as the verified DynamicPortalLinkVector provider.
// Destruction proves ownership at +0; the remaining two fields stay neutral.
#include "../../../../Include/GameLogic/DynamicPortalLink.h"
namespace _STL {
template <> vector<DynamicPortalLink, allocator<DynamicPortalLink> >::~vector();
}

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_timeoutMs;
};

// Coord3D: shared header/view; no private copy.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class DynamicPortalBehaviourModuleData : public Rva00253487Base
{
public:
	DynamicPortalBehaviourModuleData();
	virtual ~DynamicPortalBehaviourModuleData();

private:
	int m_numberOfBones; // +0x118, NumberOfBones
	AsciiString m_bonePrefix; // +0x11C, BonePrefix
	_STL::vector<DynamicPortalWayPoint> m_wayPoint; // +0x120, WayPoint
	_STL::vector<DynamicPortalLink> m_link; // +0x12C, Link
	AsciiString m_wallBoundsMesh; // +0x138, WallBoundsMesh
	bool m_generateNow; // +0x13C, GenerateNow
	bool m_allowEnemies; // +0x13D, AllowEnemies
	unsigned char m_pad13E[2];
	int m_aboveWall; // +0x140, AboveWall
	Coord3D m_topAttackPos; // +0x144, TopAttackPos
	float m_topAttackRadius; // +0x150, TopAttackRadius
	float m_activationDelaySeconds; // +0x154, ActivationDelaySeconds
	Rva003623E5Filter m_destroyedDamageTimeout; // +0x158, DestroyedDamageTimeoutMS
};

// ??0DynamicPortalBehaviourModuleData@@QAE@XZ @0x0046142A
DynamicPortalBehaviourModuleData::DynamicPortalBehaviourModuleData() :
	Rva00253487Base(),
	m_numberOfBones(0),
	m_generateNow(false),
	m_allowEnemies(false),
	m_aboveWall(-1),
	m_topAttackRadius(5.0f),
	m_activationDelaySeconds(0.0f)
{
	m_wallBoundsMesh.setCopyInline(AsciiString::TheEmptyString);
	m_bonePrefix.clear();
	m_wayPoint.clear();
	Coord3D *topAttackPos = &m_topAttackPos;
	topAttackPos->x = 0.0f;
	topAttackPos->y = 0.0f;
	topAttackPos->z = 0.0f;
	m_destroyedDamageTimeout.applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)));
}
