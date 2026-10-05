// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Listener-list walks around 0x005D49F9.  Each list's forEach packs a vcall
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
//   0x005D4C01  0x005D49F9  1
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

// ---- forEach 0x005D4C01, walk 0x005D49F9
class Rva005D4C01Listener
{
public:
	virtual void notify(void *);
};

struct Rva005D49F9Call
{
	void (Rva005D4C01Listener::*notify)(void *);
	void *arg;
};

class Rva005D4C01List
{
public:
	void forEach(void (Rva005D4C01Listener::*notify)(void *), void *arg);
	void apply(const Rva005D49F9Call &call);

private:
	Rva005D4C01Listener **m_begin;		// +0x00
	Rva005D4C01Listener **m_end;		// +0x04
	Rva005D4C01Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005D4C01List::forEach(void (Rva005D4C01Listener::*notify)(void *), void *arg)
{
	Rva005D49F9Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva005D4C01List::apply(const Rva005D49F9Call &call)
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

// ---- forEach 0x005D4C1F, walk 0x005D4A66: (int, float) slots.  The record is
// the functor rowed at 0x005D48DB (Rva005D48DBForward.cpp), whose call is not
// inlined, so the walk hands it each listener.
class Rva005D48DBElem
{
public:
	void Method(int a, float b);
};

typedef void (Rva005D48DBElem::*Rva005D48DBFn)(int, float);

class Rva005D48DB
{
	friend class Rva005D4C1FList;

public:
	void rva005D48DB(void *elem);

private:
	Rva005D48DBFn m_fn;
	int m_4;
	float m_8;
};

class Rva005D4C1FList
{
public:
	void forEach(Rva005D48DBFn fn, int a, float b);
	void apply(Rva005D48DB &call);

private:
	Rva005D48DBElem **m_begin;		// +0x00
	Rva005D48DBElem **m_end;		// +0x04
	Rva005D48DBElem **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005D4C1FList::forEach(Rva005D48DBFn fn, int a, float b)
{
	Rva005D48DB call;
	call.m_fn = fn;
	call.m_4 = a;
	call.m_8 = b;
	apply(call);
}

void Rva005D4C1FList::apply(Rva005D48DB &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		call.rva005D48DB(m_begin[i]);
		i = m_index;
	}
}
