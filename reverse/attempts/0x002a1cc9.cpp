// StringIntListPairCtor
// partial score=1.0 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Ob2 /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// STLport4.5.3 pair construction with the existing list copy providers.
#include <utility>
#include <list>
#include "ascii_string.h"
namespace _STL {
template <> list<int>::list(const list<int>&);
}
typedef _STL::list<int> IntList;
typedef _STL::pair<const AsciiString,IntList> IntListPair;
template IntListPair::pair(const AsciiString&,const IntList&);
