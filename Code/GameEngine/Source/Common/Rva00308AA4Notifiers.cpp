// cl: /O1 /DNDEBUG /MD /EHsc
//
// Six broadcast slots of the vtable around 0x00C07F88, the same pattern as
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
//   0x00C07F7C    0x00308B04  0x00538099  +0x0C (secondary base at +0x30)
//
// 0x00308B04 sits in the table of the secondary base at +0x30 and overrides
// a virtual that base introduces, so it is entered with that subobject and
// steps back 0x30 to the owner (lea edi, [esi-0x30]).
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

// The by-reference call records forEach builds on its stack: the member-function
// pointer first, then the arguments the listener slot takes.
struct Rva00308688Call
{
	void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *);
	Rva00308AA4Owner *owner;
};

struct Rva003086F5Call
{
	void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *, int);
	Rva00308AA4Owner *owner;
	int value;
};

// Zero Hour's Common/LatchRestore.h: overrides a variable for a scope and puts
// the old value back in the (virtual) destructor.  Retail's copy for a 4-byte
// type is the ctor 0x0027EA63, dtor 0x0027EA82 and vtable 0x00BFB1CC.
template <typename T>
class LatchRestore
{
protected:
	T valueToRestore;
	T &whereToRestore;

public:
	LatchRestore(T &dest, const T &src) : whereToRestore(dest)
	{
		valueToRestore = dest;
		dest = src;
	}

	virtual ~LatchRestore()
	{
		whereToRestore = valueToRestore;
	}
};

// A vector of listener pointers plus the index of the listener being called.
// The walk latches the index to 0 for its own pass and restores it afterwards,
// so a nested broadcast neither skips nor repeats listeners of the outer one.
class Rva003089CFList
{
public:
	void forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *), Rva00308AA4Owner *owner);
	void forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *, int), Rva00308AA4Owner *owner, int value);

	void apply(const Rva00308688Call &call);
	void apply(const Rva003086F5Call &call);

private:
	Rva00308AA4Listener **m_begin;		// +0x00
	Rva00308AA4Listener **m_end;		// +0x04
	Rva00308AA4Listener **m_capacity;	// +0x08
	unsigned int m_index;				// +0x0C
};

// The primary base runs the same broadcast over its own listener list at +0x08
// (forEach 0x00537F56 over the walk 0x00537EE9), with the same slot mapping as
// the owner: 0x0053805D +0x04, 0x0053806C +0x08, 0x0053807B +0x10,
// 0x0053808A +0x14, 0x00538099 +0x0C.  Each body is push this / push thunk /
// lea ecx,[this+8] / call; the Rva00308AA4Notifiers, Rva0030C1FCNotifiers and
// Rva003F87FFNotifiers owners all call them non-virtually.
class Rva0053805DBase;

class Rva0053805DListener
{
public:
	virtual void notify00(Rva0053805DBase *owner);
	virtual void notify04(Rva0053805DBase *owner);
	virtual void notify08(Rva0053805DBase *owner);
	virtual void notify0C(Rva0053805DBase *owner);
	virtual void notify10(Rva0053805DBase *owner);
	virtual void notify14(Rva0053805DBase *owner);
};

struct Rva00537EE9Call
{
	void (Rva0053805DListener::*notify)(Rva0053805DBase *);
	Rva0053805DBase *owner;
};

class Rva00537F56List
{
public:
	void forEach(void (Rva0053805DListener::*notify)(Rva0053805DBase *), Rva0053805DBase *owner);

	void apply(const Rva00537EE9Call &call);

private:
	Rva0053805DListener **m_begin;		// +0x00
	Rva0053805DListener **m_end;		// +0x04
	Rva0053805DListener **m_capacity;	// +0x08
	unsigned int m_index;				// +0x0C
};

class Rva0053805DBase
{
public:
	virtual ~Rva0053805DBase();
	void rva0053805D();
	void rva0053806C();
	void rva0053807B();
	void rva0053808A();
	void rva00538099();

private:
	char m_unmodelled_04[0x08 - 0x04];
	Rva00537F56List m_listeners;		// +0x08
	char m_unmodelled_18[0x30 - 0x18];
};

// Secondary base at +0x30, which introduces the virtual 0x00308B04 overrides.
class Rva00308B04Base
{
public:
	virtual void rva00308B04();
};

class Rva00308AA4Owner : public Rva0053805DBase, public Rva00308B04Base
{
public:
	void rva00308AA4();
	void rva00308ABC();
	void rva00308AD4();
	void rva00308AEC();
	virtual void rva00308B04();
	void rva00308B23(int value);

private:
	char m_unmodelled_34[0x68 - 0x34];
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

void Rva00308AA4Owner::rva00308B04()
{
	rva00538099();
	m_listeners.forEach(&Rva00308AA4Listener::notify0C, this);
}

void Rva00308AA4Owner::rva00308B23(int value)
{
	m_listeners.forEach(&Rva00308AA4Listener::notify18, this, value);
}

// 0x003089CF and 0x003089ED: pack the slot and its arguments into a call record
// and hand it to the list walk.
void Rva003089CFList::forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *), Rva00308AA4Owner *owner)
{
	Rva00308688Call call;
	call.notify = notify;
	call.owner = owner;
	apply(call);
}

void Rva003089CFList::forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *, int), Rva00308AA4Owner *owner, int value)
{
	Rva003086F5Call call;
	call.notify = notify;
	call.owner = owner;
	call.value = value;
	apply(call);
}

void Rva00537F56List::forEach(void (Rva0053805DListener::*notify)(Rva0053805DBase *), Rva0053805DBase *owner)
{
	Rva00537EE9Call call;
	call.notify = notify;
	call.owner = owner;
	apply(call);
}

void Rva0053805DBase::rva0053805D()
{
	m_listeners.forEach(&Rva0053805DListener::notify04, this);
}

void Rva0053805DBase::rva0053806C()
{
	m_listeners.forEach(&Rva0053805DListener::notify08, this);
}

void Rva0053805DBase::rva0053807B()
{
	m_listeners.forEach(&Rva0053805DListener::notify10, this);
}

void Rva0053805DBase::rva0053808A()
{
	m_listeners.forEach(&Rva0053805DListener::notify14, this);
}

void Rva0053805DBase::rva00538099()
{
	m_listeners.forEach(&Rva0053805DListener::notify0C, this);
}

// 0x00308688 and 0x003086F5: call every listener through the record's slot.
// The index is published before each call and re-read after it, so a listener
// that broadcasts again (and latches the index to 0 for its own pass) leaves
// this pass to resume where it was.
void Rva003089CFList::apply(const Rva00308688Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.owner);
		i = m_index;
	}
}

void Rva003089CFList::apply(const Rva003086F5Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.owner, call.value);
		i = m_index;
	}
}

// 0x00537EE9: the same walk over the base's own listener list.
void Rva00537F56List::apply(const Rva00537EE9Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.owner);
		i = m_index;
	}
}
template class LatchRestore<unsigned int>;
