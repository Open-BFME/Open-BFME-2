// cl: /ICode/Libraries/Include /O1 /arch:SSE /G7 /DNDEBUG /MD
// 83B target boundary 0x002FC95E-0x002FC9B1. The target creates a 0x34
// callback record, gets the destination layer, invokes the rowed Pathfinder
// world-line walk at 0x002F95B7, and copies the record's +0x28 position to
// the destination only when its +0x18 byte says that a change was produced.
// The initializer 0x002EE43A has an independent 97B Ghidra boundary and
// stores this/owner/opaque argument/layer plus three incoming coordinate
// words, returning its receiver. The parity splitter establishes its +4
// object argument. This follows the reference Pathfinder line-query family,
// but the original method name and the second argument's meaning are unknown.
// Keep the method and callback-record view address-derived.
#include "Lib/Coord3D.h"
class Object;
enum PathfindLayerEnum { LAYER_INVALID=0 };
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object*, const Coord3D*); };
extern TerrainLogic* TheTerrainLogic;
class Rva002EE43A {
public:
    Rva002EE43A* rva002EE43A(int,void*,int,int,const Coord3D*);
    char m_lead[0x14];
    PathfindLayerEnum m_layer;
    bool m_changed;
    char m_gap[0xf];
    Coord3D m_result;
};
struct Rva002F600CInfo;
class Pathfinder {
public:
    void rva002FC95E(Object*,int,Coord3D*,const Coord3D*);
    int rva002F95B7(const Coord3D*,const Coord3D*,PathfindLayerEnum,Rva002F600CInfo*);
};
void Pathfinder::rva002FC95E(Object* obj,int arg,Coord3D* destination,const Coord3D* start) {
    Rva002EE43A info;
    info.rva002EE43A((int)this,obj,arg,TheTerrainLogic->getLayerForDestination(obj,destination),start);
    rva002F95B7(destination,start,info.m_layer,(Rva002F600CInfo*)&info);
    if(info.m_changed) *destination=info.m_result;
}
