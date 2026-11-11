// cl: /Ob0

struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

#include "../../Include/Common/Rva004C5DD0Pair.h"

class Rva004C5DD0
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;

public:
	Rva004C5DD0(const Rva004C5DD0 &other);
};

Rva004C5DD0::Rva004C5DD0(const Rva004C5DD0 &other)
{
	Rva004C5DD0Ref *firstRef = other.m_00;
	m_00 = firstRef;
	if (firstRef)
		firstRef->m_refs++;
	Rva004C5DD0Ref *secondRef = other.m_04;
	m_04 = secondRef;
	if (secondRef)
		secondRef->m_refs++;
}

void __cdecl Rva004F6A52Assign(Rva004C5DD0 *dest, const Rva004C5DD0Pair *src)
{
	if (dest)
		dest->Rva004C5DD0::Rva004C5DD0(*(const Rva004C5DD0 *)src);
}

Rva004C5DD0 *__cdecl Rva004F6AAEFill(Rva004C5DD0 *dest, unsigned int count, const Rva004C5DD0Pair *value)
{
	Rva004C5DD0 *cur = dest;
	for (; count > 0; --count, ++cur)
		Rva004F6A52Assign(cur, value);
	return cur;
}

Rva004C5DD0 *__cdecl Rva004F6A88Copy(const Rva004C5DD0Pair *first, const Rva004C5DD0Pair *last, Rva004C5DD0 *result)
{
	Rva004C5DD0 *cur = result;
	for (; first != last; ++first, ++cur)
		Rva004F6A52Assign(cur, first);
	return cur;
}
