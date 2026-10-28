// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

// WB1628A20 names CanSwapArmyMembers; native5F516D..5F523F is210B.
// The genuine update caller5F5537..5F55D6 preserves its first/second selections
// in ESI/EDI across this static call. A real set::empty accessor, visible STLport
// helpers and the movie-clip getter reproduce that ABI without register tricks.
// Target selection header/count are+10/+14, integer node payload+10; the28B
// selection constructor5F2381 and WB iterator accesses establish the set view.
// WB1628ED0 establishes update control flow; wrapper/class identity stays neutral.
// Existing opaque key iterator and four-byte ScienceType reserve retain their
// already-owned provider symbols. No new alias, pin or volatile field is used.

#include <vector>
#include <map>
#include <set>
void __cdecl Rva00030830GameFree(void *);
namespace _STL { template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,size_t) const { if(p) Rva00030830GameFree(p); } }
struct Rva005FSelectionView {char unknown[16];_STL::set<int> members;};
class Rva005FArmyView {public:char pad00[0x20];int id;__forceinline int getID(){return id;}};
struct Rva005E59FCKeyIterator {
 typedef _STL::bidirectional_iterator_tag iterator_category;
 typedef int value_type;
 typedef int difference_type;
 typedef int *pointer;
 typedef int &reference;
 _STL::_Rb_tree_node_base *node;
 int &operator*() const {return *(int*)((char*)node+16);}
 Rva005E59FCKeyIterator &operator++(){node=_STL::_Rb_global<bool>::_M_increment(node);return *this;}
 Rva005E59FCKeyIterator &operator--(){node=_STL::_Rb_global<bool>::_M_decrement(node);return *this;}
 bool operator==(const Rva005E59FCKeyIterator&b)const{return node==b.node;}
 bool operator!=(const Rva005E59FCKeyIterator&b)const{return node!=b.node;}
};


namespace _STL {
template<> int *copy(Rva005E59FCKeyIterator,Rva005E59FCKeyIterator,int *);
template<> inline __declspec(noinline) int *__uninitialized_copy(Rva005E59FCKeyIterator first,Rva005E59FCKeyIterator last,int *result,const __true_type&) {
 _Rb_tree_node_base *n=first.node; int *d=result;
 for(;n!=last.node;n=_Rb_global<bool>::_M_increment(n),++d) {if(d) *d=*(int*)((char*)n+16);}
 return d;
}
}
// The canonical four-byte reserve provider owns the ScienceType spelling;
// only its measured three-pointer header and four-byte allocation stride are
// borrowed for this integer-key buffer, with no new alias pin.
enum ScienceType { SCIENCE_NONE=0 };

class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002B6C9F {public:bool rva002B6C9F(int,int,int);};
class Rva002B6D18 {public:bool rva002B6D18(int,int,int,int);};
namespace StrategicInGameUI {
static __declspec(noinline) bool CanSwapArmyMembers(Rva005FArmyView*source,const Rva005FSelectionView*first,Rva005FArmyView*target,const Rva005FSelectionView*second){
 if(first->members.empty() || second->members.empty())return false;
 _STL::forward_iterator_tag marker;
 _STL::vector<int> firstIds;
 ((_STL::vector<ScienceType>*)&firstIds)->reserve(first->members.size());
 Rva005E59FCKeyIterator begin={first->members.begin()._M_node},end={first->members.end()._M_node};
 firstIds._M_assign_aux(begin,end,marker);
 _STL::vector<int> secondIds;
 ((_STL::vector<ScienceType>*)&secondIds)->reserve(second->members.size());
 Rva005E59FCKeyIterator begin2={second->members.begin()._M_node},end2={second->members.end()._M_node};
 secondIds._M_assign_aux(begin2,end2,marker);
 return ((Rva002B6D18*)TheLivingWorldLogic)->rva002B6D18((int)source,(int)&firstIds,(int)target,(int)&secondIds);
}

} // namespace StrategicInGameUI

// WorldBuilder StrategicInGameUI::CanMoveArmyMembers, WB VA 0x01628580 (callgraph lead, score 1.0).
namespace StrategicInGameUI {
static __declspec(noinline) bool CanMoveArmyMembers(const Rva005FSelectionView*first,Rva005FArmyView*source,Rva005FArmyView*target){
 if(first->members.empty())return false;
 _STL::forward_iterator_tag marker;
 _STL::vector<int> ids((const _STL::allocator<int>&)marker);((_STL::vector<ScienceType>*)&ids)->reserve(first->members.size());
 Rva005E59FCKeyIterator begin={first->members.begin()._M_node},end={first->members.end()._M_node};
 ids._M_assign_aux(begin,end,(const _STL::forward_iterator_tag&)marker);
 return ((Rva002B6C9F*)TheLivingWorldLogic)->rva002B6C9F((int)source,(int)&ids,(int)target);
}
}

struct Rva005FEntryView {char prefix[16];Rva005FArmyView*army;Rva005FSelectionView selection;};
class Rva005F4B57 {public:void rva005F4B57();};
class Rva005FD8A9 {public:void rva005FD8A9(bool);};
class Rva005FD8B1 {public:void rva005FD8B1(bool);};
class Rva005FD8B9 {public:void rva005FD8B9(bool);};
class Rva005FD4F7 {public:void rva005FD4F7();};
class Rva005F5537 {public:void rva005F5537();char prefix[12];Rva005FEntryView *source,*target;void *clip;bool dirty;void *getClip(){return clip;}};
void Rva005F5537::rva005F5537(){
 ((Rva005F4B57*)source)->rva005F4B57();
 ((Rva005F4B57*)target)->rva005F4B57();
 if(getClip()){
  if(dirty){
   Rva005FArmyView *army1=source->army;
   Rva005FSelectionView &first=source->selection;
   Rva005FArmyView *army2=target->army;
   Rva005FSelectionView &second=target->selection;
   ((Rva005FD8A9*)getClip())->rva005FD8A9(StrategicInGameUI::CanMoveArmyMembers(&first,army1,army2));
   ((Rva005FD8B1*)getClip())->rva005FD8B1(StrategicInGameUI::CanMoveArmyMembers(&second,army2,army1));
   ((Rva005FD8B9*)getClip())->rva005FD8B9(StrategicInGameUI::CanSwapArmyMembers(army1,&first,army2,&second));
   dirty=false;
  }
  ((Rva005FD4F7*)getClip())->rva005FD4F7();
 }
}

class GameMessage {public:void appendIntegerArgument(int);};
class MessageStream {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0a();
virtual void slot0b();
virtual void slot0c();
virtual void slot0d();
virtual void slot0e();
virtual void slot0f();
virtual void slot10();
virtual void slot11();
virtual GameMessage*appendMessage(int);};
extern MessageStream*TheMessageStream;
// WorldBuilder StrategicInGameUI::SendSwapArmyMembersMessage; rowed at 0x005E5DF5 in StrategicUiArmyDragDrop.cpp.
namespace StrategicInGameUI {
static __declspec(noinline) void SendSwapArmyMembersMessage(int army1,const Rva005FSelectionView*first,int army2,const Rva005FSelectionView&second) {
 GameMessage*message=TheMessageStream->appendMessage(0x6af);
 message->appendIntegerArgument(army1);
 message->appendIntegerArgument(first->members.size());
 _STL::_Rb_tree_node_base*firstEnd=first->members.end()._M_node;
 for(_STL::_Rb_tree_node_base*n=firstEnd->_M_left;n!=firstEnd;n=_STL::_Rb_global<bool>::_M_increment(n))message->appendIntegerArgument(*(int*)((char*)n+16));
 message->appendIntegerArgument(army2);
 message->appendIntegerArgument(second.members.size());
 _STL::_Rb_tree_node_base*secondEnd=second.members.end()._M_node;
 for(_STL::_Rb_tree_node_base*n=secondEnd->_M_left;n!=secondEnd;n=_STL::_Rb_global<bool>::_M_increment(n))message->appendIntegerArgument(*(int*)((char*)n+16));
}
}

// WB 1628960 calls strict-pointer operator-> (16295C0) four times,
// in source-army / source-selection / target-army / target-selection order.
struct Rva005FEntryPtr {Rva005FEntryView*value;Rva005FEntryView*operator->()const{return value;}};
struct Rva005F53A2Context {char prefix[12];Rva005FEntryPtr source,target;};
class Rva005F53A2 {public:void SwapArmyMembers();char prefix[8];Rva005F53A2Context*context;Rva005F53A2Context*getContext(){return context;}};
void Rva005F53A2::SwapArmyMembers(){
 Rva005F53A2Context*owner=getContext();
 Rva005FArmyView*source=owner->source->army;
 Rva005FSelectionView&first=getContext()->source->selection;
 Rva005FArmyView*target=getContext()->target->army;
 Rva005FSelectionView&second=owner->target->selection;
 if(StrategicInGameUI::CanSwapArmyMembers(source,&first,target,&second))
  StrategicInGameUI::SendSwapArmyMembersMessage(source->getID(),&first,target->getID(),second);
}
