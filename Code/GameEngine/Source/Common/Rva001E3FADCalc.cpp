// cl: /MD
// ?Rva001E3FADGet@@YAMPBUCoord3D@@0@Z, retail 0x001E3FAD, 80 bytes.
// Diff of two Coord3D then normalize then (y+x)*BfmeZeroRange+z.
// Evidence: calls rowed ?normalize@Coord3D@@QAEXXZ 0x000035B6, uses BfmeZeroRange VA 0x00BBAEAC.
// Callers at 0x001E9BEC 0x001E9C51 in FUN_005e9a00. Owner unproven honest Rva name.

// The data ledger identifies the shared read-only operand as float +0.0.

struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

float __cdecl Rva001E3FADGet(const Coord3D *a, const Coord3D *b)
{
	Coord3D d;
	d.x = b->x;
	d.y = b->y;
	d.z = b->z;
	d.x -= a->x;
	d.y -= a->y;
	d.z -= a->z;
	d.normalize();
	return (d.y + d.x) * 0.0f + d.z;
}
