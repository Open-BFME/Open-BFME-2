// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Reference STLport4.5.3 AsciiString->list map cleanup. Retail keeps one
// 56B tree-dtor shell at 0x005CA918 for the two list-valued maps of
// GameSpyLoginPreferences (+0x2c/+0x2c order in dtor 0x5CAB59); the shell is
// byte-identical to the string-pair tree dtor 0x3B1E83 except it clears
// through the list-tree clear 0x5CA780 (whose head matches the pair clear
// 0x2E44F2 with the list-tree erase 0x5CA25C as callee).
#include "ascii_string.h"
#include <map>
#include <list>
typedef _STL::pair<const AsciiString,_STL::list<AsciiString> > StringListPair;
typedef _STL::_Rb_tree<AsciiString,StringListPair,_STL::_Select1st<StringListPair>,_STL::less<AsciiString>,_STL::allocator<StringListPair> > StringListTree;
template StringListTree::~_Rb_tree();
