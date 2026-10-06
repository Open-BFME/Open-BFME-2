// cl: /DNDEBUG /MD
// ?Rva00564D06Copy@@YAPAVRva003B3080@@PAV1@00@Z, retail 0x00564D06, 50 bytes.
// Range-copy loop over 0x14-byte Rva003B3080 elements: count is (last-first) via idiv 0x14, assigns each slot through rowed operator= 0x00564B41, advances src/dst, returns final dst. Caller at 0x005656BD; unblocks 0x005656AA.
// Pattern from Rva00564CA5Copy 0x00564CA5 / Rva00564D38Copy 0x00564D38; 0x14 forces idiv hence 50B vs 47B.
class Rva003B3080
{
public:
	Rva003B3080 &operator=(const Rva003B3080 &other);
private:
	char m_pad[0x14];
};

Rva003B3080 *Rva00564D06Copy(Rva003B3080 *first, Rva003B3080 *last, Rva003B3080 *dest)
{
	if (last - first <= 0)
		return dest;
	int n = last - first;
	do
	{
		*dest = *first;
		++first;
		++dest;
	} while (--n != 0);
	return dest;
}
