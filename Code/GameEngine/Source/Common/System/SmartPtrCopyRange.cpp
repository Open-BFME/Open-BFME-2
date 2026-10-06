// cl: /DNDEBUG /MD
//
// ?Rva0004CCCDCopyRange@@YAPAVRvaSmartPtr12@@PAV1@00@Z, retail 0x0004CCCD (50 bytes).
//
// Array copy over RvaSmartPtr12 via the rowed assignment at 0x4CC3D:
// count is (last-first) element difference (byte diff over stride 12 via
// push 0xC pop idiv), then assignment loop stepping both pointers. Caller
// is 0x4CD20; prev is __uninitialized_fill_n 0x4CCA8 in the STL TU family.

class RvaSmartPtr12
{
public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

RvaSmartPtr12 *Rva0004CCCDCopyRange(RvaSmartPtr12 *first, RvaSmartPtr12 *last, RvaSmartPtr12 *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int count = n;
		do
		{
			*dest = *first;
			++first;
			++dest;
			--count;
		} while (count != 0);
	}
	return dest;
}
