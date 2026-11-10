// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// SpecialPowerModule::aboutToDoSpecialPower(const Coord3D *), retail
// 0x004939AB (268 bytes). Name and shape carried from Zero Hour's
// SpecialPowerModule.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference); access (protected) follows that
// donor. Target evidence: the sole caller is triggerSpecialPower (pinned
// 0x004941F3) at 0x0049420B; the body notifies TheScriptEngine (0x009FE16C,
// rowed 0x00357E7B) with the controlling player's index (+0x54), the final
// override's name (+0x10) and the object ID (+0x74), then builds the 0x88-byte
// audio event (shared header, rowed ctor 0x002D97D6 with flag 0) from the
// template's +0x34 sound, sets its object ID (rowed 0x002D9531) and queues it
// through TheAudio slot 25; with a location it does the same with the +0x38
// sound, the rowed position setter 0x002D9508 and the player-index setter
// 0x0033F15D. Zero Hour's EVA block is absent from retail. Codegen: the
// script notification is its own block with locals for the ID, the module data
// and the player index; the rest reads the template through a second local.
//
// SpecialPowerModule::triggerSpecialPower(const Coord3D *), retail 0x004941F3
// (926 bytes). Name and outline carried from Zero Hour's SpecialPowerModule
// (aboutToDo, createViewObject, recharge, then the shared-synced-timer loop).
// Target evidence: the three do entries 0x0049490F/0x0049495B/0x004949D8 call
// it; it calls aboutToDoSpecialPower and createViewObject (rowed 0x00493845),
// startPowerRecharge(1.0) through interface slot 15 unless data+0x0C, and
// for a non-empty +0x6C name that differs from the template name walks the
// object's behavior modules (+0x244) for special powers whose template has that
// name. The controlling player gets the rowed 0x002A9EFB with the final
// override's +0x30. A model condition at data+0x50 is set for data+0x54
// seconds of frames (x87 fild/fmul/__ftol2: unsigned conversion), optionally
// disabling the object until then (data+0x5C); the +0x48 FXList plays at the
// location or on the object. With data+0x2C the weather-system calls (rowed
// 0x00318719/0x00318807/0x003186EE) end the power; otherwise a filtered range
// query (rowed iterateObjectsInRange) around the location or the object,
// optionally appending the source or its horde (0x0028C197) through the rowed
// result append 0x00626630, goes to 0x0049402B. Field meanings past the
// donor's are inferred. Codegen levers: the position copy is an if/else
// assignment, and everything from it on sits in one nested block (puts the
// query result in the dead parameter slot and schedules the +0x40 test into the
// copy).
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../Common/GameLogicObjectLookupView.h"

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

class Rva002D9531 { public: void rva002D9531(int v); };
class Rva002D9508 { public: void rva002D9508(const void *p); };
class Rva0033F15DDwordSlot { public: void set(int v); };

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
#include "../../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;

#include "../../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../../Include/Common/Overridable.h"

#include "../../../../Include/Common/SpecialPower.h"
// The final override's initiate sounds at +0x34/+0x38 are audio-event records.
__forceinline const OpaqueRefElement4 *initiateSound(const SpecialPowerTemplate *t) { return (const OpaqueRefElement4 *)&t->getFO()->field34; }
__forceinline const OpaqueRefElement4 *initiateAtTargetSound(const SpecialPowerTemplate *t) { return (const OpaqueRefElement4 *)&t->getFO()->field38; }
__forceinline int lightPointCost(const SpecialPowerTemplate *t) { return t->getFO()->m_lightPointCost; }

class Rva002A9EFB { public: void rva002A9EFB(int v); };

#include "../../../../Include/Common/Player.h"

#include "../../../../Include/Common/ThingTemplate.h"

enum ModelConditionFlagType { MODELCONDITION_INVALID = -1 };
enum DisabledType { DISABLED_3 = 3 };

class BehaviorModule;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Player *getControllingPlayer() const;
	int getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	void setSpecialModelConditionState(ModelConditionFlagType type, unsigned int frames);
	void setDisabledUntil(DisabledType type, unsigned int frame);
	void *rva0028C197() const;
	void *m_vptr;
	const ThingTemplate *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	int m_id;
	char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors;
};

extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;

class Matrix3D;
class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};


class GlobalWeatherSystem;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class Rva00318333
{
public:
	void rva00318719();
	void rva00318807(int kind, int *what, void *player, const StringBase<char> *name, int *mask, int value);
};
class Rva003186EE { public: void rva003186EE(int a, int b, int c); };

extern PartitionManager *ThePartitionManager;

#include "../../../../Include/GameLogic/PartitionFilter.h"
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"
#include "../../../../Include/GameLogic/Rva002611BFFilter.h"
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

class Rva0028C197Members
{
public:
#define MEMBERS_SLOT(n) virtual void slot##n();
	MEMBERS_SLOT(0) MEMBERS_SLOT(1) MEMBERS_SLOT(2) MEMBERS_SLOT(3) MEMBERS_SLOT(4)
	MEMBERS_SLOT(5) MEMBERS_SLOT(6) MEMBERS_SLOT(7) MEMBERS_SLOT(8) MEMBERS_SLOT(9)
	MEMBERS_SLOT(10) MEMBERS_SLOT(11) MEMBERS_SLOT(12) MEMBERS_SLOT(13) MEMBERS_SLOT(14)
	MEMBERS_SLOT(15) MEMBERS_SLOT(16) MEMBERS_SLOT(17) MEMBERS_SLOT(18) MEMBERS_SLOT(19)
	MEMBERS_SLOT(20) MEMBERS_SLOT(21) MEMBERS_SLOT(22) MEMBERS_SLOT(23) MEMBERS_SLOT(24)
	MEMBERS_SLOT(25) MEMBERS_SLOT(26) MEMBERS_SLOT(27) MEMBERS_SLOT(28) MEMBERS_SLOT(29)
	MEMBERS_SLOT(30) MEMBERS_SLOT(31) MEMBERS_SLOT(32) MEMBERS_SLOT(33) MEMBERS_SLOT(34)
	MEMBERS_SLOT(35) MEMBERS_SLOT(36) MEMBERS_SLOT(37) MEMBERS_SLOT(38) MEMBERS_SLOT(39)
	MEMBERS_SLOT(40) MEMBERS_SLOT(41) MEMBERS_SLOT(42) MEMBERS_SLOT(43) MEMBERS_SLOT(44)
	MEMBERS_SLOT(45) MEMBERS_SLOT(46) MEMBERS_SLOT(47) MEMBERS_SLOT(48) MEMBERS_SLOT(49)
	MEMBERS_SLOT(50) MEMBERS_SLOT(51) MEMBERS_SLOT(52) MEMBERS_SLOT(53) MEMBERS_SLOT(54)
	MEMBERS_SLOT(55) MEMBERS_SLOT(56) MEMBERS_SLOT(57) MEMBERS_SLOT(58) MEMBERS_SLOT(59)
	MEMBERS_SLOT(60) MEMBERS_SLOT(61) MEMBERS_SLOT(62) MEMBERS_SLOT(63) MEMBERS_SLOT(64)
	MEMBERS_SLOT(65) MEMBERS_SLOT(66)
#undef MEMBERS_SLOT
	virtual void getMembers(_STL::list<int> *members);	// slot 67 (+0x10C)
};

struct BfmeWideResultCursor
{
	void *m_begin;
	char m_pad04[0x0C - 0x04];
	void *m_cursor;
};

template <int N>
class BitFlags
{
public:
	bool any() const;
	unsigned int m_words[(N + 31) / 32];
};

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

// +0x34 holds the BitFlags<11> AntiCategory mask the canonical header keeps as neutral storage.
static inline const BitFlags<11> &antiCategoryMask(const SpecialPowerModuleData *data)
{
	return *(const BitFlags<11> *)&data->field34;
}

class SpecialPowerModuleInterface;

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual ~SpecialPowerModule();
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return (const SpecialPowerModuleData *)m_moduleData; }
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual void s03(); virtual void s04(); virtual void s05();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
	virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14();
	virtual void startPowerRecharge(float readyFraction);
	void triggerSpecialPower(const Coord3D *location);
	void rva0049402B(BfmeWideResult *iter);
protected:
	void aboutToDoSpecialPower(const Coord3D *location);
	void createViewObject(const Coord3D *location);
};

void SpecialPowerModule::aboutToDoSpecialPower(const Coord3D *location)
{
	{
		Object *obj = getObject();
		int id = obj->getID();
		const SpecialPowerModuleData *specialPowerModuleData = getSpecialPowerModuleData();
		int idx = obj->getControllingPlayer()->getPlayerIndex();
		TheScriptEngine->rva00357E7B(idx, specialPowerModuleData->m_specialPowerTemplate->getName(), id);
	}
	const SpecialPowerModuleData *specialPowerModuleData = getSpecialPowerModuleData();
	BfmeAudioEventPrefix136 soundToPlay(*initiateSound(specialPowerModuleData->m_specialPowerTemplate), 0);
	((Rva002D9531 *)&soundToPlay)->rva002D9531(getObject()->getID());
	TheAudio->addAudioEvent(&soundToPlay);
	if (location)
	{
		BfmeAudioEventPrefix136 soundAtLocation(*initiateAtTargetSound(specialPowerModuleData->m_specialPowerTemplate), 0);
		((Rva002D9508 *)&soundAtLocation)->rva002D9508(location);
		((Rva0033F15DDwordSlot *)&soundAtLocation)->set(getObject()->getControllingPlayer()->getPlayerIndex());
		TheAudio->addAudioEvent(&soundAtLocation);
	}
}

void SpecialPowerModule::triggerSpecialPower(const Coord3D *location)
{
	aboutToDoSpecialPower(location);
	createViewObject(location);

	const SpecialPowerModuleData *specialPowerModuleData = getSpecialPowerModuleData();
	if (!specialPowerModuleData->m_updateModuleStartsAttack)
		startPowerRecharge(1.0f);

	if (!((const StringBase<char> *)&specialPowerModuleData->field6C)->isEmpty()
		&& ((const StringBase<char> *)&specialPowerModuleData->field6C)->compare(*(const StringBase<char> *)&specialPowerModuleData->m_specialPowerTemplate->getName()) != 0)
	{
		for (BehaviorModule **behaviorModule = getObject()->getBehaviorModules(); *behaviorModule; ++behaviorModule)
		{
			SpecialPowerModuleInterface *sp = (*behaviorModule)->getSpecialPower();
			if (!sp)
				continue;
			const SpecialPowerTemplate *specialPowerTemplate = sp->getSpecialPowerTemplate();
			if (!specialPowerTemplate)
				continue;
			const StringBase<char> *name = (const StringBase<char> *)&specialPowerTemplate->getName();
			if (name->compare(*(const StringBase<char> *)&specialPowerModuleData->field6C) == 0)
				sp->startPowerRecharge(1.0f);
		}
	}

	Player *player = getObject()->getControllingPlayer();
	if (player)
		((Rva002A9EFB *)player)->rva002A9EFB(lightPointCost(specialPowerModuleData->m_specialPowerTemplate));

	if (specialPowerModuleData->field50 != MODELCONDITION_INVALID && specialPowerModuleData->field54 > 0.0f)
	{
		unsigned int frames = (unsigned int)(BfmeLogicFramesPerSecond * specialPowerModuleData->field54);
		getObject()->setSpecialModelConditionState((ModelConditionFlagType)specialPowerModuleData->field50, frames);
		if (specialPowerModuleData->field5C)
			getObject()->setDisabledUntil(DISABLED_3, TheGameLogic->getFrame() + frames);
	}

	if (specialPowerModuleData->field48)
	{
		if (location)
			FXList::doFXPos(specialPowerModuleData->field48, location, 0, 0.0f, 0);
		else
			FXList::doFXObj(specialPowerModuleData->field48, getObject(), 0);
	}

	if (specialPowerModuleData->field2C)
	{
		if (specialPowerModuleData->field42)
			((Rva00318333 *)TheGlobalWeatherSystem)->rva00318719();
		else
		{
			int kind = 1;
			if (specialPowerModuleData->field5F)
				kind = 2;
			else if (specialPowerModuleData->field5E)
				kind = 3;
			((Rva00318333 *)TheGlobalWeatherSystem)->rva00318807(kind, (int *)&specialPowerModuleData->field24, player,
				(const StringBase<char> *)&specialPowerModuleData->field18, (int *)&antiCategoryMask(specialPowerModuleData), specialPowerModuleData->field30);
		}
		int type = specialPowerModuleData->field64;
		if (type != 5)
			((Rva003186EE *)TheGlobalWeatherSystem)->rva003186EE(type, specialPowerModuleData->field70, specialPowerModuleData->field30);
		return;
	}

	bool hasMask = false;
	if (antiCategoryMask(specialPowerModuleData).any())
		hasMask = true;
	Object *obj = getObject();
	{
	Coord3D pos;
	if (location)
		pos = *location;
	else
		pos = *obj->getPosition();
	int relationship = 4;
	if (specialPowerModuleData->field40)
		relationship = 1;
	if (specialPowerModuleData->field41)
		relationship = 7;
	else if (specialPowerModuleData->field42)
		relationship = 5;
	else if (hasMask)
	{
		if (relationship == 1)
			relationship = 4;
		else
			relationship = 1;
	}

	Rva002614ECFilter filterWhat(&specialPowerModuleData->field24, obj->getControllingPlayer(), true);
	Rva00260EB1Filter filterRelationship(obj, relationship, false);
	Rva0026119DFilter filterAlive;
	Rva002611BFFilter filterMapStatus(obj);
	filterWhat.link(filterRelationship.link(&filterAlive));
	if (!((obj->getTemplate()->m_kindof[3] & (1U << 27)) != 0))
		filterWhat.link(&filterMapStatus);

		BfmeWideResult result = ThePartitionManager->iterateObjectsInRange(&pos, specialPowerModuleData->field1C, 0, &filterWhat, 1);
		if (specialPowerModuleData->field20)
		{
			if (((obj->getTemplate()->m_kindof[3] & (1U << 13)) != 0))
			{
				Rva0028C197Members *horde = (Rva0028C197Members *)obj->rva0028C197();
				if (horde)
				{
					_STL::list<int> members;
					horde->getMembers(&members);
					for (_STL::list<int>::iterator it = members.begin(); it._M_node != members.end()._M_node; ++it)
						if (*it)
							result.rva00626630((Object *)*it, 0.0f);
				}
			}
			else
			{
				bool addSelf = true;
				Object *other;
				while ((other = result.next()) != 0)
				{
					if (other == obj)
					{
						addSelf = false;
						break;
					}
				}
				BfmeWideResultCursor *cursor = (BfmeWideResultCursor *)result.m_value;
				cursor->m_cursor = cursor->m_begin;
				if (addSelf)
					result.rva00626630(obj, 0.0f);
			}
		}
		rva0049402B(&result);
	}
}
