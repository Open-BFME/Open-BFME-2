// Ported from BFME1; retain only after independent BFME2 placement.
typedef float Real;

inline const Real &bfmeMax(const Real &a, const Real &b)
{
	return (a > b) ? a : b;
}

#include "../../Include/Common/Geometry.h"

// Retail shape-vector elements are 0x24 bytes; the canonical GeometryInfo
// retains the native vector's begin/end/capacity pointers in field2c.
struct BfmeShape
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	unsigned char m_unmodelled_00c[0x18 - 0x0C];
	Real m_offsetZ;
	unsigned char m_unmodelled_01c[0x20 - 0x1C];
	bool m_enabled;
	bool m_flag21;
	unsigned char m_unmodelled_022[0x24 - 0x22];
};

Real GeometryInfo::getMaxHeightAbovePosition(void) const
{
	Real best = 0.0f;

	for (const BfmeShape *shape = reinterpret_cast<const BfmeShape *>(field2c[0]);
		 shape != reinterpret_cast<const BfmeShape *>(field2c[1]); ++shape)
	{
		if (!shape->m_enabled)
			continue;

		Real height = 0.0f;
		switch (shape->m_type)
		{
			case GEOMETRY_SPHERE:
				height = shape->m_majorRadius;
				break;
			case GEOMETRY_CYLINDER:
			case GEOMETRY_BOX:
				height = shape->m_height;
				break;
		}

		height += shape->m_offsetZ;
		best = bfmeMax(height, best);
	}

	return best;
}


Real GeometryInfo::rva006BD830(void) const
{
	Real best = 0.0f;

	for (const BfmeShape *shape = reinterpret_cast<const BfmeShape *>(field2c[0]);
		 shape != reinterpret_cast<const BfmeShape *>(field2c[1]); ++shape)
	{
		if (!shape->m_enabled)
			continue;
		if (!shape->m_flag21)
			continue;

		Real height = 0.0f;
		switch (shape->m_type)
		{
			case GEOMETRY_SPHERE:
				height = shape->m_majorRadius;
				break;
			case GEOMETRY_CYLINDER:
			case GEOMETRY_BOX:
				height = shape->m_height;
				break;
		}

		height += shape->m_offsetZ;
		best = bfmeMax(height, best);
	}

	return best;
}
