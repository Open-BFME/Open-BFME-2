// cl: /DNDEBUG /MD
// ?test@Rva00331682Holder@@QBE_NPBX@Z @0x00331682 37B. Overlap test over four
// dwords: returns true when any (this[i] & other[i]) != 0. Unblocks 17
// callers including 0x004BB8BA 0x004389FE 0x00331808. No donor. Honest
// address name per opaque convention.

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
private:
	int m_vals[4];
};

bool Rva00331682Holder::test(const void *other) const
{
	const int *o = (const int *)other;
	for (unsigned i = 0; i < 4; ++i)
		if (m_vals[i] & o[i])
			return true;
	return false;
}
