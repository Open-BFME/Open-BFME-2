// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B4B3D@Rva002B4B3D@@QAE_NXZ @0x002B4B3D 70B and
// ?rva002E0AEA@Rva002E0AEA@@QAE_NXZ @0x002E0AEA 70B.
// Both are any-of loops over a pointer vector re-reading size() every pass:
// 002B4B3D walks the vector at +0x8c calling 002E0AEA on each element and
// 002E0AEA walks the vector at +0x1b8 calling the rowed byte getter
// rva00318B94. Original names unknown so address-derived Rva names are used.
#include <vector>
class Rva00318B94
{
public:
    unsigned char rva00318B94();
};
class Rva002E0AEA
{
public:
    bool rva002E0AEA();
private:
    char m_pad[0x1b8];
    _STL::vector<Rva00318B94 *> m_items;
};
bool Rva002E0AEA::rva002E0AEA()
{
    for (unsigned int i = 0; i < m_items.size(); ++i) {
        if (m_items[i]->rva00318B94())
            return true;
    }
    return false;
}
class Rva002B4B3D
{
public:
    bool rva002B4B3D();
private:
    char m_pad[0x8c];
    _STL::vector<Rva002E0AEA *> m_items;
};
bool Rva002B4B3D::rva002B4B3D()
{
    for (unsigned int i = 0; i < m_items.size(); ++i) {
        if (m_items[i]->rva002E0AEA())
            return true;
    }
    return false;
}
