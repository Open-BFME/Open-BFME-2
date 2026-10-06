// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// Open-BFME5: BFME MeshGeometryClass::intersect_obbox_brute_force ABI slice.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include "always.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "inttest.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass
{
public:
	virtual void Retail_Vtable_Slot_0();
	virtual void Retail_Vtable_Slot_1();
	virtual void Retail_Vtable_Slot_2();
	virtual void Compute_Plane_Equations(Vector4 *array);

protected:
	Vector4 *get_planes(bool create);

	unsigned char m_unmodelled_04[0x14];
	unsigned int Flags;
	unsigned char m_unmodelled_1c[8];
	int PolyCount;
	unsigned char m_unmodelled_28[4];
	ShareBufferClass<TriIndex> *Poly;
	ShareBufferClass<Vector3> *Vertex;

	bool intersect_obbox_brute_force(OBBoxIntersectionTestClass &localtest);
};

// ?intersect_obbox_brute_force@MeshGeometryClass@@IAE_NAAVOBBoxIntersectionTestClass@@@Z
bool MeshGeometryClass::intersect_obbox_brute_force(OBBoxIntersectionTestClass &localtest)
{
	TriClass tri;
	const Vector3 *loc = Vertex->Get_Array();
	const TriIndex *polyverts = Poly->Get_Array();
	const Vector4 *norms = get_planes(true);

	if (norms != NULL && (Flags & 2) != 0) {
		Compute_Plane_Equations(const_cast<Vector4 *>(norms));
	}

	for (int srtri = 0; srtri < PolyCount; srtri++) {
		tri.V[0] = &(loc[polyverts[srtri][0]]);
		tri.V[1] = &(loc[polyverts[srtri][1]]);
		tri.V[2] = &(loc[polyverts[srtri][2]]);
		tri.N = (Vector3 *)&(norms[srtri]);

		if (CollisionMath::Intersection_Test(localtest.Box, tri)) {
			return true;
		}
	}
	return false;
}
