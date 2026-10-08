// cl: /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Five SpecialPowerModule members from one retail run (0x00493251,
// 0x004932DC, 0x00493620, 0x00494599, 0x0049466D). Original names unknown;
// the WorldBuilder debug bodies (0x011E7CD0, 0x011EA550, 0x011E7E00,
// 0x011EA590, 0x011E7ED0, all unnamed) are the shape leads by call graph.
//
// 0x0049466D is slot 18 of the SpecialPowerModuleInterface vftable (this =
// module+0x10) at 0x0085C4B8, entry 0x0085C500, and the matching slot of the
// derived vftables; slot 6 there is the data+8 template getter 0x00493236. It
// fails unless 0x00493251 and 0x00493620 both pass and, for a
// location whose module data byte +0x74 is set (0x004932DC), 0x00494599
// accepts it. It then asks the first behavior module (Object+0x244 list)
// whose BehaviorModuleInterface slot 25 interface accepts the data's
// SpecialPowerTemplate in its slot 7 to judge the location through slot 8.
// Retail keeps ecx across the 0x004932DC call, which cl only does when that
// callee's body is visible earlier in the same TU, so it lives here; the
// getObject/getSpecialPowerModuleData accessors give retail's esi/edi split.
//
// 0x00494599 collects the controlling player's Coord3D points (rowed
// Player::rva002AF614) and reports whether any lies within the data's +0x78
// float of the location; no data, object or player counts as a hit.
//
// 0x00493251 picks the module data's +0x3C ObjectFilter, or +0x38 when the
// GameLogic word at +0x114 is 3 and the rowed BfmeGlob939D gate passes (else
// it passes outright), and fails only when that filter is valid (rowed
// ObjectFilter::isValid) and the controlling player's rowed rva002AB2D9
// rejects it. Retail adjusts the loaded data pointer in place, which is what
// keeps this in esi and the filter in edi; a typed &data->member pointer
// swaps them.
//
// 0x00493620 fails only for a template whose final override has type 0x20:
// when the object's rowed rva0028C1CC holds, or when the body (+0x254) was
// last damaged within 10 frames of TheGameLogic's frame (slot 16) and that
// damage record (slot 15) has a nonzero +0x20 float and a +0x10 word other than
// 7. Slots 15/16 follow Zero Hour's getLastDamageInfo/getLastDamageTimestamp
// order; that naming is inferred.
//
// 0x004946F3 is initiateIntentToDoSpecialPower, called by doSpecialPower /
// AtObject / AtLocation (0x0049490F, 0x0049495B, 0x004949D8) with the options
// third; no caller reads a result and the body leaves eax unset, so it is
// void here (Zero Hour's returns Bool). The name follows Zero Hour's
// initiateIntentToDoSpecialPower, which also hands the template, target and
// options to the first behavior module's update interface that claims the
// power; the rest is BFME 2 only and read from retail: the target's ID
// (Object+0x74) goes to +0x2C; template types 0x33 and 0x88 poke each other's
// rowed Object::rva0028BD92 module (rowed Rva0044E6AE::rva0049C8FC), type
// 0x8D sends the AI (Object+0x258) to harvest at the controlling player's
// resource manager (Player+0x2E4, pinned 0x004F5A67) pick and clears AI byte
// +0x3CC; data byte +0x5D idles the AI. Once an interface took the power, the
// template's rowed 0x00493313 name (if any) goes to the pinned
// BfmeSinkBLD::bfmeDoBLD on the 0x00DFF028 global, interface slot 2 plus
// options 0x40000 set +0x28, the data's +0x44 FXList plays on owner and
// target, and the owner's drawable voices message 0x7EC through the pinned
// pickAndPlayUnitVoiceResponse with the template (+0x10), target drawable and
// position in a PickAndPlayInfo. Retail keeps the name in the dead way slot
// only when that tail is a nested if (found) block, and pushes the s7
// template from a register only through an inline data getter.
// Offsets are target evidence; field and slot meanings are inferred.

#include <stddef.h>
#include <list>
#include <vector>

#include "ascii_string.h"
#include "Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef unsigned int UnsignedInt;

extern GameLogic *TheGameLogic;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Waypoint;
class Drawable;

// Retail calls the shared pointer-list destructor 0x00239AF4 out of line.
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};

class SpecialPowerTemplate;

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	bool m_air;
	Drawable *m_drawTarget; // +0x04
	void *m_weaponSlot;
	int m_specialPowerType;
	const SpecialPowerTemplate *m_specialPowerTemplate; // +0x10
	Coord3D m_position; // +0x14
	unsigned int m_unmodelled_20;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7EC = 0x7EC
	};
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_command; // +0x20
	char m_pad21[0x3CC - 0x21];
	bool m_3cc; // +0x3CC
};

class ResourceGatheringManager
{
public:
	bool rva004F5A67(Object *obj, Coord3D *pos);
};

class Rva0044E6AE
{
public:
	void rva0049C8FC();
};

class Rva00493313
{
public:
	AsciiString rva00493313() const;
};

class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class BfmeSinkBLD
{
public:
	void bfmeDoBLD(void *name, int flag);
};

struct Rva00493251GameLogicView
{
	char m_pad[0x114];
	int m_114;
};

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

class BfmeTab1026;

class Player
{
public:
	void rva002AF614(void *points);
	bool rva002AB2D9(BfmeTab1026 *tab, bool flag) const;
	ResourceGatheringManager *getResourceGatheringManager() const { return m_resourceGatheringManager; }
private:
	char m_pad[0x2E4];
	ResourceGatheringManager *m_resourceGatheringManager; // +0x2E4
};

class ObjectFilter
{
public:
	bool isValid() const;
private:
	int m_value;
};

class DamageInfo
{
public:
	char m_pad[0x10];
	int m_type; // +0x10
	char m_pad14[0x20 - 0x14];
	float m_amount; // +0x20
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual const DamageInfo *getLastDamageInfo() const;
	virtual unsigned int getLastDamageTimestamp() const;
};

class BehaviorModule;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva0028C1CC() const;
	void *rva0028BD92(int key);
	Drawable *getDrawable() const;
	int getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_pad[0x74];
	int m_id; // +0x74
	char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x10];
};

class SpecialPowerTemplate : public Overridable
{
public:
	int getType() const { return m_type; }
private:
	char m_pad10[0x1C - 0x10];
	int m_type; // +0x1C
};

class SpecialPowerModuleData
{
public:
	void *m_vtable;
	int m_04;
	const SpecialPowerTemplate *m_specialPowerTemplate; // +0x08
	const SpecialPowerTemplate *getTemplate() const { return m_specialPowerTemplate; }
	char m_pad0C[0x38 - 0x0C];
	ObjectFilter m_filter38;
	ObjectFilter m_filter3C;
	char m_pad40[0x44 - 0x40];
	const FXList *m_fx44; // +0x44
	char m_pad48[0x5D - 0x48];
	bool m_5d; // +0x5D
	char m_pad5E[0x74 - 0x5E];
	bool m_74;
	char m_pad75[0x78 - 0x75];
	float m_78;
};

// Interface returned by BehaviorModuleInterface slot 25.
class Rva0049466DUpdateInterface
{
public:
	virtual bool initiateIntentToDoSpecialPower(const SpecialPowerTemplate *power, const Object *targetObj,
		const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way) = 0;
	virtual void s1() = 0; virtual bool s2() = 0; virtual void s3() = 0;
	virtual void s4() = 0; virtual void s5() = 0; virtual void s6() = 0;
	virtual bool s7(const SpecialPowerTemplate *power) = 0;
	virtual bool s8(const Coord3D *loc) = 0;
};

template <int N> class BehaviorModuleInterfaceSlots : public BehaviorModuleInterfaceSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class BehaviorModuleInterfaceSlots<0>
{
};

class BehaviorModuleInterface : public BehaviorModuleInterfaceSlots<25>
{
public:
	virtual Rva0049466DUpdateInterface *getRva0049466DUpdateInterface() = 0;
};

class Module
{
public:
	virtual void moduleSlot0();
protected:
	const SpecialPowerModuleData *m_moduleData; // +0x04
};

class ObjectModule : public Module
{
public:
	Object *getObject() const { return m_object; }
protected:
	Object *m_object; // +0x08
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
	virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0;
	virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual bool rva0049466D(const Coord3D *loc) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
	virtual bool rva0049466D(const Coord3D *loc);
	bool rva00493251();
	bool rva004932DC();
	bool rva00493620();
	bool rva00494599(const Coord3D *pos);
	void initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos,
		UnsignedInt commandOptions, const Waypoint *way);
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
private:
	char m_pad14[0x28 - 0x14];
	bool m_28; // +0x28
	int m_2c; // +0x2C
};

// ?rva00493251@SpecialPowerModule@@QAE_NXZ @0x00493251
bool SpecialPowerModule::rva00493251()
{
	const char *filter = (const char *)getSpecialPowerModuleData();
	if (((const Rva00493251GameLogicView *)TheGameLogic)->m_114 != 3)
		filter += offsetof(SpecialPowerModuleData, m_filter3C);
	else
	{
		if (!((BfmeGlob939D *)TheGameLogic)->bfmeCall939D())
			return true;
		filter += offsetof(SpecialPowerModuleData, m_filter38);
	}
	if (((const ObjectFilter *)filter)->isValid())
	{
		if (!getObject()->getControllingPlayer()->rva002AB2D9((BfmeTab1026 *)filter, true))
			return false;
	}
	return true;
}

// ?rva004932DC@SpecialPowerModule@@QAE_NXZ @0x004932DC
bool SpecialPowerModule::rva004932DC()
{
	if (m_moduleData)
	{
		if (m_moduleData->m_74)
			return true;
	}
	return false;
}

// ?rva00493620@SpecialPowerModule@@QAE_NXZ @0x00493620
bool SpecialPowerModule::rva00493620()
{
	const SpecialPowerTemplate *power = getSpecialPowerTemplate();
	if (power == 0)
		return true;
	Object *obj = getObject();
	if (obj == 0)
		return true;
	if (((const SpecialPowerTemplate *)power->friend_getFinalOverride())->getType() == 0x20)
	{
		if (obj->rva0028C1CC())
			return false;
		BodyModuleInterface *body = obj->getBodyModule();
		if (body)
		{
			unsigned int now = TheGameLogic->getFrame();
			if (body->getLastDamageTimestamp() + 10 >= now)
			{
				const DamageInfo *info = body->getLastDamageInfo();
				if (info && info->m_amount != 0.0f && info->m_type != 7)
					return false;
			}
		}
	}
	return true;
}

// ?rva00494599@SpecialPowerModule@@QAE_NPBUCoord3D@@@Z @0x00494599
bool SpecialPowerModule::rva00494599(const Coord3D *pos)
{
	const SpecialPowerModuleData *data = m_moduleData;
	Object *obj;
	if (data == 0 || (obj = m_object) == 0)
		return true;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return true;

	_STL::vector<Coord3D> points;
	player->rva002AF614(&points);

	bool found = false;
	for (Coord3D *it = points.begin(); it != points.end(); ++it)
	{
		float dx = pos->x;
		float dy = pos->y;
		float dz = pos->z;
		dx -= it->x;
		dy -= it->y;
		dz -= it->z;
		Coord3D delta;
		delta.x = dx;
		delta.y = dy;
		delta.z = dz;
		if (delta.length() <= data->m_78)
		{
			found = true;
			break;
		}
	}
	return found;
}

// ?rva0049466D@SpecialPowerModule@@UAE_NPBUCoord3D@@@Z @0x0049466D
bool SpecialPowerModule::rva0049466D(const Coord3D *loc)
{
	if (!rva00493251())
		return false;
	if (loc && rva004932DC() && !rva00494599(loc))
		return false;
	if (!rva00493620())
		return false;
	for (BehaviorModule **m = getObject()->getBehaviorModules(); *m; ++m)
	{
		Rva0049466DUpdateInterface *update = (*m)->getRva0049466DUpdateInterface();
		if (update && update->s7(getSpecialPowerModuleData()->m_specialPowerTemplate))
			return update->s8(loc);
	}
	return true;
}

// ?initiateIntentToDoSpecialPower@SpecialPowerModule@@QAEXPBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z @0x004946F3
void SpecialPowerModule::initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos,
	UnsignedInt commandOptions, const Waypoint *way)
{
	if (targetObj)
		m_2c = targetObj->getID();
	const SpecialPowerModuleData *data = getSpecialPowerModuleData();
	switch (((const SpecialPowerTemplate *)data->m_specialPowerTemplate->friend_getFinalOverride())->getType())
	{
	case 0x33:
	{
		void *other = m_object->rva0028BD92(0x88);
		if (other)
			((Rva0044E6AE *)other)->rva0049C8FC();
		break;
	}
	case 0x88:
	{
		void *other = m_object->rva0028BD92(0x33);
		if (other)
			((Rva0044E6AE *)other)->rva0049C8FC();
		break;
	}
	case 0x8D:
	{
		Object *obj = m_object;
		AIUpdateInterface *ai = obj->getAI();
		if (ai)
		{
			ResourceGatheringManager *manager = obj->getControllingPlayer()->getResourceGatheringManager();
			if (manager)
			{
				Coord3D pos;
				if (manager->rva004F5A67(obj, &pos))
				{
					ai->m_command.aiHarvest(&pos, CMD_FROM_AI);
					ai->m_3cc = false;
				}
			}
		}
		break;
	}
	}

	Rva0049466DUpdateInterface *found = 0;
	for (BehaviorModule **m = getObject()->getBehaviorModules(); *m; ++m)
	{
		Rva0049466DUpdateInterface *update = (*m)->getRva0049466DUpdateInterface();
		if (update && update->s7(getSpecialPowerModuleData()->getTemplate()))
		{
			update->initiateIntentToDoSpecialPower(getSpecialPowerModuleData()->m_specialPowerTemplate,
				targetObj, targetPos, commandOptions, way);
			found = update;
			break;
		}
	}

	if (getSpecialPowerModuleData()->m_5d)
	{
		AIUpdateInterface *ai = getObject()->getAI();
		if (ai)
			ai->m_command.aiIdle(CMD_FROM_AI);
	}

	if (found)
	{

		const SpecialPowerTemplate *power = getSpecialPowerModuleData()->m_specialPowerTemplate;
		AsciiString name = ((const Rva00493313 *)power)->rva00493313();
		if (!name.isEmpty())
			((BfmeSinkBLD *)theRadarWindowOverrideSource)->bfmeDoBLD(&name, 0);

		if (found->s2() && (commandOptions & 0x40000))
			m_28 = true;

		Object *obj = m_object;
		if (obj)
		{
			FXList::doFXObj(data->m_fx44, obj, targetObj);
			Drawable *drawable = obj->getDrawable();
			if (drawable)
			{
				DrawableList list;
				list.push_back(drawable);
				PickAndPlayInfo info;
				info.m_specialPowerTemplate = power;
				if (targetObj)
					info.m_drawTarget = targetObj->getDrawable();
				if (targetPos)
					info.m_position = *targetPos;
				pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7EC, &info);
			}
		}
	}
}
