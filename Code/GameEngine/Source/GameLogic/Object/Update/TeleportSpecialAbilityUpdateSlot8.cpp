// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?vslot08@Rva00492C59@@UAE_NH@Z, retail 0x00492E79 (132 bytes): slot 8
// of the +0x20 interface table of the teleport special ability update whose
// constructor is rowed as Rva00492C59 (its xfer 0x00492E10 and update
// 0x00492D11 share the class), so `this` is that subobject (module data at
// -0x1C, the Object at -0x18). With a target position and a positive maximum
// distance in the module data (+0xD4), a target farther than that from the
// Object's position (+0x38) is refused; otherwise the SpecialAbilityUpdate
// +0x20 slot-8 base 0x0044EDA6 decides. Named vslot08 after the canonical
// SpecialPowerUpdateInterface slot 8 (no donor name).
typedef bool Bool;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
typedef float Real;
#include "../object.h"
struct Rva00492C59ModuleData
{
	unsigned char m_pad000[0xD4];
	Real m_maxDistance; // +0xD4
};
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
class Rva00492C59 : public SpecialAbilityUpdate
{
public:
	virtual Bool vslot08(int value);
};
Bool Rva00492C59::vslot08(int value)
{
	const Coord3D *pos = (const Coord3D *)value;
	if (pos)
	{
		const Rva00492C59ModuleData *data = (const Rva00492C59ModuleData *)m_moduleData;
		if (data && data->m_maxDistance > 0.0f)
		{
			Object *obj = m_object;
			if (obj)
			{
				Real dx = pos->x - obj->m_cachedPos.x;
				Real dy = pos->y - obj->m_cachedPos.y;
				Real dz = pos->z - obj->m_cachedPos.z;
				if (dz * dz + dy * dy + dx * dx > data->m_maxDistance * data->m_maxDistance)
					return false;
			}
		}
	}
	return SpecialAbilityUpdate::vslot08(value);
}
