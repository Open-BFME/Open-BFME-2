// 0x004BA9E4 (321B): TransitionDamageFX update step over the neighbour list. /Oa (assume no aliasing)
// is what gives retail's EBX/EDI roles for the module data and the iterator receiver; the region
// default supplies /O1 /arch:SSE /G7.
// ?mapLoadPostProcess@TransitionDamageFX@@UAEXPBVDict@@@Z
// partial score=0.9582139148494289 date=2026-10-13
// ?mapLoadPostProcess@TransitionDamageFX@@UAEXPBVDict@@@Z
// partial score=0.9582139148494289 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /ICode/GameEngine/Source /Oa /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// NEW native4BA9E4..4BAB25 RET4. Owned ctor4BA3EA installs Behavior interface+0C
// table whose slot 45 is this rubble-neighbor initialization callback.
// Named mapLoadPostProcess: slot 45 of the +0x0C table 0x00C59A30, as in the
// sibling tables (CastleMemberBehavior, ThreatFinderUpdate, CastleBehavior). BF1 clean donor
// TransitionDamageFXRubbleNeighbors.cpp575ba2b04 supplies semantic guide.
// Target expands mask24->28 and kind59->60; native fields moduledata1034,
// record44B/neighborOffset14/OCL10 and resolvedvector secondary+C8 are proven.
#include "Lib/Coord3D.h"
#include "ascii_string.h"
#include "Common/PartitionRangeQueryCallView.h"
#include <string.h>
#include <vector>
// Use the existing string-vector destructor instead of emitting this unit's
// conflicting buffer-base destructor and its unused cleanup helpers.
namespace _STL {template <> vector<AsciiString, allocator<AsciiString> >::~vector();}
class Matrix3D;class ObjectCreationList;class Dict;
// Bind the append to the rowed vector<Rva004BA1D0>::push_back instead of
// emitting this unit's own copy of the header's inline growth path.
class Rva004BA1D0;
namespace _STL {template <> void vector<Rva004BA1D0, allocator<Rva004BA1D0> >::push_back(const Rva004BA1D0 &);}
#include "../../../Common/Thing/thing.h"
class Object:public Thing {public:unsigned getID()const{return *(const unsigned*)((const char*)this+0x74);}};
class Rva004BA1D0
{
public:
	Rva004BA1D0(const Rva004BA1D0 &other);
	int m_objectID; // +0x00
	_STL::vector<AsciiString> m_subObjects; // +0x04
	const ObjectCreationList *m_ocl; // +0x10
	Coord3D m_neighborOffset; // +0x14
	Coord3D m_oclOffset; // +0x20
};
struct TransitionDamageFXModuleDataView {char pad00[0x1034];_STL::vector<Rva004BA1D0,_STL::allocator<Rva004BA1D0> >neighbors;};
class BfmeFixedStorage0004543D {public:unsigned words[7];};
#include "../../../../Include/GameLogic/PartitionFilter.h"
class Rva003959FA:public Rva000421C8 {public:Rva003959FA(const BfmeFixedStorage0004543D&);virtual ~Rva003959FA(){}virtual bool allow(Object*);BfmeFixedStorage0004543D mask;};
extern PartitionManager*ThePartitionManager;
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleinterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void mapLoadPostProcess(const Dict *) = 0;
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
	virtual void mapLoadPostProcess(const Dict *);

	const TransitionDamageFXModuleDataView *getTransitionDamageFXModuleData() const
	{
		return (const TransitionDamageFXModuleDataView *)m_moduleData;
	}

private:
	unsigned m_particleSystemID[4][12];
	_STL::vector<Rva004BA1D0, _STL::allocator<Rva004BA1D0> >
		resolvedNeighbors;
};

void TransitionDamageFX::mapLoadPostProcess(const Dict *)
{
 
 const TransitionDamageFXModuleDataView*data=getTransitionDamageFXModuleData();
 if(!data)return;
 BfmeFixedStorage0004543D mask;memset(&mask,0,28);mask.words[0]|=1U<<7;mask.words[1]|=1U<<28;
 for(const Rva004BA1D0*it=data->neighbors.begin();it!=data->neighbors.end();++it) {
  if(it->m_subObjects.empty()||!it->m_ocl)continue;
  const Coord3D&offset=it->m_neighborOffset;Coord3D pos;pos.x=offset.x;pos.y=offset.y;pos.z=offset.z;
  Object*owner=m_object;
  owner->convertBonePosToWorldPos(&pos,0,&pos,0);
  Object*other=ThePartitionManager->getClosestObject(&pos,30000.f,0,&Rva003959FA(mask));
  if(other&&other!=m_object) {
   Rva004BA1D0 neighbor(*it);neighbor.m_objectID=other->getID();
   ((_STL::vector<Rva004BA1D0> *)&(this?this:this)->resolvedNeighbors)->push_back(neighbor);
  }
 }
}
