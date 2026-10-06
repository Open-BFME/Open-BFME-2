// cl: /EHs /MD
// ??1Rva0033BD50@@QAE@XZ @0x0033BD50 56B.
// Scalar dtor over a two-word holder: body calls the rowed 0x002CF7B5 clear
// on this then the inlined member dtor frees m_begin.p via the rowed C free
// 0x00030830 when non-null. Same EH prolog shape as the rowed 63B 0x0033C3F3
// and the landed 56B 0x0033BDC0 under /EHs. Caller at 0x0033DE77 unblocks 0x0033DDA1.
struct Rva002CF7B5
{
	void *m_header;
	int m_size;
	void rva002CF7B5();
};
extern "C" void free(void *block);

struct Rva0033BD50Begin
{
	void *m_ptr;
	~Rva0033BD50Begin()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

struct Rva0033BD50End
{
	~Rva0033BD50End()
	{
	}
	void *m_ptr;
};

struct Rva0033BD50
{
	Rva0033BD50Begin m_begin;
	Rva0033BD50End m_end;
	~Rva0033BD50();
};

Rva0033BD50::~Rva0033BD50()
{
	((Rva002CF7B5 *)this)->rva002CF7B5();
}
