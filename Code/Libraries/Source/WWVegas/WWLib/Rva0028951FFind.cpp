// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva0028951F@Rva0028951F@@QAEPBVOverridable@@H@Z @0x0028951F 144B.
// NameKey cache lookup with hashtable fallback and final-override chase.
// Retail first probes map<int int> at +0x28 via rowed _M_find 0x388F63; on hit
// returns second as pointer. On miss it iterates hash_map at +0x0C via rowed
// begin 0x427195 and operator++ 0x41E832, walks each value's circular list
// via head at +0 until sentinel, compares int at +0x1C with key, chases
// rowed Overridable::friend_getFinalOverride 0x288609, caches via rowed
// operator[] 0x28932C and returns. Miss caches 0 and returns null.
// Evidence: unlock lane; callers 0x2897A8 0x28A294 0x28A473 0x3C4570 0x3C45D4
// 0x408150 0x420F3F pass NameKey from 0x9FA65; 0x28A294 throws Experience
// Level not found and 0x408150 builds CreateAHeroLevel names; BFME1 donor
// ExperienceLevelSystemFindLevel hash plus list plus final-override shape.
#include <map>

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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}

class GameWindow;
class WindowVideo;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	void *m_v0;
	Overridable *m_next;
};

struct ListNode
{
	ListNode *m_next;
	int m_pad04;
	Overridable m_over;
	int m_pad10;
	int m_pad14;
	int m_pad18;
	int m_key1C;
};

class WindowVideo
{
public:
	ListNode *m_head;
};

#include "../../../../GameEngine/Include/GameClient/WindowVideoManagerClass.h"

typedef std::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, std::equal_to<const GameWindow *> > WindowVideoMap;

class Rva0028951F
{
public:
	const Overridable *rva0028951F(int key);
private:
	char m_pad[0x0C];
	WindowVideoMap *m_hashPtr;
	char m_pad2[0x18];
	_STL::map<int, int> m_map;
};

// bfme link decl-only begin
namespace _STL { template <> pair<int const,int>::pair(int const &,int const &); }
namespace _STL { template <> pair<_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,bool>::pair(_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > const &,bool const &); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > & _Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >::operator++(); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > & _Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >::operator--(); }
namespace _STL { template <> unsigned int hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_bkt_num(_STL::pair<GameWindow const * const,WindowVideo *> const &) const; }
namespace _STL { template <> unsigned int hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_bkt_num_key(GameWindow const * const &) const; }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::_M_create_node(_STL::pair<int const,int> const &); }
namespace _STL { template <> _STL::_Hashtable_node<_STL::pair<GameWindow const * const,WindowVideo *> > * _Hashtable_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_skip_to_next(); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,int> > *,_STL::_Rb_tree_node<_STL::pair<int const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> _STL::_Ht_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,_STL::_Nonconst_traits<_STL::pair<GameWindow const * const,WindowVideo *> >,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > > hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::begin(); }
namespace _STL { template <> unsigned int hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::bucket_count() const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,int> > *,_STL::_Rb_tree_node<_STL::pair<int const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,int> > *,unsigned int); }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,bool> _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::insert_unique(_STL::pair<int const,int> const &); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::insert_unique(_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,_STL::pair<int const,int> const &); }
namespace _STL { template <> int & map<int,int,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::operator[](int const &); }
// bfme link decl-only end
const Overridable *Rva0028951F::rva0028951F(int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it != m_map.end())
		return (const Overridable *)(*it).second;
	WindowVideoMap::iterator tmp = m_hashPtr->begin();
	WindowVideoMap::iterator jt = tmp;
	for (; jt != m_hashPtr->end(); ++jt)
	{
		WindowVideo *v = (*jt).second;
		for (ListNode *n = v->m_head; n != (ListNode *)v; n = n->m_next)
		{
			if (n->m_key1C == key)
			{
				const Overridable *f = ((Overridable *)((char *)n + 8))->friend_getFinalOverride();
				m_map[key] = (int)f;
				return f;
			}
		}
	}
	m_map[key] = 0;
	return 0;
}
