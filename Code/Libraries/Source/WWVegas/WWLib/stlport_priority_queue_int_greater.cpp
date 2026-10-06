// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?pop@?$priority_queue@HV?$vector@HV?$allocator@H@_STL@@@_STL@@U?$greater@H@2@@_STL@@QAEXXZ
// @0x003B032A 26B: priority_queue<int, vector<int>, greater<int> >::pop,
// pop_heap(c.begin(), c.end(), comp) through the rowed greater<int> pop_heap
// 0x003B030E, then c.pop_back() as finish -= 4. Layout from the body: the
// vector at +0 (begin +0, finish +4) and the empty comparator byte at +0xC.
// Callers 0x003B0389, 0x003B05BC, 0x003B0A80. /G7: the default P6 model adds
// an xor eax,eax before the byte load of the comparator that retail lacks,
// which is why this is not in the default-model int algorithm unit.
#include <queue>
#include <vector>
#include <functional>

template void _STL::priority_queue<int, _STL::vector<int>, _STL::greater<int> >::pop();
