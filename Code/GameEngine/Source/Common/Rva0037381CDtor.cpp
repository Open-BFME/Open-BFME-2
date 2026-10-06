// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva0037381C@@UAE@XZ @0x0037381C (85B).
// Dtor for MI class with GameEngineDeletingBase primary (size 0xC) and empty
// secondary at +0xC, Tree00372FF4 map at +0x10. Calls rowed values-delete
// 0x003734C0 then member and base dtors with EH states 2/1. Caller of 3734C0.
// Vtables 0x00C17E14/0x00C17E04 via gate, base reset to g_00BBB554.
#include <map>

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;

extern const void *const g_00BBB554[];

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad[0xC - 4];
};

class Rva003734C0
{
public:
	void rva003734C0();
};

class Rva0037381CSecond
{
public:
	virtual ~Rva0037381CSecond() {}
};

class Rva0037381C : public GameEngineDeletingBase, public Rva0037381CSecond
{
public:
	virtual ~Rva0037381C();
private:
	Tree00372FF4 m_map;
};

// ??1Rva0037381C@@UAE@XZ
Rva0037381C::~Rva0037381C()
{
	((Rva003734C0 *)(void *)this)->rva003734C0();
}
