// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Trimmed to the two T1 bodies the sweep places; the donor's other
// definitions are omitted.

// Both are the same guarded indirect call; only the vtable slot the function
// pointer sits at differs (0x1E0 vs 0x1E4), so retail's two bodies differ only
// in that displacement.

struct BfmeThingEHCa
{
	int bfmeGoEHCa(void *a, void *b, void *c);
	unsigned char m_bfmeHead[0x1e0];
	int (__cdecl *m_bfmeFn)(void *self, void *a, void *b, void *c);
};

int BfmeThingEHCa::bfmeGoEHCa(void *a, void *b, void *c)
{
	int (__cdecl *fn)(void *, void *, void *, void *) = m_bfmeFn;
	if (fn)
		return fn(this, a, b, c);
	return 0;
}

struct BfmeThingEHCb
{
	int bfmeGoEHCb(void *a, void *b, void *c);
	unsigned char m_bfmeHead[0x1e4];
	int (__cdecl *m_bfmeFn)(void *self, void *a, void *b, void *c);
};

int BfmeThingEHCb::bfmeGoEHCb(void *a, void *b, void *c)
{
	int (__cdecl *fn)(void *, void *, void *, void *) = m_bfmeFn;
	if (fn)
		return fn(this, a, b, c);
	return 0;
}