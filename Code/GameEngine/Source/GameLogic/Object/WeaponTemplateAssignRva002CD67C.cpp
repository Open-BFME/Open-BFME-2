// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX- /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4WeaponTemplate@@QAEAAV0@ABV0@@Z @0x002CD67C 1170B unlock: WeaponTemplate copy assignment, vectors at +0x40/+0x4C via rowed assigns, list at +0x17C, callers 0x002CE0B0
// Evidence: tu_map proposes Weapon.cpp, +0x17C list<int> nuggets and +0x160 flag match WeaponTemplateRva002CBA59/ParseClearNuggets, +0x40 scatter vector via rowed BfmePod8 assign, caller 0x002CE063 new 0x180 then ctor+assign.
#include <vector>
#include <list>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
// bfme link decl-only begin
namespace _STL { template <> vector<Coord3D, allocator<Coord3D> > & vector<Coord3D, allocator<Coord3D> >::operator=(vector<Coord3D, allocator<Coord3D> > const &); }
namespace _STL { template <> unsigned int vector<Coord3D, allocator<Coord3D> >::capacity() const; }
// bfme link decl-only end

struct BfmePod8
{
	int a[2];
};

// Retail calls the existing vector assignment at 0x001D9BEE.
namespace _STL {
template <> vector<BfmePod8> &vector<BfmePod8>::operator=(const vector &);
}

#include "../../../Include/Common/OpaqueRefElement4.h"

#include "../../../Include/Common/Rva002C99FB.h"

#include "../../../Include/GameLogic/WeaponTemplate.h"

WeaponTemplate &WeaponTemplate::operator=(const WeaponTemplate &other)
{
	m_nextTemplate = other.m_nextTemplate;
	((StringBase<char> &)*(AsciiString *)&m_field08).set((const StringBase<char> &)*(const AsciiString *)&other.m_field08);
	m_nameKey = other.m_nameKey;
	m_field10 = other.m_field10;
	m_attackRange = other.m_attackRange;
	m_minimumAttackRange = other.m_minimumAttackRange;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_requestAssistRange = other.m_requestAssistRange;
	m_aimDelta = other.m_aimDelta;
	m_field30 = other.m_field30;
	m_scatterRadius = other.m_scatterRadius;
	m_scatterTargetScalar = other.m_scatterTargetScalar;
	m_field3C = other.m_field3C;
	m_field3D = other.m_field3D;
	*(_STL::vector<BfmePod8> *)m_field40 = *(const _STL::vector<BfmePod8> *)other.m_field40;
	*(_STL::vector<Coord3D> *)m_field4C = *(const _STL::vector<Coord3D> *)other.m_field4C;
	m_damageType = other.m_damageType;
	m_deathType = other.m_deathType;
	m_field60 = other.m_field60;
	m_field64 = other.m_field64;
	m_weaponSpeed = other.m_weaponSpeed;
	m_minWeaponSpeed = other.m_minWeaponSpeed;
	m_field70 = other.m_field70;
	m_isScaleWeaponSpeed = other.m_isScaleWeaponSpeed;
	m_field75 = other.m_field75;
	m_idleAfterFiringDelay = other.m_idleAfterFiringDelay;
	m_field7C = other.m_field7C;
	m_field80 = other.m_field80;
	m_field81 = other.m_field81;
	m_field82 = other.m_field82;
	m_field83 = other.m_field83;
	m_weaponRecoil = other.m_weaponRecoil;
	m_minTargetPitch = other.m_minTargetPitch;
	m_maxTargetPitch = other.m_maxTargetPitch;
	((StringBase<char> &)*(AsciiString *)&m_field90).set((const StringBase<char> &)*(const AsciiString *)&other.m_field90);
	for (int i = 0; i < 4; ++i)
		m_projectileExhausts[i] = other.m_projectileExhausts[i];
	for (int i = 0; i < 4; ++i)
		m_fireFXs[i] = other.m_fireFXs[i];
	m_fieldB4 = other.m_fieldB4;
	for (int i = 0; i < 4; ++i)
		m_fieldB8[i] = other.m_fieldB8[i];
	*(OpaqueRefElement4 *)&m_fieldC8 = *(const OpaqueRefElement4 *)&other.m_fieldC8;
	m_fireSoundLoopTime = other.m_fireSoundLoopTime;
	*(Rva002C99FB *)m_fieldD0 = *(const Rva002C99FB *)other.m_fieldD0;
	*(Rva002C99FB *)m_fieldD8 = *(const Rva002C99FB *)other.m_fieldD8;
	m_extraBonus = other.m_extraBonus;
	m_clipSize = other.m_clipSize;
	m_minClipReloadTime = other.m_minClipReloadTime;
	m_maxClipReloadTime = other.m_maxClipReloadTime;
	m_minDelayBetweenShots = other.m_minDelayBetweenShots;
	m_maxDelayBetweenShots = other.m_maxDelayBetweenShots;
	m_continuousFireOneShotsNeeded = other.m_continuousFireOneShotsNeeded;
	m_continuousFireTwoShotsNeeded = other.m_continuousFireTwoShotsNeeded;
	m_continuousFireCoastFrames = other.m_continuousFireCoastFrames;
	m_autoReloadWhenIdleFrames = other.m_autoReloadWhenIdleFrames;
	m_shotsPerBarrel = other.m_shotsPerBarrel;
	m_antiMask = other.m_antiMask;
	m_affectsMask = other.m_affectsMask;
	m_field114 = other.m_field114;
	m_collideMask = other.m_collideMask;
	m_damageDealtAtSelfPosition = other.m_damageDealtAtSelfPosition;
	m_field120 = other.m_field120;
	m_field124 = other.m_field124;
	m_field125 = other.m_field125;
	m_field126 = other.m_field126;
	m_field128 = other.m_field128;
	m_prefireType = other.m_prefireType;
	m_leechRangeWeapon = other.m_leechRangeWeapon;
	m_field131 = other.m_field131;
	m_capableOfFollowingWaypoint = other.m_capableOfFollowingWaypoint;
	m_isShowsAmmoPips = other.m_isShowsAmmoPips;
	m_allowAttackGarrisonedBldgs = other.m_allowAttackGarrisonedBldgs;
	m_playFXWhenStealthed = other.m_playFXWhenStealthed;
	m_preAttackDelay = other.m_preAttackDelay;
	m_field13C = other.m_field13C;
	m_field140 = other.m_field140;
	m_field141 = other.m_field141;
	m_field144 = other.m_field144;
	m_continueAttackRange = other.m_continueAttackRange;
	m_infantryInaccuracyDist = other.m_infantryInaccuracyDist;
	m_suspendFXDelay = other.m_suspendFXDelay;
	m_field154 = other.m_field154;
	m_field155 = other.m_field155;
	m_field156 = other.m_field156;
	m_field157 = other.m_field157;
	m_field158 = other.m_field158;
	m_field15C = other.m_field15C;
	m_field160 = other.m_field160;
	m_field161 = other.m_field161;
	m_field164 = other.m_field164;
	m_field168 = other.m_field168;
	m_field169 = other.m_field169;
	m_field16A = other.m_field16A;
	m_field16B = other.m_field16B;
	m_field16C = other.m_field16C;
	m_field16D = other.m_field16D;
	m_field16E = other.m_field16E;
	m_lockWhenUsing = other.m_lockWhenUsing;
	m_field170 = other.m_field170;
	m_field171 = other.m_field171;
	m_field174 = other.m_field174;
	((StringBase<char> &)*(AsciiString *)&m_field178).set((const StringBase<char> &)*(const AsciiString *)&other.m_field178);
	*(_STL::list<int> *)&m_field17C = *(const _STL::list<int> *)&other.m_field17C;
	return *this;
}
