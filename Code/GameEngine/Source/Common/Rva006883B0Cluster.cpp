// cl: /DNDEBUG /MD /EHsc /Ob2
//
// One-argument sibling of Rva0081D520Owner::broadcast (Rva0081D520Owner.cpp):
// the same listener-pointer span at +0x14/+0x18 walked with the /O2 array
// count, calling each listener's slot-2 virtual with the argument. Only the
// class and the callee slot differ. Identity is unproven; the name is this
// image's address.

class Rva006883B0Listener
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void receive(int value);
};

class Rva006883B0Owner
{
public:
	void broadcast(int value);

private:
	unsigned char m_unmodelled[0x14];
	Rva006883B0Listener **m_begin;	// +0x14
	Rva006883B0Listener **m_end;	// +0x18
};

// ?broadcast@Rva006883B0Owner@@QAEXH@Z @ 0x006883B0 (56B)
void Rva006883B0Owner::broadcast(int value)
{
	for (unsigned i = 0; i < (unsigned)(m_end - m_begin); ++i)
		m_begin[i]->receive(value);
}
