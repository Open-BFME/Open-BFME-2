// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
//
// ?onSpawnDeath@SpawnBehavior@@UAEXW4ObjectID@@PAVDamageInfo@@@Z,
// retail 0x0045FCFB, 164 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Behavior/
// SpawnBehavior.cpp:769) with the BFME2 layout, modeled on the BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Behavior/
// SpawnBehavior_onSpawnDeath.cpp. BFME2 deltas from the BFME1 donor: the spawn
// lists sit 4 further out (m_replacementTimes at secondary-this+0x28,
// m_spawnIDs at +0x2C), GameLogic::m_frame is at +0x40, and a null damageInfo
// guard skips the killer-report while still destroying the owner. The `this`
// pointer is the SpawnBehaviorInterface secondary subobject (module data at
// -0x1C, owner object at -0x18). True extent is 164 bytes: leave plus ret 8
// follow the pop sequence past the 160-byte ghidra estimate.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>

typedef bool Bool;

#include "../../../Common/GameLogicObjectLookupView.h"

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object;

#include "../../../../Include/GameLogic/Damage.h"

#include "../object.h"

#include "../../../../Include/GameLogic/Module/Rva00294D61.h"

#include "../../../../Include/GameLogic/Module/SpawnBehaviorModuleData.h"


extern GameLogic *TheGameLogic;

class SpawnBehavior
{
public:
	virtual void onSpawnDeath(ObjectID deadSpawn, DamageInfo *damageInfo);

private:
	// Secondary-subobject view: Die/Damage interface slots, spawn scalars and
	// 0xC of unrecovered members precede the replacement-time list.
	unsigned char m_pad00[0x24];
	_STL::list<int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_active;
	unsigned char m_aggregateHealth;
	unsigned char m_pad2e[2];
	unsigned int m_spawnCount;
};

// ?onSpawnDeath@SpawnBehavior@@UAEXW4ObjectID@@PAVDamageInfo@@@Z
void SpawnBehavior::onSpawnDeath(ObjectID deadSpawn, DamageInfo *damageInfo)
{
	_STL::list<ObjectID>::iterator it = _STL::find(m_spawnIDs.begin(), m_spawnIDs.end(), deadSpawn);

	if (it == m_spawnIDs.end())
		return;

	SpawnBehaviorModuleData *moduleData = *reinterpret_cast<SpawnBehaviorModuleData **>(
		reinterpret_cast<unsigned char *>(this) - 0x1c);
	int replacementTime = moduleData->m_spawnReplaceDelayData + TheGameLogic->getFrame();
	m_replacementTimes.push_back(replacementTime);
	m_spawnIDs.erase(it);
	--m_spawnCount;

	if (m_spawnCount == 0 && m_aggregateHealth)
	{
		if (damageInfo != 0)
		{
			Object *killer = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
			if (killer != 0)
			{
				Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 0x18);
				(reinterpret_cast<Rva00294D61 *>(killer))->report(owner, 1);
			}
		}
		Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 0x18);
		owner->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
}
