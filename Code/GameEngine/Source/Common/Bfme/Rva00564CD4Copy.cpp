// cl: /DNDEBUG /MD
// ?Rva00564CD4Copy@@YAPAVRva00564B1A@@PAV1@00@Z, retail 0x00564CD4, 50 bytes.
// Range-copy loop over 0xc-byte Rva00564B1A elements: count is (last-first) via idiv 0xc, assigns each slot through rowed method 0x00564B1A, advances src/dst, returns final dst. Caller at 0x0056567B; unblocks 0x00565668.
// Pattern from Rva00564CA5Copy 0x00564CA5 / Rva00564D06Copy 0x00564D06; 0xc forces idiv hence 50B vs 47B.

class Rva00564B1A
{
public:
	Rva00564B1A &rva00564B1A(const Rva00564B1A &other);
private:
	char m_pad[0xc];
};

Rva00564B1A *Rva00564CD4Copy(Rva00564B1A *first, Rva00564B1A *last, Rva00564B1A *dest)
{
	if (last - first <= 0)
		return dest;
	int n = last - first;
	do
	{
		dest->rva00564B1A(*first);
		++first;
		++dest;
	} while (--n != 0);
	return dest;
}
