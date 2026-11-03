// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva005543D5@Rva005543D5@@QAEXXZ @0x005543D5 142B
// Guarded lazy init: if m_64 nonzero return; else new LockClass(m_9C -1)
// via rowed 0x00613A70 plus new 0x0002FDA0 into m_A4 via rowed set
// 0x000998EA; then new PSThreadClass(m_9C) via rowed ctor 0x0055436A plus
// new 0x0002FDA0 into m_64 plus virtual slot +4 call. Evidence: chain from
// 0x0055436A; no callers; sizes 8 and 0x6C match news.
#include <map>
#include "../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"
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
// Pointer-map storage retains this unit's verified ABI view; payload type is provisional.
class PSThreadClass : public ThreadClass
{
public:
	PSThreadClass(void *arg);
	virtual ~PSThreadClass(); // Native owner: PersistentStorageThread.cpp, RVA 0x0055405A.
protected:
	virtual void Thread_Function(); // Native slot 2: RVA 0x005580FB.
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
	PSThreadClass *m_thread;
	char m_pad1[0x9C - 0x68];
	MutexClass m_mutex;
	Rva0009990D m_lock;
public:
	void rva005543D5();
};
void Rva005543D5::rva005543D5()
{
	if (m_thread != 0)
		return;
	m_lock.set(new MutexClass::LockClass(m_mutex, -1));
	PSThreadClass *obj = new PSThreadClass(&m_mutex);
	m_thread = obj;
	obj->Execute();
}
