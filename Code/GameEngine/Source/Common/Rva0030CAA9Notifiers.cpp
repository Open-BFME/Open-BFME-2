// cl: /O1 /DNDEBUG /MD
//
// Three broadcast slots of the vtables around 0x00C089A4, the pattern of
// Rva00308AA4Notifiers.cpp over a listener list at +0x68 (forEach
// 0x0030CA8B): each first runs the shared base broadcast and then hands a
// member-function pointer to a listener virtual plus the owner to the list.
// 0x0030CAD9 sits in the table of the secondary base at +0x30 and overrides
// a virtual that base introduces, so it is entered with that subobject and
// steps back 0x30 to the owner (lea edi, [esi-0x30]).
//
//   slot address  body        base call   listener slot
//   0x00C089B0    0x0030CAA9  0x0053805D  +0x04
//   0x00C089B4    0x0030CAC1  0x0053806C  +0x08
//   0x00C089A4    0x0030CAD9  0x00538099  +0x0C (secondary base at +0x30)
//
// The member-function pointers are MSVC's generic vcall thunks
// ??_9@$B<slot>AE, pinned at the ICF-folded retail copies the bodies push.
// Owner, bases, listener and list identities are not recovered (address
// names); the listener's slot signatures are inferred from the arguments.

class Rva0030CAA9Owner;

class Rva0030CAA9Listener
{
public:
	virtual void notify00(Rva0030CAA9Owner *owner);
	virtual void notify04(Rva0030CAA9Owner *owner);
	virtual void notify08(Rva0030CAA9Owner *owner);
	virtual void notify0C(Rva0030CAA9Owner *owner);
};

class Rva0030CA8BList
{
public:
	void forEach(void (Rva0030CAA9Listener::*notify)(Rva0030CAA9Owner *), Rva0030CAA9Owner *owner);
};

// The primary base: its broadcasts are called non-virtually here.
class Rva0053805DBase
{
public:
	virtual ~Rva0053805DBase();
	void rva0053805D();
	void rva0053806C();
	void rva00538099();

private:
	char m_unmodelled_04[0x30 - 0x04];
};

// Secondary base at +0x30, which introduces the virtual 0x0030CAD9 overrides.
class Rva0030CAD9Base
{
public:
	virtual void rva0030CAD9();
};

class Rva0030CAA9Owner : public Rva0053805DBase, public Rva0030CAD9Base
{
public:
	void rva0030CAA9();
	void rva0030CAC1();
	virtual void rva0030CAD9();

private:
	char m_unmodelled_34[0x68 - 0x34];
	Rva0030CA8BList m_listeners;		// +0x68
};

void Rva0030CAA9Owner::rva0030CAA9()
{
	rva0053805D();
	m_listeners.forEach(&Rva0030CAA9Listener::notify04, this);
}

void Rva0030CAA9Owner::rva0030CAC1()
{
	rva0053806C();
	m_listeners.forEach(&Rva0030CAA9Listener::notify08, this);
}

void Rva0030CAA9Owner::rva0030CAD9()
{
	rva00538099();
	m_listeners.forEach(&Rva0030CAA9Listener::notify0C, this);
}
