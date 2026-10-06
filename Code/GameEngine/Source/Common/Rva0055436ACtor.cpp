// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva0055436A@@QAE@PAX@Z @0x0055436A 79B
// Thread-subclass ctor: ThreadClass(0) base plus int-pointer map at +0x5C
// plus arg store at +0x68 and zero bytes/dword at +0x50 +0x51 +0x54 +0x58.
// Evidence: new(0x6C) plus lea +0x9C push at caller 0x0055443F; rowed
// ThreadClass ctor 0x00610430 map ctor 0x0033C432; vtable 0x0086B0D0;
// size 0x6C matches allocation.
#include <map>
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};
class Rva0055436A : public ThreadClass
{
public:
	Rva0055436A(void *arg);
private:
	bool m_50;
	bool m_51;
	int m_54;
	bool m_58;
	_STL::map<int, void *> m_5C;
	void *m_68;
};
Rva0055436A::Rva0055436A(void *arg) : ThreadClass(0)
{
	m_68 = arg;
	m_51 = false;
	m_58 = false;
	m_50 = false;
	m_54 = 0;
}
