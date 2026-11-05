// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include/Lib
//
// ?rva000EE04A@W3DPropBuffer@@QAEXPBUCoord3D@@M@Z, retail 0x000EE04A..0x000EE132
// (232 bytes, thiscall RET 8): clears every prop of the buffer within a radius
// of a position (the radius variant of removeProp): for each live prop whose
// squared distance to the position is below radius squared, zero its location
// and bounds centre, set the bounds radius to 1.0, mark the type -1, release
// the render object and flag the buffer as changed. Layout (retail-measured):
// 4000 props of 0x30 bytes from +4, count at +0x2EE04, changed flag +0x2EE08.
// Positions are read through retail's non-POD Coord3D (Lib/Coord3DCtorView.h,
// member-wise user copy constructor): the by-value copies load all six
// components into registers before the subtractions; the dead copy stores
// vanish. The loop test is written as retail evaluates it, !(dist < r*r).
// The bounds radius constant is the shared rdata literal 1.0f (0x007BB8D8).
// Evidence: native bytes plus the removeProp sibling (W3DPropBuffer.cpp); the
// method name remains address-derived; the buffer uses its canonical layout.
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
#include "../../../Include/W3DDevice/GameClient/W3DPropBufferClass.h"
class RenderObjClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}
private:
	int m_refCount;
};
void W3DPropBuffer::rva000EE04A(const Coord3D *pos, float radius)
{
	for (int i = 0; i < m_numProps; ++i)
	{
		if (m_props[i].m_robj == 0)
			continue;
		Coord3D a(*pos);
		Coord3D b(m_props[i].location);
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float distSq = dz * dz + dy * dy + dx * dx;
		if (!(distSq < radius * radius))
			continue;
		m_props[i].location.set(0, 0, 0);
		RenderObjClass *robj = m_props[i].m_robj;
		m_props[i].propType = -1;
		if (robj != 0)
		{
			robj->Release_Ref();
			m_props[i].m_robj = 0;
		}
		m_props[i].bounds.Center.Set(0, 0, 0);
		m_props[i].bounds.Radius = 1.0f;
		m_anythingChanged = true;
	}
}
