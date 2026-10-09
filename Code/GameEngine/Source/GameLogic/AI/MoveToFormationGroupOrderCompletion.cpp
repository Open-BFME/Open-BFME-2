// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include/Lib 
// stlport
// Native 00547BCF..00547C9A RET4. The matched formation vtable establishes
// this class. Object presence/AI258 and map membership gate the completion
// scan; native flags438 bit0 and range check547B17 filter each member. AI
// query slot110 remains unnamed. Exhaustion caches completion at +44.
// Region O1/G7/SSE preserves native early returns; one const iterator is
// reassigned from find to begin, explaining the retail stack-slot reuse.
#include "Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include <hash_map>
namespace rts {template<class T>struct hash {size_t operator()(const T &v)const{return(size_t)v;}};}
typedef _STL::hash_map<ObjectID,Coord3D,rts::hash<ObjectID>,_STL::equal_to<ObjectID> > ObjectCoord3DMap;
extern GameLogic *TheGameLogic;
class FormationCompletionAI {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual bool slot110();
};
class Object {public:char prefix[0x258];FormationCompletionAI*ai;char gap[0x438-0x25C];unsigned char flags438;};
bool Rva00547B17Check(void*,void*);
class MoveToFormationGroupOrder {public:
char prefix[0x30];ObjectCoord3DMap m_positions;bool m_flag44;
bool rva00547BCF(ObjectID);
};
namespace _STL {
typedef pair<const ObjectID,Coord3D> P;
template __declspec(noinline) _Hashtable_node<P>* hashtable<P,ObjectID,rts::hash<ObjectID>,_Select1st<P>,equal_to<ObjectID>,allocator<P> >::_M_find<ObjectID>(const ObjectID&) const;
}
bool MoveToFormationGroupOrder::rva00547BCF(ObjectID id)
{
if(m_flag44) return true;
Object*object=TheGameLogic->findObjectByID(id);
if(object==0) return true;
if(object->ai==0) return true;
ObjectCoord3DMap::const_iterator test=m_positions.find(id);
if(test==m_positions.end())return true;
test=m_positions.begin();
for(;test!=m_positions.end();++test) {
 Object*object=TheGameLogic->findObjectByID(test->first);
 if(object && !(object->flags438&1) && !Rva00547B17Check(object,(void*)&test->second)) {
 FormationCompletionAI *ai=object->ai;
 if(ai && !ai->slot110())break;
}
}
if(test==m_positions.end())m_flag44=true;
return m_flag44;
}
