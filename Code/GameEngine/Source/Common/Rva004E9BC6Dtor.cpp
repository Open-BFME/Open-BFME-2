// cl: /EHs /MD
// ??1Rva004E9B46@@UAE@XZ @0x004E9BC6 77B. Identity: dtor storing vtable 0x00862874 then member cleanup via 0x004E9B70 and free of +0x0C then base vtable via 0x00506B28.
// Evidence: vtable store at [this]; callees rowed 0x004E9B70 0x00506B28 free 0x00030830; unblocks 0x004E9F52.
class Rva004E9B70
{
public:
	void rva004E9B70();
};

extern "C" void __cdecl free(void *);

struct Holder0C
{
	void *m_ptr;
	~Holder0C()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

class Rva00598CFDBase
{
public:
	virtual ~Rva00598CFDBase();
};

class Rva004E9B46 : public Rva00598CFDBase
{
public:
	virtual ~Rva004E9B46();
	char m_pad04[8];
	Holder0C m_hold0C;
};

Rva004E9B46::~Rva004E9B46()
{
	((Rva004E9B70 *)this)->rva004E9B70();
}
