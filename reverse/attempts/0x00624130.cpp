// ?rva00624130@Rva00624130@@QAEXXZ
// partial score=0.99 date=2026-10-07
// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/sweep
// stlport
// Banked target worker624130..624690:1347B executable body, one byte
// of alignment, seven four-byte switch entries. Native table included in
// the1376B extent. Reference Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/Libraries/Source/assetmanager/Q1Receiver0134FAAC_Gen009F1510.cpp.
// Native differences: TLS heap tag61737374 via30980/309B0, existing global
// E09C08 set for queues4..6, target +8 layout and64bit unsigned-cost counter.
// The custom20B set header avoids donor allocator/OOM divergence. Original
// element and receiver names remain opaque; no allocation extent is claimed.
// Remaining code gap: six operand bytes in the mathematically equivalent
// aggregate queue-count calculation (120 order). Other executable bytes
// match after relocations are masked. Callee binding still needs review:
// pointer-set const find at native4D7546 actually belongs to the rowed
// map<int,void*> nonconst find wrapper; pointer-tree destructor6BF2A has
// an existing legacy alias and is not a reliable linking provider.
// No new pins were admitted. Native EH data and all switch targets remain
// to be verified through the normal gates before this body may be claimed.

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



#ifndef THREAD_PRIORITY_BELOW_NORMAL
#define THREAD_PRIORITY_BELOW_NORMAL (-1)
#endif

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *> Rva001408C0Set;

// The receiver's 0x14-byte set wrapper (the name the pinned 0x009EFD40 member
// and the matched 0x009F0E50 member already use for it, with their member
// spelling). Retail builds the local one here as header node, 0 at +0xC and
// 1 at +0x10.
struct WorkerSetHeader {
    unsigned char color;
    unsigned char pad[3];
    WorkerSetHeader *parent,*left,*right;
    Rva001408C0Target *key;
};
struct Q1ReceiverLocalSet {
    WorkerSetHeader *m_header;
    unsigned m_count;
    unsigned m_compare;
    int m_zero;
    bool m_one;
    __forceinline Q1ReceiverLocalSet() : m_header(0) {
        m_header=(WorkerSetHeader *)_STL::allocator<char>::allocate(20,0);
        m_count=0;
        m_header->color=0;
        m_header->parent=0;
        m_header->left=m_header;
        m_header->right=m_header;
        m_zero=0;
        m_one=true;
    }
    __forceinline ~Q1ReceiverLocalSet() {
        ((_STL::_Rb_tree<Rva001408C0Target *,Rva001408C0Target *,
            _STL::_Identity<Rva001408C0Target *>,_STL::less<Rva001408C0Target *>,
            _STL::allocator<Rva001408C0Target *> > *)this)->~_Rb_tree();
    }
    __forceinline const Rva001408C0Set &get() const { return *(const Rva001408C0Set *)this; }
};

class Rva009EF0D0Element
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(Q1ReceiverLocalSet *set);
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
};

typedef _STL::deque<int> Q1Queue009F1510;

// 0x009EFBF0 is landed as AssetManagerImpl::AddRequiredAssets
// (AssetRegistryQueueKeys009EFBF0.cpp) on the same g_theAssetRegistry
// object; this TU reaches it through that declaration.
class AssetRegistry
{
public:
	void Queue_Keys_00622680(bool known, const Rva001408C0Set &keys);
};

class Q1Receiver0134FAAC
{
public:
	void refresh();

protected:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	__int64 m_field20;
	unsigned int m_field28;
	unsigned char m_target_growth02c[8];
	CRITICAL_SECTION m_lock2c;
	unsigned char m_unmodelled_044[0x1C];
	CRITICAL_SECTION m_lock60;
	Q1Queue009F1510 m_deques78[7];
	Q1ReceiverLocalSet m_set190;
	Q1ReceiverLocalSet m_set1a4;
	Q1ReceiverLocalSet m_set1b8;
	Q1ReceiverLocalSet m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_unmodelled_1e8[4];
	bool m_flag1ec;
	bool m_flag1ed;
	bool m_flag1ee;
	unsigned char m_unmodelled_1ef[5];
};

class Rva00624130 : public Q1Receiver0134FAAC
{
public:
	void rva00624130();
};

typedef char Rva00624130SizeCheck[sizeof(Rva00624130) == 0x200 ? 1 : -1];

extern volatile bool g_q1Flag0134FAA8;
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


void Rva00624130::rva00624130()
{
	bool changed = false;
	AssetWorkerHeapScope heap(0x61737374);
	g_q1Flag0134FAA8 = false;
	for (int q = 0; q < 7; ++q)
	{
		if (q == 3)
			continue;
		if (m_flag1ec && (q == 1 || q == 5))
			continue;
		while (!m_deques78[q].empty())
		{
            if (q >= 4 && q <= 6) g_q1Flag0134FAA8 = true;
			EnterCriticalSection(&m_lock60);
			if ((q == 0 || q == 4) && m_deques78[q + 1].size() >= 100)
			{
				LeaveCriticalSection(&m_lock60);
				break;
			}
			Rva009EF0D0Element *entry = (Rva009EF0D0Element *)m_deques78[q].front();
			m_deques78[q].pop_front();
			entry->m_queue = 8;
			LeaveCriticalSection(&m_lock60);
			switch (q)
			{
			case 0:
				entry->slot04();
				break;
			case 2:
			{
				entry->slot0C();
				m_field20 += (unsigned int)entry->slot38();
				Q1ReceiverLocalSet set;
				entry->slot10(&set);
				if (set.m_count != 0)
				{
					((AssetRegistry *)this)->Queue_Keys_00622680(
						m_set1a4.get().find((Rva001408C0Target *)entry->m_key08) !=
						m_set1a4.get().end(), set.get());
				}
				break;
			}
			case 4:
				entry->slot14();
				break;
			case 6:
				entry->slot1C();
				break;
			case 1:
				entry->slot08();
				break;
			case 5:
				entry->slot18();
				break;
			}
			EnterCriticalSection(&m_lock60);
			if (q == 6)
			{
				entry->m_queue = 7;
				if (entry->m_bit25)
				{
					entry->m_queue = 0;
					m_deques78[entry->m_queue].push_back(*(int *)&entry);
				}
			}
			else
			{
				entry->m_queue = q + 1;
				if (q == 2 && !entry->m_bit25 && !entry->m_bit26)
				{
					entry->m_queue = 4;
					m_field20 -= (unsigned int)entry->slot38();
					if (m_field20 < 0)
						m_field20 = 0;
				}
				m_deques78[entry->m_queue].push_back(*(int *)&entry);
				if (q == 2 && m_deques78[0].empty() && m_deques78[1].empty() &&
					m_deques78[2].empty())
				{
					changed = true;
				}
			}
			LeaveCriticalSection(&m_lock60);
		}
	}
	if (changed)
		refresh();
	EnterCriticalSection(&m_lock60);
	unsigned int total = m_deques78[1].size() + m_deques78[2].size() + m_deques78[0].size();
	LeaveCriticalSection(&m_lock60);
	if (total <= m_field1e4)
		SetThreadPriority(reinterpret_cast<HANDLE>(m_thread), THREAD_PRIORITY_BELOW_NORMAL);
	else
		SetThreadPriority(reinterpret_cast<HANDLE>(m_thread), THREAD_PRIORITY_NORMAL);
}
