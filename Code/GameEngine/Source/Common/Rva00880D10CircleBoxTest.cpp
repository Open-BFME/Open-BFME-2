// cl: /DNDEBUG /MD /EHsc
// Open-BFME: address-derived reconstruction of retail RVA 0x00880D10.
// Builds a rotated BfmeBoxF0 from a center/extent/angle source struct and
// forwards to BfmeBoxF0::contains (retail 0x006C0440).
// No caller names this cdecl helper, so identity is not recovered; the two
// argument structs are laid out only as far as the bytes this body touches.
// FSINCOS has no portable VC7.1 intrinsic, so the sin/cos pair is inline asm
// per the anti-lift policy's proven-codegen-blocker exception.

typedef float Real;

extern const float BfmeZeroRange;

struct BfmePointF0
{
	Real x;
	Real y;
};

class BfmeBoxF0
{
public:
	bool contains(const BfmePointF0 *point, Real radius) const;

	Real m_centerX;
	Real m_centerY;
	Real m_axisX;
	Real m_axisY;
	Real m_perpX;
	Real m_perpY;
	Real m_extentX;
	Real m_extentY;
};

struct Rva00880D10Subject
{
	unsigned char m_pad0[8];
	Real m_radius;
	unsigned char m_pad1[0x18];
	BfmePointF0 m_point;
};

struct Rva00880D10Info
{
	unsigned char m_pad0[8];
	Real m_extentX;
	Real m_extentY;
	unsigned char m_pad1[0x14];
	Real m_centerX;
	Real m_centerY;
	unsigned char m_pad2[4];
	Real m_angle;
};

bool BfmeBoxF0::contains(const BfmePointF0 *point, Real radius) const
{
	Real deltaX = point->x - m_centerX;
	Real deltaY = point->y - m_centerY;
	Real proj[2];
	proj[0] = deltaY * m_axisY + deltaX * m_axisX;
	proj[1] = deltaY * m_perpY + deltaX * m_perpX;
	Real distSq = BfmeZeroRange;
	if (proj[0] < -m_extentX)
	{
		Real distAxis = proj[0] + m_extentX;
		distSq = distAxis * distAxis;
	}
	else if (proj[0] > m_extentX)
	{
		Real distAxis = proj[0] - m_extentX;
		distSq = distAxis * distAxis;
	}
	if (proj[1] < -m_extentY)
	{
		Real distPerp = proj[1] + m_extentY;
		distSq += distPerp * distPerp;
	}
	else if (proj[1] > m_extentY)
	{
		Real distPerp = proj[1] - m_extentY;
		distSq += distPerp * distPerp;
	}
	if (distSq > radius * radius)
		return false;
	return true;
}

bool rva00880D10(Rva00880D10Subject *subject, Rva00880D10Info *info)
{
	Real extentY = info->m_extentY;
	Real extentX = info->m_extentX;
	Real angle = info->m_angle;

	BfmeBoxF0 box;
	box.m_centerX = info->m_centerX;
	box.m_centerY = info->m_centerY;

	Real cosA, sinA;
	__asm {
		fld     angle
		fsincos
		fstp    cosA
		fstp    sinA
	}

	box.m_perpX = -sinA;
	box.m_extentX = extentX;
	box.m_extentY = extentY;
	box.m_axisX = cosA;
	box.m_axisY = sinA;

	const BfmePointF0 *point = &subject->m_point;
	box.m_perpY = cosA;

	return box.contains(point, subject->m_radius);
}
