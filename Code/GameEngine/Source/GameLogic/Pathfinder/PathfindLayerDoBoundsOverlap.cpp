// cl: /O1 /DNDEBUG /MD
// PathfindLayer::DoBoundsOverlap, retail 0x003665CB (91 bytes):
// ?DoBoundsOverlap@PathfindLayer@@QAE_NPBUIRegion2D@@@Z
// Identity (target): WorldBuilder's debug pathfinder_layer.cpp
// PathfindLayer::DoBoundsOverlap walks the layer's polygon triggers calling
// PolygonTrigger::getBounds (WB-named, 0x002E3978), as retail does.
// Body (target): true when the given cell region, grown by 10 on every
// side, overlaps the bounds of any trigger in the layer's list (+0x38,
// linked through +0x3C).
#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

#include "../../../Include/GameLogic/PolygonTrigger.h"

#include "../../../Include/GameLogic/PathfindLayer.h"

bool PathfindLayer::DoBoundsOverlap(const IRegion2D *bounds)
{
	for (PolygonTrigger *trigger = m_triggers; trigger; trigger = trigger->getNext())
	{
		IRegion2D triggerBounds;
		trigger->getBounds(&triggerBounds);
		if (bounds->hi.x + 10 > triggerBounds.lo.x && bounds->hi.y + 10 > triggerBounds.lo.y &&
			bounds->lo.x - 10 < triggerBounds.hi.x && bounds->lo.y - 10 < triggerBounds.hi.y)
			return true;
	}
	return false;
}
