// cl: /O1 /G7 /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// Native 0x00599EDC..0x00599F51 (117 bytes): prune the integer list at receiver+0
// using the canonical ObjectID lookup, then run the same receiver's 599D56 worker.
// Native establishes Object bytes 0x94/0x438 bit 0 and the list-node value at +8;
// the owner, worker purpose and flag meanings remain unresolved. The native
// erase/pop_front calls use the already rowed STLport list<int> providers.
#include <list>
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct Rva00599EDCObjectView
{
    char prefix[0x94];
    unsigned char flag94;
    char gap95[0x438-0x95];
    unsigned char flag438;
};

class Rva00599EDC
{
public:
    void rva00599EDC();
    void rva00599D56();
private:
    _STL::list<int> ids;
};

void Rva00599EDC::rva00599EDC()
{
    bool removeFirst = false;
    _STL::list<int>::iterator end=ids.end();
    for (_STL::list<int>::iterator i=ids.begin(); i._M_node!=end._M_node; ++i, end=ids.end())
    {
        Object *object=TheGameLogic->findObjectByID((ObjectID)*i);
        Rva00599EDCObjectView *view=(Rva00599EDCObjectView *)object;
        if (!object || (view->flag94&1) || (view->flag438&1))
        {
            if (i._M_node!=end._M_node->_M_next)
            {
                --i;
                _STL::list<int>::iterator next=i;
                ++next;
                ids.erase(next);
            }
            else
                removeFirst=true;
        }
    }
    if (removeFirst)
        ids.pop_front();
    rva00599D56();
}
