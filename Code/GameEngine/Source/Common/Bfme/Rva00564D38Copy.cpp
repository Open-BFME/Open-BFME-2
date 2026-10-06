// cl: /DNDEBUG /MD
// ?Rva00564D38Copy@@YAPAVRva003AC980@@PAV1@00@Z, retail 0x00564D38, 47 bytes.
// Range-copy loop over 0x20-byte Rva003AC980 elements: count is
// (last-first), assigns each slot through the rowed operator= 0x00564B7A,
// advances src/dst, returns final dst. Caller at 0x005656DA; unblocks 0x005656C7.

class Rva003AC980
{
public:
	Rva003AC980 &operator=(const Rva003AC980 &other);
private:
	char m_pad[0x20];
};

Rva003AC980 *Rva00564D38Copy(Rva003AC980 *first, Rva003AC980 *last, Rva003AC980 *dest)
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
