// cl: /MD
// ?Rva000C0CE1Copy@@YAPAUBfmeVectorRecord000C0BEC@@PAU1@00@Z at 0x000C0CE1 (50B). Array copy via rowed operator=.
// Evidence: byte stride 0x14 with push/pop idiv; loop calls 0xBDD21; returns final dest;
// chain lane via 0xBDD21; same idiv shape as generic vector copy.
struct BfmeVectorRecord000C0BEC {
	unsigned char m_data[0x14];
	BfmeVectorRecord000C0BEC &operator=(const BfmeVectorRecord000C0BEC &o);
};

struct BfmeVectorRecord000C0BEC *Rva000C0CE1Copy(struct BfmeVectorRecord000C0BEC *first, struct BfmeVectorRecord000C0BEC *last, struct BfmeVectorRecord000C0BEC *dest);

struct BfmeVectorRecord000C0BEC *Rva000C0CE1Copy(struct BfmeVectorRecord000C0BEC *first, struct BfmeVectorRecord000C0BEC *last, struct BfmeVectorRecord000C0BEC *dest)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	int c = n;
	do {
		*dest = *first;
		++first;
		++dest;
		--c;
	} while (c != 0);
	return dest;
}
