// ??1?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@QAE@XZ
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@QAE@XZ @0x002BBB18 63B:
// vector<BfmeAssignRecord52> dtor; same 63B shape as sibling 0x002BBB57 which calls its own _Destroy.
// Retail calls __destroy_aux for BfmeAssignRecord52 0x002BB6A5 plus _free 0x00030830 with EH prolog handler 0xB768C5.
// Callers 0x002BD52C 0x003F6920 0x004FA3B5 plus vector-of-vector chains; prev/next share TU flags.
#include <vector>
#include "ascii_string.h"
struct BfmeAssignRecord52 { AsciiString s; int a[12]; };
// ??1?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@QAE@XZ present-unmatched
template _STL::vector<BfmeAssignRecord52>::~vector();
