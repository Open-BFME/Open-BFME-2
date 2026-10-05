// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@VRva000BB491@@V?$allocator@VRva000BB491@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x000C20C1 206B: vector<Rva000BB491> operator= via allocate_and_copy 0x000BC6A4 plus dtor 0x000C2067 plus copy 0x000B9615 plus destroy 0x000BDD08 plus uninitialized_copy 0x000BBAC7. Evidence: same 3-path 206B shape as SaveMapPreview assign 0x002DD043; idiv 0x18 stride 24 matches Rva000BB491 size 24; callers at 0x000C2832 plus 0x000C6CDE.
class Rva000BB491 {
public:
    Rva000BB491(const Rva000BB491 &o);
    char m_pad[0x18];
};
typedef char Rva000BB491SizeCheck[sizeof(Rva000BB491) == 24 ? 1 : -1];
struct Rva000C1CAEElement {
    char m_pad[0x18];
};
typedef char Rva000C1CAEElementSizeCheck[sizeof(Rva000C1CAEElement) == 24 ? 1 : -1];
class Rva000B9AAA {
public:
    ~Rva000B9AAA();
    char m_pad[0x18];
};
void __cdecl Rva000BDD08Destroy(Rva000B9AAA *first, Rva000B9AAA *last);
class Rva000C2067 {
    Rva000B9AAA *m_start;
    Rva000B9AAA *m_finish;
public:
    ~Rva000C2067();
};
namespace _STL {
struct __false_type {
    __false_type() {}
};
template <class Type>
class allocator {
};
template <class Type, class Allocator>
class vector {
public:
    typedef Type *pointer;
    typedef const Type *const_pointer;
    typedef unsigned int size_type;
    vector &operator=(const vector &x);
    pointer begin() { return m_start; }
    const_pointer begin() const { return m_start; }
    pointer end() { return m_finish; }
    const_pointer end() const { return m_finish; }
    size_type size() const { return size_type(m_finish - m_start); }
    size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
    template <class ForwardIter>
    pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
    pointer m_start;
    pointer m_finish;
    pointer m_endOfStorage;
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
inline _STL::vector<Rva000BB491, _STL::allocator<Rva000BB491> > &_STL::vector<Rva000BB491, _STL::allocator<Rva000BB491> >::operator=(const vector &x)
{
    if (&x != this) {
        size_type xsize = x.size();
        if (xsize > capacity()) {
            pointer tmp = _M_allocate_and_copy(xsize, const_cast<pointer>(x.begin()), const_cast<pointer>(x.end()));
            reinterpret_cast<Rva000C2067 *>(this)->~Rva000C2067();
            m_start = tmp;
            m_endOfStorage = tmp + xsize;
        } else if (size() >= xsize) {
            Rva000C1CAEElement *new_finish = _STL::__copy_ptrs(const_cast<Rva000C1CAEElement *>(reinterpret_cast<const Rva000C1CAEElement *>(x.begin())), const_cast<Rva000C1CAEElement *>(reinterpret_cast<const Rva000C1CAEElement *>(x.end())), reinterpret_cast<Rva000C1CAEElement *>(m_start), _STL::__false_type());
            Rva000BDD08Destroy(reinterpret_cast<Rva000B9AAA *>(new_finish), reinterpret_cast<Rva000B9AAA *>(m_finish));
        } else {
            _STL::__copy_ptrs(const_cast<Rva000C1CAEElement *>(reinterpret_cast<const Rva000C1CAEElement *>(x.begin())), const_cast<Rva000C1CAEElement *>(reinterpret_cast<const Rva000C1CAEElement *>(x.begin() + size())), reinterpret_cast<Rva000C1CAEElement *>(m_start), _STL::__false_type());
            _STL::__uninitialized_copy(const_cast<pointer>(x.begin() + size()), const_cast<pointer>(x.end()), m_finish, _STL::__false_type());
        }
        m_finish = m_start + xsize;
    }
    return *this;
}

// operator= is a header inline: another unit emits a select-any copy of it,
// so a strong definition here was a duplicate symbol in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva000BB491Assign@@YAXPAV?$vector@VRva000BB491@@V?$allocator@VRva000BB491@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitRva000BB491Assign(_STL::vector<Rva000BB491, _STL::allocator<Rva000BB491> > *p, const _STL::vector<Rva000BB491, _STL::allocator<Rva000BB491> > &that)
{
    *p = that;
}
#pragma inline_depth()
