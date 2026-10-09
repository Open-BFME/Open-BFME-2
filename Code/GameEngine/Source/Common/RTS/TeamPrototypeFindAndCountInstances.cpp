// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
// Zero Hour Team.cpp provides the instance lookup/count source.
// Native 39D92A42B and 39D95442B prove head334 and ID34;
// established Team two-base member iterator calls next getter5C4AF5.
#include "Common/Snapshot.h"
namespace _STL {
struct _Rb_tree_node_base { bool color; _Rb_tree_node_base *parent,*left,*right; };
template<class Dummy> class _Rb_global { public: static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *); };
}
class MemoryPoolObject { public: virtual ~MemoryPoolObject(); };
class Team : public MemoryPoolObject, public Snapshot {
public:
 Team *dlink_next_TeamInstanceList() const;
 unsigned getID() const { return id; }
private:
 char unknown08[0x34-8]; unsigned id;
};
template<class T> class DLINK_ITERATOR {
public:
 typedef T *(T::*GetNextFunc)() const;
 DLINK_ITERATOR(T *cur,GetNextFunc next):m_cur(cur),m_next(next) {}
 void advance() { if(m_cur) m_cur=(m_cur->*m_next)(); }
 bool done()const{return m_cur==0;}
 T *cur()const{return m_cur;}
private: T *m_cur; GetNextFunc m_next;
};
class TeamPrototype {
public:
 unsigned getID()const{return id;}
 Team *findTeamByID(unsigned id);
 int countTeamInstances();
 DLINK_ITERATOR<Team> iterate_TeamInstanceList()const {return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList);}
private:
 char unknown00[0x0c]; unsigned id; char unknown10[0x334-0x10]; Team *head;
};

Team *TeamPrototype::findTeamByID(unsigned id) {
 for(DLINK_ITERATOR<Team> iter=iterate_TeamInstanceList();!iter.done();iter.advance())
  if(iter.cur()->getID()==id)return iter.cur();
 return 0;
}
int TeamPrototype::countTeamInstances() {
 int count=0;
 for(DLINK_ITERATOR<Team> iter=iterate_TeamInstanceList();!iter.done();iter.advance())++count;
 return count;
}
