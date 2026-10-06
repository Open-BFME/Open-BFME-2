// cl: /MD
// ?Rva00275D9FGet@@YA_NPBVRva00263546@@@Z @0x00275D9F 47B: one-time init global mask then overlap test.
// Evidence: chain of 0x001E4912 you landed; callers at 0x00277585 0x00279294 0x002792A0; globals 0xDFEBF0 0xDFEC3C.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a, unsigned int b, unsigned int c);
	unsigned m_bits[19];
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
	int m_mask[19];
};

struct Rva00275D9FMaskStorage
{
	unsigned int m_bits[19];
};

// g_Va00DFEBF0: VA 0x00DFEBF0 (.data/bss); the shared 19-dword mask view is
// 0x4C bytes and zero-filled in game.dat.
Rva00275D9FMaskStorage g_Va00DFEBF0;
// g_Va00DFEC3C: VA 0x00DFEC3C (.data/bss); the one-time-init flag is zero-filled.
int g_Va00DFEC3C;

#define GlobalMask (reinterpret_cast<Rva001E4912 *>(&g_Va00DFEBF0))
#define GlobalMask2 (reinterpret_cast<const Rva00263546 *>(&g_Va00DFEBF0))
#define InitFlag g_Va00DFEC3C

bool __cdecl Rva00275D9FGet(const Rva00263546 *a)
{
	if ((InitFlag & 1) == 0) {
		InitFlag |= 1;
		GlobalMask->rva001E4912(0, 0x43, 0x45);
	}
	return a->rva00263546(GlobalMask2);
}
