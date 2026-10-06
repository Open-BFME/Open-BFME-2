// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva0039C415Element { unsigned words[5];Rva0039C415Element();Rva0039C415Element(const Rva0039C415Element&b){words[0]=b.words[0];words[1]=b.words[1];words[2]=b.words[2];words[3]=b.words[3];words[4]=b.words[4];}bool operator<(const Rva0039C415Element&)const;bool operator==(const Rva0039C415Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0039C415Element, _STL::allocator<Rva0039C415Element> >::_M_fill_insert(Rva0039C415Element *, unsigned int, Rva0039C415Element const &);
