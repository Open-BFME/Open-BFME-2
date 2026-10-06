// cl: /DNDEBUG /MD /EHsc
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

// ---- forEach 0x003F5224, walk 0x003F4C56: five-argument slots.  The record is
// the six-dword Rva005E957C, filled by its rowed init 0x005E957C (which returns
// the record), and its call 0x003F41A4 is not inlined, so the walk hands it
// each listener.
class Rva003F41A4Elem
{
public:
	void Method(int a, int b, int c, int d, int e);
};

typedef void (Rva003F41A4Elem::*Rva003F41A4Fn)(int, int, int, int, int);

class Rva005E957C
{
public:
	Rva005E957C *rva005E957C(int a1, int a2, int a3, int a4, int a5, int a6);
	void rva003F41A4(void *elem);

private:
	Rva003F41A4Fn m_fn;	// +0x00
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	int m_14;
};

void Rva005E957C::rva003F41A4(void *elem)
{
	Rva003F41A4Elem *e = (Rva003F41A4Elem *)elem;
	(e->*m_fn)(m_4, m_8, m_c, m_10, m_14);
}

class Rva003F5224List
{
public:
	void forEach(Rva003F41A4Fn fn, int a, int b, int c, int d, int e);
	void apply(Rva005E957C &call);

private:
	Rva003F41A4Elem **m_begin;		// +0x00
	Rva003F41A4Elem **m_end;		// +0x04
	Rva003F41A4Elem **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva003F5224List::forEach(Rva003F41A4Fn fn, int a, int b, int c, int d, int e)
{
	Rva005E957C call;
	apply(*call.rva005E957C(*(int *)&fn, a, b, c, d, e));
}

void Rva003F5224List::apply(Rva005E957C &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		call.rva003F41A4(m_begin[i]);
		i = m_index;
	}
}
