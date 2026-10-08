// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005DBDA0@@YAPAURva005DBDA0Item@@PAU1@00@Z @0x005DBDA0 58B.
// Copies the two words at +4 and +6 of each 8-byte item from [begin, end) to
// dst, returning dst. Count is the item count; an empty range returns dst
// unchanged. Cdecl, no stack cleanup in the callee. Identity unproven.

struct Rva005DBDA0Item
{
	char m_pad[4];
	unsigned short m_lo;
	unsigned short m_hi;
};

Rva005DBDA0Item *rva005DBDA0(Rva005DBDA0Item *begin, Rva005DBDA0Item *end, Rva005DBDA0Item *dst)
{
	if (end - begin > 0)
	{
		int count = end - begin;
		unsigned short *src = &begin->m_hi;
		do
		{
			dst->m_lo = src[-1];
			dst->m_hi = *src;
			src += 4;
			++dst;
		} while (--count != 0);
	}
	return dst;
}
