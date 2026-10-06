// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00241C25@Rva00241C25@@QAEXPAVObject@@@Z @0x00241C25 80B
// evidence: unlock caller 0x00291EB1; rowed Object::rva002931BA 0x002931BA plus rowed find 0x0020E873 plus pinned push_back vector<Object*> 0x001F211B; single end-load plus direct begin push pattern
#include <vector>
#include <algorithm>

class Object
{
public:
    bool rva002931BA();
};

class CreateAHeroData;

class Rva00241C25
{
private:
    char m_pad00[0x6d];
    bool m_6d;
    bool m_6e;
    char m_pad6f[0x164 - 0x6f];
    _STL::vector<CreateAHeroData *> m_vec164;
public:
    void rva00241C25(Object *obj);
};

void Rva00241C25::rva00241C25(Object *obj)
{
    if (!obj)
        return;
    if (obj->rva002931BA())
        return;
    if (m_6d)
        return;
    if (m_6e)
        return;
    CreateAHeroData **end = m_vec164.end();
    if (_STL::find(m_vec164.begin(), end, (CreateAHeroData * const &)obj) != end)
        return;
    ((_STL::vector<Object *> *)&m_vec164)->push_back(obj);
}
