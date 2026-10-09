// cl: /O1 /arch:SSE /G7 /EHsc /MD /DNDEBUG /ICode/Libraries/Include/Lib /I.
// Native 0036CA3B..0036CB3E RET8; caller0036C8A5 supplies XYZ and desired height.
// WB F30DF0 establishes geometry-copy/collision flow; named GeometryInfo providers
// prove its5C-byte layout and14 radius. Existing neutral filter providers own
// their28-byte masks. Original state and helper names remain unproven.
#include "Coord3D.h"
class GeometryInfo{public:GeometryInfo(const GeometryInfo&);virtual ~GeometryInfo();float getMaxHeightAbovePosition()const;char pad4[0x14-4];float radius;char pad18[0x5c-0x18];};
class Object{public:char pad0[0xa8];GeometryInfo geometry;};
class BfmeFixedStorage0004543D{public:unsigned words[7];};template<int N>class BitFlags{public:unsigned words[7];};extern BitFlags<116> KINDOFMASK_NONE;
class Rva002618A2{public:Rva002618A2*rva002618A2(int,int,int,int);unsigned words[7];};
class Rva000421C8{public:virtual ~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask(){return -1;}Rva000421C8*next;};
class Rva0004584D:public Rva000421C8{public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&);virtual ~Rva0004584D(){}virtual bool allow(Object*);BfmeFixedStorage0004543D a,b;};
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager*ThePartitionManager;
template<int N>class Slots:public Slots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class Slots<0>{};class TerrainView:public Slots<6>{public:virtual float height(float,float,Coord3D*)=0;};class TerrainLogic;extern TerrainLogic*TheTerrainLogic;
class StateMachine{public:char pad0[0x14];Object*owner;};class Rva0036C6AFState{public:char pad0[0x18];StateMachine*machine;bool rva0036CA3B(const Coord3D*,float);};
bool Rva0036C6AFState::rva0036CA3B(const Coord3D*position,float desired){float ground=((TerrainView*)TheTerrainLogic)->height(position->x,position->y,0);if(ground>desired)return false;GeometryInfo ownerGeometry(machine->owner->geometry);Rva002618A2 mask;Object*closest=ThePartitionManager->getClosestObject(position,ownerGeometry.radius,0,&Rva0004584D(*reinterpret_cast<BfmeFixedStorage0004543D*>(mask.rva002618A2(0,7,10,11)),*reinterpret_cast<const BfmeFixedStorage0004543D*>(&KINDOFMASK_NONE)));if(closest){GeometryInfo geometry(closest->geometry);if(geometry.getMaxHeightAbovePosition()+ground>desired)return false;}return true;}
