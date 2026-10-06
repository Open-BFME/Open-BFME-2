// cl: /DNDEBUG /MD
// ?Rva00564D67Copy@@YAPAVRva003AD0A0@@PAV1@00@Z, retail 0x00564D67, 50 bytes.
// Uninitialized-copy loop over 0x14-byte Rva003AD0A0 elements: count is (last-first) via idiv 0x14, constructs each dest via rowed copy ctor 0x00564BA8, advances src/dst, returns final dst. Caller at 0x0056571C; unblocks 0x00565709.
// Pattern from Rva00564D06Copy 0x00564D06 but copy ctor not assign.
class Rva003AD0A0
{
public:
	Rva003AD0A0(const Rva003AD0A0 &other);
private:
	char m_pad[0x14];
};

Rva003AD0A0 *Rva00564D67Copy(Rva003AD0A0 *first, Rva003AD0A0 *last, Rva003AD0A0 *dest)
{
	if (last - first <= 0)
		return dest;
	int n = last - first;
	do
	{
		dest->Rva003AD0A0::Rva003AD0A0(*first);
		++first;
		++dest;
	} while (--n != 0);
	return dest;
}
