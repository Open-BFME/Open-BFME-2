// cl: /DNDEBUG /MD
// ?rva0056D3E3@Rva0056D3E3@@QAEXXZ @ 0x0056D3E3 26B.
// Free wrapper for Rva0056C996: load m_ptr, clear with and [ecx],0, if non-null call dtor then operator delete.
// Evidence: caller 0x0056D3FD lea ecx [esi+8] then call, callees rowed dtor 0x0056C996 and delete 0x0002FD60.
// Flags /O1 /DNDEBUG /MD without /GX: under /GX the explicit dtor call routes through a local ??_G (push 0, +2B);
// without EH it calls ??1 directly. Same idiom and flags as Rva002827F3Clear.cpp precedent.
struct Rva0056C996
{
	~Rva0056C996();
};

class Rva0056D3E3
{
public:
	void rva0056D3E3();
private:
	Rva0056C996 *m_ptr;
};

void Rva0056D3E3::rva0056D3E3()
{
	Rva0056C996 *p = m_ptr;
	m_ptr = 0;
	if (!p)
		return;
	p->~Rva0056C996();
	::operator delete(p);
}
