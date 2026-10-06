// cl: /DNDEBUG /MD
//
// ?rva00262B0F@AIUpdateInterface@@QAEXH@Z, retail 0x00262B0F, 42 bytes.
// AIUpdateInterface lock-guard sibling of friend_setPath: save machine+0x30
// lock byte +0x38 to bl then clear it then virtual slot 0x38 with the int
// arg then restore the lock to 1 if it was set. Outer ret 4. Honest
// address-derived name; slot identity unproven (likely setGoalObject shape).
// No other callees.

class LockMachine
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34();
	virtual void s38(int v);
	char m_pad04[0x38 - 4];
	bool m_locked;
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	LockMachine *m_machine;
public:
	void rva00262B0F(int v);
};

void AIUpdateInterface::rva00262B0F(int v)
{
	bool wasLocked = m_machine->m_locked;
	m_machine->m_locked = false;
	m_machine->s38(v);
	if (wasLocked)
		m_machine->m_locked = true;
}
