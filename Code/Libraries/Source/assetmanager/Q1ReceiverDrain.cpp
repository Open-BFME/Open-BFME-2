// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/sweep
// stlport

// Retail RVA 0x00624790 (VA 0x009F1AE0), 1476 bytes. Identity is address-derived: its one
// caller, the unclaimed guarded forwarder at 0x009EBC40 (mov ecx,[0x0134FAAC];
// test ecx,ecx; je; jmp 0x009F1AE0), proves the receiver and the no-argument
// thiscall ABI but is itself unnamed, and no vtable slot or string names this
// body, so the method keeps its address.
//
// The receiver is the object g_theAssetRegistry (0x0134FAAC) points at, the
// same object as the matched Q1Receiver0134FAAC methods beside this file and
// the Gen_dtor_009eb9e0 constructor in
// W3DDevice/GameLogic/Rva009EB960Ctor.cpp: it holds the section
// at +0x60, seven 0x28-byte STLport deques from +0x78 and four 0x14-byte set
// wrappers from +0x190. Retail proves each piece here:
//   * every deque block is 0x80 bytes and operator[] advances 32 elements per
//     node, so the element is one pointer;
//   * each element has a vtable (slot +0x38 returns an int that is subtracted
//     from +0x20 and clamped at zero) and a flag word at +4 whose bits 16..23
//     name the deque the element belongs in (the push target is
//     m_deques78[queue]) and whose bit 25 is cleared on every visit. Retail
//     loads, masks and stores the queue number and re-reads it after writing
//     it, which is a volatile bit-field; the single-bit flags are plain (the
//     sibling 0x009F1510 tests bit 25 in the register it just stored);
//   * push_back's _M_push_back_aux_v is inlined, so the TU was built without
//     STLport exceptions (a try block keeps MSVC from inlining it);
//   * the +0x1CC wrapper's tree is cleared through an inline member that also
//     sets the flag at wrapper +0x10, addressed from the wrapper pointer.
// 0x009F1510 is pinned as Rva00624130::handle (the pointer-tail thunk at
// 0x009EBA30 reaches it); retail passes this same receiver in ECX.

// Retail mixes direct static free with imported memmove.
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <deque>
#include <utility>
#include <functional>
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
template <> inline void deque<int>::_M_pop_back_aux() {
    if (_M_finish._M_first) free(_M_finish._M_first);
    _M_finish._M_set_node(_M_finish._M_node - 1);
    _M_finish._M_cur = _M_finish._M_last - 1;
}
template <> inline void deque<int>::_M_pop_front_aux() {
    if (_M_start._M_first) free(_M_start._M_first);
    _M_start._M_set_node(_M_start._M_node + 1);
    _M_start._M_cur = _M_start._M_first;
}
}
#include <windows.h>



// ABI-only use of the existing POD subtree erase provider at692F5.
// It reads node links at+8/+C and frees nodes; this call proves no payload
// identity. Both source views have the observed 16-byte link prefix.
namespace _STL {
template<class V> struct _Rb_tree_node;
template<class K,class V,class Extract,class Compare,class Alloc> class _Rb_tree {
private:
    void _M_erase(_Rb_tree_node<V> *node);
public:
    // ?_Rb_tree::eraseNative absent-from-retail
    __forceinline void eraseNative(_Rb_tree_node<V> *node) { _M_erase(node); }
};
}
typedef _STL::pair<const int,int> DrainEraseValue;
typedef _STL::_Rb_tree_node<DrainEraseValue> DrainEraseNode;
typedef _STL::_Rb_tree<int,DrainEraseValue,_STL::_Select1st<DrainEraseValue>,
    _STL::less<int>,_STL::allocator<DrainEraseValue> > DrainEraseTree;
struct DrainTreeHeader {
    int color;
    DrainTreeHeader *parent, *left, *right;
};
struct Q1ReceiverLocalSet {
    DrainTreeHeader *m_header;
    unsigned m_count;
    unsigned m_compare;
    int m_zero;
    bool m_one;
    // ?Q1ReceiverLocalSet::reset absent-from-retail
    __forceinline void reset() {
        if (m_count != 0) {
            DrainTreeHeader *node=m_header->parent;
            while (node) {
                ((DrainEraseTree *)this)->eraseNative((DrainEraseNode *)node->right);
                DrainTreeHeader *left=node->left;
                free(node);
                node=left;
            }
            m_header->left=m_header;
            m_header->parent=0;
            m_header->right=m_header;
            m_count=0;
        }
        m_one=true;
    }
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

class Rva00624130
{
public:
	void rva00624130();
};

class Q1Receiver0134FAAC
{
public:
	void Rva00624790();

private:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	__int64 m_field20;
	unsigned int m_field28;
	unsigned char m_target_growth_02c[8];
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
	unsigned char m_unmodelled_1e8[0x0C];
};

typedef char Q1Receiver009F1AE0SizeCheck[sizeof(Q1Receiver0134FAAC) == 0x200 ? 1 : -1];

void Q1Receiver0134FAAC::Rva00624790()
{
	EnterCriticalSection(&m_lock60);
	for (;;)
	{
		for (int q = 0; q <= 3; ++q)
		{
			for (unsigned int i = 0; i < m_deques78[q].size(); ++i)
			{
				Rva009EF0D0Element *entry = (Rva009EF0D0Element *)m_deques78[q][i];
				entry->m_bit25 = 0;
				if (q == 3)
				{
					m_field20 -= (unsigned int)entry->slot38();
					if (m_field20 < 0)
						m_field20 = 0;
					entry->m_queue = 4;
					m_deques78[entry->m_queue].push_back(m_deques78[3][i]);
					m_deques78[3][i] = m_deques78[3][m_deques78[3].size() - 1];
					m_deques78[3].pop_back();
					--i;
				}
				else if (q == 0)
				{
					entry->m_queue = 7;
					m_deques78[0][i] = m_deques78[0][m_deques78[0].size() - 1];
					m_deques78[0].pop_back();
					--i;
				}
			}
		}
		int k;
		for (k = 0; k < 7; ++k)
		{
			if (!m_deques78[k].empty())
				break;
		}
		if (k == 7)
			break;
		LeaveCriticalSection(&m_lock60);
		reinterpret_cast<Rva00624130 *>(this)->rva00624130();
		Sleep(1);
		EnterCriticalSection(&m_lock60);
	}
	m_set1cc.reset();
	LeaveCriticalSection(&m_lock60);
}
