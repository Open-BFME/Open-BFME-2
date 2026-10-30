// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME: ??0Rva003C2F40Owner@@QAE@XZ at retail 0x002BAE57.
// The native constructor installs the vtable at 0x007FE408, whose name slot
// returns "DelayedSplineCameraEventModule", then constructs the map at +0x0c.
// The placeholder base/owner hierarchy below still needs native vtable and
// destructor reconciliation; its historical VNI label was unsupported.

// stlport
#define _STLP_USE_STATIC_LIB 1
#include <memory>

// The native call at 0x002BAE75 reaches the existing 25-byte map constructor
// at 0x005011C1. Several int-keyed maps share that body. Use its rowed
// provider spelling and twelve-byte storage, without asserting that this
// event's mapped values are BfmePod24.
struct BfmePod24;
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class K, class V, class C, class A> class map
{
public:
	map();
private:
	char m_storage[12];
};
}
typedef _STL::map<int, BfmePod24, _STL::less<int>,
	_STL::allocator<_STL::pair<const int, BfmePod24> > > Rva003C2F40Tree;

class Rva003C2F40Base
{
public:
	Rva003C2F40Base();
	virtual ~Rva003C2F40Base();
	virtual void handle() = 0;

	unsigned m_bfme04;
	char m_bfme08;
};

// ??0Rva003C2F40Base@@QAE@XZ absent-from-retail (empty scaffold base, emits no code)
Rva003C2F40Base::Rva003C2F40Base()
{
}

class Rva003C2F40Owner : public Rva003C2F40Base
{
public:
	Rva003C2F40Owner();
	virtual ~Rva003C2F40Owner();
	Rva003C2F40Tree m_tree;
};
// ??0Rva003C2F40Owner@@QAE@XZ
Rva003C2F40Owner::Rva003C2F40Owner()
{
}
