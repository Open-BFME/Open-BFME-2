// cl: /DNDEBUG /MD
// ?Rva004F6BB3Fill@@YAPAURva004F6966@@PAU1@IPBU1@@Z @0x004F6BB3 (37B): uninitialized_fill_n.
// Fills count copies of 0xC-sized Rva004F6966 via rowed placement construct
// ?Rva004F6B69Construct@@YAXPAURva004F6966@@PBU1@@Z at 0x004F6B69 and returns
// the end pointer. Caller at 0x004F8AA3 walks into 0x004F8A35. Prev
// UninitializedCopy next Rva004F6B7BInit /O1 /DNDEBUG /MD.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
};

void Rva004F6B69Construct(Rva004F6966 *dst, const Rva004F6966 *src);

Rva004F6966 *Rva004F6BB3Fill(Rva004F6966 *dst, unsigned int count, const Rva004F6966 *src)
{
	Rva004F6966 *p = dst;
	unsigned int n = count;
	for (; n > 0; --n) {
		Rva004F6B69Construct(p, src);
		p = (Rva004F6966 *)((char *)p + 0xC);
	}
	return p;
}
