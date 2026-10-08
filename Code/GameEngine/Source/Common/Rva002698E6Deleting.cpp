// cl: /MD /GX
// ?rva002698E6@Rva002698E6@@QAEPAV1@I@Z @0x002698E6 (28B): scalar deleting
// dtor shape (call dtor, test flags bit0, conditional operator delete,
// return this). Retail: push esi; esi=ecx; call dtor 0x268B04; test byte
// [esp+8],1; je skip; push esi; call delete 0x2FD60; pop; eax=esi; pop esi;
// ret 4. Dtor pinned TU-local to rowed 0x268B04; delete resolves to rowed
// 0x2FD60; address-derived outer.
// The member teardown is the rowed Rva00268B04::rva00268B04.
class Rva00268B04
{
public:
	void rva00268B04();
};

class Rva002698E6Dtor
{
public:
	void dtor();
};

class Rva002698E6
{
public:
	Rva002698E6 *rva002698E6(unsigned int flags);
private:
	Rva002698E6Dtor m_dtor;
};

// ?rva002698E6@Rva002698E6@@QAEPAV1@I@Z
Rva002698E6 *Rva002698E6::rva002698E6(unsigned int flags)
{
	((Rva00268B04 *)&m_dtor)->rva00268B04();
	if (flags & 1) {
		operator delete(this);
	}
	return this;
}
