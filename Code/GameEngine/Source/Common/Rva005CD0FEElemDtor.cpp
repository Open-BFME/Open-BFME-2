// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 005CD0FE..005CD131 is the complete destructor (51B).
// Existing constructor 005CD0DC proves parent0, scalar4, list head8.
// WB Checklist::Impl and rowed drain005CCFD1 prove detached item teardown;
// native second call owns the rowed 005CD032 list-base destructor. The
// original constructor used an 8-byte POD element view; this destructor
// uses the independently rowed 8-byte counted-record list base.
struct Rva005F8F96;
namespace _STL {
template<class T> class allocator;
template<class T,class A> class _List_base {
public: ~_List_base();
private: char head[4];
};
}
namespace StrategicInGameUI { class Checklist { public: class Impl { public: void rva005CCFD1(); }; }; }
class Rva005CD1A9;
class Rva005CD0FEElem {
public: ~Rva005CD0FEElem();
private:
 Rva005CD1A9 *m_parent;
 int m_x;
 _STL::_List_base<Rva005F8F96,_STL::allocator<Rva005F8F96> > m_list;
};
Rva005CD0FEElem::~Rva005CD0FEElem()
{
 reinterpret_cast<StrategicInGameUI::Checklist::Impl *>(this)->rva005CCFD1();
}
