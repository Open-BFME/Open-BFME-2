// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva005504F9@Rva0055011A@@UAEXABUBfmeNarrowRecord0054FEF1@@@Z @0x005504F9 125B.
// Rva0055011A slot-6 method: lock m_14, map[text]=word0, lock m_0C, m_70++, m_44.push_back.
// Evidence: vtable slot 6 of 0x0086AB90; callees rowed 0x00613A70 0x0038E041 0x00613AC0 0x00550384; offsets match landed ctor layout.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include <map>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
namespace _STL { template <> unsigned int & map<basic_string<char, char_traits<char>, allocator<char> >, unsigned int, less<basic_string<char, char_traits<char>, allocator<char> > >, allocator<pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int> > >::operator[](basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int>, _Nonconst_traits<pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int> > >, bool> _Rb_tree<basic_string<char, char_traits<char>, allocator<char> >, pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int>, _Select1st<pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int> >, less<basic_string<char, char_traits<char>, allocator<char> > >, allocator<pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int> > >::insert_unique(pair<basic_string<char, char_traits<char>, allocator<char> > const, unsigned int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

#include "../../../../GameEngine/Include/Common/BfmeNarrowRecord0054FEF1.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void deque<BfmeNarrowRecord0054FEF1,allocator<BfmeNarrowRecord0054FEF1> >::_M_push_back_aux_v(BfmeNarrowRecord0054FEF1 const &); }

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

typedef _STL::deque<BfmeNarrowRecord0054FEF1, _STL::allocator<BfmeNarrowRecord0054FEF1> > NarrowRecord0054FEF1Deque;
typedef _STL::map<_STL::basic_string<char>, unsigned int, _STL::less<_STL::basic_string<char> > > NarrowWordMap;

class Rva0055011A
{
public:
	virtual ~Rva0055011A();
	virtual void rva005504F9(const BfmeNarrowRecord0054FEF1 &rec);
private:
	MutexClass m_04;
	MutexClass m_0C;
	MutexClass m_14;
	char m_1C[0x28];
	NarrowRecord0054FEF1Deque m_44;
	int m_6C;
	int m_70;
	NarrowWordMap m_74;
	char m_pad[0xB4 - 0x74 - 12];
};

void Rva0055011A::rva005504F9(const BfmeNarrowRecord0054FEF1 &rec)
{
	{
		MutexClass::LockClass lock(m_14);
		m_74[rec.text] = rec.word0;
	}
	{
		MutexClass::LockClass lock(m_0C);
		++m_70;
		m_44.push_back(rec);
	}
}
