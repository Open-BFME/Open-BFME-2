// cl: /O1 /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x0053F97F.  Each list's forEach packs a vcall
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
//   0x0053F9EC  0x0053F97F  1
//   0x005402DC  0x005401E3  2
//   0x005414E5  0x00541340  2
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

// ---- forEach 0x0053F9EC, walk 0x0053F97F
class Rva0053F9ECListener
{
public:
	virtual void notify(void *);
};

struct Rva0053F97FCall
{
	void (Rva0053F9ECListener::*notify)(void *);
	void *arg;
};

class Rva0053F9ECList
{
public:
	void forEach(void (Rva0053F9ECListener::*notify)(void *), void *arg);
	void apply(const Rva0053F97FCall &call);

private:
	Rva0053F9ECListener **m_begin;		// +0x00
	Rva0053F9ECListener **m_end;		// +0x04
	Rva0053F9ECListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva0053F9ECList::forEach(void (Rva0053F9ECListener::*notify)(void *), void *arg)
{
	Rva0053F97FCall call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva0053F9ECList::apply(const Rva0053F97FCall &call)
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

// ---- forEach 0x005402DC, walk 0x005401E3
class Rva005402DCListener
{
public:
	virtual void notify(void *, int);
};

struct Rva005401E3Call
{
	void (Rva005402DCListener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva005402DCList
{
public:
	void forEach(void (Rva005402DCListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva005401E3Call &call);

private:
	Rva005402DCListener **m_begin;		// +0x00
	Rva005402DCListener **m_end;		// +0x04
	Rva005402DCListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005402DCList::forEach(void (Rva005402DCListener::*notify)(void *, int), void *arg, int value)
{
	Rva005401E3Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva005402DCList::apply(const Rva005401E3Call &call)
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

// ---- forEach 0x005414E5, walk 0x00541340
class Rva005414E5Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva00541340Call
{
	void (Rva005414E5Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva005414E5List
{
public:
	void forEach(void (Rva005414E5Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva00541340Call &call);

private:
	Rva005414E5Listener **m_begin;		// +0x00
	Rva005414E5Listener **m_end;		// +0x04
	Rva005414E5Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005414E5List::forEach(void (Rva005414E5Listener::*notify)(void *, int), void *arg, int value)
{
	Rva00541340Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva005414E5List::apply(const Rva00541340Call &call)
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
