// cl: /DNDEBUG /MD
// ?Rva00564D99Copy@@YAPAVRva003AD070@@PAV1@00@Z, retail 0x00564D99, 50 bytes.
// Uninitialized-copy loop over 0xC-byte Rva003AD070 elements: count is (last-first) via idiv 0xC, constructs each dest via rowed copy ctor 0x00564BD5, advances src/dst, returns final dst. Caller at 0x005657A8; unblocks 0x00565795.
// Pattern from Rva00564D67Copy 0x00564D67 direct ctor call.
class Rva003AD070
{
public:
	Rva003AD070(const Rva003AD070 &other);
private:
	char m_pad[0xC];
};

Rva003AD070 *Rva00564D99Copy(Rva003AD070 *first, Rva003AD070 *last, Rva003AD070 *dest)
{
	if (last - first <= 0)
		return dest;
	int n = last - first;
	do
	{
		dest->Rva003AD070::Rva003AD070(*first);
		++first;
		++dest;
	} while (--n != 0);
	return dest;
}
