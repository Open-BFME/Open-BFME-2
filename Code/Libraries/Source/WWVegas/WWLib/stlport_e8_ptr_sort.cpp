// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's two-argument sort over a pointer range of 8-byte elements: sort
// (0x005A97E1, 67B) and the whole family it instantiates, 0x005A9146 ..
// 0x005A9743. Target evidence: the introsort loop at 0x005A975E is one of the
// two callers outside the BfmeE12 deque sort of the median folded at
// 0x005A9215 (rowed in stlport_deque_e12_sort.cpp), and the less-than every
// body inlines is a single comiss on the float at +4. Compiled with the BfmeE12
// sort's flags, this unit's bodies equal retail at the addresses the retail
// calls fix, sort included: its frame and the garbage push for the empty
// less<> argument are the two-argument sort's, not the comparator form's.
//
// The element type is a STAND-IN, as in stlport_deque_e12_sort.cpp: the image
// fixes its size (the stride and the >> 3) and the float key at +4, nothing
// more. BfmeE8 has the layout the deque<BfmeE8> heap helpers
// (Rva0054A5EEPushHeap.cpp) give it. Three bodies retail folded with other
// instantiations are pinned there, not rowed: the median, swap and
// copy_backward. The build uses the stock STLport headers, as
// stlport_copy_backward_e12.cpp does: the bfmealloc shim force-inlines the
// copy_backward helpers into a 29-byte copy_backward, and retail's (0x004C72FE)
// is the 27-byte one that calls __copy_backward_ptrs.

#include <algorithm>

struct BfmeE8 { int a; float b; };

inline bool operator<(const BfmeE8 &x, const BfmeE8 &y) { return x.b < y.b; }

template void _STL::sort<BfmeE8 *>(BfmeE8 *, BfmeE8 *);

// A second sort over 8-byte records, compared through a function pointer: sort
// (0x004C75DE, 67B) and its family, 0x004C6F77 .. 0x004C755B. Its median, linear
// inserts, __push_heap and __insertion_sort are rowed by hand
// (Rva004C6F77Median.cpp: Rva004C6F77Median takes the pointer as
// bool (*)(void *, void *)); this instantiation reproduces them and is pinned
// there. Its swap and copy_backward are the folded ones above.
typedef bool (*BfmeE8Less)(const BfmeE8 &, const BfmeE8 &);

template void _STL::sort<BfmeE8 *, BfmeE8Less>(BfmeE8 *, BfmeE8 *, BfmeE8Less);

// BFME1 predlod.cpp1399ad37 supplies the float-key comparison expression.
// Native5A90F9..5A910E establishes thiscall RET4, both float reads at+4, and
// EAX0/1 with unordered comparisons false. The adjacent matched sort family
// independently has eight-byte records with the same float key position.
// Original owner and first-word meaning are unknown; no LOD type asserted.
class Rva005A90F9FloatKey {
 unsigned char m_unknown00[4];
 float m_key;
public:
 int operator<(const Rva005A90F9FloatKey &other);
};
int Rva005A90F9FloatKey::operator<(const Rva005A90F9FloatKey &other)
{ return m_key < other.m_key; }
