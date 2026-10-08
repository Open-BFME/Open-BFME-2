// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva005B26CELess@@YG_NPBX0@Z @0x005B26CE 53B: stdcall 16-byte nullness-order comparator for introsort/heap.
// Evidence: leaf (no callees); callers are 16-byte sort/heap bodies 0x005B282E median 0x005B28BD push-heap
// 0x005B28F3 push-heap 0x005B2FDC partition 0x005B2A8C heap 0x005B38B1 0x005B3C25 introsort-loop;
// element stride 0x10 in callers matches BfmeE16 stand-in size; ret-8 stdcall shape matches sibling
// ?Rva0056866ALess@@YG_NPBX0@Z precedent; /O1 gives inc xor-first frameless shape.
bool __stdcall Rva005B26CELess(const void *a_, const void *b_)
{
    const unsigned int *a = (const unsigned int *)a_;
    const unsigned int *b = (const unsigned int *)b_;
    for (int i = 0; i < 4; ++i) {
        unsigned int av = a[i];
        unsigned int bv = b[i];
        if (av != 0 && bv == 0)
            return true;
        if (av == 0 && bv != 0)
            return false;
    }
    return true;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??RRva005B26CECmp@@QBE_NPBX0@Z=?Rva005B26CELess@@YG_NPBX0@Z")
