// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x0027F519.  Each list's forEach packs a vcall
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
//   0x00281A33  0x0027F519  2
//   0x00281A15  0x00280B1A  1
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

// ---- forEach 0x00281A33, walk 0x0027F519
class Rva00281A33Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva0027F519Call
{
	void (Rva00281A33Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva00281A33List
{
public:
	void forEach(void (Rva00281A33Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva0027F519Call &call);

private:
	Rva00281A33Listener **m_begin;		// +0x00
	Rva00281A33Listener **m_end;		// +0x04
	Rva00281A33Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva00281A33List::forEach(void (Rva00281A33Listener::*notify)(void *, int), void *arg, int value)
{
	Rva0027F519Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva00281A33List::apply(const Rva0027F519Call &call)
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

// ---- forEach 0x00281A15, walk 0x00280B1A
class Rva00281A15Listener
{
public:
	virtual void notify(void *);
};

struct Rva00280B1ACall
{
	void (Rva00281A15Listener::*notify)(void *);
	void *arg;
};

class Rva00281A15List
{
public:
	void forEach(void (Rva00281A15Listener::*notify)(void *), void *arg);
	void apply(const Rva00280B1ACall &call);

private:
	Rva00281A15Listener **m_begin;		// +0x00
	Rva00281A15Listener **m_end;		// +0x04
	Rva00281A15Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva00281A15List::forEach(void (Rva00281A15Listener::*notify)(void *), void *arg)
{
	Rva00280B1ACall call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva00281A15List::apply(const Rva00280B1ACall &call)
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
