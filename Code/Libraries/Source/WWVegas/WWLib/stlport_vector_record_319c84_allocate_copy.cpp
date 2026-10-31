// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/bfmealloc/stl /ICode/Libraries/Include/Lib
// stlport
// ??$_M_allocate_and_copy@PAUBfmeVectorRecord00319C84@@@?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@IAEPAUBfmeVectorRecord00319C84@@IPAU2@0@Z @0x00319304 45B
// Evidence: caller reserve 0x00319C84 plus unclaimed 0x00319BFF; rowed allocate 0x002226BE via BfmeVectorRecord00319C84 pin plus rowed copy 0x00318D75; same 45B ebp-tag shape as 0x001FFA2D and 0x00317D5C
#define _CRTIMP
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// Target correction: _Destroy at 0x00319784 calls the complete 26-byte loop
// at 0x00319331, whose slot-0 virtual destruction (flag 0) and +0x10 stride
// prove a virtual destructor and 16-byte extent. Other fields and the original
// element identity remain unknown; the former AsciiString/vector view was a
// size-only guess. BF1 575ba2b Q4VectorDtorPolymorphic.cpp supplies the same
// evidence-backed STLport virtual-element pattern, not the target identity.
struct BfmeVectorRecord00319C84
{
	virtual ~BfmeVectorRecord00319C84();
	char m_body[12];
	BfmeVectorRecord00319C84();
	BfmeVectorRecord00319C84(const BfmeVectorRecord00319C84 &);
};
class Rva00318B5C;
void Rva00318D63Copy(Rva00318B5C *dest, const Rva00318B5C &src);
namespace _STL
{
// Retail's copy loop 0x00318D75 calls the 18B null-guarded construct at 0x00318D63.
template <> __declspec(dllimport) __forceinline void _Construct<BfmeVectorRecord00319C84, BfmeVectorRecord00319C84>(BfmeVectorRecord00319C84 *p, const BfmeVectorRecord00319C84 &v)
{ ::Rva00318D63Copy(reinterpret_cast<Rva00318B5C *>(p), reinterpret_cast<const Rva00318B5C &>(v)); }
// Declared, not defined: retail routes the range destruction through the
// pinned worker at 0x00319784 (pin 247), and the rowed vector dtor
// (0x00319B58) calls it as such. Defining the template here inlines the
// element-dtor loop, whose COMDAT copy loses to retail's dispatch bytes
// (L+S ??$_Destroy@PAU...). With only the declaration, the instantiation
// below calls the pinned address and this unit emits no copy of its own.
// (Single-element _Destroy is unaffected.)
template <> void _Destroy<BfmeVectorRecord00319C84 *>(BfmeVectorRecord00319C84 *, BfmeVectorRecord00319C84 *);
}
template BfmeVectorRecord00319C84 *_STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::_M_allocate_and_copy<BfmeVectorRecord00319C84 *>(unsigned int, BfmeVectorRecord00319C84 *, BfmeVectorRecord00319C84 *);
