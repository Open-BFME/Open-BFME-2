// cl: /EHsc /MD /D_CRTIMP=
// STLport 4.5.3 vector resize with a 60-byte element passed by value.
// BfmePod60 names the proven stride; the retail element type is not established.
// Shape follows Open-BFME-1 vector_ICoord2D_resize.cpp. The retail call at
// 0x0058816D reaches the 38-byte erase body at 0x00587C1A.
struct BfmePod60 { int a[15]; };
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
template <class A> class vector<BfmePod60, A> {
public:
    typedef unsigned int size_type;
    typedef BfmePod60 *iterator;
    iterator erase(iterator first, iterator last);
    void _M_fill_insert(iterator position, size_type count, const BfmePod60 &value);
    void resize(size_type newSize, BfmePod60 value);
private:
    iterator begin() { return m_start; }
    iterator end() { return m_finish; }
    size_type size() const { return (size_type)(m_finish - m_start); }
    BfmePod60 *m_start;
    BfmePod60 *m_finish;
    BfmePod60 *m_endOfStorage;
};
template <class A>
void vector<BfmePod60,A>::resize(size_type newSize, BfmePod60 value) {
    if (newSize < size())
        erase(begin() + newSize, end());
    else
        _M_fill_insert(end(), newSize - size(), value);
}
template void vector<BfmePod60,allocator<BfmePod60> >::resize(unsigned int,BfmePod60);
}

// The retail call in this body reads 0x00587DCD, an address the ledger already
// carries as ?_M_fill_insert@?$vector@URva00587375@@V?$allocator@URva00587375@@@_STL@@@_STL@@QAEXPAURva00587375@@IABU3@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?_M_fill_insert@?$vector@UBfmePod60@@V?$allocator@UBfmePod60@@@_STL@@@_STL@@QAEXPAUBfmePod60@@IABU3@@Z=?_M_fill_insert@?$vector@URva00587375@@V?$allocator@URva00587375@@@_STL@@@_STL@@QAEXPAURva00587375@@IABU3@@Z")
