// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x002E16C0.  Each list's forEach packs a vcall
// member-function pointer and its arguments into a stack call record and
// passes it by reference to an EH-guarded walk.  The walk latches the list's
// index at +0x0C with Zero Hour's LatchRestore (Common/LatchRestore.h; retail
// ctor 0x0027EA63, dtor 0x0027EA82, vtable 0x00BFB1CC for a 4-byte type),
// publishes the index before each call and re-reads it after, so a nested
// broadcast that latches the index to 0 for its own pass leaves this pass to
// resume where it was.  The shape is the one recovered byte for byte in
// Rva00308AA4Notifiers.cpp.
//
//   forEach     walk        arguments
//   0x002E1E51  0x002E16C0  1
//   0x002E1E6F  0x002E172D  3
//
// Identity is not recovered: lists and listeners are named after their
// forEach address, records after their walk address, and the argument types
// are inferred from their size only.

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

// ---- forEach 0x002E1E51, walk 0x002E16C0
class Rva002E1E51Listener
{
public:
	virtual void notify(void *);
};

struct Rva002E16C0Call
{
	void (Rva002E1E51Listener::*notify)(void *);
	void *arg;
};

class Rva002E1E51List
{
public:
	void forEach(void (Rva002E1E51Listener::*notify)(void *), void *arg);
	void apply(const Rva002E16C0Call &call);

private:
	Rva002E1E51Listener **m_begin;		// +0x00
	Rva002E1E51Listener **m_end;		// +0x04
	Rva002E1E51Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva002E1E51List::forEach(void (Rva002E1E51Listener::*notify)(void *), void *arg)
{
	Rva002E16C0Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva002E1E51List::apply(const Rva002E16C0Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.arg);
		i = m_index;
	}
}

// ---- forEach 0x002E1E6F, walk 0x002E172D
class Rva002E1E6FListener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva002E172DCall
{
	void (Rva002E1E6FListener::*notify)(void *, int, int);
	void *arg;
	int value;
	int extra;
};

class Rva002E1E6FList
{
public:
	void forEach(void (Rva002E1E6FListener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva002E172DCall &call);

private:
	Rva002E1E6FListener **m_begin;		// +0x00
	Rva002E1E6FListener **m_end;		// +0x04
	Rva002E1E6FListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva002E1E6FList::forEach(void (Rva002E1E6FListener::*notify)(void *, int, int), void *arg, int value, int extra)
{
	Rva002E172DCall call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	call.extra = extra;
	apply(call);
}

void Rva002E1E6FList::apply(const Rva002E172DCall &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.arg, call.value, call.extra);
		i = m_index;
	}
}
