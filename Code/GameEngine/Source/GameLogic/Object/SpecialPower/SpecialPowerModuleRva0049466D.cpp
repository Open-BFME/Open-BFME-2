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
// Offsets are target evidence; field and slot meanings are inferred.

#include <stddef.h>
#include <vector>

#include "Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

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
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
private:
	char m_pad[0x244];
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body; // +0x254
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
	char m_pad0C[0x38 - 0x0C];
	ObjectFilter m_filter38;
	ObjectFilter m_filter3C;
	char m_pad40[0x74 - 0x40];
	bool m_74;
	char m_pad75[0x78 - 0x75];
	float m_78;
};

// Interface returned by BehaviorModuleInterface slot 25.
class Rva0049466DUpdateInterface
{
public:
	virtual void s0() = 0; virtual void s1() = 0; virtual void s2() = 0; virtual void s3() = 0;
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
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
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
