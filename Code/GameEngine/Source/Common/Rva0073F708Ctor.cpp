// cl: /MD /EHsc
// ??0Rva0073F708@@QAE@PAXH@Z @0x0073F708 112B.
// Stores the first argument, allocates an 8-byte thread object (vtable
// 0x007C93A0, its handle nulled before the vtable store) into an owning
// holder at +4, builds the rowed
// event Rva0040F9D at +8 with (1, 0, 0, 0), then starts the thread through
// the rowed Rva0073F778::rva0073F778 with start routine 0x0073F6FC, this,
// resume 1, default stack and the given priority.
// Retail's unwind map destroys +4 in state 0 through 0x000A880F (the rowed
// holder clear, folded with the holder's dtor) and +8 in state 1 through
// the event dtor thunk 0x000411BC. The banked 0.96 attempt held both as
// plain pointers and had no EH states.
// The 8-byte object's table 0x007C93A0 is the Rva00514E6B handle table
// {0x00040EF8 wait; 0x0050B5C6 predicate; scalar destructor}; retail folds
// that descendant table across the classes that share it. The class view
// derives from that base instead of re-declaring its virtuals as unnamed
// placeholders, so every slot binds to the rowed function retail holds.
#include "../../Include/Common/Rva00041004Lock.h"

class Rva0073F778 : public Rva00514E6B
{
public:
	bool createThread(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security);
};

class Rva000A880F
{
public:
	Rva000A880F(Rva0073F778 *thread) : m_ptr(thread) {}
	~Rva000A880F();
	Rva0073F778 *get() const { return m_ptr; }
private:
	Rva0073F778 *m_ptr;
};

class Rva0040F9D
{
public:
	Rva0040F9D(int a1, int a2, char const *a3, void *a4);
	virtual ~Rva0040F9D();
private:
	void *m_handle;
};

unsigned __stdcall workerThreadProc(void *arg);

class Rva0073F708
{
public:
	Rva0073F708(void *owner, int priority);
private:
	void *m_a1;
	Rva000A880F m_thread;
	Rva0040F9D m_event;
};

Rva0073F708::Rva0073F708(void *owner, int priority)
	: m_a1(owner), m_thread(new Rva0073F778), m_event(1, 0, 0, 0)
{
	m_thread.get()->createThread(workerThreadProc, this, 1, 0, priority, 0);
}

// ??0Rva000A8893Worker@@QAE@PAXH@Z @0x000A8893 112B: byte-identical to Rva0073F708's constructor
// above except its own EH handler (formerly matched as the alias dup_000a8893); Rva00A897DDtor.cpp
// constructs it by this name. Same members: owner pointer, thread holder and event.
class Rva000A8893Worker
{
public:
	Rva000A8893Worker(void *owner, int priority);
private:
	void *m_a1;
	Rva000A880F m_thread;
	Rva0040F9D m_event;
};

Rva000A8893Worker::Rva000A8893Worker(void *owner, int priority)
	: m_a1(owner), m_thread(new Rva0073F778), m_event(1, 0, 0, 0)
{
	m_thread.get()->createThread(workerThreadProc, this, 1, 0, priority, 0);
}
