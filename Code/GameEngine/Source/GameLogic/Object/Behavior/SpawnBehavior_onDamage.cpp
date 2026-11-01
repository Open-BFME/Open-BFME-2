// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?onDamage@SpawnBehavior@@UAEXPAVDamageInfo@@@Z, retail 0x0045FDF3, 87 bytes.
// Identity: slot 0 of SpawnBehavior's DamageModuleInterface vftable at
// 0x0084259C, ahead of the empty onHealing 0x0047A69C and the rowed
// onBodyDamageStateChange 0x004604D5. Zero Hour's SpawnBehavior::onDamage
// statement for statement: every live spawn's SlavedUpdate is told through
// onSlaverDamage (SlavedUpdateInterface slot 3). The damage interface sits
// at SpawnBehavior +0x28, so the spawn IDs (+0x4C) are at this +0x24.
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4; MSVC calls the out-of-line copy 0x00049DC5, and only the
// inline declaration gives retail's register assignment (this in EBX).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <cstddef>
// Keep the inline accessors without emitting per-unit COMDAT copies (retail's
// one out-of-line vector<void*> size/begin is the /Od body at 0x00023BC0/0x00023B90).
// Declaration-only forms made the hashtable _M_find copy call them out of line,
// unlike retail's 0x002888D4.
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

#include "../../../Common/GameLogicObjectLookupView.h"

class Object;
class DamageInfo;

class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const;
	virtual void onEnslave(const Object *slaver);
	virtual void onSlaverDie(const DamageInfo *info);
	virtual void onSlaverDamage(const DamageInfo *info);
};

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

private:
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

extern GameLogic *TheGameLogic;

// The DamageModuleInterface view of SpawnBehavior (primary +0x28).
class SpawnBehavior
{
public:
	virtual void onDamage(DamageInfo *info);

private:
	unsigned char m_pad04[0x24 - 0x04];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?onDamage@SpawnBehavior@@UAEXPAVDamageInfo@@@Z
void SpawnBehavior::onDamage(DamageInfo *info)
{
	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID(*iter);
		if (currentSpawn)
		{
			// Go through all my spawns and see if they have a SlavedUpdate I can tell I was hurt to
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = static_cast<SlavedUpdateInterface *>(static_cast<BehaviorModuleInterface &>(**update).slot26());
				if (sdu != NULL)
				{
					sdu->onSlaverDamage(info);
					break;
				}
			}
		}
	}
}
