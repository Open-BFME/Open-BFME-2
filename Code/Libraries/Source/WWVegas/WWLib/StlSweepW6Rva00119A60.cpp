// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva00119A60Element { int word0;int word1;int word2;int word3;int word4;int word5;int word6;int word7;int word8;int word9;int word10;int word11;int word12;int word13;int word14;int word15;int word16;int word17;int word18;int word19;int word20;int word21;int word22;int word23;int word24;int word25;int word26;int word27;int word28;bool operator<(const Rva00119A60Element&)const;bool operator==(const Rva00119A60Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00119A60Element & _STL::vector<Rva00119A60Element, _STL::allocator<Rva00119A60Element> >::operator[](unsigned int);
