// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
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

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

typedef _STL::list<int, _STL::allocator<int> > IntList;

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

class Rva0036AE51ListView
{
public:
	void *a;
	IntList *b;
	IntList rva0036AE51();
};

class HordeContainInterface
{
public:
#define HORDE_SLOT(n) virtual void hordeSlot##n();
	HORDE_SLOT(0) HORDE_SLOT(1) HORDE_SLOT(2) HORDE_SLOT(3) HORDE_SLOT(4)
	HORDE_SLOT(5) HORDE_SLOT(6) HORDE_SLOT(7) HORDE_SLOT(8) HORDE_SLOT(9)
	HORDE_SLOT(10) HORDE_SLOT(11) HORDE_SLOT(12) HORDE_SLOT(13) HORDE_SLOT(14)
	HORDE_SLOT(15) HORDE_SLOT(16) HORDE_SLOT(17) HORDE_SLOT(18) HORDE_SLOT(19)
	HORDE_SLOT(20) HORDE_SLOT(21) HORDE_SLOT(22) HORDE_SLOT(23) HORDE_SLOT(24)
	HORDE_SLOT(25) HORDE_SLOT(26) HORDE_SLOT(27) HORDE_SLOT(28) HORDE_SLOT(29)
	HORDE_SLOT(30) HORDE_SLOT(31) HORDE_SLOT(32) HORDE_SLOT(33) HORDE_SLOT(34)
	HORDE_SLOT(35) HORDE_SLOT(36) HORDE_SLOT(37) HORDE_SLOT(38) HORDE_SLOT(39)
	HORDE_SLOT(40) HORDE_SLOT(41) HORDE_SLOT(42) HORDE_SLOT(43) HORDE_SLOT(44)
	HORDE_SLOT(45) HORDE_SLOT(46) HORDE_SLOT(47) HORDE_SLOT(48) HORDE_SLOT(49)
	HORDE_SLOT(50) HORDE_SLOT(51) HORDE_SLOT(52) HORDE_SLOT(53) HORDE_SLOT(54)
	HORDE_SLOT(55) HORDE_SLOT(56) HORDE_SLOT(57) HORDE_SLOT(58) HORDE_SLOT(59)
	HORDE_SLOT(60) HORDE_SLOT(61) HORDE_SLOT(62) HORDE_SLOT(63) HORDE_SLOT(64)
	HORDE_SLOT(65)
#undef HORDE_SLOT
	virtual Rva0036AE51ListView getMemberList();	// slot 66 (+0x108)
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void containSlot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3) CONTAIN_SLOT(4)
	CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7) CONTAIN_SLOT(8) CONTAIN_SLOT(9)
	CONTAIN_SLOT(10) CONTAIN_SLOT(11) CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23) CONTAIN_SLOT(24)
	CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27) CONTAIN_SLOT(28) CONTAIN_SLOT(29)
	CONTAIN_SLOT(30)
#undef CONTAIN_SLOT
	virtual HordeContainInterface *getHordeContainInterface();	// slot 31 (+0x7C)
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);	// 0x002984D4
	ContainModuleInterface *getContain() const { return m_contain; }
	void *getBodyModule() const { return m_body; }
private:
	unsigned char m_pad000[0x250];
	ContainModuleInterface *m_contain;	// +0x250
	void *m_body;				// +0x254
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *unitParameter);	// 0x003588E7
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doKillHordeMembers(Parameter *unitParameter, Real percentage);
};

void ScriptActions::doKillHordeMembers(Parameter *unitParameter, Real percentage)
{
	Object *horde = TheScriptEngine->getUnitNamed(unitParameter);
	if (!horde)
		return;

	ContainModuleInterface *contain = horde->getContain();
	HordeContainInterface *hordeContain = contain ? contain->getHordeContainInterface() : 0;
	if (!hordeContain)
		return;

	IntList members = hordeContain->getMemberList().rva0036AE51();
	volatile Real &percentageView = percentage;
	Int toKill = (Int)((percentageView * 0.01f) * members.size());
	if (toKill > members.size() || toKill <= 0)
		return;
	for (IntList::iterator it = members.begin(); it != members.end(); ++it) {
		Object *member = (Object *)*it;
		if (member && member->getBodyModule() && toKill) {
			member->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
			--toKill;
		}
	}
}
