// cl: /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Three SpecialPowerModule members from one retail run (0x004932DC,
// 0x00494599, 0x0049466D). Original names unknown; the WorldBuilder debug
// bodies (0x011EA550, 0x011EA590, 0x011E7ED0, all unnamed) are the shape
// leads by call graph.
//
// 0x0049466D is the SpecialPowerModuleInterface slot (this = module+0x10)
// listed at 0x0085C500 and the matching slot of the derived vftables. It
// fails unless the pinned 0x00493251 and 0x00493620 both pass and, for a
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
// Offsets are target evidence; field and slot meanings are inferred.

#include <vector>

#include "Coord3D.h"

class Player
{
public:
	void rva002AF614(void *points);
};

class BehaviorModule;

class Object
{
public:
	Player *getControllingPlayer() const;
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
private:
	char m_pad[0x244];
	BehaviorModule **m_behaviors;
};

class SpecialPowerTemplate;

class SpecialPowerModuleData
{
public:
	void *m_vtable;
	int m_04;
	const SpecialPowerTemplate *m_specialPowerTemplate; // +0x08
	char m_pad0C[0x74 - 0x0C];
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
	virtual bool rva0049466D(const Coord3D *loc) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual bool rva0049466D(const Coord3D *loc);
	bool rva00493251();
	bool rva004932DC();
	bool rva00493620();
	bool rva00494599(const Coord3D *pos);
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
};

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
