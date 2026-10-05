// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x005789F3.  Each list's forEach packs a vcall
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
//   0x00578A60  0x005789F3  1
//   0x0057BC45  0x0057BB4E  1
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

// ---- forEach 0x00578A60, walk 0x005789F3
class Rva00578A60Listener
{
public:
	virtual void notify(void *);
};

struct Rva005789F3Call
{
	void (Rva00578A60Listener::*notify)(void *);
	void *arg;
};

class Rva00578A60List
{
public:
	void forEach(void (Rva00578A60Listener::*notify)(void *), void *arg);
	void apply(const Rva005789F3Call &call);

private:
	Rva00578A60Listener **m_begin;		// +0x00
	Rva00578A60Listener **m_end;		// +0x04
	Rva00578A60Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva00578A60List::forEach(void (Rva00578A60Listener::*notify)(void *), void *arg)
{
	Rva005789F3Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva00578A60List::apply(const Rva005789F3Call &call)
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

// ---- forEach 0x0057BC45, walk 0x0057BB4E
class Rva0057BC45Listener
{
public:
	virtual void notify(void *);
};

struct Rva0057BB4ECall
{
	void (Rva0057BC45Listener::*notify)(void *);
	void *arg;
};

class Rva0057BC45List
{
public:
	void forEach(void (Rva0057BC45Listener::*notify)(void *), void *arg);
	void apply(const Rva0057BB4ECall &call);

private:
	Rva0057BC45Listener **m_begin;		// +0x00
	Rva0057BC45Listener **m_end;		// +0x04
	Rva0057BC45Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0057BC45List::forEach(void (Rva0057BC45Listener::*notify)(void *), void *arg)
{
	Rva0057BB4ECall call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva0057BC45List::apply(const Rva0057BB4ECall &call)
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
