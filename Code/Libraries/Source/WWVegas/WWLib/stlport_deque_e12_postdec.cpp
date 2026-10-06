// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??F?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@QAE?AU01@H@Z retail 0x004222D1 40B.
// Postfix operator-- for deque<BfmeE12> nonconst iterator: copy *this to tmp,
// prefix -- via rowed _M_decrement 0x00421B47, return tmp via hidden pointer.
// Evidence: retail push ebp frame 4x movsd copy call _M_decrement 4x movsd ret 8;
// neighbours 0x004221E6 ??G and 0x004226AD back share TU and flags.
#include <deque>

struct BfmeE12 { float x, y, z; };
typedef _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > IterE12;
template IterE12 IterE12::operator--(int);
