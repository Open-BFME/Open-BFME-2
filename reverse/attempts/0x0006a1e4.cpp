// ?recalculate@LineSegClass@@IAEXXZ
// partial score=0.93 date=2026-09-07
// cl: /G7 /Oy- /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep

#include "vector3.h"

class LineSegClass
{
public:
	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;


protected:
	void recalculate(void);
};

void LineSegClass::recalculate(void)
{
	DP = P1 - P0;
	Dir = DP;
	Dir.Normalize();
	Length = DP.Length();
}
