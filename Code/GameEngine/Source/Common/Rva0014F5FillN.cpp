// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014F5ABFillN@@YAPAVRva0014F480@@PAV1@IABV1@ABUTag@@@Z retail 0x0014F5AB 40B, ?Rva0014F5E5FillN@@YAPAVRva0014F4A1@@PAV1@IABV1@ABUTag@@@Z retail 0x0014F5E5 40B, ?Rva0014F61FFillN@@YAPAVRva0014F4C2@@PAV1@IABV1@ABUTag@@@Z retail 0x0014F61F 40B: uninitialized_fill_n helpers calling derived copy ctors 0x0014F480 0x0014F4A1 0x0014F4C2 in a count loop (add 8, dec, jne) returning end pointer. Callers 0x0014F90D 0x0014F951 0x0014F9CC dispatch with tag and 0x00150282 0x00150337 0x001503EC insert_overflow paths. Placement new forces the copy call like FXParticleSystem precedent.

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

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

struct Tag
{
	char x;
};

Rva0014F480 *__cdecl Rva0014F5ABFillN(Rva0014F480 *result, unsigned count, const Rva0014F480 &value, const Tag &tag)
{
	Rva0014F480 *cur = result;
	for (; count > 0; --count)
	{
		if (cur != 0)
			new (cur) Rva0014F480(value);
		++cur;
	}
	return cur;
}

Rva0014F4A1 *__cdecl Rva0014F5E5FillN(Rva0014F4A1 *result, unsigned count, const Rva0014F4A1 &value, const Tag &tag)
{
	Rva0014F4A1 *cur = result;
	for (; count > 0; --count)
	{
		if (cur != 0)
			new (cur) Rva0014F4A1(value);
		++cur;
	}
	return cur;
}

Rva0014F4C2 *__cdecl Rva0014F61FFillN(Rva0014F4C2 *result, unsigned count, const Rva0014F4C2 &value, const Tag &tag)
{
	Rva0014F4C2 *cur = result;
	for (; count > 0; --count)
	{
		if (cur != 0)
			new (cur) Rva0014F4C2(value);
		++cur;
	}
	return cur;
}
