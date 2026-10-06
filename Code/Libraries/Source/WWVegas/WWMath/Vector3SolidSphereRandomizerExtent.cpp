// cl: /DNDEBUG /MD /EHsc
//
// ?Get_Maximum_Extent@Vector3SolidSphereRandomizer@@UAEMXZ,
// retail 0x007234A0 (4 bytes, fld [ecx+4]; ret).
// BFME1 v3_rnd.cpp verbatim: return Radius.
// Dedicated TU with the proven 8-byte model (vptr + Radius at +4).
// Vtable proof: both SolidSphere (0xCEFD00) and HollowSphere (0xCEFD1C)
// vtables carry 0x7234A0 in Get_Maximum_Extent slots 3 and 6 (masked
// 5-hit pattern disambiguated by file context plus slots); the two
// classes fold here so Hollow rides as an ICF-fold pin in the same commit.

class Vector3Randomizer
{
public:
	virtual float Get_Maximum_Extent(void) = 0;
};

class Vector3SolidSphereRandomizer : public Vector3Randomizer
{
public:
	virtual float Get_Maximum_Extent(void);

private:
	float Radius; // +4
};

// ?Get_Maximum_Extent@Vector3SolidSphereRandomizer@@UAEMXZ
float Vector3SolidSphereRandomizer::Get_Maximum_Extent(void)
{
	return Radius;
}
