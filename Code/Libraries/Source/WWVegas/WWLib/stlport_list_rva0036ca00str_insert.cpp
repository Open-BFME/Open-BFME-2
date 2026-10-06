// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@QAE?AU?$_List_iterator@VRva0036CA00Str@@U?$_Nonconst_traits@VRva0036CA00Str@@@_STL@@@2@U32@ABVRva0036CA00Str@@@Z retail 0x00054B75 37B
// Evidence: identical 37B insert shape to list<AsciiString>::insert at 0x001FD72C and list<TreeKey00242F5E>::insert at 0x002A1BC6;
// here calls rowed Rva0036CA00Str _M_create_node at 0x00053DA3 then list hook insertion; caller 0x00055486.
#include <list>

class Rva0036CA00Str { public: unsigned char m_data[4]; };

bool operator==(const Rva0036CA00Str &a, const Rva0036CA00Str &b);
bool operator<(const Rva0036CA00Str &a, const Rva0036CA00Str &b);

template class _STL::list<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >;
