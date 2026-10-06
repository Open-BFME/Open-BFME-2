// cl: /DNDEBUG /MD /EHsc
//
// Listener-list walks around 0x005C98F6.  Each list's forEach packs a vcall
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
//   0x005C9A46  0x005C98F6  1
//   0x005C9A64  0x005C9963  2
//   0x005C9A89  0x005C99D3  3
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

// ---- forEach 0x005C9A46, walk 0x005C98F6
class Rva005C9A46Listener
{
public:
	virtual void notify(void *);
};

struct Rva005C98F6Call
{
	void (Rva005C9A46Listener::*notify)(void *);
	void *arg;
};

class Rva005C9A46List
{
public:
	void forEach(void (Rva005C9A46Listener::*notify)(void *), void *arg);
	void apply(const Rva005C98F6Call &call);

private:
	Rva005C9A46Listener **m_begin;		// +0x00
	Rva005C9A46Listener **m_end;		// +0x04
	Rva005C9A46Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005C9A46List::forEach(void (Rva005C9A46Listener::*notify)(void *), void *arg)
{
	Rva005C98F6Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva005C9A46List::apply(const Rva005C98F6Call &call)
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

// ---- forEach 0x005C9A64, walk 0x005C9963
class Rva005C9A64Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva005C9963Call
{
	void (Rva005C9A64Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva005C9A64List
{
public:
	void forEach(void (Rva005C9A64Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva005C9963Call &call);

private:
	Rva005C9A64Listener **m_begin;		// +0x00
	Rva005C9A64Listener **m_end;		// +0x04
	Rva005C9A64Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005C9A64List::forEach(void (Rva005C9A64Listener::*notify)(void *, int), void *arg, int value)
{
	Rva005C9963Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva005C9A64List::apply(const Rva005C9963Call &call)
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

// ---- forEach 0x005C9A89, walk 0x005C99D3
class Rva005C9A89Listener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva005C99D3Call
{
	void (Rva005C9A89Listener::*notify)(void *, int, int);
	void *arg;
	int value;
	int extra;
};

class Rva005C9A89List
{
public:
	void forEach(void (Rva005C9A89Listener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva005C99D3Call &call);

private:
	Rva005C9A89Listener **m_begin;		// +0x00
	Rva005C9A89Listener **m_end;		// +0x04
	Rva005C9A89Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva005C9A89List::forEach(void (Rva005C9A89Listener::*notify)(void *, int, int), void *arg, int value, int extra)
{
	Rva005C99D3Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	call.extra = extra;
	apply(call);
}

void Rva005C9A89List::apply(const Rva005C99D3Call &call)
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
