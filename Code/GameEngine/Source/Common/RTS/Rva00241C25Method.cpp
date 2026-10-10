// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// GameLogic::QueueForNotifyPathfindCellChanged @0x00241C25 80B (WorldBuilder name,
// GameLogic.cpp line 1307: the same Object check, +0x6D/+0x6E guards and
// find-then-push_back on the +0x164 object list)
// evidence: unlock caller 0x00291EB1; rowed Object::rva002931BA 0x002931BA plus rowed find 0x0020E873 plus pinned push_back vector<Object*> 0x001F211B; single end-load plus direct begin push pattern
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>

class Object
{
public:
    bool rva002931BA();
};

class CreateAHeroData;

class GameLogic
{
private:
    char m_pad00[0x6d];
    bool m_6d;
    bool m_6e;
    char m_pad6f[0x164 - 0x6f];
    _STL::vector<CreateAHeroData *> m_vec164;
public:
    void QueueForNotifyPathfindCellChanged(Object *obj);
};

void GameLogic::QueueForNotifyPathfindCellChanged(Object *obj)
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
