// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?Cull_Sphere@Rva007C454@@UBE_NABVSphereClass@@@Z @0x0007BEA7 (51B):
// Slot-129 overlap scan: walks PlaneClass array [+0x3FC,+0x400) stride 16
// via rowed CollisionMath::Overlap_Test(Plane,Sphere) and returns true on
// the first OverlapType 1, else false. Class proven by vtable 0x007C6C58
// plus ctor TU Rva007C454Ctor.cpp layout; slot identity from packet.
// Evidence: rowed Overlap_Test 0x007151F0; no callers yet (vtable ref).
class PlaneClass
{
public:
	float m_n[3];
	float m_d;
};
#include "../../../Libraries/Source/WWVegas/WWMath/SphereClass.h"
class CollisionMath
{
public:
	enum OverlapType { POS, NEG, BOTH };
	static OverlapType Overlap_Test(const PlaneClass &plane, const SphereClass &sphere);
};
class Rva007C454
{
public:
	virtual bool Cull_Sphere(const SphereClass &sphere) const;
private:
	char m_pad00[0x3f8];
	PlaneClass *m_begin3FC;
	PlaneClass *m_end400;
};
bool Rva007C454::Cull_Sphere(const SphereClass &sphere) const
{
	for (PlaneClass *plane = m_begin3FC; plane != m_end400; ++plane) {
		if (CollisionMath::Overlap_Test(*plane, sphere) == 1)
			return true;
	}
	return false;
}
