// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x0038153B.  Each list's forEach packs a vcall
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
//   0x0038188B  0x0038153B  2
//   0x003818B0  0x003815AB  1
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

// ---- forEach 0x0038188B, walk 0x0038153B
class Rva0038188BListener
{
public:
	virtual void notify(void *, int);
};

struct Rva0038153BCall
{
	void (Rva0038188BListener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva0038188BList
{
public:
	void forEach(void (Rva0038188BListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva0038153BCall &call);

private:
	Rva0038188BListener **m_begin;		// +0x00
	Rva0038188BListener **m_end;		// +0x04
	Rva0038188BListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0038188BList::forEach(void (Rva0038188BListener::*notify)(void *, int), void *arg, int value)
{
	Rva0038153BCall call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva0038188BList::apply(const Rva0038153BCall &call)
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

// ---- forEach 0x003818B0, walk 0x003815AB
class Rva003818B0Listener
{
public:
	virtual void notify(void *);
};

struct Rva003815ABCall
{
	void (Rva003818B0Listener::*notify)(void *);
	void *arg;
};

class Rva003818B0List
{
public:
	void forEach(void (Rva003818B0Listener::*notify)(void *), void *arg);
	void apply(const Rva003815ABCall &call);
	void rva003818E3(void *arg);

private:
	Rva003818B0Listener **m_begin;		// +0x00
	Rva003818B0Listener **m_end;		// +0x04
	Rva003818B0Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

class Rva005CB260
{
public:
	void rva005CB260();
};

void Rva003818B0List::forEach(void (Rva003818B0Listener::*notify)(void *), void *arg)
{
	Rva003815ABCall call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva003818B0List::apply(const Rva003815ABCall &call)
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

// ?rva003818E3@Rva003818B0List@@QAEXPAX@Z, retail 0x003818E3, 17 bytes.
// Thin wrapper over forEach 0x003818B0 with fixed notify 0x005CB260.
// Evidence: unlock lane, caller 0x00381900 loads g_00E02310 as this.
void Rva003818B0List::rva003818E3(void *arg)
{
	forEach((void (Rva003818B0Listener::*)(void *))&Rva005CB260::rva005CB260, arg);
}
