// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x002B55F2.  Each list's forEach packs a vcall
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
//   0x002B6151  0x002B55F2  1
//   0x002B616F  0x002B565F  2
//   0x002B6126  0x002B5739  3
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

// ---- forEach 0x002B6151, walk 0x002B55F2
class Rva002B6151Listener
{
public:
	virtual void notify(void *);
};

struct Rva002B55F2Call
{
	void (Rva002B6151Listener::*notify)(void *);
	void *arg;
};

class Rva002B6151List
{
public:
	void forEach(void (Rva002B6151Listener::*notify)(void *), void *arg);
	void apply(const Rva002B55F2Call &call);

private:
	Rva002B6151Listener **m_begin;		// +0x00
	Rva002B6151Listener **m_end;		// +0x04
	Rva002B6151Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva002B6151List::forEach(void (Rva002B6151Listener::*notify)(void *), void *arg)
{
	Rva002B55F2Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva002B6151List::apply(const Rva002B55F2Call &call)
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

// ---- forEach 0x002B616F, walk 0x002B565F
class Rva002B616FListener
{
public:
	virtual void notify(void *, int);
};

struct Rva002B565FCall
{
	void (Rva002B616FListener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva002B616FList
{
public:
	void forEach(void (Rva002B616FListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva002B565FCall &call);

private:
	Rva002B616FListener **m_begin;		// +0x00
	Rva002B616FListener **m_end;		// +0x04
	Rva002B616FListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva002B616FList::forEach(void (Rva002B616FListener::*notify)(void *, int), void *arg, int value)
{
	Rva002B565FCall call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva002B616FList::apply(const Rva002B565FCall &call)
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

// ---- forEach 0x002B6126, walk 0x002B5739
class Rva002B6126Listener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva002B5739Call
{
	void (Rva002B6126Listener::*notify)(void *, int, int);
	void *arg;
	int value;
	int extra;
};

class Rva002B6126List
{
public:
	void forEach(void (Rva002B6126Listener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva002B5739Call &call);

private:
	Rva002B6126Listener **m_begin;		// +0x00
	Rva002B6126Listener **m_end;		// +0x04
	Rva002B6126Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva002B6126List::forEach(void (Rva002B6126Listener::*notify)(void *, int, int), void *arg, int value, int extra)
{
	Rva002B5739Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	call.extra = extra;
	apply(call);
}

void Rva002B6126List::apply(const Rva002B5739Call &call)
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

// ---- forEach 0x002B6194, walk 0x002B56CF: four-argument slots.  The record
// is the functor rowed at 0x002B2FCB (Rva002B2FCBInvoke.cpp), whose call is
// not inlined, so the walk hands it each listener instead of calling the
// member pointer itself.
class Rva002B2FCBElem
{
public:
	void Method(int a, int b, int c, int d);
};

typedef void (Rva002B2FCBElem::*Rva002B2FCBFn)(int, int, int, int);

class Rva002B2FCB
{
	friend class Rva002B6194List;

public:
	void rva002B2FCB(void *elem);

private:
	Rva002B2FCBFn m_fn;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
};

class Rva002B6194List
{
public:
	void forEach(Rva002B2FCBFn fn, int a, int b, int c, int d);
	void apply(Rva002B2FCB &call);

private:
	Rva002B2FCBElem **m_begin;		// +0x00
	Rva002B2FCBElem **m_end;		// +0x04
	Rva002B2FCBElem **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva002B6194List::forEach(Rva002B2FCBFn fn, int a, int b, int c, int d)
{
	Rva002B2FCB call;
	call.m_fn = fn;
	call.m_4 = a;
	call.m_8 = b;
	call.m_c = c;
	call.m_10 = d;
	apply(call);
}

void Rva002B6194List::apply(Rva002B2FCB &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		call.rva002B2FCB(m_begin[i]);
		i = m_index;
	}
}
