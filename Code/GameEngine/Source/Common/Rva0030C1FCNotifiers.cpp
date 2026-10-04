// cl: /O1 /DNDEBUG /MD
//
// Ten broadcast slots of the class whose vtable is 0x00C088D8 (slots 11-21;
// slots 2-8 are vtordisp thunks, so the class has a virtual base). Each one
// hands a member-function pointer to a virtual of the listener interface,
// plus the owner itself, to the listener list at +0x30, whose forEach
// (0x0030C185, one extra argument: 0x0030C1A3) calls it on every listener.
// The member-function pointers are the compiler's vcall thunks (mov eax,
// [ecx]; jmp [eax+slot*4]), ICF-folded in retail with other one-slot
// forwarders: 0x005CB260 (+0x04) ... 0x005CB27E (+0x20), 0x005CC208 (+0x08),
// 0x000D20D6 (+0x24) and 0x001F34BA (+0x28). Five of the slots first run
// the base class's version (0x0053805D, 0x0053806C, 0x0053807B, 0x0053808A
// and 0x00538099, each the same broadcast over the base's own list at +8).
//
//   slot  body        base call   listener slot
//   11    0x0030C1FC  0x0053805D  +0x04
//   12    0x0030C214  0x0053806C  +0x08
//   13    0x0030C22C  0x0053807B  +0x14
//   14    0x0030C244  0x0053808A  +0x1C
//   16    0x0030C25C  -           +0x0C (one extra argument)
//   17    0x0030C280  -           +0x18
//   18    0x0030C28F  -           +0x20
//   19    0x0030C29E  0x00538099  +0x24
//   20    0x0030C2B6  0x00538099  +0x28
//   21    0x0030C271  -           +0x10
//
// Owner, listener and list identities are not recovered (address names);
// the bodies are modelled as the non-virtual calls they compile to, and the
// listener's slot signatures are inferred from the arguments pushed.

class Rva0030C1FCOwner;

class Rva0030C1FCListener
{
public:
	virtual void notify00(Rva0030C1FCOwner *owner);
	virtual void notify04(Rva0030C1FCOwner *owner);
	virtual void notify08(Rva0030C1FCOwner *owner);
	virtual void notify0C(Rva0030C1FCOwner *owner, int value);
	virtual void notify10(Rva0030C1FCOwner *owner);
	virtual void notify14(Rva0030C1FCOwner *owner);
	virtual void notify18(Rva0030C1FCOwner *owner);
	virtual void notify1C(Rva0030C1FCOwner *owner);
	virtual void notify20(Rva0030C1FCOwner *owner);
	virtual void notify24(Rva0030C1FCOwner *owner);
	virtual void notify28(Rva0030C1FCOwner *owner);
};

class Rva0030C185List
{
public:
	void forEach(void (Rva0030C1FCListener::*notify)(Rva0030C1FCOwner *), Rva0030C1FCOwner *owner);
	void forEach(void (Rva0030C1FCListener::*notify)(Rva0030C1FCOwner *, int), Rva0030C1FCOwner *owner, int value);
};

class Rva0053805DBase
{
public:
	void rva0053805D();
	void rva0053806C();
	void rva0053807B();
	void rva0053808A();
	void rva00538099();
};

class Rva0030C1FCOwner : public Rva0053805DBase
{
public:
	void rva0030C1FC();
	void rva0030C214();
	void rva0030C22C();
	void rva0030C244();
	void rva0030C25C(int value);
	void rva0030C271();
	void rva0030C280();
	void rva0030C28F();
	void rva0030C29E();
	void rva0030C2B6();

private:
	char m_unmodelled_00[0x30];
	Rva0030C185List m_listeners;		// +0x30
};

void Rva0030C1FCOwner::rva0030C1FC()
{
	rva0053805D();
	m_listeners.forEach(&Rva0030C1FCListener::notify04, this);
}

void Rva0030C1FCOwner::rva0030C214()
{
	rva0053806C();
	m_listeners.forEach(&Rva0030C1FCListener::notify08, this);
}

void Rva0030C1FCOwner::rva0030C22C()
{
	rva0053807B();
	m_listeners.forEach(&Rva0030C1FCListener::notify14, this);
}

void Rva0030C1FCOwner::rva0030C244()
{
	rva0053808A();
	m_listeners.forEach(&Rva0030C1FCListener::notify1C, this);
}

void Rva0030C1FCOwner::rva0030C25C(int value)
{
	m_listeners.forEach(&Rva0030C1FCListener::notify0C, this, value);
}

void Rva0030C1FCOwner::rva0030C271()
{
	m_listeners.forEach(&Rva0030C1FCListener::notify10, this);
}

void Rva0030C1FCOwner::rva0030C280()
{
	m_listeners.forEach(&Rva0030C1FCListener::notify18, this);
}

void Rva0030C1FCOwner::rva0030C28F()
{
	m_listeners.forEach(&Rva0030C1FCListener::notify20, this);
}

void Rva0030C1FCOwner::rva0030C29E()
{
	rva00538099();
	m_listeners.forEach(&Rva0030C1FCListener::notify24, this);
}

void Rva0030C1FCOwner::rva0030C2B6()
{
	rva00538099();
	m_listeners.forEach(&Rva0030C1FCListener::notify28, this);
}
