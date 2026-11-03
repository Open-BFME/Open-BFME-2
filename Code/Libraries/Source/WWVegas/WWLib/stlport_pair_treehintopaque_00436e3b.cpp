// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@QAE@XZ @0x00434513 53B: pair<const AsciiString, TreeHintOpaque0043671B> dtor destroys mapped 0x00229840 at +4 then narrow StringBase<D> releaseBuffer 0x00036410 at +0; layout from pair copy 0x00435DAA and mapped copy 0x0022D106; unwind caller 0x00787FB8 and tree insert context prove pair identity.
// The node allocates 0xE08 bytes and constructs its 0xDF8-byte value at node+16; same flags as stlport_rb_tree_hint_00436e3b.cpp.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../GameEngine/Include/GameClient/TreeHintOpaque0043671B.h"
inline bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
template void _STL::_Destroy<TreeHintPair0043671B>(TreeHintPair0043671B *);
template TreeHintPair0043671B::pair(const AsciiString &, const TreeHintOpaque0043671B &);
