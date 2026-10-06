// cl: /EHs /MD
// ??1Rva0033C3F3@@QAE@XZ @0x0033C3F3 63B.
// Scalar dtor over a two-word holder: body calls the rowed 0x002CF891
// wrapper with (m_begin.p, m_end), then the inlined member dtor frees
// m_begin.p via the rowed C free 0x00030830 when non-null. The member with
// the non-trivial dtor is what arms the EH prolog/states under /EHsc.
// Same net logic as the frameless 30B rowed 0x002CFB90. Caller at
// 0x0033DF2C unblocks 0x0033DDA1.
struct Rva002CF571Item;
void __cdecl Rva002CF891Wrap(Rva002CF571Item *first, Rva002CF571Item *last);
extern "C" void free(void *block);

struct Rva0033C3F3Begin
{
	Rva002CF571Item *m_ptr;
	~Rva0033C3F3Begin()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

struct Rva0033C3F3End
{
	~Rva0033C3F3End()
	{
	}
	Rva002CF571Item *m_ptr;
};

struct Rva0033C3F3
{
	Rva0033C3F3Begin m_begin;
	Rva0033C3F3End m_end;
	~Rva0033C3F3();
};

Rva0033C3F3::~Rva0033C3F3()
{
	Rva002CF891Wrap(m_begin.m_ptr, m_end.m_ptr);
}
