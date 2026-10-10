// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@QAE@XZ retail 0x00319B58 63B: vector dtor via Destroy plus free.
// Evidence: calls pin Destroy 0x00319784 and rowed free 0x00030830 with EH prolog scopetable 0x00B7A8FD; callers include thunk and unwinds.
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
}
template _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::~vector();
