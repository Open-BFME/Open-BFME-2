// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva002E01C6Element { unsigned word0;Rva002E01C6Element& operator=(const Rva002E01C6Element&b){if(this!=&b){word0=b.word0;}return *this;}bool operator<(const Rva002E01C6Element&)const;bool operator==(const Rva002E01C6Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva002E01C6Element, _STL::allocator<Rva002E01C6Element> >::push_back(Rva002E01C6Element const &);
