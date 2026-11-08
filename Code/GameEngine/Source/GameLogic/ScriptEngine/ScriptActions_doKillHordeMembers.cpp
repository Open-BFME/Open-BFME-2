// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii
// stlport
//
// ScriptActions::doKillHordeMembers, retail 0x003C6507 (240B; ret 8)
// Target identity: executeAction case 436 (KILL_HORDE_MEMBERS) calls it on
// the ScriptActions instance (ecx = edi) with parameter 0 itself and
// parameter 1's real (+0x0C); BFME 1's ScriptActions_KillHordeMembers.cpp is
// the donor for the name and flow.
// Target body: the unit by parameter (getUnitNamed 0x003588E7), its +0x250
// interface's slot 31 (+0x7C) result, whose slot 66 (+0x108) list view is
// copied out by the pinned 0x0036AE51 into a local list<int> (dtor
// 0x004EC395). percentage * 0.01f * size, truncated, members are killed
// (Object::kill 0x002984D4, damage 8, death 0) while the count lasts, skipping
// null entries and ones whose +0x254 field is null; nothing is killed unless
// 0 < count <= size.
// Target differences from the donor: the unit comes from the non-virtual
// getUnitNamed, the members from the slot-66 view rather than a list
// reference, and both sizes are of the local copy. Donor-carried: the
// contain / horde-contain / body-module meaning of +0x250, slot 31 and +0x254
// and the unresistable / normal meaning of damage 8 and death 0.
// Shape: the count read goes through a volatile view (retail multiplies the
// percentage before converting the size), and the range test is an early
// return; nesting the loop under the test pushes EBX in the prologue instead
// of after the first size walk.
#include <list>
#include "../../../Include/GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}


typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

typedef ContainmentList IntList;

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

class Parameter;

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};


#include "../../../Include/GameLogic/Module/HordeContainInterface.h"

#include "../../../Include/GameLogic/Module/ContainModule.h"

#include "../Object/object.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptActionsBFME2.h"

void ScriptActions::doKillHordeMembers(Parameter *unitParameter, Real percentage)
{
	Object *horde = TheScriptEngine->getUnitNamed(unitParameter);
	if (!horde)
		return;

	ContainModuleInterface *contain = horde->getContain();
	HordeContainInterface *hordeContain = contain ? contain->slot31() : 0;
	if (!hordeContain)
		return;

	IntList members = hordeContain->getMemberList().rva0036AE51();
	volatile Real &percentageView = percentage;
	Int toKill = (Int)((percentageView * 0.01f) * members.size());
	if (toKill > members.size() || toKill <= 0)
		return;
	for (IntList::iterator it = members.begin(); it != members.end(); ++it) {
		Object *member = (Object *)containmentFirstWord(*it);
		if (member && member->getBodyModule() && toKill) {
			member->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
			--toKill;
		}
	}
}
