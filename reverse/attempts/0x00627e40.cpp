// ?SetTreeDepth@PartitionManagerImpl@@QAEXI@Z
// partial score=0.97 date=2026-10-09
// cl: /O2 /G6 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /I.
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
// The target calls the ordinary STLport copy dispatch rather than force-inlining
// the BFME allocator shim's by-value copy dispatch into vector assignment.
#include "reference/open-bfme-1/inputs/vendor/stlport/stl/_algobase.h"
#include <vector>
#undef free

class Gen_dtor_009f2600 { public: void cleanup(); };
struct Gen009F5040Node;
class Gen009F5040 { public: void linkNode(Gen009F5040Node *); };
struct PartitionNode { char pad00[0xc]; PartitionNode *next; };

// The 8-byte node in each tree has a counter and its leaf-list head.
struct PartitionCounter {
    int count;
    void *head;
    PartitionCounter() : count(0), head(0) {}
};
class PartitionManagerImpl {
public:
    void SetTreeDepth(unsigned depth);
    int prefix[6];
    _STL::vector<PartitionCounter> trees[21];
    PartitionNode *head;
    float scale;
    int mask;
};

// Semantic guide: BFME 1 9cbfb551 Rva009F59D0Method.cpp.
// WB1681440 and native627E40 independently prove tree count and field offsets.
void PartitionManagerImpl::SetTreeDepth(unsigned depth)
{
    if (depth > 11) return;
    int value = 1 << depth;
    if (value == mask) return;
    mask = value;
    unsigned count = 1;
    while (depth != 0) {
        --depth;
        count = count * 4 + 1;
    }
    ((Gen_dtor_009f2600 *)this)->cleanup();
    for (int i = 0; i < 21; ++i) {
        _STL::vector<PartitionCounter> fresh(count);
        trees[i] = fresh;
    }
    for (PartitionNode *node = head; node; node = node->next)
        ((Gen009F5040 *)this)->linkNode((Gen009F5040Node *)node);
}
