// cl: /MD /GX- /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002ACD09@Player@@QAEXPAXH@Z @0x002ACD09 98B: Player factory creating
// Rva002AC3BE entry (new 0x18) from source +0x118 via rowed ctor 0x002AC3BE
// then vector<uint> assign via pinned 0x0026F4F4 from source +0x11c and int
// at +0x10 from second arg and bool at +0x14 from source +0x12a then
// list<int> push_back via rowed 0x0005548F at Player+0x6f4. Callers at
// 0x004B5B38 and 0x004B5B7B pass Player as this with object and ObjectID.
// Prev PlayerRva002AC629 next Rva002ACF9CInsert. Honest Player method name
// with voidptr-int args; uint vector spelling matches 4B assign row.
#include <vector>
#include <list>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
// bfme link decl-only begin
namespace _STL { template <> vector<unsigned int,allocator<unsigned int> > & vector<unsigned int,allocator<unsigned int> >::operator=(vector<unsigned int,allocator<unsigned int> > const &); }
namespace _STL { template <> void vector<unsigned int,allocator<unsigned int> >::_M_clear(); }
namespace _STL { template <> unsigned int * _STLP_alloc_proxy<unsigned int *,unsigned int,allocator<unsigned int> >::allocate(unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<unsigned int *,unsigned int,allocator<unsigned int> >::deallocate(unsigned int *,unsigned int); }
namespace _STL { template <> void allocator<unsigned int>::deallocate(unsigned int *,unsigned int)const ; }
// bfme link decl-only end
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

class Rva002AC3BE
{
public:
	Rva002AC3BE(void *a);
	void *m_00;
	_STL::vector<unsigned int> m_04;
	int m_10;
	bool m_14;
};

struct Src002ACD09
{
	char m_pad[0x118];
	void *m_118;
	_STL::vector<unsigned int> m_11c;
	char m_pad128[2];
	bool m_12a;
};

class Player
{
public:
	void rva002ACD09(void *src, int id);
private:
	char m_pad[0x6f4];
	_STL::list<int> m_list6f4;
};

void Player::rva002ACD09(void *srcVoid, int id)
{
	Src002ACD09 *src = (Src002ACD09 *)srcVoid;
	Rva002AC3BE *entry = new Rva002AC3BE(&src->m_118);
	int entryId = (int)entry;
	entry->m_04 = src->m_11c;
	entry->m_10 = id;
	entry->m_14 = src->m_12a;
	m_list6f4.push_back(entryId);
}
