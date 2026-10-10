// ?rva004BA9E4@TransitionDamageFX@@UAEXH@Z
// partial score=0.9582139148494289 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /ICode/GameEngine/Source
// NEW native4BA9E4..4BAB25 RET4. Owned ctor4BA3EA installs Behavior interface+0C
// table whose slot39 corresponds to this rubble-neighbor initialization callback.
// Original method name unproven; neutral address retained. BF1 clean donor
// TransitionDamageFXRubbleNeighbors.cpp575ba2b04 supplies semantic guide.
// Target expands mask24->28 and kind59->60; native fields moduledata1034,
// record44B/neighborOffset14/OCL10 and resolvedvector secondary+C8 are proven.
#include "Lib/Coord3D.h"
#include "ascii_string.h"
#include "Common/PartitionRangeQueryCallView.h"
extern "C" void*memset(void*,int,unsigned);
class Matrix3D;class ObjectCreationList;
namespace _STL {template<class T>class allocator{};template<class T,class A>class vector{public:T*begin;T*end;T*cap;const T*getBegin()const{return begin;}const T*getEnd()const{return end;}bool empty()const{return begin==end;}~vector();void push_back(const T&);};}
class Thing {public:void convertBonePosToWorldPos(const Coord3D*,const Matrix3D*,Coord3D*,Matrix3D*)const;};
class Object:public Thing {public:unsigned getID()const{return *(const unsigned*)((const char*)this+0x74);}};
class Rva004BA1D0 {public:
 Rva004BA1D0(const Rva004BA1D0&);
 unsigned objectID;_STL::vector<AsciiString,_STL::allocator<AsciiString> >names;
 const ObjectCreationList*ocl;Coord3D neighborOffset;Coord3D oclOffset;
};
struct TransitionDamageFXModuleDataView {char pad00[0x1034];_STL::vector<Rva004BA1D0,_STL::allocator<Rva004BA1D0> >neighbors;};
class BfmeFixedStorage0004543D {public:unsigned words[7];};
class Rva000421C8 {public:Rva000421C8():next(0){}virtual ~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask(){return -1;}Rva000421C8*next;};
class Rva003959FA:public Rva000421C8 {public:Rva003959FA(const BfmeFixedStorage0004543D&);virtual ~Rva003959FA(){}virtual bool allow(Object*);BfmeFixedStorage0004543D mask;};
extern PartitionManager*ThePartitionManager;
class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const TransitionDamageFXModuleDataView *m_moduleData;
	Object *m_object;
};

class BehaviorModuleinterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void rva004BA9E4(int) = 0;
};

// The three-slot table the constructor installs at +0x10 (0x010B2588).
class DamageModuleinterface
{
public:
	virtual void slot00();
};

// Layout from constructor 0x00252F50: interfaces at +0x0C and +0x10, 0x30
// zeroed words from +0x14, and the vector at +0xD4 (allocation 0xE0).
class TransitionDamageFX : public ObjectModule,
	public BehaviorModuleinterface,
	public DamageModuleinterface
{
public:
	virtual void rva004BA9E4(int);

	const TransitionDamageFXModuleDataView *getTransitionDamageFXModuleData() const
	{
		return (const TransitionDamageFXModuleDataView *)m_moduleData;
	}

private:
	unsigned m_particleSystemID[4][12];
	_STL::vector<Rva004BA1D0, _STL::allocator<Rva004BA1D0> >
		resolvedNeighbors;
};

void TransitionDamageFX::rva004BA9E4(int)
{
 
 const TransitionDamageFXModuleDataView*data=getTransitionDamageFXModuleData();
 if(!data)return;
 BfmeFixedStorage0004543D mask;memset(&mask,0,28);mask.words[0]|=1U<<7;mask.words[1]|=1U<<28;
 for(const Rva004BA1D0*it=data->neighbors.getBegin();it!=data->neighbors.getEnd();++it) {
  if(it->names.empty()||!it->ocl)continue;
  const Coord3D&offset=it->neighborOffset;Coord3D pos;pos.x=offset.x;pos.y=offset.y;pos.z=offset.z;
  Object*owner=m_object;
  owner->convertBonePosToWorldPos(&pos,0,&pos,0);
  Object*other=ThePartitionManager->getClosestObject(&pos,30000.f,0,&Rva003959FA(mask));
  if(other&&other!=m_object) {
   Rva004BA1D0 neighbor(*it);neighbor.objectID=other->getID();
   (this?this:this)->resolvedNeighbors.push_back(neighbor);
  }
 }
}
