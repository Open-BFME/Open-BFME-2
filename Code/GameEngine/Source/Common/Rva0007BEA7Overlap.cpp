// cl: /MD
//
// ?rva0007BEA7@Rva007C454@@UAE_NABVSphereClass@@@Z @0x0007BEA7 (51B):
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
class SphereClass
{
public:
	float m_center[3];
	float m_radius;
};
class CollisionMath
{
public:
	enum OverlapType { POS, NEG, BOTH };
	static OverlapType Overlap_Test(const PlaneClass &plane, const SphereClass &sphere);
};
class Rva007C454
{
public:
	virtual bool rva0007BEA7(const SphereClass &sphere);
private:
	char m_pad00[0x3f8];
	PlaneClass *m_begin3FC;
	PlaneClass *m_end400;
};
bool Rva007C454::rva0007BEA7(const SphereClass &sphere)
{
	for (PlaneClass *p = m_begin3FC; p != m_end400; ++p) {
		if (CollisionMath::Overlap_Test(*p, sphere) == 1)
			return true;
	}
	return false;
}
