// cl: /DNDEBUG /MD /EHsc
// ?isUsingAirborneLocomotor@Object@@QBE_NXZ @0x0028B81E
// (36B): Object::isUsingAirborneLocomotor, BFME1 ObjectFields.cpp verbatim
// with BFME2 offsets. m_ai at +0x258, cur locomotor at AI+0x1f0, template at
// loco+0x04, surfaces at tmpl+0x14 with AIR as (1<<3). Callers include
// 0x004671E8 0x00429903 0x00483CC0.

#include "../../../Include/GameLogic/LocomotorTemplate.h"

// Retail 0x0028B81E inlines only the direct m_template->m_surfaces load,
// not the real Locomotor::getLegalSurfaces (AIUpdate.cpp's kept copy tests
// m_template==null and calls Overridable::getFinalOverride).
#include "../../../Include/GameLogic/LocomotorClass.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "object.h"

bool Object::isUsingAirborneLocomotor() const
{
	return (m_ai && m_ai->getCurLocomotor() && ((m_ai->getCurLocomotor()->m_template->m_surfaces & (1 << 3)) != 0));
}
