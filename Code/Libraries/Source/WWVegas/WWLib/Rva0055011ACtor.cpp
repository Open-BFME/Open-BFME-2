// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva0055011A@@QAE@XZ @0x0055011A 157B.
// Virtual-class default ctor: vtable store, three MutexClass members, two deque wrappers,
// string-key map member, tail zeroes plus a 10-dword body loop.
// Evidence: vtable store at +0 proves ctor; callees rowed 0x006139F0 0x00550083 0x00413727;
// two 0x28-spaced wrapper slots plus mutex/map offsets fix the layout.
// Native FuncInfo94CDEC binds seven complete cleanup actions. State0 passes
// this to the7B primary-base dtor54F91B (table C6AB10); the existing156B
// destructor54FFA5 uses the same base view. States4/5 call distinct5B deque
// wrappers54FF9B/54FFA0 which both reach the complete87B dtor54FF17.
// The slot10 clear and slot6 lookup/store units independently identify the
// string-key map at74; its native5B outer teardown38A5D1 calls the existing
// full56B string/int tree destructor38A48B. Signedness and queue element
// identities remain unspecified beyond these existing provider views.
#include <map>
#include <string>

#include "mutex.h"

// Existing opaque lifetime view from the complete156B owner destructor.
struct Rva00660470Deque
{
public:
	~Rva00660470Deque();
	char m_body[ 0x28 ]; // +0x00
};

class Rva00550083
{
public:
	Rva00550083();
	~Rva00550083() { ((Rva00660470Deque *)this)->~Rva00660470Deque(); }
private:
	char m_pad[0x28];
};

// The second wrapper shares the exact21B storage construction. Its distinct
// native destructor copy still tears down precisely one underlying deque.
class Rva0055011ADeque44
{
public:
    ~Rva0055011ADeque44() {}
private:
    Rva00550083 m_storage;
};

typedef _STL::basic_string<char> PingKey;
typedef _STL::pair<const PingKey, int> PingPair;
typedef _STL::_Rb_tree<PingKey, PingPair, _STL::_Select1st<PingPair>,
    _STL::less<PingKey>, _STL::allocator<PingPair> > PingTree;
// The complete tree lifetime is already defined and verified in PeerStatMapTreeDestructor.cpp.
namespace _STL { template<> PingTree::~_Rb_tree(); }
typedef _STL::map<PingKey, int, _STL::less<PingKey> > PingMap;
extern template PingMap::map();

class Rva006609D0Base
{
public:
    virtual ~Rva006609D0Base() {}
};

class Rva0055011A : public Rva006609D0Base
{
public:
	Rva0055011A();
	virtual ~Rva0055011A();
private:
	MutexClass m_04;
	MutexClass m_0C;
	MutexClass m_14;
	Rva00550083 m_1C;
	Rva0055011ADeque44 m_44;
	int m_6C;
	int m_70;
	PingMap m_74;
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
