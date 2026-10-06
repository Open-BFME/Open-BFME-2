// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva005543D5@Rva005543D5@@QAEXXZ @0x005543D5 142B
// Guarded lazy init: if m_64 nonzero return; else new LockClass(m_9C -1)
// via rowed 0x00613A70 plus new 0x0002FDA0 into m_A4 via rowed set
// 0x000998EA; then new Rva0055436A(m_9C) via rowed ctor 0x0055436A plus
// new 0x0002FDA0 into m_64 plus virtual slot +4 call. Evidence: chain from
// 0x0055436A; no callers; sizes 8 and 0x6C match news.
#include <map>
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function();
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};
class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &m, int t);
		~LockClass();
		MutexClass &mutex;
		bool failed;
	};
	void *handle;
	int locked;
};
class Rva0009990D
{
public:
	void set(void *p);
private:
	MutexClass::LockClass *m_ptr;
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
class Rva005543D5
{
	char m_pad0[0x64];
	Rva0055436A *m_64;
	char m_pad1[0x9C - 0x68];
	MutexClass m_9C;
	Rva0009990D m_A4;
public:
	void rva005543D5();
};
void Rva005543D5::rva005543D5()
{
	if (m_64 != 0)
		return;
	m_A4.set(new MutexClass::LockClass(m_9C, -1));
	Rva0055436A *obj = new Rva0055436A(&m_9C);
	m_64 = obj;
	obj->Execute();
}
