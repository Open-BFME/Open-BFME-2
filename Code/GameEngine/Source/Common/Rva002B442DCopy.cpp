// cl: /MD
// ?Rva002B442DCopy@@YAPAVRva002B2F97@@PAV1@00@Z, retail 0x002B442D, 47 bytes.
// Forward copy for Rva002B2F97 holders using rowed assignment 0x002B2F97.
// Same shape as Rva005EF4C0Copy for Rva005EEFD2. Caller at 0x002B4423.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva002B2F97Target
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ac;
};

class Rva002B2F97
{
public:
	Rva002B2F97 &operator=(const Rva002B2F97 &other);

private:
	Rva002B2F97Target *m_ptr;
};

Rva002B2F97 * __cdecl Rva002B442DCopy(Rva002B2F97 *first, Rva002B2F97 *last, Rva002B2F97 *dest)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}
