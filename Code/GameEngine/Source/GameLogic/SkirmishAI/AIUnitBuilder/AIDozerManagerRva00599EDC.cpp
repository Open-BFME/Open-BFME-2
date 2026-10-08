// cl: /O1 /GX- /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 00599EDC..00599F51: list head at +0, four-byte ObjectID payloads;
// object flags +94 bit0 and +438 bit0 determine invalid entries. The first
// entry is deferred until after the walk; other removals retain the previous
// iterator. WB1530830 calls the named preEmptivelyBuildDozers at1530980,
// mapped to retail00599D56, whose full390B boundary returns without arguments.
// Existing AIDozerManager DoXfer and registration bodies prove list and owner
// identity. The entry's original name and the two target flag names are unknown.
#include <list>
#include "../../../Common/GameLogicObjectLookupView.h"

class Object
{
public:
    unsigned char prefix00[0x94];
    unsigned char status94;
    unsigned char prefix95[0x438 - 0x95];
    unsigned char status438;
};
extern GameLogic *TheGameLogic;

class AIDozerManager
{
public:
    void rva00599EDC();
    void preEmptivelyBuildDozers();
private:
    _STL::list<int> m_dozers;
};
void AIDozerManager::rva00599EDC()
{
    bool removeFirst = false;
    _STL::list<int>::iterator end = m_dozers.end();
    for (_STL::list<int>::iterator it = m_dozers.begin(); it != end; ++it, end = m_dozers.end())
    {
        Object *object = TheGameLogic->findObjectByID((ObjectID)*it);
        if (!object || (object->status94 & 1) || (object->status438 & 1))
        {
            if (it._M_node != end._M_node->_M_next)
            {
                --it;
                _STL::list<int>::iterator erased = it;
                ++erased;
                m_dozers.erase(erased);
            }
            else
                removeFirst = true;
        }
    }
    if (removeFirst)
        m_dozers.pop_front();
    preEmptivelyBuildDozers();
}
