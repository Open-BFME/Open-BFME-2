// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x005F211B.  Each list's forEach packs a vcall
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
//   0x005F2230  0x005F211B  1
//   0x005F224E  0x005F2188  2
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

// ---- forEach 0x005F2230, walk 0x005F211B
class Rva005F2230Listener
{
public:
	virtual void notify(void *);
};

struct Rva005F211BCall
{
	void (Rva005F2230Listener::*notify)(void *);
	void *arg;
};

class Rva005F2230List
{
public:
	void forEach(void (Rva005F2230Listener::*notify)(void *), void *arg);
	void apply(const Rva005F211BCall &call);

private:
	Rva005F2230Listener **m_begin;		// +0x00
	Rva005F2230Listener **m_end;		// +0x04
	Rva005F2230Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005F2230List::forEach(void (Rva005F2230Listener::*notify)(void *), void *arg)
{
	Rva005F211BCall call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva005F2230List::apply(const Rva005F211BCall &call)
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

// ---- forEach 0x005F224E, walk 0x005F2188
class Rva005F224EListener
{
public:
	virtual void notify(void *, int);
};

struct Rva005F2188Call
{
	void (Rva005F224EListener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva005F224EList
{
public:
	void forEach(void (Rva005F224EListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva005F2188Call &call);

private:
	Rva005F224EListener **m_begin;		// +0x00
	Rva005F224EListener **m_end;		// +0x04
	Rva005F224EListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005F224EList::forEach(void (Rva005F224EListener::*notify)(void *, int), void *arg, int value)
{
	Rva005F2188Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva005F224EList::apply(const Rva005F2188Call &call)
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
