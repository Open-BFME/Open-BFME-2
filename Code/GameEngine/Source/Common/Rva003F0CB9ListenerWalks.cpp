// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x003F0CB9.  Each list's forEach packs a vcall
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
//   0x003F119C  0x003F0CB9  3
//   0x003F11C7  0x003F0D2C  2
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

// ---- forEach 0x003F119C, walk 0x003F0CB9
class Rva003F119CListener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva003F0CB9Call
{
	void (Rva003F119CListener::*notify)(void *, int, int);
	void *arg;
	int value;
	int extra;
};

class Rva003F119CList
{
public:
	void forEach(void (Rva003F119CListener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva003F0CB9Call &call);

private:
	Rva003F119CListener **m_begin;		// +0x00
	Rva003F119CListener **m_end;		// +0x04
	Rva003F119CListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva003F119CList::forEach(void (Rva003F119CListener::*notify)(void *, int, int), void *arg, int value, int extra)
{
	Rva003F0CB9Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	call.extra = extra;
	apply(call);
}

void Rva003F119CList::apply(const Rva003F0CB9Call &call)
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

// ---- forEach 0x003F11C7, walk 0x003F0D2C
class Rva003F11C7Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva003F0D2CCall
{
	void (Rva003F11C7Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva003F11C7List
{
public:
	void forEach(void (Rva003F11C7Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva003F0D2CCall &call);

private:
	Rva003F11C7Listener **m_begin;		// +0x00
	Rva003F11C7Listener **m_end;		// +0x04
	Rva003F11C7Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva003F11C7List::forEach(void (Rva003F11C7Listener::*notify)(void *, int), void *arg, int value)
{
	Rva003F0D2CCall call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva003F11C7List::apply(const Rva003F0D2CCall &call)
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
