// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x003196A7.  Each list's forEach packs a vcall
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
//   0x003197EE  0x003196A7  1
//   0x0031980C  0x00319714  2
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

// ---- forEach 0x003197EE, walk 0x003196A7
class Rva003197EEListener
{
public:
	virtual void notify(void *);
	void notifyX(void *);
	void notifyY(void *);
};

struct Rva003196A7Call
{
	void (Rva003197EEListener::*notify)(void *);
	void *arg;
};

class Rva003197EEList
{
public:
	void forEach(void (Rva003197EEListener::*notify)(void *), void *arg);
	void apply(const Rva003196A7Call &call);

private:
	Rva003197EEListener **m_begin;		// +0x00
	Rva003197EEListener **m_end;		// +0x04
	Rva003197EEListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva003197EEList::forEach(void (Rva003197EEListener::*notify)(void *), void *arg)
{
	Rva003196A7Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva003197EEList::apply(const Rva003196A7Call &call)
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

// ---- forEach 0x0031980C, walk 0x00319714
class Rva0031980CListener
{
public:
	virtual void notify(void *, int);
};

struct Rva00319714Call
{
	void (Rva0031980CListener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva0031980CList
{
public:
	void forEach(void (Rva0031980CListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva00319714Call &call);

private:
	Rva0031980CListener **m_begin;		// +0x00
	Rva0031980CListener **m_end;		// +0x04
	Rva0031980CListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0031980CList::forEach(void (Rva0031980CListener::*notify)(void *, int), void *arg, int value)
{
	Rva00319714Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva0031980CList::apply(const Rva00319714Call &call)
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

class Rva00319B0AVirt
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
};

class Rva00319B0AOwner
{
public:
	void rva00319B0A();
	void rva00319B31();
private:
	char m_pad0[8];
	Rva003197EEList m_list;
	char m_pad1[0x70];
	Rva00319B0AVirt *m_ptr;
};

void Rva00319B0AOwner::rva00319B0A()
{
	if (m_ptr)
		m_ptr->v1();
	m_list.forEach((void (Rva003197EEListener::*)(void *))&Rva003197EEListener::notifyX, this);
}

void Rva00319B0AOwner::rva00319B31()
{
	if (m_ptr)
		m_ptr->v2();
	m_list.forEach((void (Rva003197EEListener::*)(void *))&Rva003197EEListener::notifyY, this);
}
