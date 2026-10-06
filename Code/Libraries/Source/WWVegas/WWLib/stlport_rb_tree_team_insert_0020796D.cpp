// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?insert_unique@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@U?$_Nonconst_traits@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@@Z @0x0020796D 151B
// _Rb_tree<pair<AsciiString AsciiString> pair<const pair int>>::insert_unique 151B team map calling rowed _M_insert 0x002072AF
// Evidence: unlock packet 0x0020796D between 0x002078D6 and 0x00207A04 same 151B shape; callees rowed pair operator< 0x00206BCF decrement 0x000242C0 and team _M_insert 0x002072AF; callers 0x00207EE8 0x00208968 family
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "ascii_string.h"

bool operator<(const _STL::pair<AsciiString, AsciiString> &, const _STL::pair<AsciiString, AsciiString> &);

typedef _STL::pair<AsciiString, AsciiString> TeamKey0020796D;
typedef _STL::pair<const TeamKey0020796D, int> TeamValue0020796D;
struct TeamLess0019B850 : _STL::less<TeamKey0020796D> {};
typedef _STL::_Rb_tree<TeamKey0020796D, TeamValue0020796D, _STL::_Select1st<TeamValue0020796D>, TeamLess0019B850, _STL::allocator<TeamValue0020796D> > TeamTree0020796D;

template _STL::pair<TeamTree0020796D::iterator, bool> TeamTree0020796D::insert_unique(const TeamValue0020796D &);
