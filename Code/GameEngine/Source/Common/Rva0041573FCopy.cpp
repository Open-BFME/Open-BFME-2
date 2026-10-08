// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0041573F@@QAE@ABV0@@Z @0x0041573F 67B
// Honest Rva copy ctor: BfmeOwnedRecordArray56 at +0 via rowed copy 0x004151A3
// plus _Rb_tree900 at +0x1C0 via rowed copy 0x0041559E. Declared Array56 dtor
// reproduces the retail EH state. Flags copied from sibling OwnedRecord900TreeCopy.cpp.
#include <map>
class AsciiString { void *m_data; public: AsciiString(const AsciiString &o); ~AsciiString(); };
class Rva002390CB { void *a; void *b; public: __declspec(nothrow) Rva002390CB(const Rva002390CB &o); ~Rva002390CB(); };
struct BfmeStringRecord002CF550 {
	~BfmeStringRecord002CF550();
	AsciiString text;
	Rva002390CB ref;
};
bool operator<(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r);
namespace _STL { template <> struct less<BfmeStringRecord002CF550> { bool operator()(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r) const; }; }
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > Tree900;
class BfmeOwnedRecordArray56 {
	char m_data[0x1C0];
public:
	BfmeOwnedRecordArray56(const BfmeOwnedRecordArray56 &o);
	~BfmeOwnedRecordArray56();
};
class Rva0041573F {
public:
	Rva0041573F(const Rva0041573F &src);
	~Rva0041573F();
private:
	BfmeOwnedRecordArray56 m_arr;
	Tree900 m_tree;
};
Rva0041573F::Rva0041573F(const Rva0041573F &src)
	: m_arr(src.m_arr)
	, m_tree(src.m_tree)
{
}

class Rva0041579E {
public:
	Rva0041579E(const Rva0041579E &src);
	~Rva0041579E();
private:
	int m_00;
	Rva0041573F m_04;
};
Rva0041579E::Rva0041579E(const Rva0041579E &src)
	: m_00(src.m_00)
	, m_04(src.m_04)
{
}

Rva0041579E::~Rva0041579E()
{
}

// ??0Rva0022A809Subsystem@@QAE@XZ, retail 0x00415704, 59 bytes.
// Gap between ??1Rva0041579E 0x004156FC and ??0Rva0041573F 0x0041573F; called by matched GameEngine::init 0x0022ED66;
// calls rowed BFME2NativeNetwork::baseConstruct 0x001B4E63 and rowed hash_map ctor 0x00415643; vtable 0x0083A288; byte at +0x20.
#include <hash_map>
struct Rva00415643Element { char bytes[1]; };
class BFME2NativeNetwork
{
public:
	void baseConstruct();
};
class __declspec(novtable) Rva0022A809SubsystemBase
{
public:
	Rva0022A809SubsystemBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022A809SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};
class Rva0022A809Subsystem : public Rva0022A809SubsystemBase
{
public:
	Rva0022A809Subsystem();
	virtual ~Rva0022A809Subsystem();
private:
	_STL::hash_map<int, Rva00415643Element> m_map0C; // +0x0C
	unsigned char m_20; // +0x20
};
Rva0022A809Subsystem::Rva0022A809Subsystem()
	: m_20(0)
{
}
