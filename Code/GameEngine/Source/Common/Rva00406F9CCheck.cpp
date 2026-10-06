// cl: /MD
// ?rva00406F9C@Rva00406F9C@@QAE_NPBX@Z @0x00406F9C 35B: 32-dword intersect test.
// If any [this+i] & [other+i] for i in 0..31 return true else false. Ret 4 is
// thiscall with one arg. Abuts 0x00406F51 (same /O1 /MD). Unblocks 11 incl 5
// ready. Callers 18 in 0x00409457 etc.
class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
private:
	unsigned m_data[32];
};

bool Rva00406F9C::rva00406F9C(const void *other)
{
	const unsigned *a = m_data;
	const unsigned *b = (const unsigned *)other;
	for (unsigned i = 0; i < 32; ++i) {
		if (a[i] & b[i])
			return true;
	}
	return false;
}
