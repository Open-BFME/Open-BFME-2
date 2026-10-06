// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z
// partial score=0.92 date=2026-10-06
// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /arch:SSE /MD
// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z 0x00354EB9 61B pickup range squared-distance check
// Evidence: callers at 0x003553D4 and 0x003554A5 pass two point pointers __cdecl; uses g_bfmePickupScanRange float at 0x007CE190; returns 1 when range exceeds dist2.

extern float g_bfmePickupScanRange;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva00354EB9Point
{
	float m_00;
	float m_04;
};

// ?Rva00354EB9Check@@YAHPBURva00354EB9Point@@0@Z present-unmatched
int Rva00354EB9Check(Rva00354EB9Point const *a, Rva00354EB9Point const *b)
{
	float dx;
	float dy;
	float dx2;
	float dy2;
	float dist2;
	int result;
	dy = a->m_04 - b->m_04;
	dy2 = dy * dy;
	_ReadWriteBarrier();
	dx = a->m_00 - b->m_00;
	dx2 = dx * dx;
	dist2 = dy2;
	dist2 += dx2;
	_ReadWriteBarrier();
	result = 0;
	if (g_bfmePickupScanRange > dist2) {
		++result;
	}
	return result;
}
