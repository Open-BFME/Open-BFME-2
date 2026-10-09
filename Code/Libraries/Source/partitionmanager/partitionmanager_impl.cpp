// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include <vector>

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

struct PartitionTreeCounter { int count; void *head; };
struct PartitionNode {
    char pad00[0xc];
    PartitionNode *next;
    PartitionNode **prevInLeaf;
};

class Gen_dtor_009f2600 {
public:
    void cleanup();
    int prefix[6];
    _STL::vector<PartitionTreeCounter> trees[21];
    PartitionNode *head;
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
