// cl: /MD
// ?Rva000C0D13Copy@@YAPAUBfmeVectorRecord000BDF17@@PAU1@00@Z at 0x000C0D13 (47B). Array copy via rowed operator=.
// Evidence: byte stride 0x40 with sar 6; loop calls 0xBDFAC; returns final dest;
// chain lane via 0xBDFAC; same lazy-esi n/c shape as 0xC0CE1.
struct BfmeVectorRecord000BDF17 {
	unsigned char m_data[0x40];
	BfmeVectorRecord000BDF17 &operator=(const BfmeVectorRecord000BDF17 &o);
};

struct BfmeVectorRecord000BDF17 *Rva000C0D13Copy(struct BfmeVectorRecord000BDF17 *first, struct BfmeVectorRecord000BDF17 *last, struct BfmeVectorRecord000BDF17 *dest);

struct BfmeVectorRecord000BDF17 *Rva000C0D13Copy(struct BfmeVectorRecord000BDF17 *first, struct BfmeVectorRecord000BDF17 *last, struct BfmeVectorRecord000BDF17 *dest)
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
