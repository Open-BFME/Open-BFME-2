// cl: /DNDEBUG /MD
//
// ?Rva00318DECCopy@@YAPAVRva00318B5C@@PBV1@0PAV1@PAXH@Z, retail 0x00318DEC, 60 bytes.
// Count is (last-first)>>4 with early-out returning result. Loop copies the
// three trailing dwords of a 0x10 polymorphic struct skipping the vtable
// slot via member copies. Caller at 0x0031968A passes its three
// pointers plus a tag pointer and 0. Sibling fill at 0x00318D9B shares the
// 0x10 stride and Rva00318B5C model. Identity beyond the stride is unproven
// so the name stays honest address-derived.

class Rva00318B5C
{
public:
	virtual ~Rva00318B5C();
	int m_4;
	int m_8;
	int m_C;
};

Rva00318B5C *Rva00318DECCopy(const Rva00318B5C *first, const Rva00318B5C *last, Rva00318B5C *result, void *unused, int unused2)
{
	int n = (int)(last - first);
	if (n > 0)
	{
		const int *sp = (const int *)first + 3;
		for (; n > 0; --n, sp += 4, ++result)
		{
			result->m_4 = sp[-2];
			result->m_8 = sp[-1];
			result->m_C = sp[0];
		}
	}
	return result;
}
