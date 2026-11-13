// cl: /O1 /DNDEBUG /MD
//
// ??0GateProxyBehaviorModuleData@@QAE@XZ, retail 0x0024E359, 18 bytes.
// Dedicated TU: derived nullary ctor running the pinned GateOpenAndClose
// base ctor (0x498E2E) then installing the derived vtable (pinned ??_7 at
// 0x00BEF380), return-this tail. Operator new uninvolved. Recipe:
// AIGateUpdateModuleDataCtor.cpp (return-this). Class identity is the
// GateProxyBehavior pool key (rowed at 0x24E30E) ending where the 5B
// vtable-getter at 0x24E353 begins, adjacent to this ctor; the base triple is rowed
// at 0x498E2E/0x253F0E/0x253F1F.

#include "../../../../Include/GameLogic/Module/GateOpenAndCloseBehaviorModuleData.h"

#include "../../../../Include/GameLogic/Module/GateProxyBehaviorModuleData.h"

// ??0GateProxyBehaviorModuleData@@QAE@XZ @0x24E359
inline GateProxyBehaviorModuleData::GateProxyBehaviorModuleData()
	: GateOpenAndCloseBehaviorModuleData()
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeGateProxyBehaviorModuleDataInlineAnchor@@YAXPAVGateProxyBehaviorModuleData@@@Z absent-from-retail
void _bfmeGateProxyBehaviorModuleDataInlineAnchor(GateProxyBehaviorModuleData *gateProxyBehaviorModuleData)
{
    gateProxyBehaviorModuleData->GateProxyBehaviorModuleData::GateProxyBehaviorModuleData();
}
#pragma inline_depth()
