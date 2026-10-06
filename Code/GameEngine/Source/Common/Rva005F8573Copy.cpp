// cl: /MD
//
// ?Rva005F8573Copy@@YAPAURva005F8536@@PAU1@00@Z @0x005F8573 47B.
// Evidence: chain lane; stride-8 copy via rowed 0x005F8536 assignment;
// caller 0x005F85AB forwards first-last-dest; returns dest end with ret.

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	void *m_ptr;
};

struct Rva005F8536
{
	TreeHintRef00217D4C m_00;
	TreeHintRef00217D4C m_04;
	Rva005F8536 &operator=(const Rva005F8536 &other);
};

Rva005F8536 *__cdecl Rva005F8573Copy(Rva005F8536 *first, Rva005F8536 *last, Rva005F8536 *dest)
{
	int count = last - first;
	if (count <= 0)
		return dest;
	int n = count;
	do {
		*dest = *first;
		++first;
		++dest;
		--n;
	} while (n != 0);
	return dest;
}
