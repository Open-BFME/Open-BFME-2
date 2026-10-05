// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x005253A0.  Each list's forEach packs a vcall
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
//   0x005258E2  0x005253A0  0
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

// ---- forEach 0x005258E2, walk 0x005253A0: the slot takes no argument
class Rva005258E2Listener
{
public:
	virtual void notify();
};

struct Rva005253A0Call
{
	void (Rva005258E2Listener::*notify)();
};

class Rva005258E2List
{
public:
	void forEach(void (Rva005258E2Listener::*notify)());
	void apply(const Rva005253A0Call &call);

private:
	Rva005258E2Listener **m_begin;		// +0x00
	Rva005258E2Listener **m_end;		// +0x04
	Rva005258E2Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005258E2List::forEach(void (Rva005258E2Listener::*notify)())
{
	Rva005253A0Call call;
	call.notify = notify;
	apply(call);
}

void Rva005258E2List::apply(const Rva005253A0Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)();
		i = m_index;
	}
}
