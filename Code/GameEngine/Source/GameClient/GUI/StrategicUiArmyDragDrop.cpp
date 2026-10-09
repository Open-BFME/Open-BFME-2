// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

// Native5E5DF5..5E5E7A,5F50E9..5F516D and two mirrored113B
// callbacks5F52C0/5F5331. WB15FEE20/1628580 independently name
// StrategicInGameUI::SendSwapArmyMembersMessage/CanMoveArmyMembers.
// Their private retail ABI is reproduced by static definitions BEFORE their
// callers: MSVC assigns the selected-members view to EAX/ECX respectively
// and leaves the remaining arguments for caller cleanup. The original C++
// method signatures and enclosing callback classes are not asserted.
// Target trees supply integer keys at node16, header/count at view10/14.
// The owned constructor5F2381 combines16B listener storage with the12B
// STLport set header, establishing the28B temporary used by both callbacks.
// Full-expression temporary construction retains the returned EAX address;
// scalar ID getters retain native EDI/ESI loads before argument pushes.
// Minimal STLport provider declarations preserve existing symbol owners.
// One stateless marker byte is loaned to allocator and forward-tag interfaces;
// their rowed providers do not read marker state. C++-linkage free retains the
// native EH state reset. The pointer read view is volatile to express the two
// native fetches at this+8, without asserting the original field qualifier.

void __cdecl free(void*);
namespace _STL {
template<class T>class allocator {public:allocator(){} ~allocator(){} static __forceinline void deallocate(T*p,unsigned){free(p);}};
struct input_iterator_tag {}; struct forward_iterator_tag:input_iterator_tag {};
template<class T,class A=allocator<T> >class _Vector_base {public:_Vector_base(const A&); T*start,*finish,*limit;};
template<class T,class A=allocator<T> >class vector;
template<>class vector<int,allocator<int> >:public _Vector_base<int,allocator<int> > {public:
__forceinline vector(const allocator<int>&a):_Vector_base<int,allocator<int> >(a){}~vector(){if(start)allocator<int>::deallocate(start,0);}
void reserve(unsigned int);
template<class Iter>void _M_assign_aux(Iter,Iter,const forward_iterator_tag&);
};
struct _Rb_tree_node_base {int color;_Rb_tree_node_base*parent,*left,*right;};
template<class Dummy>struct _Rb_global {static _Rb_tree_node_base*_M_increment(_Rb_tree_node_base*);};
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
struct Rva005FSelectionView {char unknown[16];_STL::_Rb_tree_node_base*root;int count;char comparatorStorage[4];};
static __declspec(noinline) void Rva005E5DF5SendSwapArmyMembers(int army1,const Rva005FSelectionView*first,int army2,const Rva005FSelectionView&second) {
 GameMessage*message=TheMessageStream->appendMessage(0x6af);
 message->appendIntegerArgument(army1);
 message->appendIntegerArgument(first->count);
 _STL::_Rb_tree_node_base*firstEnd=first->root;
 for(_STL::_Rb_tree_node_base*n=firstEnd->left;n!=firstEnd;n=_STL::_Rb_global<bool>::_M_increment(n))message->appendIntegerArgument(*(int*)((char*)n+16));
 message->appendIntegerArgument(army2);
 message->appendIntegerArgument(second.count);
 _STL::_Rb_tree_node_base*secondEnd=second.root;
 for(_STL::_Rb_tree_node_base*n=secondEnd->left;n!=secondEnd;n=_STL::_Rb_global<bool>::_M_increment(n))message->appendIntegerArgument(*(int*)((char*)n+16));
}
class Rva005FArmyView {public:char pad00[0x20];int id;__forceinline int getID(){return id;}};
struct Rva005E59FCKeyIterator {_STL::_Rb_tree_node_base*node;};

// The canonical four-byte reserve provider owns the ScienceType spelling;
// only its measured three-pointer header and four-byte allocation stride are
// borrowed for this integer-key buffer, with no new alias pin.
enum ScienceType { SCIENCE_NONE=0 };
namespace _STL {template<>class vector<ScienceType,allocator<ScienceType> > {public:void reserve(unsigned);};}
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002B6C9F {public:bool rva002B6C9F(int,int,int);};
static __declspec(noinline) bool Rva005F50E9CanMoveArmyMembers(const Rva005FSelectionView*first,Rva005FArmyView*source,Rva005FArmyView*target){
 if(first->count==0)return false;
 _STL::forward_iterator_tag marker;
 _STL::vector<int> ids((const _STL::allocator<int>&)marker);((_STL::vector<ScienceType>*)&ids)->reserve(first->count);
 Rva005E59FCKeyIterator begin={first->root->left},end={first->root};
 ids._M_assign_aux(begin,end,(const _STL::forward_iterator_tag&)marker);
 return ((Rva002B6C9F*)TheLivingWorldLogic)->rva002B6C9F((int)source,(int)&ids,(int)target);
}
struct Rva005FEntryView {char prefix[16];Rva005FArmyView*army;Rva005FSelectionView selection;};
struct Rva005FContextView {char prefix[12];Rva005FEntryView*source;Rva005FEntryView*target;};
class Rva005F23B2 {public:~Rva005F23B2();};
class Rva005F2381 {public:Rva005F2381();__forceinline ~Rva005F2381(){((Rva005F23B2*)this)->~Rva005F23B2();}char bytes[28];};
class Rva005F52C0 {public:void rva005F52C0();void rva005F5331();char unknown[8];Rva005FContextView*volatile context;};
void Rva005F52C0::rva005F52C0(){
 Rva005FArmyView*source=context->source->army;Rva005FContextView*owner=context;Rva005FEntryView*entry=owner->source;Rva005FArmyView*target=owner->target->army;
 Rva005FSelectionView&first=entry->selection;
 if(Rva005F50E9CanMoveArmyMembers(&first,source,target)){
  Rva005E5DF5SendSwapArmyMembers(source->getID(),&first,target->getID(),*(const Rva005FSelectionView*)&Rva005F2381());
 }
}

void Rva005F52C0::rva005F5331(){
 Rva005FArmyView*source=context->target->army;Rva005FContextView*owner=context;Rva005FEntryView*entry=owner->target;Rva005FArmyView*target=owner->source->army;
 Rva005FSelectionView&first=entry->selection;
 if(Rva005F50E9CanMoveArmyMembers(&first,source,target)){
  Rva005E5DF5SendSwapArmyMembers(source->getID(),&first,target->getID(),*(const Rva005FSelectionView*)&Rva005F2381());
 }
}
