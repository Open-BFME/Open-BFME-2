// cl: /EHs /MD
// ??1Rva0033BD88@@QAE@XZ @0x0033BD88 56B.
// Scalar dtor over a two-word holder: body calls the rowed 0x002CF7DE clear
// on this then the inlined member dtor frees m_begin.p via the rowed C free
// 0x00030830 when non-null. Same EH prolog shape as the rowed 63B 0x0033C3F3
// and the landed 56B 0x0033BDC0 0x0033BD50 under /EHs. Caller at 0x0033DE59 unblocks 0x0033DDA1.
struct Rva002CF7DE
{
	void *m_header;
	int m_size;
	void rva002CF7DE();
};
extern "C" void free(void *block);

struct Rva0033BD88Begin
{
	void *m_ptr;
	~Rva0033BD88Begin()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

struct Rva0033BD88End
{
	~Rva0033BD88End()
	{
	}
	void *m_ptr;
};

struct Rva0033BD88
{
	Rva0033BD88Begin m_begin;
	Rva0033BD88End m_end;
	~Rva0033BD88();
};

Rva0033BD88::~Rva0033BD88()
{
	((Rva002CF7DE *)this)->rva002CF7DE();
}

// Native0033C2BD5B tail call to the sole56B nonvirtual holder destructor.
// Unchanged thiscall receiver and RET0; original wrapper/type unknown.
struct Rva0033C2BDHolderCleanupForward { void cleanup(); };
void Rva0033C2BDHolderCleanupForward::cleanup() {
    reinterpret_cast<Rva0033BD88 *>(this)->~Rva0033BD88();
}
