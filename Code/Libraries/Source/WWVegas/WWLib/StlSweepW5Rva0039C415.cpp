// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

// Rva00587375 is the 60-byte element of the rowed vector<Rva00587375>
// _M_insert_overflow (0x00587C40); its _M_fill_insert at 0x00587DCD shares
// this unit's codegen with 0x0039C415 (masked twin, stride 0x3C).
struct Rva00587375Block8 { int v[8]; };
struct Rva00587375 { int m00, m04, m08; unsigned char m0c; int m10; Rva00587375Block8 m14; int m34; unsigned char m38, m39;
 Rva00587375(const Rva00587375 &b) { m00=b.m00; m04=b.m04; m08=b.m08; m0c=b.m0c; m10=b.m10; m14=b.m14; m34=b.m34; m38=b.m38; m39=b.m39; } };

struct Rva0039C415Element { unsigned words[5];Rva0039C415Element();Rva0039C415Element(const Rva0039C415Element&b){words[0]=b.words[0];words[1]=b.words[1];words[2]=b.words[2];words[3]=b.words[3];words[4]=b.words[4];}bool operator<(const Rva0039C415Element&)const;bool operator==(const Rva0039C415Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0039C415Element, _STL::allocator<Rva0039C415Element> >::_M_fill_insert(Rva0039C415Element *, unsigned int, Rva0039C415Element const &);
template void _STL::vector<Rva00587375, _STL::allocator<Rva00587375> >::_M_fill_insert(Rva00587375 *, unsigned int, Rva00587375 const &);
