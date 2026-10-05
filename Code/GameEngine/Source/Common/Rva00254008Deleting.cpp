// cl: /O1 /MD /GX
// ?rva00254008@Rva00254008@@QAEPAV1@I@Z @0x00254008 (28B): scalar deleting
// dtor shape (call dtor, test flags bit0, conditional operator delete,
// return this). Retail: push esi; esi=ecx; call dtor 0x254024; test byte
// [esp+8],1; je skip; push esi; call delete 0x2FD60; pop; eax=esi; pop esi;
// ret 4. Dtor pinned TU-local to rowed 0x254024; delete resolves to rowed
// 0x2FD60; address-derived outer.
class Rva00254008Dtor
{
public:
	void dtor();
};

class Rva00254008
{
public:
	Rva00254008 *rva00254008(unsigned int flags);
private:
	Rva00254008Dtor m_dtor;
};

// ?rva00254008@Rva00254008@@QAEPAV1@I@Z
Rva00254008 *Rva00254008::rva00254008(unsigned int flags)
{
	m_dtor.dtor();
	if (flags & 1) {
		operator delete(this);
	}
	return this;
}
