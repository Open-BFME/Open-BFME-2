// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x00330590.  Each list's forEach packs a vcall
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
//   0x0033066D  0x00330590  1
//   0x0033068B  0x003305FD  2
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

// ---- forEach 0x0033066D, walk 0x00330590
class Rva0033066DListener
{
public:
	virtual void notify(void *);
};

struct Rva00330590Call
{
	void (Rva0033066DListener::*notify)(void *);
	void *arg;
};

class Rva0033066DList
{
public:
	void forEach(void (Rva0033066DListener::*notify)(void *), void *arg);
	void apply(const Rva00330590Call &call);

private:
	Rva0033066DListener **m_begin;		// +0x00
	Rva0033066DListener **m_end;		// +0x04
	Rva0033066DListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0033066DList::forEach(void (Rva0033066DListener::*notify)(void *), void *arg)
{
	Rva00330590Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva0033066DList::apply(const Rva00330590Call &call)
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

// ---- forEach 0x0033068B, walk 0x003305FD
class Rva0033068BListener
{
public:
	virtual void notify(void *, int);
};

struct Rva003305FDCall
{
	void (Rva0033068BListener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva0033068BList
{
public:
	void forEach(void (Rva0033068BListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva003305FDCall &call);

private:
	Rva0033068BListener **m_begin;		// +0x00
	Rva0033068BListener **m_end;		// +0x04
	Rva0033068BListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0033068BList::forEach(void (Rva0033068BListener::*notify)(void *, int), void *arg, int value)
{
	Rva003305FDCall call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva0033068BList::apply(const Rva003305FDCall &call)
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
