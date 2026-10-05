// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /arch:SSE /MD
// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z 0x00354EB9 61B pickup range squared-distance check
// Evidence: callers at 0x003553D4 and 0x003554A5 pass two point pointers __cdecl; uses g_bfmePickupScanRange float at 0x007CE190; returns 1 when range exceeds dist2.

extern float g_bfmePickupScanRange;

struct Rva00354EB9Point
{
	float m_00;
	float m_04;
};

// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z present-unmatched
int Rva00354EB9Check(Rva00354EB9Point const *a, Rva00354EB9Point const *b)
{
	float dy = a->m_04 - b->m_04;
	float dy2 = dy * dy;
	float dx = a->m_00 - b->m_00;
	float dx2 = dx * dx;
	float dist2 = dx2 + dy2;
	int result = 0;
	if (g_bfmePickupScanRange > dist2) {
		++result;
	}
	return result;
}
