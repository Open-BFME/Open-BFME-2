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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <hash_map>

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

class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
	{
		size_t operator()(const GameWindow *const &p) const
		{
			return (size_t)p;
		}
	};
};

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
