// ?rva001C3B70Filter@@YAXPAXPAEHPBH@Z
// partial score=0.784 date=2026-10-07
// cl: /O2 /Ob0 /G7 /arch:SSE /MD /DNDEBUG
// Reference family: BF1 ba7 BfmeLoopFilterVert.cpp / Rva009AF570FilterVert.cpp.
// Native1C3B70..1C3F4D is a complete989B leaf, followed by padding before
// the already matched vertical filter at1C3F50. Original owner is unknown.
// Native reads four unsigned pixel taps, obtains a correction from the
// caller's int table, and writes through the owned clamp-table zero point.
// Its arithmetic is 2*centralDelta-leftSlope+rightSlope+4. Outer taps receive
// half the correction only when both side slopes are zero. The cursor advances
// only on a nonzero central delta: all eight native branch targets prove this.
// The eight explicit C++ steps mirror the fixed native unrolling. This remains
// unverified: O2/G7 emits961B with a different spill frame, G6 emits929B,
// and O1 or O2/Os emit915B. A rolled increasing loop emits486B; countdown143B.
// Shared local declarations and G5/GB/Oy variants do not fix the gap.
extern const unsigned char g_bfmeClampTable[];
#define RVA001C3B70_STEP() \
    { \
        int p1=ptr[1]; \
        int p2=ptr[2]; \
        int value=p2-p1; \
        if (value!=0) { \
            int left=p1-ptr[0]; \
            int p3=ptr[3]; \
            int right=p3-p2; \
            int delta=bounding[(2*value-left+right+4)>>3]; \
            ptr[1]=g_bfmeClampTable[p1+delta]; \
            ptr[2]=g_bfmeClampTable[p2-delta]; \
            int half=(!(left|right))*(delta>>1); \
            ptr[0]=g_bfmeClampTable[ptr[0]+half]; \
            ptr[3]=g_bfmeClampTable[p3-half]; \
            ptr+=stride; \
        } \
    }
void rva001C3B70Filter(void *,unsigned char *ptr,int stride,const int *bounding)
{
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
    RVA001C3B70_STEP();
}
#undef RVA001C3B70_STEP
