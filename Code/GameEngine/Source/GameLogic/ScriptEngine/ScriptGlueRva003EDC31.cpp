// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva003EDC31@Rva0020DXXXElem@@QAEXXZ @0x003EDC31 101B: refresh cached rect from TerrainLogic::getMaximumPathfindExtent (slot 0x30) then walk pointer array with pinned 0x569AA8.
// Evidence: caller Rva0020D7F9Family.cpp; TheTerrainLogic rowed; pinned rva00569AA8; sibling ScriptGlueRva003EDC16 walk; movss needs arch SSE.
#include "../../../Include/GameLogic/Rva00569AA8.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"
#include "../../../Include/GameLogic/TerrainLogic.h"

class Rva0020DXXXElem
{
public:
	void rva003EDC31();
private:
	char m_pad00[0x1C];
	void **m_begin;
	void **m_end;
	char m_pad24[0xC4];
	float m_E8;
	float m_EC;
	float m_F0;
	float m_F4;
};

void Rva0020DXXXElem::rva003EDC31()
{
	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent(&extent);
	m_F0 = extent.hi.x;
	m_F4 = extent.hi.y;
	m_E8 = extent.lo.x;
	m_EC = extent.lo.y;
	for (void **it = m_begin; it != m_end; ++it)
		((Rva00569AA8 *)*it)->rva00569AA8();
}
