// cl: /DNDEBUG /MD /EHsc
// ?Rva0028867DCheck@@YA_NPBX@Z, retail 0x0028867D, 37 bytes.
// Multiplayer-gated zero-check on bytes at +0x101/+0x102 via TheBfmeGlob 0x00DFE78C gate (rowed bfmeCall939D 0x0023C6FD).
// Evidence: 5 callers home object into ESI for post-call reads (0x00288937 0x0028895A 0x00288DCD 0x00288E59 0x002897E6);
// adjacent byte getters at 0x002885EC (+0x102) and 0x002885F3 (+0x101) prove the offsets;
// same-gate donor Rva0031DF89 selects offsets via TheBfmeGlob; static ESI-arg convention per Rva008B8F80 precedent.

extern class GameLogic *TheGameLogic;

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

struct Rva0028867DData
{
	char m_pad[0x101];
	unsigned char m_b101;
	unsigned char m_b102;
};

static bool Rva0028867DCheck(const void *p)
{
	const Rva0028867DData *d = (const Rva0028867DData *)p;
	if (TheBfmeGlob->bfmeCall939D())
		return d->m_b101 == 0;
	return d->m_b102 == 0;
}

// absent-from-retail: keeps the static alive with the ESI argument convention.
bool Rva0028867DCaller(const void *p)
{
	if (p)
		return Rva0028867DCheck(p);
	return false;
}

// ?Rva0028891FCheck@@YG_NPBQBXPBX@Z, retail 0x0028891F, 33 bytes.
// Chain on Rva0028867DCheck: null guard plus equality-against-first guard then ESI call with +8.
// Evidence: callers at 0x00288ADA plus 19 others push two dwords; same-TU static call gives lea esi call shape.
bool __stdcall Rva0028891FCheck(const void *const *p1, const void *p2)
{
	if (!p1)
		return false;
	if (p2 == *p1)
		return false;
	return Rva0028867DCheck((const char *)p2 + 8);
}
