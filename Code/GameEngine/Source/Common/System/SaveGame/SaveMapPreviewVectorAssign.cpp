// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x002DD043 206B: vector<SaveMapPreview> operator= via allocate_and_copy 0x002DC5B0 plus tidy 0x00565A42 plus copy 0x002DC593 plus destroy 0x0022C8E3 plus uninitialized_copy 0x002DBEFF. Evidence: same 3-path 206B shape as BfmeStringRecord assign 0x000C084D; idiv 0x14 stride 20 matches SaveMapPreview size 20; callers include 0x002DDCF1.
class Rva002262E7SnapshotBase {
public:
    virtual ~Rva002262E7SnapshotBase();
    virtual void crc(class Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(class Xfer *);
};
class SaveMapPreview : public Rva002262E7SnapshotBase {
public:
    unsigned int word04;
    struct Words { unsigned int a, b, c; } words08;
};
typedef char SaveMapPreviewSizeCheck[sizeof(SaveMapPreview) == 20 ? 1 : -1];
struct Rva002DCFEEElement {
    unsigned int w[5];
};
typedef char Rva002DCFEEElementSizeCheck[sizeof(Rva002DCFEEElement) == 20 ? 1 : -1];
struct Rva0052BF9BElem;
void __cdecl Rva0022C8E3DestroyRange(struct Rva0052BF9BElem *first, struct Rva0052BF9BElem *last);
struct Rva0052BF9BElem {
    virtual ~Rva0052BF9BElem();
};
class Rva00565A42 {
public:
    void rva00565A42();
private:
    Rva0052BF9BElem *m_00;
    Rva0052BF9BElem *m_04;
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
inline _STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> > &_STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> >::operator=(const vector &x)
{
    if (&x != this) {
        size_type xsize = x.size();
        if (xsize > capacity()) {
            pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
            reinterpret_cast<Rva00565A42 *>(this)->rva00565A42();
            m_start = tmp;
            m_endOfStorage = tmp + xsize;
        } else if (size() >= xsize) {
            Rva002DCFEEElement *new_finish = _STL::__copy_ptrs(const_cast<Rva002DCFEEElement *>(reinterpret_cast<const Rva002DCFEEElement *>(x.begin())), const_cast<Rva002DCFEEElement *>(reinterpret_cast<const Rva002DCFEEElement *>(x.end())), reinterpret_cast<Rva002DCFEEElement *>(m_start), _STL::__false_type());
            Rva0022C8E3DestroyRange(reinterpret_cast<Rva0052BF9BElem *>(new_finish), reinterpret_cast<Rva0052BF9BElem *>(m_finish));
        } else {
            _STL::__copy_ptrs(const_cast<Rva002DCFEEElement *>(reinterpret_cast<const Rva002DCFEEElement *>(x.begin())), const_cast<Rva002DCFEEElement *>(reinterpret_cast<const Rva002DCFEEElement *>(x.begin() + size())), reinterpret_cast<Rva002DCFEEElement *>(m_start), _STL::__false_type());
            _STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, _STL::__false_type());
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
// ?bfmeEmitSaveMapPreviewAssign@@YAXPAV?$vector@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitSaveMapPreviewAssign(_STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> > *p, const _STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> > &that)
{
    *p = that;
}
#pragma inline_depth()
