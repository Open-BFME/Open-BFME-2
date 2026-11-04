// cl: /MD
// PathfindLayer::AddArea (WorldBuilder name, pathfinder_layer.cpp line 145: push onto the +0x38 area list head).
// was ?rva003665BB@Rva003665BB@@QAEXPAX@Z 0x003665BB 16B via link old head at +0x38 into arg +0x3c
// Evidence: retail mov edx [ecx+38] mov eax [esp+4] mov [eax+3c] edx mov [ecx+38] eax ret 4; neighbours Rva0036658B/Rva0036666B (/O1 /MD); caller 0x0052F736
#include "../../Include/GameLogic/PathfindLayer.h"

// The area is a PolygonTrigger whose list link sits at +0x3C.
void PathfindLayer::AddArea(void *area)
{
	*(PolygonTrigger **)((char *)area + 0x3c) = m_triggers;
	m_triggers = (PolygonTrigger *)area;
}
