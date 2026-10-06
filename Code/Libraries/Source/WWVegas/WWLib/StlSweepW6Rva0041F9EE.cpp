// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>
#include <utility>

struct Rva0041F9EEElement { void* words[1];bool operator<(const Rva0041F9EEElement&)const;bool operator==(const Rva0041F9EEElement&)const; };
template struct _STL::pair<Rva0041F9EEElement,unsigned>;
template struct _STL::pair<unsigned,Rva0041F9EEElement>;
