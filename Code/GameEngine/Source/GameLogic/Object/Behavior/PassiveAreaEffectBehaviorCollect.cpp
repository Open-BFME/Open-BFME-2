// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport
// Retail484C8B..484DF4 RET0; primary PassiveAreaEffectBehavior vtable slot13
// and ctor484A67 establish owner/data+4/object+8/list+24. BF1 clean donor
// PassiveAreaEffectCollect00202490.cpp at575ba2b04 supplies list/filter scan
// semantics; target changes kind bit150 to151, and uses owned opaque query.
#include <list>
#include <algorithm>
// Keep iterator comparisons local, as in the owned list<int> provider.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}
#include "Lib/Coord3D.h"
#include "Common/PartitionRangeQueryCallView.h"
class Player;
class Object {public:int getID()const{return id;}Player *getControllingPlayer()const;char pad[0x38];Coord3D position;char pad44[0x74-0x44];int id;};
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	bool allows(Object *obj);	// 0x00625720
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
// (or none), +0x0C a flag.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BF8FF0: +0x08 the object, +0x0C whether its controlling
// player's +0x5C is 1.
class PartitionFilterRejectBuildings : public Rva000421C8
{
public:
	PartitionFilterRejectBuildings(Object *obj);
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

class Rva002614ECFilter:public Rva000421C8 {
public: Rva002614ECFilter(const void *what,Player *player,bool match):what(what),player(player),match(match){}
virtual bool allow(Object *); const void *what; Player *player; bool match;
};

template<int N>class BitFlags {public:unsigned words[7];};
struct Rva0006EE7A {unsigned words[7];Rva0006EE7A(int,int,int);__forceinline operator const BitFlags<69>&()const{return *(const BitFlags<69>*)this;}};
class Thing {public:bool isAnyKindOf(const BitFlags<69>&)const;};
extern PartitionManager *ThePartitionManager;
struct AreaData {char pad00[8];float radius;char pad0C[0x20-0x0C];char sub20;};
class PassiveAreaEffectBehavior {public:virtual void rva00484C8B();AreaData *data;Object *object;char pad0C[0x24-0x0C];_STL::list<int> ids;};
void PassiveAreaEffectBehavior::rva00484C8B()
{
 Object *owner=object;AreaData *d=data;
 ids.clear();
 Rva00260EB1Filter relationship(owner,4,false);
 Rva0026119DFilter alive;
 Rva002611BFFilter sameMap(owner);
 Rva002614ECFilter match(&d->sub20,owner->getControllingPlayer(),true);
 relationship.link(&alive);relationship.link(&sameMap);relationship.link(&match);
 BfmeWideResult iterator=ThePartitionManager->iterateObjectsInRange(&owner->position,d->radius,0,&relationship,1);
 Object *other=iterator.next();
 if(other)do{
  if(other!=owner&&!((const Thing*)other)->isAnyKindOf(Rva0006EE7A(0,47,151))){
   int id=other->getID();
   if(_STL::find(ids.begin(),ids.end(),id)==ids.end())ids.push_front(other->getID());
  }
  other=iterator.next();
 }while(other);
}
