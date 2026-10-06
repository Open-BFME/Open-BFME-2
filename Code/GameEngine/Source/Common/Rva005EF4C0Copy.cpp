// cl: /MD
// ?Rva005EF4C0Copy@@YAPAVRva005EEFD2@@PAV1@00@Z, retail 0x005EF4C0, 47 bytes.
// Forward copy for Rva005EEFD2 holders using rowed assignment 0x005EEFD2.
// count = last-first; if <=0 return dest; else for (i=n;i!=0;--i)
// { *dest = *first; ++first; ++dest; } return dest. Caller at 0x005EF54D.

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

Rva005EEFD2 * __cdecl Rva005EF4C0Copy(Rva005EEFD2 *first, Rva005EEFD2 *last, Rva005EEFD2 *dest)
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
