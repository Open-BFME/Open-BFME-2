// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00550041@Rva0055011A@@QAEXXZ @0x00550041 66B.
// Rva0055011A slot-10 method: lock m_14, clear map at +0x74.
// Evidence: vtable slot 10 of 0x0086AB90; callees rowed 0x00613A70 0x00389A4C 0x00613AC0.
#include <map>
#include <string>

class MutexClass
{
	void *handle;
	unsigned locked;
	bool Lock(int time);
	void Unlock();
public:
	MutexClass(const char *name = 0);
	~MutexClass();
	enum { WAIT_INFINITE = -1 };
	class LockClass
	{
		MutexClass &mutex;
		bool failed;
	public:
		LockClass(MutexClass &m, int time = WAIT_INFINITE);
		~LockClass();
	private:
		LockClass &operator=(const LockClass &) { return *this; }
	};
	friend class LockClass;
};

typedef _STL::map<_STL::basic_string<char>, int, _STL::less<_STL::basic_string<char> > > WordMapH;

class Rva0055011A
{
public:
	virtual ~Rva0055011A();
	void rva00550041();
private:
	MutexClass m_04;
	MutexClass m_0C;
	MutexClass m_14;
	char m_pad[0x74 - 0x1C];
	WordMapH m_74;
	char m_tail[0xB4 - 0x74 - 12];
};

void Rva0055011A::rva00550041()
{
	MutexClass::LockClass lock(m_14);
	m_74.clear();
}
