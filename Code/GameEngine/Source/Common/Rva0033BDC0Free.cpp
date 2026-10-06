// cl: /EHs /MD
// ??1Rva0033BDC0@@QAE@XZ @0x0033BDC0 56B.
// Scalar dtor over a two-word holder: body calls the rowed 0x002CF807 clear
// on this, then the inlined member dtor frees m_begin.p via the rowed C free
// 0x00030830 when non-null. Same EH prolog/statesshape as the rowed 63B
// 0x0033C3F3 (same handler 0xB7C604) under /EHs; the 7B delta is the wrapper
// call sequence. Caller at 0x0033DE2C in 0x0033DDA1 unblocks 0x0033DDA1.
struct Rva002CF807
{
	void *m_header;
	int m_size;
	void rva002CF807();
};
extern "C" void free(void *block);

struct Rva0033BDC0Begin
{
	void *m_ptr;
	~Rva0033BDC0Begin()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

struct Rva0033BDC0End
{
	~Rva0033BDC0End()
	{
	}
	void *m_ptr;
};

struct Rva0033BDC0
{
	Rva0033BDC0Begin m_begin;
	Rva0033BDC0End m_end;
	~Rva0033BDC0();
};

Rva0033BDC0::~Rva0033BDC0()
{
	((Rva002CF807 *)this)->rva002CF807();
}
