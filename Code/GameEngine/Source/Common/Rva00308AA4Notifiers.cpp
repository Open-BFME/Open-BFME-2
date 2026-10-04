// cl: /O1 /DNDEBUG /MD
//
// Five broadcast slots of the vtable around 0x00C07F88, the same pattern as
// the 0x00C088D8 slots in Rva0030C1FCNotifiers.cpp over a listener list at
// +0x68 (forEach 0x003089CF, one extra argument: 0x003089ED): four first run
// the shared base broadcast (0x0053805D..0x0053808A) and then hand a
// member-function pointer to a listener virtual plus the owner to the list.
// The member-function pointers are MSVC's generic vcall thunks
// ??_9@$B<slot>AE, pinned at the ICF-folded retail copies the bodies push.
//
//   slot address  body        base call   listener slot
//   0x00C07F88    0x00308AA4  0x0053805D  +0x04
//   0x00C07F8C    0x00308ABC  0x0053806C  +0x08
//   0x00C07F90    0x00308AD4  0x0053807B  +0x10
//   0x00C07F94    0x00308AEC  0x0053808A  +0x14
//   0x00C07F9C    0x00308B23  -           +0x18 (one extra argument)
//
// Owner, listener and list identities are not recovered (address names);
// the bodies are modelled as the non-virtual calls they compile to, and the
// listener's slot signatures are inferred from the arguments pushed.

class Rva00308AA4Owner;

class Rva00308AA4Listener
{
public:
	virtual void notify00(Rva00308AA4Owner *owner);
	virtual void notify04(Rva00308AA4Owner *owner);
	virtual void notify08(Rva00308AA4Owner *owner);
	virtual void notify0C(Rva00308AA4Owner *owner);
	virtual void notify10(Rva00308AA4Owner *owner);
	virtual void notify14(Rva00308AA4Owner *owner);
	virtual void notify18(Rva00308AA4Owner *owner, int value);
};

class Rva003089CFList
{
public:
	void forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *), Rva00308AA4Owner *owner);
	void forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *, int), Rva00308AA4Owner *owner, int value);
};

class Rva0053805DBase
{
public:
	void rva0053805D();
	void rva0053806C();
	void rva0053807B();
	void rva0053808A();
};

class Rva00308AA4Owner : public Rva0053805DBase
{
public:
	void rva00308AA4();
	void rva00308ABC();
	void rva00308AD4();
	void rva00308AEC();
	void rva00308B23(int value);

private:
	char m_unmodelled_00[0x68];
	Rva003089CFList m_listeners;		// +0x68
};

void Rva00308AA4Owner::rva00308AA4()
{
	rva0053805D();
	m_listeners.forEach(&Rva00308AA4Listener::notify04, this);
}

void Rva00308AA4Owner::rva00308ABC()
{
	rva0053806C();
	m_listeners.forEach(&Rva00308AA4Listener::notify08, this);
}

void Rva00308AA4Owner::rva00308AD4()
{
	rva0053807B();
	m_listeners.forEach(&Rva00308AA4Listener::notify10, this);
}

void Rva00308AA4Owner::rva00308AEC()
{
	rva0053808A();
	m_listeners.forEach(&Rva00308AA4Listener::notify14, this);
}

void Rva00308AA4Owner::rva00308B23(int value)
{
	m_listeners.forEach(&Rva00308AA4Listener::notify18, this, value);
}
