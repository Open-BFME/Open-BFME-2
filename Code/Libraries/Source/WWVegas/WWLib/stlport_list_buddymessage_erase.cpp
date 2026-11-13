// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 0x004168D3 unlinks a message node and calls the rowed BuddyMessage cleanup.
#include <stdlib.h>
#include <list>

#include "../../../../GameEngine/Include/Common/BuddyMessage.h"

struct BfmeStringRecord00415F34
{
    BuddyMessage message;
};

namespace _STL
{
template <> list<BfmeStringRecord00415F34>::iterator
list<BfmeStringRecord00415F34>::erase(iterator position)
{
    _List_node_base *next = position._M_node->_M_next;
    _List_node_base *previous = position._M_node->_M_prev;
    previous->_M_next = next;
    next->_M_prev = previous;
    ((_List_node<BfmeStringRecord00415F34> *)position._M_node)->_M_data.message.~BuddyMessage();
    free(position._M_node);
    return iterator((_List_node<BfmeStringRecord00415F34> *)next);
}
}
template _STL::list<BfmeStringRecord00415F34>::iterator _STL::list<BfmeStringRecord00415F34>::erase(iterator);
