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
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../Common/GameLogicObjectLookupView.h"

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
class AudioManager : public VSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
};
extern AudioManager *TheAudio;

class ScriptEngine
{
public:
	void rva00357E7B(int playerIndex, const AsciiString &name, int id);
};
extern ScriptEngine *TheScriptEngine;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x10];
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_name; }
	const OpaqueRefElement4 *getInitiateSound() const { return &((const SpecialPowerTemplate *)friend_getFinalOverride())->m_initiateSound; }
	const OpaqueRefElement4 *getInitiateAtTargetSound() const { return &((const SpecialPowerTemplate *)friend_getFinalOverride())->m_initiateAtLocationSound; }
	int get30() const { return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_30; }
	AsciiString m_name;
	char m_pad14[0x30 - 0x14];
	int m_30;
	OpaqueRefElement4 m_initiateSound;
	OpaqueRefElement4 m_initiateAtLocationSound;
};

class Rva002A9EFB { public: void rva002A9EFB(int v); };

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	char m_pad[0x54];
	int m_playerIndex;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const
	{
		return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0;
	}
	char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

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
extern int g_Va00DBA4E4;

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

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};
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

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	int m_unknown4;
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x08
	bool m_0C;
	char m_pad0D[0x18 - 0x0D];
	AsciiString m_18;	// +0x18
	float m_radius;		// +0x1C
	bool m_includeSelf;	// +0x20
	char m_pad21[0x24 - 0x21];
	int m_24;		// +0x24
	char m_pad28[0x2C - 0x28];
	bool m_2C;
	char m_pad2D[0x30 - 0x2D];
	int m_30;
	BitFlags<11> m_mask;	// +0x34
	char m_pad38[0x40 - 0x38];
	bool m_40;
	bool m_41;
	bool m_42;
	char m_pad43[0x48 - 0x43];
	const FXList *m_fx48;
	const FXList *m_fx4C;
	ModelConditionFlagType m_50;
	float m_54;
	char m_pad58[0x5C - 0x58];
	bool m_5C;
	char m_pad5D;
	bool m_5E;
	bool m_5F;
	char m_pad60[0x64 - 0x60];
	int m_64;
	char m_pad68[0x6C - 0x68];
	AsciiString m_6C;
	int m_70;
};

class SpecialPowerModuleInterface;

class ObjectModule
{
public:
	virtual ~ObjectModule();
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual SpecialPowerModuleInterface *getSpecialPower();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
	virtual void s07() = 0; virtual void s08() = 0; virtual void s09() = 0;
	virtual void s10() = 0; virtual void s11() = 0; virtual void s12() = 0;
	virtual void s13() = 0; virtual void s14() = 0;
	virtual void startPowerRecharge(float readyFraction) = 0;
};

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
		const SpecialPowerModuleData *d = getSpecialPowerModuleData();
		int idx = obj->getControllingPlayer()->getPlayerIndex();
		TheScriptEngine->rva00357E7B(idx, d->m_specialPowerTemplate->getName(), id);
	}
	const SpecialPowerModuleData *d = getSpecialPowerModuleData();
	BfmeAudioEventPrefix136 soundToPlay(*d->m_specialPowerTemplate->getInitiateSound(), 0);
	((Rva002D9531 *)&soundToPlay)->rva002D9531(getObject()->getID());
	TheAudio->addAudioEvent(&soundToPlay);
	if (location)
	{
		BfmeAudioEventPrefix136 soundAtLocation(*d->m_specialPowerTemplate->getInitiateAtTargetSound(), 0);
		((Rva002D9508 *)&soundAtLocation)->rva002D9508(location);
		((Rva0033F15DDwordSlot *)&soundAtLocation)->set(getObject()->getControllingPlayer()->getPlayerIndex());
		TheAudio->addAudioEvent(&soundAtLocation);
	}
}

void SpecialPowerModule::triggerSpecialPower(const Coord3D *location)
{
	aboutToDoSpecialPower(location);
	createViewObject(location);

	const SpecialPowerModuleData *d = getSpecialPowerModuleData();
	if (!d->m_0C)
		startPowerRecharge(1.0f);

	if (!((const StringBase<char> *)&d->m_6C)->isEmpty()
		&& ((const StringBase<char> *)&d->m_6C)->compare(*(const StringBase<char> *)&d->m_specialPowerTemplate->getName()) != 0)
	{
		for (BehaviorModule **m = getObject()->getBehaviorModules(); *m; ++m)
		{
			SpecialPowerModuleInterface *sp = (*m)->getSpecialPower();
			if (!sp)
				continue;
			const SpecialPowerTemplate *t = sp->getSpecialPowerTemplate();
			if (!t)
				continue;
			const StringBase<char> *name = (const StringBase<char> *)&t->getName();
			if (name->compare(*(const StringBase<char> *)&d->m_6C) == 0)
				sp->startPowerRecharge(1.0f);
		}
	}

	Player *player = getObject()->getControllingPlayer();
	if (player)
		((Rva002A9EFB *)player)->rva002A9EFB(d->m_specialPowerTemplate->get30());

	if (d->m_50 != MODELCONDITION_INVALID && d->m_54 > 0.0f)
	{
		unsigned int frames = (unsigned int)(g_Va00DBA4E4 * d->m_54);
		getObject()->setSpecialModelConditionState(d->m_50, frames);
		if (d->m_5C)
			getObject()->setDisabledUntil(DISABLED_3, TheGameLogic->getFrame() + frames);
	}

	if (d->m_fx48)
	{
		if (location)
			FXList::doFXPos(d->m_fx48, location, 0, 0.0f, 0);
		else
			FXList::doFXObj(d->m_fx48, getObject(), 0);
	}

	if (d->m_2C)
	{
		if (d->m_42)
			((Rva00318333 *)TheGlobalWeatherSystem)->rva00318719();
		else
		{
			int kind = 1;
			if (d->m_5F)
				kind = 2;
			else if (d->m_5E)
				kind = 3;
			((Rva00318333 *)TheGlobalWeatherSystem)->rva00318807(kind, (int *)&d->m_24, player,
				(const StringBase<char> *)&d->m_18, (int *)&d->m_mask, d->m_30);
		}
		int type = d->m_64;
		if (type != 5)
			((Rva003186EE *)TheGlobalWeatherSystem)->rva003186EE(type, d->m_70, d->m_30);
		return;
	}

	bool hasMask = false;
	if (d->m_mask.any())
		hasMask = true;
	Object *obj = getObject();
	{
	Coord3D pos;
	if (location)
		pos = *location;
	else
		pos = *obj->getPosition();
	int relationship = 4;
	if (d->m_40)
		relationship = 1;
	if (d->m_41)
		relationship = 7;
	else if (d->m_42)
		relationship = 5;
	else if (hasMask)
	{
		if (relationship == 1)
			relationship = 4;
		else
			relationship = 1;
	}

	Rva002614ECFilter filterWhat(&d->m_24, obj->getControllingPlayer(), true);
	Rva00260EB1Filter filterRelationship(obj, relationship, false);
	Rva0026119DFilter filterAlive;
	Rva002611BFFilter filterMapStatus(obj);
	filterWhat.link(filterRelationship.link(&filterAlive));
	if (!obj->getTemplate()->isKindOf(123))
		filterWhat.link(&filterMapStatus);

		BfmeWideResult result = ThePartitionManager->iterateObjectsInRange(&pos, d->m_radius, 0, &filterWhat, 1);
		if (d->m_includeSelf)
		{
			if (obj->getTemplate()->isKindOf(109))
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
