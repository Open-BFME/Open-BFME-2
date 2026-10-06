// cl: /MD /EHsc
// ??0Rva0073F708@@QAE@PAXH@Z @0x0073F708 112B.
// Stores the first argument, allocates an 8-byte thread object (vtable
// 0x007C93A0, handle nulled before the vtable store, so the handle lives in
// a base without a vtable) into an owning holder at +4, builds the rowed
// event Rva0040F9D at +8 with (1, 0, 0, 0), then starts the thread through
// the rowed Rva0073F778::rva0073F778 with start routine 0x0073F6FC, this,
// resume 1, default stack and the given priority.
// Retail's unwind map destroys +4 in state 0 through 0x000A880F (the rowed
// holder clear, folded with the holder's dtor) and +8 in state 1 through
// the event dtor thunk 0x000411BC. The banked 0.96 attempt held both as
// plain pointers and had no EH states.
struct Rva0073F778Base
{
	Rva0073F778Base() : m_handle(0) {}
	void *m_handle;
};

class Rva0073F778 : public Rva0073F778Base
{
public:
	virtual void v0();
	virtual bool v1();
	virtual ~Rva0073F778();
	bool rva0073F778(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security);
};

class Rva000A880F
{
public:
	Rva000A880F(Rva0073F778 *p) : m_ptr(p) {}
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

unsigned __stdcall Rva0073F6FCCb(void *arg);

class Rva0073F708
{
public:
	Rva0073F708(void *a1, int priority);
private:
	void *m_a1;
	Rva000A880F m_thread;
	Rva0040F9D m_event;
};

Rva0073F708::Rva0073F708(void *a1, int priority)
	: m_a1(a1), m_thread(new Rva0073F778), m_event(1, 0, 0, 0)
{
	m_thread.get()->rva0073F778(Rva0073F6FCCb, this, 1, 0, priority, 0);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v1@Rva0073F778@@UAE_NXZ=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
