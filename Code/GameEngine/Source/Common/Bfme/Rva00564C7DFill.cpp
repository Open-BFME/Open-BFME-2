// cl: /DNDEBUG /MD
// ?Rva00564C7DFill@@YAPAVRva003A6360Record@@PAV1@IABV1@@Z @0x00564C7D 40B.
// Counted copy-construct loop over 0x10-byte records: skips null slots,
// copy-constructs each live slot from src through the rowed copy ctor
// 0x0052BB9A, advances dst. Caller at 0x0056602F; unblocks 0x00565FC1.
// Dedicated TU so the copy ctor stays a call.

class Rva003A6360Record
{
public:
	Rva003A6360Record(const Rva003A6360Record &other);

	int m_vtable;
	int m_word04;
	unsigned char m_byte08;
	int m_word0C;
};

Rva003A6360Record *Rva00564C7DFill(Rva003A6360Record *dst, unsigned int count, const Rva003A6360Record &src)
{
	Rva003A6360Record *p = dst;
	unsigned int n = count;
	if (n > 0)
	{
		do
		{
			if (p != 0)
				p->Rva003A6360Record::Rva003A6360Record(src);
			++p;
		}
		while (--n != 0);
	}
	return p;
}
