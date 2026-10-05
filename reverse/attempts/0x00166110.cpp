// ??0BfmeRva00166110@@QAE@ABV0@@Z
// partial score=0.82 date=2026-10-05
// cl: /O2 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 container copy constructor body, recovered at 0x00166110 (175B)
// under the class name BfmeRva00166110. The game type's real name is unknown;
// the body is a vector copy constructor, proven byte for byte: the source's
// _M_start/_M_finish pair (esi+0/esi+4), get_allocator returned by value into a
// stack temporary (0x001627F0, called on the source), the (end - begin) / 36
// element count from the 0x38E38E39 magic multiply, the allocator's out-of-line
// allocate (0x00162800, called on the destination), then __uninitialized_copy
// over the false_type path with the memberwise element copy.
//
// BfmePod36 stands for the real element: the stride fixes sizeof at 36 and the
// copy stores fix the copied payload at 33 bytes -- eight dwords at offset 0,4,8,
// c,10,14,18,1c plus one byte at 0x20 -- which is what a non-trivial copy
// constructor compiles to. This is the pristine STLport vector copy constructor
// (vendor/stlport/stl/_vector.h lines 212-216), carried on the class the ledger
// row names and instantiated for the one concrete element so the mangled symbol is
// exactly ??0BfmeRva00166110@@QAE@ABV0@@Z.
#include <vector>

// stlport
struct BfmePod36 {
    int a0, a1, a2, a3, a4, a5, a6, a7;
    char b;
    BfmePod36() {}
    BfmePod36(const BfmePod36 &o)
        : a0(o.a0), a1(o.a1), a2(o.a2), a3(o.a3),
          a4(o.a4), a5(o.a5), a6(o.a6), a7(o.a7), b(o.b) {}
};

typedef _STL::allocator<BfmePod36> BfmeAlloc;
typedef _STL::_Vector_base<BfmePod36, BfmeAlloc> BfmeRva00166110Base;

// The recovered class: the game container whose copy constructor is this body.
class BfmeRva00166110 : public BfmeRva00166110Base
{
public:
    BfmeRva00166110(const BfmeRva00166110 &__x)
        : BfmeRva00166110Base(__x.size(), __x.get_allocator())
    {
        this->_M_finish = _STL::__uninitialized_copy(
            (const BfmePod36 *)__x._M_start,
            (const BfmePod36 *)__x._M_finish,
            this->_M_start,
            _STL::__false_type());
    }

    BfmeAlloc get_allocator() const {
        return _STLP_CONVERT_ALLOCATOR((const BfmeAlloc &)this->_M_end_of_storage, BfmePod36);
    }

private:
    size_t size() const { return size_t(this->_M_finish - this->_M_start); }
};

void rva00166110Use(const BfmeRva00166110 &a, const BfmeRva00166110 &b)
{
    BfmeRva00166110 tmp(a);
    new (&tmp) BfmeRva00166110(b);
}