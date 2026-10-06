// cl: /MD
//
// ??1Rva005DA4DC@@QAE@XZ, retail 0x005DA4DC, 29 bytes.
// Non-virtual dtor null-checking the +8 pointer member, dispatching its
// slot-0 virtual with flag 0, freeing the result via the rowed global
// operator delete 0x0002FD60, then nulling the member. Precedent
// Rva00341796Dtor (slot0+0 plus delete plus null) without the slot15 call.
// Evidence: push 0 then call [eax] then push eax then delete then null;
// caller 0x0058B60B in unclaimed vector deleting dtor 0x0058B5D8;
// unblocks 0x0058B5D8. Layout: member at +8 per [esi+8].

class Rva005DA4DCMember
{
public:
	virtual void *v0(int);
};

class Rva005DA4DC
{
public:
	~Rva005DA4DC();

private:
	unsigned int m_00;
	unsigned int m_04;
	Rva005DA4DCMember *m_08;
};

void __cdecl operator delete(void *p);

Rva005DA4DC::~Rva005DA4DC()
{
	if (m_08 != 0)
	{
		void *p = m_08->v0(0);
		::operator delete(p);
		m_08 = 0;
	}
}
