// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// stlport
// Refresh at retail 006227E0..0062348C, 3244 bytes, frame 0xBC, EH graph
// exact. WB twin: AssetManagerImpl::UpdateActiveAssets (WB 0x167A320); the
// target name remains the pinned neutral receiver label.
//
// BFME1 009EFF50 is the semantic guide. Five matched target callers and the
// existing refresh pin establish this member's relationship to the asset
// registry receiver. Legacy field labels retain donor offsets: native lock
// is +68, hash map +4C, seven deques +80, set wrappers +198/+1AC/+1C0/+1D4,
// and output counters +1E8/+1EC. Size200 is checked below.
// The +20/+28 cost and budget are signed64: native adc/sbb0 of unsigned
// slot38 cost, signed64 comparisons. Pending entries are key+pointer pairs
// (target-proven unsigned key / element pointer).
//
// Under the lock, normalize/copy the known-key sets; sweep seven queues;
// collect eligible queue3 entries in the pending multimap, move queue4
// entries to3, and evict by cost/budget. Retain/subtract key-set passes
// return queue7 entries to0 and record active deque0..2 totals.
// The volatile eight-bit queue field is supported by native full-word
// accesses/reloads and the landed AssetManagerImplUpdate sibling.
//
// Count tails: c2 sorts the flattened size() terms by a hash of their
// address temporaries and local symbols, so the declaration order of the
// deque references (r1 before r0) and the per-arm addressing fix the
// node/finish/start operand order (handoff
// reverse/attempt_support/0x006227e0-reduction-mechanism-20261021.md).

#include <deque>
#include <hash_map>
#include <map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>
// Suppress this TU's non-retail copy of ?_M_reallocate_map@?$deque@HV?$allocator@H@_STL@@@_STL@@IAEXI_N@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void deque<int,allocator<int> >::_M_reallocate_map(unsigned int,bool); }

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
namespace _STL {
template <> _Rb_tree<Rva001408C0Key, Rva001408C0Key, _Identity<Rva001408C0Key>,
	less<Rva001408C0Key>, allocator<Rva001408C0Key> >::~_Rb_tree();
}

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;

struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		get().~Rva001408C0Set();
	}
	Rva001408C0Set &get() { return *(Rva001408C0Set *)m_storage; }
	int m_storage[sizeof(Rva001408C0Set) / sizeof(int)];
};

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

class BfmeThingBVA
{
public:
	BfmeThingBVA()
	{
		m_value = 0;
		m_active = true;
	}

	BfmeThingBVA &operator=(BfmeThingBVA &other)
	{
		if (this != &other)
		{
			bfmeStepBVA(&other);
			m_active = true;
			m_value = other.m_value;
		}
		return *this;
	}

	void bfmeStepBVA(BfmeThingBVA *other);

	Rva001408C0Set m_tree;
	unsigned int m_value;
	bool m_active;
};

class Rva0061F910Set
{
public:
	Rva0061F910Set &subtract(const Rva0061F910Set &other);
	Rva0061F910Set &retain(const Rva0061F910Set &other);
};

class Rva009EF0D0Element
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual int slot38();

	volatile unsigned int m_bits00 : 16;
	volatile unsigned int m_queue : 8;
	unsigned int m_bit24 : 1;
	unsigned int m_bit25 : 1;
	unsigned int m_bit26 : 1;
	int m_key08;
	int m_field0c;
	unsigned int m_field10;
};

struct Rva00620A00Record
{
	Rva009EF0D0Element *m_entry;
};

typedef _STL::multimap<unsigned int, Rva00620A00Record> Q1ReceiverPending;
namespace _STL {
template <> _Rb_tree<unsigned int, pair<const unsigned int, Rva00620A00Record>,
	_Select1st<pair<const unsigned int, Rva00620A00Record> >, less<unsigned int>,
	allocator<pair<const unsigned int, Rva00620A00Record> > >::~_Rb_tree();
}
typedef _STL::pair<const unsigned int, Rva00620A00Record> Q1ReceiverPendingPair;
typedef _STL::hash_map<int, Rva009EF0D0Element *> Q1ReceiverAssetHash;
typedef _STL::deque<int> Q1ReceiverQueue;

class Q1ReceiverLock
{
public:
	explicit Q1ReceiverLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~Q1ReceiverLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

class Q1Receiver0134FAAC
{
public:
	void refresh();
	void m009EFD40(Q1ReceiverLocalSet *set);

private:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	__int64 m_field20;
	__int64 m_limit28;
	unsigned int m_field30;
	CRITICAL_SECTION m_lock2c;
	Q1ReceiverAssetHash m_map44;
	unsigned char m_unmodelled_058[8];
	CRITICAL_SECTION m_lock60;
	Q1ReceiverQueue m_deques78[7];
	BfmeThingBVA m_set190;
	BfmeThingBVA m_set1a4;
	BfmeThingBVA m_set1b8;
	BfmeThingBVA m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_unmodelled_1e8[0x0C];
};

typedef char Q1ReceiverRefreshSizeCheck[sizeof(Q1Receiver0134FAAC) == 0x200 ? 1 : -1];

void Q1Receiver0134FAAC::refresh()
{
	Q1ReceiverLock lock(&m_lock60);
	m009EFD40((Q1ReceiverLocalSet *)&m_set190);
	m009EFD40((Q1ReceiverLocalSet *)&m_set1a4);

	Q1ReceiverPending pending;
	Q1ReceiverLocalSet known = { *(const Q1ReceiverSet *)&m_set190, 0, true };
	known.m_set.get().insert(m_set1b8.m_tree.begin(), m_set1b8.m_tree.end());
	known.m_one = true;

	for (int queueIndex = 0; queueIndex < 7; ++queueIndex)
	{
		for (unsigned int i = 0; i < m_deques78[queueIndex].size(); ++i)
		{
			Rva009EF0D0Element *entry = (Rva009EF0D0Element *)m_deques78[queueIndex][i];
			if ((known.m_set.get().find((Rva001408C0Key)entry->m_key08) !=
					known.m_set.get().end()) == (queueIndex < 4))
				continue;
			entry->m_bit25 = queueIndex > 3;
			if (queueIndex == 3 && !entry->m_bit26)
			{
				Q1ReceiverPendingPair value(entry->m_field10, Rva00620A00Record());
				value.second.m_entry = entry;
				pending.insert(value);
				Q1ReceiverQueue &q1ReceiverQueue = m_deques78[3];
				q1ReceiverQueue[i] = q1ReceiverQueue[q1ReceiverQueue.size() - 1];
				q1ReceiverQueue.pop_back();
				--i;
			}
			else if (queueIndex == 4)
			{
				entry->m_queue = 3;
				m_field20 += (unsigned int)entry->slot38();
				Q1ReceiverQueue &queue4 = m_deques78[4];
				m_deques78[entry->m_queue].push_back(queue4[i]);
				queue4[i] = queue4[queue4.size() - 1];
				queue4.pop_back();
				--i;
			}
			else if (queueIndex == 0)
			{
				entry->m_queue = 7;
				m_deques78[queueIndex][i] = m_deques78[queueIndex][m_deques78[queueIndex].size() - 1];
				m_deques78[queueIndex].pop_back();
				--i;
			}
		}
	}

	while ((m_field20 >= m_limit28 || m_limit28 < 2) && pending.size() != 0)
	{
		Rva009EF0D0Element *entry = pending.begin()->second.m_entry;
		pending.erase(pending.begin());
		entry->m_queue = 4;
		m_field20 -= (unsigned int)entry->slot38();
		m_deques78[entry->m_queue].push_back((int)entry);
		if (m_field20 < 0)
			m_field20 = 0;
	}

	for (Q1ReceiverPending::iterator it = pending.begin(); it != pending.end(); ++it)
		m_deques78[3].push_back(*(const int *)&it->second.m_entry);

	Q1ReceiverQueue *queues = m_deques78;
	Q1ReceiverQueue &queue1 = m_deques78[1];
	Q1ReceiverQueue &queue0 = m_deques78[0];
	Q1ReceiverQueue &queue2 = m_deques78[2];
	for (int pass = 0; pass < 2; ++pass)
	{
		BfmeThingBVA keys;
		if (pass == 0)
		{
			keys = m_set1a4;
			((Rva0061F910Set *)&keys)->retain(*(Rva0061F910Set *)&m_set190);
			keys.m_tree.insert(m_set1b8.m_tree.begin(), m_set1b8.m_tree.end());
			keys.m_active = true;
		}
		else
		{
			keys = m_set190;
			((Rva0061F910Set *)&keys)->subtract(*(Rva0061F910Set *)&m_set1a4);
		}

		for (Rva001408C0Set::iterator it = keys.m_tree.begin(); it != keys.m_tree.end(); ++it)
		{
			Q1ReceiverAssetHash::const_iterator found = m_map44.find((int)*it);
			if (found != m_map44.end())
			{
				Rva009EF0D0Element *asset = (*found).second;
				if (asset->m_queue == 7)
				{
					asset->m_queue = 0;
					asset->m_bit25 = 1;
					m_deques78[asset->m_queue].push_back((int)asset);
				}
			}
		}

		if (pass == 0)
			m_field1e0 = queue0.size() + queue1.size() + queues[2].size();
		else
			m_field1e4 = queue0.size() + queue1.size() + queue2.size() - m_field1e0;
	}
}

// Use the pointer-set providers and keep the remaining helpers inline.
namespace _STL {
typedef Rva001408C0Target *Q1LinkKey;
typedef _Rb_tree_node<Q1LinkKey> Q1LinkNode;
typedef _Rb_tree<Q1LinkKey, Q1LinkKey, _Identity<Q1LinkKey>, less<Q1LinkKey>, allocator<Q1LinkKey> > Q1LinkTree;
template <> void allocator<Q1LinkNode>::deallocate(Q1LinkNode *, size_t) const;
template <> Q1LinkNode *Q1LinkTree::_M_create_node(Q1LinkKey const &);
template <> _Rb_tree_base<Q1LinkKey, allocator<Q1LinkKey> >::~_Rb_tree_base();
}

namespace _STL {
template <> __declspec(dllimport) __forceinline
Q1LinkNode *allocator<Q1LinkNode>::allocate(size_t __n, const void *) const
{ return __n != 0 ? (Q1LinkNode *)allocator<char>::allocate(__n * sizeof(Q1LinkNode), 0) : 0; }
template <> __declspec(dllimport) __forceinline
Q1LinkNode *_STLP_alloc_proxy<Q1LinkNode *, Q1LinkNode, allocator<Q1LinkNode> >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<allocator<Q1LinkNode> &>(*this), (Q1LinkNode *)0).allocate(__n, 0); }
}

namespace _STL {

template <> template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *Q1LinkTree::_M_find<Rva001408C0Target *>(Rva001408C0Target * const &__k) const
{
    _Link_type __y = this->_M_header._M_data;
    _Link_type __x = _M_root();
    while (__x != 0)
        if (!_M_key_compare(_S_key(__x), __k))
            __y = __x, __x = _S_left(__x);
        else
            __x = _S_right(__x);
    if (__y == this->_M_header._M_data || _M_key_compare(__k, _S_key(__y)))
        __y = this->_M_header._M_data;
    return __y;
}
template <> template <> __declspec(dllimport) __forceinline
Q1LinkTree::const_iterator Q1LinkTree::find<Rva001408C0Target *>(Rva001408C0Target * const &__x) const
{ return const_iterator(_M_find(__x)); }
}

// Keep STLport's pointer-set construction inline without competing external copies.
namespace _STL {
typedef _Rb_tree<Rva001408C0Key, Rva001408C0Key, _Identity<Rva001408C0Key>,
    less<Rva001408C0Key>, allocator<Rva001408C0Key> > AssetPointerLinkTree;
template <> __declspec(dllimport) __forceinline
_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Key> *, _Rb_tree_node<Rva001408C0Key>, allocator<_Rb_tree_node<Rva001408C0Key> > >::_STLP_alloc_proxy(
    const allocator<_Rb_tree_node<Rva001408C0Key> > &__a, _Rb_tree_node<Rva001408C0Key> *__p)
    : allocator<_Rb_tree_node<Rva001408C0Key> >(__a), _M_data(__p) {}
template <> __declspec(dllimport) __forceinline
_Rb_tree_base<Rva001408C0Key, allocator<Rva001408C0Key> >::_Rb_tree_base(const allocator_type &__a)
    : _M_header(_STLP_CONVERT_ALLOCATOR(__a, _Node), (_Node *)0)
{ _M_header._M_data = _M_header.allocate(1); }
// ?AssetPointerLinkTree::_M_empty_initialize present-unmatched
template <> __declspec(dllimport) __forceinline
void AssetPointerLinkTree::_M_empty_initialize()
{
    _S_color(this->_M_header._M_data) = _S_rb_tree_red;
    _M_root() = 0;
    _M_leftmost() = this->_M_header._M_data;
    _M_rightmost() = this->_M_header._M_data;
}
// ?AssetPointerLinkTree::_Rb_tree present-unmatched
template <> __declspec(dllimport) __forceinline
AssetPointerLinkTree::_Rb_tree(const less<Rva001408C0Key> &__comp, const allocator_type &__a)
    : _Rb_tree_base<Rva001408C0Key, allocator<Rva001408C0Key> >(__a),
      _M_node_count(0), _M_key_compare(__comp)
{ _M_empty_initialize(); }
}
