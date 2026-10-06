// cl: /DNDEBUG /MD
//
// ?Rva00568EB4Copy@@YAPAVRva00568B4E@@PAV1@00@Z @0x00568EB4 50B: range-copy loop
// over 0x14-byte Rva00568B4E elements: count is (last-first) via idiv 0x14,
// assigns each slot through rowed operator= 0x00568B4E, advances src/dst,
// returns final dst. Same recipe as Rva00564D06Copy; caller at 0x0056911C.
class Rva00568B4E
{
public:
	Rva00568B4E &operator=(const Rva00568B4E &other);

private:
	char m_pad[0x14];
};

Rva00568B4E *Rva00568EB4Copy(Rva00568B4E *first, Rva00568B4E *last, Rva00568B4E *dest)
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
