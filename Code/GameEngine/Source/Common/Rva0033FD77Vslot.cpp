// cl: /DNDEBUG /MD
// ?rva0033FD77@Rva00367E26@@UAE_NXZ @0x0033FD77 33B. Vslot 12 (0x30) of vtable
// 0x00817600 (class Rva00367E26): if sub-object at +0x50 exists and its
// virtual at +0x28 returns true return true else tail-jmp to rowed
// StateMachine::isInBusyState 0x004D7309. Evidence: vtable slot plus rowed
// isInBusyState plus virtual call shape; no callers.
class StateMachine
{
public:
	bool isInBusyState() const;
};

class Sub50
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual bool v10();
};

class Rva00367E26
{
public:
	virtual bool rva0033FD77();
private:
	char m_pad04[0x50 - 4];
	Sub50 *m_50;
};

bool Rva00367E26::rva0033FD77()
{
	if (m_50 != 0 && m_50->v10())
		return true;
	return ((StateMachine *)this)->isInBusyState();
}
