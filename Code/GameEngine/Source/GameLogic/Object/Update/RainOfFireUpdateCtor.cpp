// cl: /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "../../../../../../reference/shims/bfme_vector3_ctor_link/vector3.h"
#include "matrix3d.h"
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "RainOfFireUpdateView.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
//
// ??0RainOfFireUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AC0A8,
// 135 bytes. Behavior-side ctor (rowed instance factory 0x24F3B3 news 0x38
// with this ctor as its sole raw caller at 0x24F3DA), written against the
// TU's RainOfFireUpdate view so the compiler installs the four vptrs.
extern GameLogic *TheGameLogic;
RainOfFireUpdate::RainOfFireUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const RainOfFireUpdateModuleData *data =
		reinterpret_cast<const RainOfFireUpdateModuleData *>(m_moduleData);
	frame = UPDATE_SLEEP_FOREVER;
	darkness = 0.0f;
	scale = 1.0f;
	pending = 0.0f;
	ramp = 0.0f;
	if (data) {
		frame = TheGameLogic->getFrame();
		ramp = data->rampup == 0.0f ? 1.0f : 0.0f;
	}
}
