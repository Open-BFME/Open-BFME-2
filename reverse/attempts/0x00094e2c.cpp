// ?Rva00094E2CGet@@YGMMMM@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva00094E2CGet@@YGMMMM@Z @0x00094E2C 147B
// Free-function distance-minus-base: if global ptr null return float const;
// else copy 12B point at +0xD4, fabs per-axis diffs, sqrt sum squares,
// return base float at +0xE0 minus length.
// Evidence: vslot 22 of 0x007C8208 Gen006E2310; no callers; neighbours
// VslotSmallBodiesA and OpaqueScalarDeletingDtors; callees rowed ji fabs
// plus ji sqrt; globals g_00DE4880 g_00BC7484 stopgaps.
extern void *g_00DE4880;
extern float g_00BC7484;
extern "C" double fabs(double v);
extern "C" double sqrt(double v);

struct Vec3 {
	float x;
	float y;
	float z;
};

struct GState {
	char m_pad[0xD4];
	Vec3 m_p;
	float m_e0;
};

// ?Rva00094E2CGet@@YGMMMM@Z present-unmatched
float __stdcall Rva00094E2CGet(float a, float b, float c)
{
	GState *g = (GState *)g_00DE4880;
	float v = g_00BC7484;
	if (g) {
		Vec3 p = g->m_p;
		v = g->m_e0;
		float dx = (float)fabs((double)(p.x - a));
		float dy = (float)fabs((double)(p.y - b));
		float dz = (float)fabs((double)(p.z - c));
		float len = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
		v -= len;
	}
	return v;
}
