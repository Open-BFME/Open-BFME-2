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

// BFME1 9cbfb551 SetTreeDepth donor (reviewed at575ba2b04) supplies
// the quadtree-count algorithm and representation-compatible vector transfer.
// Target WB1681440 independently names SetTreeDepth. Native627E40..627F4A
// includes its RET4 (Ghidra omits the final3 bytes); native627AA0..627AD9
// ends in RET4 followed by padding and proves the57B zero-fill constructor.
// Retail uses the existing8B allocation and pair<int,int> assignment providers
// (6278F0/627CC0). These two-word views adapt those verified providers; they
// do not establish original tree-element typedefs or an ObjectID payload.
enum ObjectID;
typedef _STL::pair<ObjectID,unsigned int> PartitionRawPair;
typedef _STL::pair<int,int> PartitionAssignPair;


// PartitionManagerImpl::_ClearNumObjBelow and RemoveAllObjects.
// Target identity: WB167FEC0/WB1680940 name both methods and this source.
// Native626AA0..626AE8 and 627600..6276A3 prove their complete 72/163-byte
// boundaries. The count is quartered for each of four child quadrants.
// Native tree vectors begin at +0x18; there are 21; the master list is +0x114.
// BFME 1 9cbfb551 Rva009F40E0Recursive.cpp supplies the recovered recursion;
// its body was already byte-exact here. Target WB and native evidence supply
// the parent list reset and the 21-tree walk. Preserve existing linker names
// used by recovered providers and consumers while consolidating these bodies.
// Retail inlines the first recursion level in RemoveAllObjects; keeping the
// recursive definition in this TU also preserves its witnessed register use.
class Rva009F40E0Owner {
public:
    void run(void **slot, unsigned count);
};

void Rva009F40E0Owner::run(void **slot, unsigned count)
{
    if (*slot == 0) return;
    *slot = 0;
    unsigned childCount = count;
    slot += 2;
    childCount >>= 2;
    unsigned stride = count * 8;
    unsigned remaining = 4;
    while (remaining != 0) {
        run(slot, childCount);
        slot = (void **)((char *)slot + stride);
        --remaining;
    }
}

struct PartitionTreeCounter {
    int count;
    void *head;
    PartitionTreeCounter() : count(0), head(0) {}
};
struct PartitionNode {
    char pad00[0xc];
    PartitionNode *next;
    PartitionNode **prevInLeaf;
};

// The legacy receiver spelling remains an ABI adapter over the one shared
// storage view; this inheritance is reconstruction scaffolding, not a retail
// class-hierarchy assertion. WB names the owner PartitionManagerImpl.
class PartitionManagerImpl {
public:
 void SetTreeDepth(unsigned);
 int prefix[6];
 _STL::vector<PartitionTreeCounter> trees[21];
 PartitionNode *head;
 float scale;
 int mask;
};
class Gen_dtor_009f2600 : public PartitionManagerImpl {
public:
 __declspec(noinline) void cleanup();
};

void Gen_dtor_009f2600::cleanup()
{
    for (PartitionNode *node = head; node; node = node->next) {
        *node->prevInLeaf = 0;
        node->prevInLeaf = 0;
    }
    if (trees[0].size() != 0) {
        for (int i = 0; i < 21; ++i)
            ((Rva009F40E0Owner *)this)->run((void **)trees[i].begin(), trees[0].size() / 4);
    }
}

struct Gen009F5040Node;
class Gen009F5040 {public:void linkNode(Gen009F5040Node*);};
class Rva00627AA0TreeVector : public _STL::_Vector_base<PartitionRawPair,_STL::allocator<PartitionRawPair> > {
 typedef _STL::_Vector_base<PartitionRawPair,_STL::allocator<PartitionRawPair> > Base;
public:
 Rva00627AA0TreeVector(unsigned n):Base(n,_STL::allocator<PartitionRawPair>()) {
  _M_finish=reinterpret_cast<PartitionRawPair*>(_STL::uninitialized_fill_n(reinterpret_cast<PartitionTreeCounter*>(_M_start),n,PartitionTreeCounter()));
 }
};

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
        Rva00627AA0TreeVector fresh(count);
        *reinterpret_cast<_STL::vector<PartitionAssignPair>*>(&trees[i]) = *reinterpret_cast<const _STL::vector<PartitionAssignPair>*>(&fresh);
    }
    for (PartitionNode *node = head; node; node = node->next)
        ((Gen009F5040 *)this)->linkNode((Gen009F5040Node *)node);
}
