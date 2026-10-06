// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <memory>
#include <utility>

struct Rva006200B0Element { unsigned char words[1];bool operator<(const Rva006200B0Element&)const;bool operator==(const Rva006200B0Element&)const; };
template class _STL::hash_map<unsigned,Rva006200B0Element>;
