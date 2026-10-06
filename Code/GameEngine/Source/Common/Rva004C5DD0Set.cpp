// cl: /Ob0

struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

struct Rva004C5DD0Pair
{
	Rva004C5DD0Ref *a;
	Rva004C5DD0Ref *b;
};

class Rva004C5DD0
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;

public:
	Rva004C5DD0 &set(const Rva004C5DD0Pair *p);
};

Rva004C5DD0 &Rva004C5DD0::set(const Rva004C5DD0Pair *p)
{
	Rva004C5DD0Ref *a = p->a;
	m_00 = a;
	if (a)
		a->m_refs++;
	Rva004C5DD0Ref *b = p->b;
	m_04 = b;
	if (b)
		b->m_refs++;
	return *this;
}

void __cdecl Rva004F6A52Assign(Rva004C5DD0 *dest, const Rva004C5DD0Pair *src)
{
	if (dest)
		dest->set(src);
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
