// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc /Os
// Retail 0x002EADF0 forwards to the S4 pop specialization. The 12-byte
// tail facade and StringBase access match the existing canonical owners.

// AsciiString and its StringBase<char> base come from the canonical header
// (reverse/canonical_classes.csv): the donor's private copies are the views the
// class gate refuses. Only the 20-byte sort element stays local.
#include "ascii_string.h"

struct BfmeSortTailElement12;

class BfmeSortElem20Tail
{
public:
    BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
    ~BfmeSortElem20Tail();
    void set(const BfmeSortElem20Tail &other);

private:
    BfmeSortTailElement12 *m_begin;
    BfmeSortTailElement12 *m_end;
    BfmeSortTailElement12 *m_capacity;
};
struct S4SortElem20
{
    AsciiString m_bfmeName;
    char m_bfmeFlag;
    BfmeSortElem20Tail m_bfmeTail;
};
struct S4Cmp002EB8E0
{
    int m_bfmeSlot;
};
namespace _STL
{

template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
    RandomAccessIterator result, Tp value, Compare comp, Distance *distance);

}
// 0x002EADF0 is a separate 47-byte forwarding body. Its fourth argument
// carries the comparator value in a pointer-sized slot; preserve that raw ABI
// while naming the actual 0x002EABF0 callee as the S4 pop specialization.
void gen002EADF0(void *a, void *b, int, void *c)
{
    _STL::__pop_heap<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0, int>(
        (S4SortElem20 *)a, (S4SortElem20 *)b - 1,
        (S4SortElem20 *)b - 1, *((S4SortElem20 *)b - 1),
        *(S4Cmp002EB8E0 *)&c, (int *)0);
}
