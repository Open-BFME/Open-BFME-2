// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Retail 0x004C51A0 (641 bytes): GrabPassengerSpecialPower::doSpecialPower, slot
// 10 of its special-power interface vftable 0x0085D8D8 (+0x10 subobject;
// [ecx-8] is the Object, [ecx-0xC] the module data; the address sits at
// 0x0085D900). Name by address, as CombineHordeSpecialPower's slot 10
// (0x004C888D). WorldBuilder twin 0x01261D60 (unnamed). From the owner's
// position it picks a target within the module data's +0x7C radius through
// ThePartitionManager->getClosestObject (BFME2's partition filter chain,
// the view AIStructureCreepTactic.cpp documents):
//   option 0x8000  kinds 0x61/0x88, and (when +0x80 is set) the rowed
//                  TerrainLogic point 0x0027F108 near the owner, which wins
//                  when there is no object or it is no farther (Coord3D length
//                  0x00003571)
//   option 0x2000  kind 0x88 only
//   otherwise      kind 8, status 3 set and none cleared, relationship 1
// and hands the point or the object to the owner's special-power module of
// type 0x27 (rowed Object::findSpecialPowerModuleInterface) through its slot
// 12 (location) or 11 (object) with option 0x2000.
#include <string.h>

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"

class Object;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
#include "../../../../Include/GameLogic/Rva00260EB1Filter.h"

// An ObjectStatusMaskType (16 bytes) as the status filter copies it.
class BfmeObject872Header
{
	char m_bytes[16];
public:
	BfmeObject872Header(const BfmeObject872Header &other);
};

// vftable 0x00C071CC, allow 0x002616EB: two status masks.
class Rva002FDF1C : public Rva000421C8
{
public:
	Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b);	// 0x002FDF1C
	virtual bool allow(Object *obj);
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA004C51A0_3 = 3
};

// 0x0023DA79 clears the mask and sets one bit (its first argument unused).
struct ObjectStatusMask
{
	int m_bits[4];
};

class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int reserved, int bit);	// 0x0023DA79 (rowed)
};

struct ObjectStatusMaskNone : public ObjectStatusMask
{
	ObjectStatusMaskNone() { memset(this, 0, sizeof(*this)); }
};

// A KindOfMaskType built from its set bits (0x00045411 one bit, 0x0006EE7A
// two bits; the first argument is unused).
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

// Rowed constructors, same 28-byte mask: 0x00045411 (one bit), 0x0006EE7A (two).
#include "../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
struct Rva0006EE7A
{
	unsigned int bits[7];
	Rva0006EE7A(int reserved, int bit1, int bit2) throw();
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask) throw();	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

extern PartitionManager *ThePartitionManager;

class BfmeThingCME
{
public:
	int rva0027F108(void *pos, float radius, int flag, int mode);	// 0x0027F108 (rowed)
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

enum SpecialPowerType
{
	SPECIAL_RVA004C51A0_39 = 0x27
};

template <int N> class Rva004C51A0Slots : public Rva004C51A0Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C51A0Slots<0>
{
};

// What Object::findSpecialPowerModuleInterface returns: slot 11 takes an
// object, slot 12 a location, each with command options.
class SpecialPowerModuleInterface : public Rva004C51A0Slots<11>
{
public:
	virtual void rva004C51A0Slot11(Object *obj, unsigned int options) = 0;
	virtual void rva004C51A0Slot12(const Coord3D *pos, unsigned int options) = 0;
};

#include "../object.h"

class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// The +0x10 interface: slots 0..9 placeholders, slot 10 below.
class Rva004C51A0Iface10 : public Rva004C51A0Slots<10>
{
public:
	virtual void doSpecialPower(unsigned int options) = 0;
};
class SpecialPowerModule : public BehaviorModule, public Rva004C51A0Iface10
{
};

class GrabPassengerSpecialPowerModuleData
{
public:
	unsigned char m_pad00[0x7C];
	float m_7C;	// +0x7C the radius
	bool m_80;	// +0x80 also consider the terrain point
};

class GrabPassengerSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
private:
	const GrabPassengerSpecialPowerModuleData *getGrabPassengerSpecialPowerModuleData() const
	{
		return (const GrabPassengerSpecialPowerModuleData *)m_moduleData;
	}
};

void GrabPassengerSpecialPower::doSpecialPower(unsigned int options)
{
	const GrabPassengerSpecialPowerModuleData *data = getGrabPassengerSpecialPowerModuleData();
	Coord3D pos = *m_object->getPosition();
	Coord3D point;
	bool usePoint = false;
	Object *target;

	if (options & 0x8000)
	{
		const Coord3D *terrainPoint = 0;
		if (data->m_80)
			terrainPoint = (const Coord3D *)((BfmeThingCME *)TheTerrainLogic)->rva0027F108(&pos, data->m_7C, 1, 1);
		target = ThePartitionManager->getClosestObject(&pos, data->m_7C, 0, &Rva003959FA(reinterpret_cast<const BfmeFixedStorage0004543D &>(Rva0006EE7A(0, 0x61, 0x88))));
		if (terrainPoint)
		{
			if (target)
			{
				point = *terrainPoint;
				float pointDist;
				{
					Coord3D toPoint;
					toPoint.x = pos.x - point.x;
					toPoint.y = pos.y - point.y;
					toPoint.z = pos.z - point.z;
					pointDist = toPoint.length();
				}
				float targetDist;
				{
					Coord3D toTarget;
					toTarget.x = pos.x - target->getPosition()->x;
					toTarget.y = pos.y - target->getPosition()->y;
					toTarget.z = pos.z - target->getPosition()->z;
					targetDist = toTarget.length();
				}
				if (pointDist <= targetDist)
					usePoint = true;
			}
			else
			{
				usePoint = true;
			}
		}
	}
	else if (!(options & 0x2000))
	{
		ObjectStatusMask status;
		target = ThePartitionManager->getClosestObject(&pos, getGrabPassengerSpecialPowerModuleData()->m_7C, 0,
			Rva003959FA(reinterpret_cast<const BfmeFixedStorage0004543D &>(Rva00045411BitSet(0, 8)))
				.link(&Rva002FDF1C(*(BfmeObject872Header *)((Rva0023DA79 *)&status)->rva0023DA79(0, (int)OBJECT_STATUS_RVA004C51A0_3),
					*(BfmeObject872Header *)&ObjectStatusMaskNone()))
				->link(&Rva00260EB1Filter(m_object, 1, false)));
	}
	else
	{
		target = ThePartitionManager->getClosestObject(&pos, getGrabPassengerSpecialPowerModuleData()->m_7C, 0, &Rva003959FA(reinterpret_cast<const BfmeFixedStorage0004543D &>(Rva00045411BitSet(0, 0x88))));
	}

	Object *owner = m_object;
	SpecialPowerModuleInterface *power = owner->findSpecialPowerModuleInterface(SPECIAL_RVA004C51A0_39);
	if (power)
	{
		if (usePoint)
			power->rva004C51A0Slot12(&point, 0x2000);
		else if (target)
			power->rva004C51A0Slot11(target, 0x2000);
	}
}
