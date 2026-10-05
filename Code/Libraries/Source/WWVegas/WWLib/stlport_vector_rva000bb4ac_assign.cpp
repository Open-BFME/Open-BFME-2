// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@VRva000BB4AC@@V?$allocator@VRva000BB4AC@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x000C218F 206B: vector<Rva000BB4AC> operator= via allocate_and_copy 0x000BC6D1 plus dtor 0x000C2085 plus copy 0x000B9632 plus destroy 0x000BD28D plus uninitialized_copy 0x000BBB12. Evidence: same 3-path 206B shape as Rva000BB491 assign 0x000C20C1; idiv 0x18 stride 24 matches Rva000BB4AC size 24; callers at 0x000C2844 plus 0x000C6D02.
class Rva000BB4AC {
public:
    Rva000BB4AC(const Rva000BB4AC &o);
    char m_pad[0x18];
};
typedef char Rva000BB4ACSizeCheck[sizeof(Rva000BB4AC) == 24 ? 1 : -1];
struct Rva000B690BRecord {
    char m_pad[0x18];
};
typedef char Rva000B690BRecordSizeCheck[sizeof(Rva000B690BRecord) == 24 ? 1 : -1];
struct Rva00B9AC2 {
    ~Rva00B9AC2();
    unsigned char m_data[0x18];
};
class Rva000C2085 {
    Rva00B9AC2 *m_start;
    Rva00B9AC2 *m_finish;
public:
    ~Rva000C2085();
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
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}
inline _STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> > &_STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> >::operator=(const vector &x)
{
    if (&x != this) {
        size_type xsize = x.size();
        if (xsize > capacity()) {
            pointer tmp = _M_allocate_and_copy(xsize, const_cast<pointer>(x.begin()), const_cast<pointer>(x.end()));
            reinterpret_cast<Rva000C2085 *>(this)->~Rva000C2085();
            m_start = tmp;
            m_endOfStorage = tmp + xsize;
        } else if (size() >= xsize) {
            Rva000B690BRecord *new_finish = _STL::__copy_ptrs(const_cast<Rva000B690BRecord *>(reinterpret_cast<const Rva000B690BRecord *>(x.begin())), const_cast<Rva000B690BRecord *>(reinterpret_cast<const Rva000B690BRecord *>(x.end())), reinterpret_cast<Rva000B690BRecord *>(m_start), _STL::__false_type());
            _STL::_Destroy(reinterpret_cast<Rva00B9AC2 *>(new_finish), reinterpret_cast<Rva00B9AC2 *>(m_finish));
        } else {
            _STL::__copy_ptrs(const_cast<Rva000B690BRecord *>(reinterpret_cast<const Rva000B690BRecord *>(x.begin())), const_cast<Rva000B690BRecord *>(reinterpret_cast<const Rva000B690BRecord *>(x.begin() + size())), reinterpret_cast<Rva000B690BRecord *>(m_start), _STL::__false_type());
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
// ?bfmeEmitRva000BB4ACAssign@@YAXPAV?$vector@VRva000BB4AC@@V?$allocator@VRva000BB4AC@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitRva000BB4ACAssign(_STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> > *p, const _STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> > &that)
{
    *p = that;
}
#pragma inline_depth()
