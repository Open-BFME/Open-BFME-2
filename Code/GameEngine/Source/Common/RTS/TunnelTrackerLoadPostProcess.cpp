// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB 0x01103EB0 names TunnelTracker::LoadPostProcess. Retail 0x004F585C..
// 0x004F5918 proves the contained-object list at +0x10, saved IDs at +0x14,
// and AI pathfinder at +0x10. ZH TunnelTracker.cpp and clean BFME1 donor
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f's loadPostProcess supply the
// save/load purpose and sequence; target-specific calls/layout come from retail.
// The two failures share one throw tail; the enclosing scope lets its eight-byte
// exception reuse the dead object-pointer home, as the retail stack frame does.
#include <list>
#include "../GameLogicObjectLookupView.h"

class XferException
{
public:
    XferException(int, const char *, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tag;
};
class Drawable;
class Object
{
public:
    Drawable *getDrawable() const;
    void leaveGroup();
};
// These two existing matched providers retain their provisional names. The
// first performs the retail Object manager cascade; the second sets Drawable's
// hidden byte at +0x43D and refreshes it. No original name is claimed here.
class Rva0028BAC0Host { public: void rva0028BAC0(); };
class Rva002716Holder { public: void rva00271601(unsigned char); };
class Pathfinder { public: void RemoveObjectFromPathfindMap(Object *); };
class AI
{
public:
    char opaque00[0x10];
    Pathfinder *m_pathfinder;
};
extern AI *TheAI;
extern GameLogic *TheGameLogic;

// Retail uses the existing four-byte list-node carriers for insertion/clear.
// Pointer and ObjectID payloads have the same node width and trivial lifetime.
namespace _STL
{
    template<> void list<int>::push_back(const int &);
    template<> void _List_base<int, allocator<int> >::clear();
}
class TunnelTracker
{
public:
    virtual ~TunnelTracker();
protected:
    virtual void loadPostProcess();
private:
    char opaque04[0x0C];
    _STL::list<Object *> m_containList;
    _STL::list<ObjectID> m_xferContainList;
};

// ?loadPostProcess@TunnelTracker@@MAEXXZ
void TunnelTracker::loadPostProcess()
{
    {
        unsigned count = 0;
        _STL::_List_node_base *sentinel = m_containList._M_node._M_data;
        for (_STL::_List_node_base *node = sentinel->_M_next;
             node != sentinel; node = node->_M_next)
            ++count;
        if (count != 0)
            goto failed;
        Object *object;
        _STL::list<ObjectID>::const_iterator it;
        for (it = m_xferContainList.begin();
             it._M_node != m_xferContainList.end()._M_node; ++it)
        {
            object = TheGameLogic->findObjectByID(*it);
            if (!object)
                goto failed;
            reinterpret_cast<_STL::list<int> *>(&m_containList)->push_back(
                reinterpret_cast<const int &>(object));
            object->leaveGroup();
            reinterpret_cast<Rva0028BAC0Host *>(object)->rva0028BAC0();
            if (object->getDrawable())
                reinterpret_cast<Rva002716Holder *>(object->getDrawable())->rva00271601(1);
            if (TheAI)
                TheAI->m_pathfinder->RemoveObjectFromPathfindMap(object);
        }
        reinterpret_cast<_STL::list<int> *>(&m_xferContainList)->clear();
        return;
    }
failed:
    throw XferException(5, 0);
}
