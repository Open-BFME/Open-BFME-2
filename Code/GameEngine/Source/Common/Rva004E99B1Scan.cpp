// cl: /O1 /DNDEBUG /MD
//
// ?rva004E99B1@@YAPAXPAX@Z @0x004E99B1 37B.
// Scan of the global RvaVector g_00E04484 (same view as Rva004E9B70Finish.cpp):
// walk [m_begin, m_end) and return the first entry whose +0x44 field equals
// the key, else null. Retail is end-first loads, jmp-to-compare loop, je to
// a reloading return (37B).
struct Rva004E99B1Rec
{
	char m_pad[0x44];
	void *m_44;
};

struct RvaVector
{
	Rva004E99B1Rec **m_begin;
	Rva004E99B1Rec **m_end;
	Rva004E99B1Rec **m_cap;
};

extern RvaVector g_00E04484;

void *rva004E99B1(void *key)
{
	Rva004E99B1Rec **end = g_00E04484.m_end;
	for (Rva004E99B1Rec **p = g_00E04484.m_begin; p != end; ++p) {
		if ((*p)->m_44 == key)
			return *p;
	}
	return 0;
}
