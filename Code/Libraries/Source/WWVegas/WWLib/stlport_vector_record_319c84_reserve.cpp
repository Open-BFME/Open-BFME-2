// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reserve@?$vector@UBfmeVectorRecord00319C84@@...@QAEXI@Z, retail 0x00319C84, 105 bytes.
// Evidence: the body is byte-identical to vector<BfmeVectorRecord0002154F3>::reserve
// except its _M_clear call, which reads 0x00565A60 rather than that vector's
// rowed _M_clear at 0x0021580E. Its _M_allocate_and_copy call reads 0x00319304,
// also apart from that vector's other bodies near 0x002155xx. So this is a second
// instantiation over a 16-byte element type. The address-owned name does not
// identify the original element; its virtual destruction is proved below.
#include <vector>
// Target correction: _Destroy at 0x00319784 calls the complete 26-byte loop
// at 0x00319331, whose slot-0 virtual destruction (flag 0) and +0x10 stride
// prove a virtual destructor and 16-byte extent. Other fields and the original
// element identity remain unknown; the former AsciiString/vector view was a
// size-only guess. BF1 575ba2b Q4VectorDtorPolymorphic.cpp supplies the same
// evidence-backed STLport virtual-element pattern, not the target identity.
struct BfmeVectorRecord00319C84 {
    virtual ~BfmeVectorRecord00319C84();
    char m_body[12];
    BfmeVectorRecord00319C84();
    BfmeVectorRecord00319C84(const BfmeVectorRecord00319C84 &);
};
namespace _STL {
template <> void _Construct<BfmeVectorRecord00319C84, BfmeVectorRecord00319C84>(BfmeVectorRecord00319C84 *, const BfmeVectorRecord00319C84 &);
// Declared, not defined: retail routes the range destruction through the
// pinned worker at 0x00319784 (pin 247), and the rowed _M_clear (0x00565A60)
// and vector dtor (0x00319B58) bodies both call it as such. Defining the
// template here inlines the element-dtor loop, whose COMDAT copy loses to
// retail's dispatch bytes (L+S ??$_Destroy@PAU...). With only the
// declaration, the instantiation below calls the pinned address and this
// unit emits no copy of its own. (Single-element _Destroy is unaffected.)
template <> void _Destroy<BfmeVectorRecord00319C84 *>(BfmeVectorRecord00319C84 *, BfmeVectorRecord00319C84 *);
}
template void _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::reserve(size_t);
