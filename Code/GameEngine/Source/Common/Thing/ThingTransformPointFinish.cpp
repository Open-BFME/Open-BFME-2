// ?transformPoint@Thing@@QAEXPBUCoord3D@@PAU2@@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Thing.h"

// Transform a point by the Thing's world matrix. Retail 0x0030A812, 191 bytes.
// Donor: ZH Thing::transformPoint plus Matrix3D::Transform_Vector, with the
// type conversion spelled as scalar locals so the SSE row order is explicit.
// Evidence: m_transform at this+0x8; callers 0x00460CBA 0x00482C4A 0x00483DA4.
//
// Rows 1 and 2 carry their partial sums in named temporaries (a0/a1/a2,
// b0/b1/b2) rather than in one expression each. That is what reproduces retail's
// SSE schedule: the row-0 result stays a single expression and reads
// z,y,x, while the two following rows read z,x,y, and the allocator only
// interleaves the matrix loads that way once each row's accumulation is
// spelled as an explicit chain.
void Thing::transformPoint(const Coord3D *in, Coord3D *out)
{
	if (in == NULL || out == NULL)
		return;
	float x = in->x;
	float y = in->y;
	float z = in->z;
	float rx = m_transform[0][2] * z + m_transform[0][1] * y + m_transform[0][0] * x + m_transform[0][3];
	float a0 = m_transform[1][2] * z;
	float a1 = a0 + m_transform[1][0] * x;
	float a2 = a1 + m_transform[1][1] * y;
	float ry = a2 + m_transform[1][3];
	float b0 = m_transform[2][2] * z;
	float b1 = b0 + m_transform[2][0] * x;
	float b2 = b1 + m_transform[2][1] * y;
	float rz = b2 + m_transform[2][3];
	Coord3D tmp;
	tmp.x = rx;
	tmp.y = ry;
	tmp.z = rz;
	*out = tmp;
}