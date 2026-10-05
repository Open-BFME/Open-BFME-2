// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x004FA738.  Each list's forEach packs a vcall
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
//   0x004FA935  0x004FA738  1
//   0x004FA953  0x004FA7A5  2
//   0x004FC320  0x004FC2B3  1
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

// ---- forEach 0x004FA935, walk 0x004FA738
class Rva004FA935Listener
{
public:
	virtual void notify(void *);
};

struct Rva004FA738Call
{
	void (Rva004FA935Listener::*notify)(void *);
	void *arg;
};

class Rva004FA935List
{
public:
	void forEach(void (Rva004FA935Listener::*notify)(void *), void *arg);
	void apply(const Rva004FA738Call &call);

private:
	Rva004FA935Listener **m_begin;		// +0x00
	Rva004FA935Listener **m_end;		// +0x04
	Rva004FA935Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva004FA935List::forEach(void (Rva004FA935Listener::*notify)(void *), void *arg)
{
	Rva004FA738Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva004FA935List::apply(const Rva004FA738Call &call)
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

// ---- forEach 0x004FA953, walk 0x004FA7A5
class Rva004FA953Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva004FA7A5Call
{
	void (Rva004FA953Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva004FA953List
{
public:
	void forEach(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva004FA7A5Call &call);

private:
	Rva004FA953Listener **m_begin;		// +0x00
	Rva004FA953Listener **m_end;		// +0x04
	Rva004FA953Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva004FA953List::forEach(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value)
{
	Rva004FA7A5Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva004FA953List::apply(const Rva004FA7A5Call &call)
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

// ---- forEach 0x004FC320, walk 0x004FC2B3
class Rva004FC320Listener
{
public:
	virtual void notify(void *);
};

struct Rva004FC2B3Call
{
	void (Rva004FC320Listener::*notify)(void *);
	void *arg;
};

class Rva004FC320List
{
public:
	void forEach(void (Rva004FC320Listener::*notify)(void *), void *arg);
	void apply(const Rva004FC2B3Call &call);

private:
	Rva004FC320Listener **m_begin;		// +0x00
	Rva004FC320Listener **m_end;		// +0x04
	Rva004FC320Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva004FC320List::forEach(void (Rva004FC320Listener::*notify)(void *), void *arg)
{
	Rva004FC2B3Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva004FC320List::apply(const Rva004FC2B3Call &call)
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
