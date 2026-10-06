// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// STLport 4.5.3 find(first, last, value) over list<AsciiString> iterators
// @0x001FD9C5 (42B): forwards to __find(..., input_iterator_tag), rowed by
// hand at 0x001FD837 (pinned). Same 42-byte forwarder shape as the
// list<ObjectID> find rowed at 0x0029B694 from SpawnBehavior.cpp.
#include <list>
#include <algorithm>
#include "ascii_string.h"

typedef _STL::list<AsciiString>::iterator Rva001FD9C5ListIter;
template Rva001FD9C5ListIter _STL::find<Rva001FD9C5ListIter, AsciiString>(Rva001FD9C5ListIter, Rva001FD9C5ListIter, const AsciiString &);
