// cl: /MD
// ?Rva005EF000CopyBackward@@YAPAVRva005EEFD2@@PAV1@00@Z, retail 0x005EF000, 47 bytes.
// copy_backward for Rva005EEFD2 holders using rowed assignment 0x005EEFD2.
// count = last-first; if <=0 return dest; else do { --last; --dest;
// *dest = *last; } while (--count). Caller at 0x005EF47E.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva005EEFD2Target
{
	int m_00;
	TargetRef00217D4C m_04;
};

class Rva005EEFD2
{
public:
	Rva005EEFD2 &operator=(const Rva005EEFD2 &other);

private:
	Rva005EEFD2Target *m_ptr;
};

Rva005EEFD2 * __cdecl Rva005EF000CopyBackward(Rva005EEFD2 *first, Rva005EEFD2 *last, Rva005EEFD2 *dest)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		--last;
		--dest;
		*dest = *last;
	}
	return dest;
}
