// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004ABFB2@Rva004ABFB2@@QAEXH@Z @0x004ABFB2 39B
// evidence: unlock caller 0x004ABFD9 dtor passes global 0x00A03CE0 as this plus int key; callees rowed tree-erase 0x004ABE65 plus Rva0020DAE0 0x0020DAE0; registry-remove pattern from Rva00E03CE0RegistryInsert
#include <map>

typedef _STL::pair<const int, void *> PairIntPtr004ABFB2;
typedef _STL::_Rb_tree<int, PairIntPtr004ABFB2, _STL::_Select1st<PairIntPtr004ABFB2>, _STL::less<int>, _STL::allocator<PairIntPtr004ABFB2> > TreeIntPtr004ABFB2;

// Declare helpers so this TU calls retail's instead of emitting competing copies.
template <> unsigned TreeIntPtr004ABFB2::erase(const int &);
template <> TreeIntPtr004ABFB2::_Link_type TreeIntPtr004ABFB2::_M_upper_bound(const int &) const;
template <> TreeIntPtr004ABFB2::_Link_type TreeIntPtr004ABFB2::_M_lower_bound(const int &) const;

// Keep the owned upper_bound row via explicit instantiation (was an implicit side effect).
template TreeIntPtr004ABFB2::iterator TreeIntPtr004ABFB2::upper_bound(const int &);

void __cdecl Rva0020DAE0(void *p);

class Rva004ABFB2
{
public:
    void rva004ABFB2(int key);
private:
    void *m_00;
    _STL::map<int, void *> m_map;
    bool m_10;
    bool m_11;
};

void Rva004ABFB2::rva004ABFB2(int key)
{
    if (m_11)
        return;
    m_map.erase(key);
    if (m_map.size() != 0)
        return;
    Rva0020DAE0(this);
}
