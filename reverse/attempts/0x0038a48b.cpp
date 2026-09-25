// ??1?$_Rb_tree@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@U?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@@_STL@@QAE@XZ
// partial score=0.93 date=2026-09-25
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
#include <string>
#include <map>

typedef _STL::pair<const std::string, int> RvaPeerStatValue;
typedef _STL::_Rb_tree<std::string, RvaPeerStatValue,
    _STL::_Select1st<RvaPeerStatValue>, _STL::less<std::string>,
    _STL::allocator<RvaPeerStatValue> > RvaPeerStatTree;
template <> void RvaPeerStatTree::clear();
template class RvaPeerStatTree;
