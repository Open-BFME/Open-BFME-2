// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x003F4BE9.  Each list's forEach packs a vcall
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
//   0x003F5206  0x003F4BE9  1
//   0x003F86B6  0x003F85D9  1
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

// ---- forEach 0x003F5206, walk 0x003F4BE9
class Rva003F5206Listener
{
public:
	virtual void notify(void *);
};

struct Rva003F4BE9Call
{
	void (Rva003F5206Listener::*notify)(void *);
	void *arg;
};

class Rva003F5206List
{
public:
	void forEach(void (Rva003F5206Listener::*notify)(void *), void *arg);
	void apply(const Rva003F4BE9Call &call);

private:
	Rva003F5206Listener **m_begin;		// +0x00
	Rva003F5206Listener **m_end;		// +0x04
	Rva003F5206Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva003F5206List::forEach(void (Rva003F5206Listener::*notify)(void *), void *arg)
{
	Rva003F4BE9Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva003F5206List::apply(const Rva003F4BE9Call &call)
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

// ---- forEach 0x003F86B6, walk 0x003F85D9
class Rva003F86B6Listener
{
public:
	virtual void notify(void *);
};

struct Rva003F85D9Call
{
	void (Rva003F86B6Listener::*notify)(void *);
	void *arg;
};

class Rva003F86B6List
{
public:
	void forEach(void (Rva003F86B6Listener::*notify)(void *), void *arg);
	void apply(const Rva003F85D9Call &call);

private:
	Rva003F86B6Listener **m_begin;		// +0x00
	Rva003F86B6Listener **m_end;		// +0x04
	Rva003F86B6Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva003F86B6List::forEach(void (Rva003F86B6Listener::*notify)(void *), void *arg)
{
	Rva003F85D9Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva003F86B6List::apply(const Rva003F85D9Call &call)
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
