// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?Rva00264237Check@@YAHPBUCoord3D@@0@Z
// 0x00264237 61B: free 2D distance-squared check. Loads x/y from two Coord3D,
// compares dx*dx+dy*dy against g_00BF9680. Callers in 0x0026CF11 twice.
// Prev Rva00263910Goal has same /arch:SSE flags.
struct Coord3D
{
	float x, y, z;
};

extern const float g_00BF9680;

int Rva00264237Check(const Coord3D *a, const Coord3D *b)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float d2 = dy * dy + dx * dx;
	return d2 < g_00BF9680 ? 1 : 0;
}
