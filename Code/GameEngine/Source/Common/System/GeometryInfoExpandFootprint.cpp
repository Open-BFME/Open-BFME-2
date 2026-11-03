// cl: /O2 /DNDEBUG /MD /EHsc
// Single-function extraction of BFME1 Code/GameEngine/Source/Common/System/Geometry.cpp
// ?expandFootprint@GeometryInfo@@QAEXM@Z (b1 0x0087F2B0, 53B, T2 byte-identical donor).
// Grows every enabled footprint shape by radius, then recomputes the extents
// through the rowed calcBoundingStuff pin at 0x006BE700.
// /O2 keeps the retail do-while guard plus load-then-test loop tail; /O1
// restructures to a jump-in while with compare-memory (47B, wrong).

struct GeometryShape
{
	char m_prefix[0x08];
	float m_radiusX;
	float m_radiusY;
	char m_suffix[0x10];
	bool m_enabled;
	char m_tail[0x03];
};

#include "../../../Include/Common/Geometry.h"

void GeometryInfo::expandFootprint(float radius)
{
	GeometryShape *shape = reinterpret_cast<GeometryShape *>(field2c[0]);
	if (shape != reinterpret_cast<GeometryShape *>(field2c[1]))
	{
		do
		{
			if (shape->m_enabled)
			{
				shape->m_radiusX += radius;
				shape->m_radiusY += radius;
			}
			++shape;
		}
		while (shape != reinterpret_cast<GeometryShape *>(field2c[1]));
	}
	calcBoundingStuff();
}
