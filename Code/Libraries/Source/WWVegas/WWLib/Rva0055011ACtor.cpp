// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva0055011A@@QAE@XZ @0x0055011A 157B.
// Virtual-class default ctor: vtable store, three MutexClass members, two deque wrappers,
// ModuleTemplateMap member, tail zeroes plus a 10-dword body loop.
// Evidence: vtable store at +0 proves ctor; callees rowed 0x006139F0 0x00550083 0x00413727;
// two 0x28-spaced wrapper slots plus mutex/map offsets fix the layout.
#include <map>

class MutexClass
{
public:
	MutexClass(const char *name);
	~MutexClass();
private:
	void *m_handle;
	bool m_locked;
	char m_pad[3];
};

class Rva00550083
{
public:
	Rva00550083();
	~Rva00550083();
private:
	char m_pad[0x28];
};

enum NameKeyType
{
	NAMEKEY_FIRST = 0
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		void *m_createProc;
		void *m_createDataProc;
		int m_whichInterfaces;
	};
};

typedef _STL::map<NameKeyType, ModuleFactory::ModuleTemplate,
	_STL::less<NameKeyType> > ModuleTemplateMap;

extern template ModuleTemplateMap::map();

class Rva0055011ABase
{
public:
	Rva0055011ABase() {}
	~Rva0055011ABase();
};

class Rva0055011A : public Rva0055011ABase
{
public:
	Rva0055011A();
	virtual ~Rva0055011A();
private:
	MutexClass m_04;
	MutexClass m_0C;
	MutexClass m_14;
	Rva00550083 m_1C;
	Rva00550083 m_44;
	int m_6C;
	int m_70;
	ModuleTemplateMap m_74;
	int m_80[10];
	MutexClass m_A8;
	int m_B0;
};

Rva0055011A::Rva0055011A()
	: m_04(NULL),
	  m_0C(NULL),
	  m_14(NULL),
	  m_6C(0),
	  m_70(0),
	  m_A8(NULL),
	  m_B0(0)
{
	for (int i = 0; i < 10; ++i)
		m_80[i] = 0;
}
