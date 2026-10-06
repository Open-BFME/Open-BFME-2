// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005DBD78FillN@@YAPAVRva005DBCD1@@PAV1@IABV1@ABUTag@@@Z 0x005DBD78 40B
// FillN helper looping count times calling rowed copy ctor 0x5DBCD1 then add 8 dec jne returning end.
// Evidence: caller 0x5DC507 with 4 pushes and add esp 0x10; same shape as Rva0014F5ABFillN 40B.
class Rva005DBCD1
{
public:
	Rva005DBCD1(const Rva005DBCD1 &other);
	virtual ~Rva005DBCD1();
	short m_field04;
	short m_field06;
};

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

struct Tag
{
	char x;
};

Rva005DBCD1 *__cdecl Rva005DBD78FillN(Rva005DBCD1 *result, unsigned int count, const Rva005DBCD1 &value, const Tag &tag)
{
	Rva005DBCD1 *cur = result;
	for (; count > 0; --count)
	{
		if (cur != 0)
			new (cur) Rva005DBCD1(value);
		++cur;
	}
	return cur;
}
