// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
// Zero Hour Team.cpp TeamFactory::loadPostProcess is the semantic donor.
// Target 0039F7A5..0039F824 (127B), WorldBuilder EEF4D0, and the
// neighbouring TeamFactory::xfer prove the secondary Snapshot receiver.
// BFME2's primary map is at B0, prototype/instance IDs at BC/C0;
// prototype ID0C/list334 and Team ID34 are target reads.
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
 DLINK_ITERATOR<Team> iterate_TeamInstanceList()const {return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList);}
private:
 char unknown00[0x0c]; unsigned id; char unknown10[0x334-0x10]; Team *head;
};
struct PrototypeNode: _STL::_Rb_tree_node_base {unsigned key[2];TeamPrototype *value;};
class SubsystemInterface {public:virtual ~SubsystemInterface();private:char unknown04[8];};
class TeamFactory: public SubsystemInterface,public Snapshot {
protected:virtual void loadPostProcess();
private:
 char unknown10[0xb0-0x10];_STL::_Rb_tree_node_base *header; unsigned count,unknownB8,prototypeID,teamID;
};
void TeamFactory::loadPostProcess() {
 teamID=0;prototypeID=0;
 for(_STL::_Rb_tree_node_base *it=header->left;it!=header;it=_STL::_Rb_global<bool>::_M_increment(it)) {
  TeamPrototype *prototype=((PrototypeNode*)it)->value;
  if(prototype->getID()>=prototypeID)prototypeID=prototype->getID()+1;
  for(DLINK_ITERATOR<Team> iter=prototype->iterate_TeamInstanceList();!iter.done();iter.advance()) {
   Team *team=iter.cur();
   if(team->getID()>=teamID)teamID=team->getID()+1;
  }
 }
}
