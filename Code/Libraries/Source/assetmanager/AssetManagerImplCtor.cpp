// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// stlport
// AssetManagerImpl constructor identity: WB167D4F0 names it in its own
// assertion; the complete native624DB0..625034 body and member lifecycle
// independently establish the shared asset-manager layout. Clean BFME1 donor
// 90fffa62857c131831171802121eef7e6604eb58 (unchanged from reviewed ba7ddda7)
// Rva009EB960Ctor.cpp supplies the constructor semantics. Native introduces
// two additional words at +24/+30, shifting locks/queues/groups by eight.
// Hash-map and deque element spellings are constructor storage ABI views;
// native initialization and matched siblings prove those helpers, not original
// application element names. Worker vtable retains its established opaque owner.

#define _STLP_USE_STATIC_LIB 1

#include <deque>
#include <hash_map>
#include <new>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <string.h>
#include <windows.h>

extern "C" __declspec(dllimport) unsigned long __cdecl _beginthread(void (__cdecl *start_address)(void *), unsigned stack_size, void *arglist);

#pragma intrinsic(memset)

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

struct Rva009F2140AssetSetGroup
{
	Rva001408C0Set m_tree;
	volatile unsigned int m_count;
	volatile bool m_active;
	unsigned char m_padding[3];

	Rva009F2140AssetSetGroup() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

class Rva009EEA70CleanupDeleting
{
public:
	Rva009EEA70CleanupDeleting() : m_last(1)
	{
		for (unsigned int i = 0; i < 0xafcf; ++i)
			m_data[i] = 0;
	}

	virtual ~Rva009EEA70CleanupDeleting();

	unsigned int m_data[0xafcf];
	unsigned int m_last;
};

class AssetManagerImpl;
class Q1Receiver0134FAAC;
extern Q1Receiver0134FAAC *TheQ1Receiver;
extern void __cdecl Rva00622670ThreadProc(void *);

typedef _STL::hash_map<int, int> GenHashMap1470;
typedef _STL::hash_map<int, int> GenHashMap14C0;
typedef _STL::deque<int> GenDeque;

class AssetManagerImpl
{
public:
	AssetManagerImpl();
	~AssetManagerImpl();

private:
	uintptr_t m_thread;
	void *m_unknown04;
	bool m_active;
	unsigned char m_pad09[3];
	GenHashMap1470 m_map0c;
	unsigned int m_field20;
	unsigned int m_reserved24;
	unsigned int m_field28;
	unsigned int m_field2c;
	unsigned int m_reserved30;
	CRITICAL_SECTION m_lock34;
	GenHashMap14C0 m_map4c;
	GenHashMap14C0::iterator m_iterator60;
	CRITICAL_SECTION m_lock68;
	GenDeque m_deques80[7];
	Rva009F2140AssetSetGroup m_set198;
	Rva009F2140AssetSetGroup m_set1ac;
	Rva009F2140AssetSetGroup m_set1c0;
	Rva009F2140AssetSetGroup m_set1d4;
	unsigned int m_field1e8;
	unsigned int m_field1ec;
	unsigned char m_pad1f0[4];
	bool m_flag1f4;
	bool m_flag1f5;
	bool m_flag1f6;
	unsigned char m_pad1f7;
	Rva009EEA70CleanupDeleting *m_hashContext;
};

typedef char GenDtorSizeCheck[sizeof(AssetManagerImpl) == 0x1fc ? 1 : -1];
typedef char RegistryWorkerSizeCheck[sizeof(Rva009EEA70CleanupDeleting) == 0x2bf44 ? 1 : -1];

AssetManagerImpl::AssetManagerImpl()
	: m_active(false),
	  m_map0c(100),
	  m_field20(0),
	  m_reserved24(0),
	  m_field28(0x10000000),
	  m_field2c(0),
	  m_reserved30(0),
	  m_map4c(100)
{
	m_field1e8 = 0;
	m_field1ec = 0;
	m_flag1f4 = true;
	m_flag1f5 = true;
	m_flag1f6 = false;

	m_iterator60 = m_map4c.begin();

	void *workerMemory = ::operator new(0x2bf44);
	Rva009EEA70CleanupDeleting *worker;
	if (workerMemory != 0)
	{
		worker = new (workerMemory) Rva009EEA70CleanupDeleting;
	}
	else
	{
		worker = 0;
	}
	m_hashContext = worker;

	InitializeCriticalSection(&m_lock34);
	InitializeCriticalSection(&m_lock68);
	TheQ1Receiver = (Q1Receiver0134FAAC *)this;
	m_thread = _beginthread(Rva00622670ThreadProc, 0, this);
	Sleep(1);
}
