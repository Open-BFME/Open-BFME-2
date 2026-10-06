// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva000B4431Element { unsigned word0;Rva000B4431Element& operator=(const Rva000B4431Element&b){if(this!=&b){word0=b.word0;}return *this;}~Rva000B4431Element(){}bool operator<(const Rva000B4431Element&)const;bool operator==(const Rva000B4431Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva000B4431Element * _STL::__copy<Rva000B4431Element *, Rva000B4431Element *, int>(Rva000B4431Element *, Rva000B4431Element *, Rva000B4431Element *, _STL::random_access_iterator_tag const &, int *);
