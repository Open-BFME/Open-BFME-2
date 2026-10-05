// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x0040D487.  Each list's forEach packs a vcall
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
//   0x0040D8B8  0x0040D487  1
//   0x0040D8D6  0x0040D4F4  2
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

// ---- forEach 0x0040D8B8, walk 0x0040D487
class Rva0040D8B8Listener
{
public:
	virtual void notify(void *);
};

struct Rva0040D487Call
{
	void (Rva0040D8B8Listener::*notify)(void *);
	void *arg;
};

class Rva0040D8B8List
{
public:
	void forEach(void (Rva0040D8B8Listener::*notify)(void *), void *arg);
	void apply(const Rva0040D487Call &call);

private:
	Rva0040D8B8Listener **m_begin;		// +0x00
	Rva0040D8B8Listener **m_end;		// +0x04
	Rva0040D8B8Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0040D8B8List::forEach(void (Rva0040D8B8Listener::*notify)(void *), void *arg)
{
	Rva0040D487Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva0040D8B8List::apply(const Rva0040D487Call &call)
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

// ---- forEach 0x0040D8D6, walk 0x0040D4F4
class Rva0040D8D6Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva0040D4F4Call
{
	void (Rva0040D8D6Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva0040D8D6List
{
public:
	void forEach(void (Rva0040D8D6Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva0040D4F4Call &call);

private:
	Rva0040D8D6Listener **m_begin;		// +0x00
	Rva0040D8D6Listener **m_end;		// +0x04
	Rva0040D8D6Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0040D8D6List::forEach(void (Rva0040D8D6Listener::*notify)(void *, int), void *arg, int value)
{
	Rva0040D4F4Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva0040D8D6List::apply(const Rva0040D4F4Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.arg, call.value);
		i = m_index;
	}
}
