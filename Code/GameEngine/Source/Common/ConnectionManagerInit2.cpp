// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport46
// ??0ConnectionManager@@QAE@XZ @ 0x004D274B 263B
// ConnectionManager::ConnectionManager: vtable + history[9] via ??_H + transport/localSlot/router + maps/set/array via ??_L + 8-way loop.
// Evidence: offsets match getFileTransferProgress layout 0x12138/0x12150; rowed ctors map<int void*> 0x33C432 set<AsciiString> 0xD3A71 ??_H ??_L; donor ConnectionManagerConstructor.cpp same init and loop.
#include <map>
#include <set>
#include <string.h>
#include <new>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::_Rb_tree_base(allocator<pair<int const, void *> > const &); }
// bfme link decl-only end

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

struct CommandHistory
{
	unsigned int words[0x800];
	CommandHistory();
};

class Connection;
class DisconnectManager;
class FrameDataManager;

class NetCommandList
{
public:
	NetCommandList();
	virtual ~NetCommandList();
	void reset();
	void *m_first;
	void *m_last;
	void *m_lastInserted;
};

class Rva004D376A
{
public:
	Rva004D376A();
	virtual ~Rva004D376A();
	char m_pad[0x288];
};

class NetCommandWrapperList
{
public:
	NetCommandWrapperList();
	virtual ~NetCommandWrapperList();
	void *m_first;
};

class Rva0055059ADwordClearer
{
public:
	void clear();
};

class FrameData12104
{
public:
	virtual void *release(int v);
};

class DisconnectManager
{
public:
	void init();
};

struct Unknown12050
{
	unsigned int m_12050;
	unsigned short m_12054;
	char m_pad[2];
	Unknown12050() : m_12050(0), m_12054(0) {}
};

struct Rva004D1B38Mapped
{
	AsciiString m_name;
};

class Rva004D0545
{
public:
	void rva004D0F82();
};

class Rva004D0572
{
public:
	void rva004D0FAB();
};

// The eight progress maps at +0x12150 are ConnectionManagerCtor.cpp's
// Rva004D1D32 owner (retail's ??_L/??_M callbacks pass 0x0033C432/0x004D1D32,
// not the generic map<int,void*> ctor/dtor), so this unit's copy of the
// constructor is that unit's.
typedef _STL::_Rb_tree<int, _STL::pair<const int, void *>,
    _STL::_Select1st<_STL::pair<const int, void *> >, _STL::less<int>,
    _STL::allocator<_STL::pair<const int, void *> > > ConnectionProgressTree;
class Rva004D1D32
{
public:
    Rva004D1D32()
        : m_tree(_STL::less<int>(), ConnectionProgressTree::allocator_type()) {}
    ~Rva004D1D32();
private:
    ConnectionProgressTree m_tree;
};

class ConnectionManager
{
public:
	ConnectionManager();
	virtual void init();
	virtual void reset();
	virtual void update(bool isInGame, int frameAdvanced);
	Connection *m_connections[8];
	CommandHistory m_history[9];
	void *m_transport;
	int m_localSlot;
	int m_packetRouterSlot;
	int m_packetRouterFallback[8];
	Unknown12050 m_12050wrap;
	AsciiString m_12058;
	unsigned int m_1205c;
	unsigned int m_12060[8];
	unsigned int m_12080[8];
	unsigned int m_120a0[8];
	unsigned int m_120c0[8];
	unsigned int m_120e0[8];
	unsigned int m_12100;
	unsigned int m_12104[8];
	unsigned int m_12124;
	unsigned int m_12128;
	unsigned int m_1212c;
	unsigned int m_12130;
	bool m_12134;
	bool m_12135;
	char m_12136pad[2];
	_STL::map<int, Rva004D1B38Mapped> m_12138;
	_STL::set<AsciiString> m_12144;
	Rva004D1D32 m_12150[8];
};

__declspec(noinline) inline ConnectionManager::ConnectionManager()
	: m_transport(0), m_localSlot(-1), m_packetRouterSlot(0),
	  m_12050wrap(), m_1205c(0),
	  m_12100(0), m_12124(0), m_12128(0), m_1212c(0), m_12130(0),
	  m_12134(false), m_12135(true)
{
	for (int i = 0; i < 8; ++i)
	{
		m_connections[i] = 0;
		m_packetRouterFallback[i] = -1;
		m_12104[i] = 0;
		m_12060[i] = 0;
		m_120c0[i] = 0;
		m_120e0[i] = 0;
		m_12080[i] = 0;
		m_120a0[i] = 1;
	}
}

void ConnectionManager::init()
{
	for (int i = 0; i < 8; ++i)
		m_connections[i] = 0;
	if (m_12124 == 0)
	{
		NetCommandList *netCommandList = new NetCommandList;
		m_12124 = (unsigned int)netCommandList;
		netCommandList->reset();
	}
	((NetCommandList *)m_12124)->reset();
	if (m_12128 == 0)
	{
		NetCommandList *q = new NetCommandList;
		m_12128 = (unsigned int)q;
		q->reset();
	}
	((NetCommandList *)m_12128)->reset();
	m_localSlot = -1;
	m_1205c = 0;
	m_packetRouterSlot = 0;
	for (int j = 0; j < 8; ++j)
	{
		m_packetRouterFallback[j] = -1;
		m_12060[j] = 0;
		m_120c0[j] = 0;
		m_120e0[j] = 0;
		m_120a0[0] = 0;
		m_120c0[0] = 1;
	}
	for (int k = 0; k < 8; ++k)
	{
		if (m_12104[k] != 0)
		{
			operator delete(((FrameData12104 *)m_12104[k])->release(0));
			m_12104[k] = 0;
		}
	}
	m_12100 = (unsigned int)new Rva004D376A;
	((DisconnectManager *)m_12100)->init();
	m_1212c = (unsigned int)new NetCommandWrapperList;
	((Rva0055059ADwordClearer *)m_1212c)->clear();
	m_12138.clear();
	((Rva004D0545 *)&m_12144)->rva004D0F82();
	for (int m = 0; m < 8; ++m)
		((Rva004D0572 *)&m_12150[m])->rva004D0FAB();
	m_12130 = 0;
	m_12134 = false;
	m_12135 = true;
}

// ?bfmeEmitConnectionManagerInit2 absent-from-retail
ConnectionManager *bfmeEmitConnectionManagerInit2()
{
	return new ConnectionManager;
}
