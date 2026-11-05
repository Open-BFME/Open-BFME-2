// Ported from BFME1; retain only after independent BFME2 placement.
// Legacy link-wide compatibility alias; consumer cleanup is a separate change.
#pragma comment(linker, "/alternatename:?getCenterPosition@GeometryInfo@@QBEXABUCoord3D@@AAU2@@Z=?getCenterPosition@GeometryInfo@@ABEXABUCoord3D@@AAU2@@Z")

// Keep the MSVC float overloads local; their inlined operations stay retail-exact.
#define inline static inline
#include <math.h>
#undef inline

typedef float Real;

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Include/Common/Geometry.h"

inline Real bfmeSqr(Real value)
{
	return value * value;
}

void GeometryInfo::calcPitches(const Coord3D &thisPos, const GeometryInfo &that,
	const Coord3D &thatPos, Real &minPitch, Real &maxPitch) const
{
	Coord3D thisCenter;
	// The canonical scalar fields at +0x18/+0x1C/+0x20 hold the center triple.
	thisCenter = *(const Coord3D *)&field18;
	thisCenter.x += thisPos.x;
	thisCenter.y += thisPos.y;
	thisCenter.z += thisPos.z;

	Real dxy = sqrt(bfmeSqr(thatPos.x - thisCenter.x) +
		bfmeSqr(thatPos.y - thisCenter.y));

	Real dz = (thatPos.z + that.getMaxHeightAbovePosition()) - thisCenter.z;
	maxPitch = atan2(dz, dxy);

	Real below = that.getMaxHeightBelowPosition();
	dz = (thatPos.z - below) - thisCenter.z;
	minPitch = atan2(dz, dxy);
}
