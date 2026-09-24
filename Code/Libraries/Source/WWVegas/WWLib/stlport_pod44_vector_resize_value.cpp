// cl: /O1 /EHsc /MD /D_CRTIMP=
// STLport 4.5.3 vector resize with a 44-byte element passed by value.
// BfmePod44 names the proven stride; the retail element type is not established.
// Shape follows Open-BFME-1 vector_ICoord2D_resize.cpp. The retail call at
// 0x00082D02 reaches the 38-byte erase body at 0x00081A4F.
struct BfmePod44 { int a[11]; };
namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector {
public:
    typedef unsigned int size_type;
    typedef T *iterator;
    iterator erase(iterator first, iterator last);
    void _M_fill_insert(iterator position, size_type count, const T &value);
    void resize(size_type newSize, T value);
private:
    iterator begin() { return m_start; }
    iterator end() { return m_finish; }
    size_type size() const { return (size_type)(m_finish - m_start); }
    T *m_start;
    T *m_finish;
    T *m_endOfStorage;
};
template <class T, class A>
void vector<T,A>::resize(size_type newSize, T value) {
    if (newSize < size())
        erase(begin() + newSize, end());
    else
        _M_fill_insert(end(), newSize - size(), value);
}
template void vector<BfmePod44,allocator<BfmePod44> >::resize(unsigned int,BfmePod44);
}
