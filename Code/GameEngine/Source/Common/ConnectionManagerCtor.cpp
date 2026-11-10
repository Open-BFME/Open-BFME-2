// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0ConnectionManager@@QAE@XZ @ 0x004D274B 263B
// ConnectionManager::ConnectionManager: vtable + history[9] via ??_H + transport/localSlot/router + maps/set/array via ??_L + 8-way loop.
// Evidence: offsets match getFileTransferProgress layout 0x12138/0x12150; rowed ctors map<int void*> 0x33C432 set<AsciiString> 0xD3A71 ??_H ??_L; donor ConnectionManagerConstructor.cpp same init and loop.
#include <map>
#include <set>
#include <string.h>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::_Rb_tree_base(allocator<pair<int const, void *> > const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
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

class Rva004D04C9
{
public:
    void *rva004D04E0(int);
};

struct CommandHistory
{
	unsigned int words[0x800];
	CommandHistory() { reinterpret_cast<Rva004D04C9 *>(this)->rva004D04E0(0); }
};

class Connection;
class DisconnectManager;
class FrameDataManager;
class NetCommandList;
class NetCommandWrapperList;

struct Unknown12050
{
	unsigned int m_12050;
	unsigned short m_12054;
	char m_pad[2];
	Unknown12050() : m_12050(0), m_12054(0) {}
};

// Preserve the verified set constructor while naming the target-specific
// tree destruction: retail4D1D2D tail-calls the rowed tree dtor4D1AC3.
// The original comparator/container spelling remains unasserted.
class Rva004D0545 {public:~Rva004D0545();};
struct ConnectionAsciiSet
{
	unsigned storage[3];
	__forceinline ConnectionAsciiSet()
	{
		typedef _STL::set<AsciiString> Native;
		((Native *)this)->Native::set();
	}
	__declspec(noinline) ~ConnectionAsciiSet();
};
ConnectionAsciiSet::~ConnectionAsciiSet()
{
	((Rva004D0545 *)this)->Rva004D0545::~Rva004D0545();
}
typedef char ConnectionAsciiSetExtent[(sizeof(ConnectionAsciiSet)==12)?1:-1];

// Retail's eight progress-map callbacks destroy through the existing
// Rva004D1D32 owner, not the unrelated generic map<int,void*> destructor.
// Keep the STLport empty-tree construction and allocator temporaries. The
// comparator and payload spelling are construction views, not target types.
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
typedef char ConnectionProgressExtent[(sizeof(Rva004D1D32)==12)?1:-1];

// +0x12138 is the map ConnectionManagerInit2.cpp and ConnectionManager_dtor.cpp
// spell map<int, Rva004D1B38Mapped>: retail's unwind for it (0x00790E8E) runs
// ~map 0x004D233F -> tree dtor 0x004D21B4, and init/reset clear it through
// 0x004D1EF1. Its default constructor is the shared folded 0x0033C432.
#include "../../Include/Common/Rva004D1B38Mapped.h"
typedef _STL::map<int, Rva004D1B38Mapped> Rva004D1B38Map;
namespace _STL { template <> _Rb_tree_base<pair<int const, Rva004D1B38Mapped>, allocator<pair<int const, Rva004D1B38Mapped> > >::_Rb_tree_base(allocator<pair<int const, Rva004D1B38Mapped> > const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, Rva004D1B38Mapped>, _Select1st<pair<int const, Rva004D1B38Mapped> >, less<int>, allocator<pair<int const, Rva004D1B38Mapped> > >::~_Rb_tree(); }
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
	Rva004D1B38Map m_12138;
	ConnectionAsciiSet m_12144;
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

// Retail 0x004D13EA, 14 bytes: default constructor passed by the matched
// ConnectionManager ehvec constructor for nine 0x2000-byte histories.
// The target calls the matched zero-and-state setter with zero and returns
// this. CommandHistory is the donor name already used by the matched parent;
// array size and callee are independently established by target bytes.

// ?bfmeEmitConnectionManagerCtor absent-from-retail
ConnectionManager *bfmeEmitConnectionManagerCtor()
{
	return new ConnectionManager;
}
