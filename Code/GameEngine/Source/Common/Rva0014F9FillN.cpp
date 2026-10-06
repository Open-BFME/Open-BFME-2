// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014F90DFillN@@YAPAVRva0014F480@@PAV1@IABV1@@Z retail 0x0014F90D 27B, ?Rva0014F951FillN@@YAPAVRva0014F4A1@@PAV1@IABV1@@Z retail 0x0014F951 27B, ?Rva0014F9CCFillN@@YAPAVRva0014F4C2@@PAV1@IABV1@@Z retail 0x0014F9CC 27B: uninitialized_fill_n dispatchers creating Tag at [ebp-1] and tail-calling fill_n helpers 0x0014F5AB 0x0014F5E5 0x0014F61F. Callers 0x00150749 0x00150827 0x0015090D insert paths.

class Rva0014F401
{
public:
	virtual void dummy();
	Rva0014F401(const Rva0014F401 &other);
};

class Rva0014F480 : public Rva0014F401
{
public:
	Rva0014F480(const Rva0014F480 &other);
	virtual void dummy();
	int m_04;
};

class Rva0014F4A1 : public Rva0014F401
{
public:
	Rva0014F4A1(const Rva0014F4A1 &other);
	virtual void dummy();
	int m_04;
};

class Rva0014F4C2 : public Rva0014F401
{
public:
	Rva0014F4C2(const Rva0014F4C2 &other);
	virtual void dummy();
	int m_04;
};

struct Tag
{
	char x;
};

Rva0014F480 *__cdecl Rva0014F5ABFillN(Rva0014F480 *result, unsigned count, const Rva0014F480 &value, const Tag &tag);
Rva0014F4A1 *__cdecl Rva0014F5E5FillN(Rva0014F4A1 *result, unsigned count, const Rva0014F4A1 &value, const Tag &tag);
Rva0014F4C2 *__cdecl Rva0014F61FFillN(Rva0014F4C2 *result, unsigned count, const Rva0014F4C2 &value, const Tag &tag);

Rva0014F480 *__cdecl Rva0014F90DFillN(Rva0014F480 *first, unsigned count, const Rva0014F480 &value)
{
	Tag tag;
	return Rva0014F5ABFillN(first, count, value, tag);
}

Rva0014F4A1 *__cdecl Rva0014F951FillN(Rva0014F4A1 *first, unsigned count, const Rva0014F4A1 &value)
{
	Tag tag;
	return Rva0014F5E5FillN(first, count, value, tag);
}

Rva0014F4C2 *__cdecl Rva0014F9CCFillN(Rva0014F4C2 *first, unsigned count, const Rva0014F4C2 &value)
{
	Tag tag;
	return Rva0014F61FFillN(first, count, value, tag);
}

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

Rva0014F4A1 *__cdecl Rva0014F928Copy(Rva0014F4A1 *first, Rva0014F4A1 *last, Rva0014F4A1 *result)
{
	Rva0014F4A1 *cur = result;
	for (; first != last; ++cur) {
		if (cur != 0)
			new (cur) Rva0014F4A1(*first);
		++first;
	}
	return cur;
}

void __cdecl Rva0014F9B2Fill(Rva0014F4A1 *first, Rva0014F4A1 *last, const Rva0014F4A1 &value)
{
	for (; first != last; ++first)
		first->m_04 = value.m_04;
}
