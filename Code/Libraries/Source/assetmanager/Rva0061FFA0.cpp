// cl: /O2 /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/sweep
// stlport
// ?rva0061FFA0@Rva0061FFA0@@QAEXIH@Z
// 0x0061FFA0 42B: small thiscall setter with clamp to 1 0. Stores args at +0x28 +0x2C then keeps them only when second arg positive or first arg nonzero with second zero. Evidence: callers unclaimed 26B. Callees none. Neighbours BfmeThingXS and Rva0061FFD0 in assetmanager.
class Rva0061FFA0
{
public:
	__declspec(noinline) void rva0061FFA0(unsigned int a, int b);
	unsigned char m_pad[0x28];
	unsigned int m_a28;
	int m_b2C;
};

void Rva0061FFA0::rva0061FFA0(unsigned int a, int b)
{
	m_a28 = a;
	m_b2C = b;
	if (b > 0)
		return;
	if (b < 0)
		goto set;
	if (a >= 1)
		return;
set:
	m_a28 = 1;
	m_b2C = 0;
}

// Target [61F1A0,61F1BA),26B: cdecl two-word forwarding operation.
// The shared registry is the same native E09C0C pointer used by the
// separately rowed26B Invoke and21B Begin wrappers. Its original class
// name remains unproved; consume only the rowed42B setter ABI above.
class Gen_009EBA60Target;
extern class Q1Receiver0134FAAC *TheQ1Receiver;
void forwardRegistrySettingRva0061F1A0(unsigned value,int second) {
 if((*(Gen_009EBA60Target **)&TheQ1Receiver))
  ((Rva0061FFA0*)(*(Gen_009EBA60Target **)&TheQ1Receiver))->rva0061FFA0(value,second);
}

// Asset worker reference: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/Libraries/Source/assetmanager/AssetRegistryWorkerThread009EFA30.cpp.
// Target 00622480..00622670 adds TLS heap scope tag 0x61737374 and the
// established registry +8 delta: lock68, seven 40-byte queues80, enable1F4.
// Native deque frees through the static CRT; /G6 and malloc storage preserve
// its complete code shape. The int deque is a four-byte pointer-storage ABI
// view of the existing aux provider621620, not a claim about source elements.
#define _STLP_USE_STATIC_LIB 1

// Retail mixes direct static free with imported memmove.
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <deque>
#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned bytes, const void *hint);
};
// Copies overlap when the map is recentered; use the retail memmove paths.
// ?copyAssetDequeNodes absent-from-retail
static __forceinline int **copyAssetDequeNodes(int **first, int **last, int **result) {
    return last == first ? result : (int **)((char *)memmove(result, first,
        (char *)last - (char *)first) + ((char *)last - (char *)first));
}
// ?copyAssetDequeNodesBackward absent-from-retail
static __forceinline int **copyAssetDequeNodesBackward(int **first, int **last, int **result) {
    int bytes = (char *)last - (char *)first;
    return bytes > 0 ? (int **)memmove((char *)result - bytes, first, bytes) : result;
}
// Adapted STLport map growth: native uses the byte allocator and static free.
template <> inline void deque<int>::_M_reallocate_map(unsigned nodesToAdd, bool addAtFront) {
    unsigned oldNumNodes = _M_finish._M_node - _M_start._M_node + 1;
    unsigned newNumNodes = oldNumNodes + nodesToAdd;
    int **newStart;
    if (_M_map_size._M_data > 2 * newNumNodes) {
        newStart = _M_map._M_data + (_M_map_size._M_data - newNumNodes) / 2
            + (addAtFront ? nodesToAdd : 0);
        if (newStart < _M_start._M_node)
            copyAssetDequeNodes(_M_start._M_node, _M_finish._M_node + 1, newStart);
        else
            copyAssetDequeNodesBackward(_M_start._M_node, _M_finish._M_node + 1, newStart + oldNumNodes);
    } else {
        unsigned newMapSize = _M_map_size._M_data + (max)(_M_map_size._M_data, nodesToAdd) + 2;
        int **newMap = newMapSize ? (int **)allocator<char>::allocate(newMapSize * 4, 0) : 0;
        newStart = newMap + (newMapSize - newNumNodes) / 2 + (addAtFront ? nodesToAdd : 0);
        copyAssetDequeNodes(_M_start._M_node, _M_finish._M_node + 1, newStart);
        if (_M_map._M_data) free(_M_map._M_data);
        _M_map._M_data = newMap;
        _M_map_size._M_data = newMapSize;
    }
    _M_start._M_set_node(newStart);
    _M_finish._M_set_node(newStart + oldNumNodes - 1);
}

template <> inline void deque<int>::_M_push_back_aux_v(const int &value) {
    int copy = value;
    if (2 > _M_map_size._M_data - (unsigned)(_M_finish._M_node - _M_map._M_data))
        _M_reallocate_map(1, false);
    *(_M_finish._M_node + 1) = (int *)allocator<char>::allocate(0x80, 0);
    if (_M_finish._M_cur) *_M_finish._M_cur = copy;
    _M_finish._M_set_node(_M_finish._M_node + 1);
    _M_finish._M_cur = _M_finish._M_first;
}
template <> inline void deque<int>::_M_pop_front_aux() {
    if (_M_start._M_first) free(_M_start._M_first);
    _M_start._M_set_node(_M_start._M_node + 1);
    _M_start._M_cur = _M_start._M_first;
}
}
#include <windows.h>

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

	union
	{
		volatile unsigned int m_word;
		struct
		{
			volatile unsigned int m_refCount : 16;
			volatile unsigned int m_state : 8;
			volatile unsigned int m_bits : 8;
		};
		struct
		{
			unsigned short m_refCountBytes;
			unsigned char m_stateByte;
			unsigned char m_bitsByte;
		};
	};
};

typedef _STL::deque<int> AssetQueue;

volatile bool g_q1Flag0134FAA8 = false;
void setFPMode();

// TLS operations are existing complete providers at 30980/309B0. The
// adapter only scopes their swap/restore lifetime around the worker loop.
class Rva000309B0 {
    void *m_previous;
public:
    Rva000309B0 *rva00030980(void *value);
    void rva000309B0();
};
class AssetWorkerHeapScope {
    Rva000309B0 m_scope;
public:
    // ?AssetWorkerHeapScope::AssetWorkerHeapScope absent-from-retail
    __forceinline AssetWorkerHeapScope(unsigned tag) { m_scope.rva00030980((void *)tag); }
    // ?AssetWorkerHeapScope::~AssetWorkerHeapScope absent-from-retail
    __forceinline ~AssetWorkerHeapScope() { m_scope.rva000309B0(); }
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
struct Rva009F2140AssetSetGroup {
    Rva001408C0Set m_tree;
    unsigned m_count;
    bool m_active;
    unsigned char m_padding[3];
};
typedef _STL::_Rb_tree<Rva001408C0Key, Rva001408C0Key,
    _STL::_Identity<Rva001408C0Key>, _STL::less<Rva001408C0Key>,
    _STL::allocator<Rva001408C0Key> > AssetKeyTree;
namespace _STL {
// Consume the existing complete insert_unique provider at422047.
template <> AssetKeyTree::iterator
AssetKeyTree::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *,
    const Rva001408C0Key &, _Rb_tree_node_base *);
}
typedef _STL::hash_map<int, Rva009EF0D0Element *> AssetHash;

class AssetRegistry
{
public:
	void Worker_Thread_00622480();
	void Queue_Keys_00622680(bool front, const Rva001408C0Set &keys);

private:
	unsigned int m_thread;
	unsigned int m_threadId;
	bool m_flag08;
	unsigned char m_unmodelled_009[0x43];
	AssetHash m_map4c;
	unsigned char m_unmodelled_060[8];
	CRITICAL_SECTION m_lock68;
	AssetQueue m_deques80[7];
	Rva009F2140AssetSetGroup m_set198;
	unsigned char m_unmodelled_1ac[0x3c];
	unsigned m_field1e8;
	unsigned m_field1ec;
	unsigned m_unmodelled_1f0;
	bool m_flag1f4;
};

typedef char AssetRegistryWorkerLayoutCheck[
	sizeof(AssetRegistry) == 0x1f8 ? 1 : -1];

void AssetRegistry::Worker_Thread_00622480()
{
	m_threadId = GetCurrentThreadId();
	AssetWorkerHeapScope heapScope(0x61737374);
	while (!m_flag08)
	{
		bool enabled = m_flag1f4;
		g_q1Flag0134FAA8 = true;
		if (!enabled)
		{
			Sleep(100);
			continue;
		}

		bool worked = false;
		for (int state = 1; state <= 5; state += 4)
		{
			if (m_deques80[state].empty())
				continue;

			EnterCriticalSection(&m_lock68);
			if (m_deques80[state].empty())
			{
				LeaveCriticalSection(&m_lock68);
				continue;
			}
			Rva009EF0D0Element *asset = (Rva009EF0D0Element *)m_deques80[state].front();
			asset->m_state = 8;
			LeaveCriticalSection(&m_lock68);

			worked = true;
			setFPMode();
			switch (state)
			{
			case 1:
				asset->slot08();
				break;
			case 5:
				asset->slot18();
				break;
			}

			EnterCriticalSection(&m_lock68);
			asset->m_state = state;
			m_deques80[state].pop_front();
			++asset->m_state;
			m_deques80[asset->m_stateByte].push_back(*(const int *)&asset);
			LeaveCriticalSection(&m_lock68);
		}

		if (!worked)
			Sleep(1);
	}
}

// Open-BFME-1 1399ad37 AssetRegistryQueueKeys009EFBF0 reference.
// Target [622680,6227D1),337B shares the worker registry layout: map4C,
// queues80, set198, counters1E8/1EC. Native hash lookup and state7 reset,
// deque front/back calls621690/621620, tree insert422047 and successor24250
// establish the same operation. The opaque key spelling is inherited from
// those existing providers; no original target class name is asserted.
void AssetRegistry::Queue_Keys_00622680(bool front, const Rva001408C0Set &keys)
{
	for (Rva001408C0Set::const_iterator it = keys.begin(); it != keys.end(); ++it)
	{
		AssetHash::const_iterator found = m_map4c.find((int)*it);
		if (found != m_map4c.end())
		{
			Rva009EF0D0Element *asset = (*found).second;
			if (asset->m_state == 7)
			{
				unsigned int flags = asset->m_word & 0xff00ffff;
				asset->m_word = flags;
				asset->m_word = flags | 0x2000000;
				if (front)
				{
					m_deques80[asset->m_state].push_front(*(const int *)&asset);
					++m_field1e8;
				}
				else
				{
					m_deques80[asset->m_state].push_back(*(const int *)&asset);
					++m_field1ec;
				}
				m_set198.m_tree.insert(*it);
			}
		}
	}
}

