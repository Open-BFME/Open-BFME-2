// Canonical twelve-byte physical vector view from class_contracts/BfmeIntVecG.json.
// Native ArmySummary40DED9 reads first4C/last50; its155B destructor frees first4C.
// LivingWorld3F6672 uses the same range-erasure callee532803 for its scalar IDs.
// The original container class and element typedef are unproven; keep opaque names.
#ifndef CANONICAL_BFMEINTVECG_H
#define CANONICAL_BFMEINTVECG_H
#include <vector>
extern "C" void __cdecl free(void*);
// Each physical four-byte word is consumed as a signed lookup key in ArmySummary.
// STLport's generic copy-ptrs29 wrapper and forward-copy31B031 establish the
// scalar range-erasure shape; they do not establish an original enum/class name.
struct ArmySummaryKeyWord { int value; };
class BfmeIntVecG {
public:
    int *first;
    int *last;
    int *limit;
    __forceinline void clear() {
        reinterpret_cast<_STL::vector<ArmySummaryKeyWord>*>(this)->clear();
    }
    ~BfmeIntVecG() { if(first) free(first); }
};
#endif
