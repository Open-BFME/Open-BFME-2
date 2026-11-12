// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?onDie@SpawnBehavior@@UAEXPBVDamageInfo@@@Z retail 0x0045F7B5, 199 bytes.
// Identity: SpawnBehavior's DieModuleInterface vftable slot 0x008425A8.
// BFME1 donor (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/
// Behavior/SpawnBehavior.cpp:110) with BFME2 layout repairs, modeled on the
// landed SpawnBehavior_onSpawnDeath shard. Deltas: kill takes (8,0) args,
// isEffectivelyDead inlines to a bit test at Object+0x438, getBehaviorModules
// is a direct member at Object+0x244, setProducer stores the producer ID.
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4; MSVC calls the out-of-line copy 0x00049DC5, and only the
// inline declaration gives retail's register assignment (this in EBX).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

// Keep the inline accessors without emitting per-unit COMDAT copies (retail's
// one out-of-line vector<void*> size/begin is the /Od body at 0x00023BC0/0x00023B90).
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *const *vector<void*>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

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
class DamageInfo;

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

#include "../../../../Include/Common/SlavedUpdateInterface.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"



#include "../object.h"

#include "../../../../Include/GameLogic/Module/SpawnBehaviorModuleData.h"

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// The Generals header's inline findObjectByID over the object hash; the
// canonical view models the map at +0xB4 as ObjectIdMap, so this body views
// it as the STLport hash_map. MSVC still calls the out-of-line copy
// 0x00049DC5, but only this inline body gives retail's register homes.
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectPtrHash &objHash = reinterpret_cast<ObjectPtrHash &>(m_map);
	ObjectPtrHash::iterator it = objHash.find(id);
	if (it == objHash.end())
		return 0;
	return (*it).second;
}

extern GameLogic *TheGameLogic;

class SpawnBehavior
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const
	{
		return *reinterpret_cast<SpawnBehaviorModuleData *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x20);
	}
	Object *getObject() const
	{
		return *reinterpret_cast<Object **>(
			reinterpret_cast<unsigned char *>(const_cast<SpawnBehavior *>(this)) - 0x1C);
	}

private:
	char m_pad[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?onDie@SpawnBehavior@@UAEXPBVDamageInfo@@@Z
void SpawnBehavior::onDie(const DamageInfo *damageInfo)
{
	const SpawnBehaviorModuleData *modData = getSpawnBehaviorModuleData();

	if (modData->m_dieMuxData.isDieApplicable(getObject(), damageInfo) == false)
		return;

	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID(*iter);
		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->m_behaviors; *update; ++update)
			{
				SlavedUpdateInterface *sdu = static_cast<SlavedUpdateInterface *>((*update)->slot26());
				if (sdu != NULL)
				{
					sdu->onSlaverDie(damageInfo);
					break;
				}
			}

			currentSpawn->setProducer(NULL);
		}
	}

	if (modData->m_spawnedRequireSpawner)
	{
		Object *obj;

		for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); )
		{
			obj = TheGameLogic->findObjectByID(*it);
			++it;

			if (obj && obj->isEffectivelyDead() == false)
				obj->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
		}
	}
}
