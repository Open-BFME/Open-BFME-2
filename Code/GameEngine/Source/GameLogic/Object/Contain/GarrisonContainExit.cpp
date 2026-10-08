// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
// Substantial transfer from the whole GeneralsMD GarrisonContain.cpp home
// at BFME1 reference revision34f59164. Native47983A..479ADA RET8 and
// independently named WB011A5AF0 prove the target exit-method identity.
// Exit receiver+30 uses contain at-10: slots41 remove;86/88 exit points;
// 20 recalc. Native owner-28; rider AI258; locomotor1F0; set1CC; radiusB8.
// BFME2 adds the two existing opaque passenger-module virtual operations
// and optional rally point, with native teleport/follow-path providers.
// Scalar initial point copies and later whole-point assignments reproduce
// observed SSE/block copies. Inline receiver access preserves the native
// compiler temporary; an explicit cached receiver reverses two spill homes.
// Existing provider dependencies only; no new pins or address globals.
#include <vector>
#include "Lib/Coord3D.h"
enum ExitDoorType { DOOR_1=0 };
enum CommandSourceType { CMD_FROM_AI=2 };
enum PathfindLayerEnum { LAYER_GROUND=1 };
class Locomotor;
class LocomotorSet;
class Object;
class Rva0035149F;
float Cos(float); float Sin(float);
class AICommandInterface { public: void rva0047971C(const Rva0035149F &,Object *,CommandSourceType); };
class AIUpdateInterface {
public:
    const Locomotor *loco() const { return *reinterpret_cast<const Locomotor *const *>(reinterpret_cast<const char *>(this)+0x1F0); }
    const LocomotorSet &set() const { return *reinterpret_cast<const LocomotorSet *>(reinterpret_cast<const char *>(this)+0x1CC); }
    AICommandInterface *commands() { return reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this)+0x20); }
};
class Thing { public: void setOrientation(float); };
class Object:public Thing {
public:
    void teleportTo(const Coord3D *,bool); bool rva002931BA(); void *rva0029439D(); void rva0028ACDC(const Coord3D *);
    const Coord3D *position() const { return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this)+0x38); }
    float orientation() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this)+0x44); }
    float radius() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this)+0xB8); }
    AIUpdateInterface *ai() const { return *reinterpret_cast<AIUpdateInterface *const *>(reinterpret_cast<const char *>(this)+0x258); }
};
class Pathfinder { public: bool IsValidMovementTerrain(PathfindLayerEnum,const Locomotor *,const Coord3D *); void AddObjectToPathfindMap(Object *); bool adjustToPossibleDestination(Object *,const LocomotorSet &,Coord3D *); };
class AI { public: char unknown00[0x10]; Pathfinder *m_pathfinder; Pathfinder *pathfinder() const { return m_pathfinder; } };
extern AI *TheAI;
template<int N> class Rva0047983ASlots:public Rva0047983ASlots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva0047983ASlots<0> {};
class Rva0047983ARemove:public Rva0047983ASlots<41> { public: virtual void remove(Object *,bool); };
class Rva0047983AStart:public Rva0047983ASlots<86> { public: virtual const Coord3D *start(); };
class Rva0047983AEnd:public Rva0047983ASlots<88> { public: virtual const Coord3D *end(); };
class Rva0047983ATeam:public Rva0047983ASlots<20> { public: virtual void recalc(); };
class Rva0047983APassenger:public Rva0047983ASlots<4> { public: virtual void state(int); };
class Rva0047983APassenger38:public Rva0047983ASlots<38> { public: virtual void leaving(Object *); };
class GarrisonContain:public Rva0047983ASlots<8> {
public:
    char *contain() { return reinterpret_cast<char *>(this)-0x10; }
    virtual const Coord3D *rally();
    virtual void exitObjectViaDoor(Object *,ExitDoorType);
    Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x28); }
};
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D &); }
void GarrisonContain::exitObjectViaDoor(Object *exitObj,ExitDoorType)
{
    AIUpdateInterface *ai;
    reinterpret_cast<Rva0047983ARemove *>(contain())->remove(exitObj,false);
    float angle=object()->orientation();
    Coord3D start; const Coord3D *point=reinterpret_cast<Rva0047983AStart *>(contain())->start();
    start.x=point->x; start.y=point->y; start.z=point->z;
    ai=exitObj->ai();
    if (ai) {
        const Locomotor *loco=ai->loco();
        if (loco && !TheAI->pathfinder()->IsValidMovementTerrain(LAYER_GROUND,loco,&start)) {
            float offset=object()->radius();
            start.x-=offset*Cos(angle); start.y-=offset*Sin(angle);
            if (!TheAI->pathfinder()->IsValidMovementTerrain(LAYER_GROUND,loco,&start)) {
                start.x+=2*offset*Cos(angle); start.y+=2*offset*Sin(angle);
                if (!TheAI->pathfinder()->IsValidMovementTerrain(LAYER_GROUND,loco,&start)) start=*object()->position();
            }
        }
    }
    exitObj->teleportTo(&start,true); exitObj->setOrientation(angle);
    TheAI->pathfinder()->AddObjectToPathfindMap(exitObj);
    if (ai && !exitObj->rva002931BA()) {
        Coord3D end; point=reinterpret_cast<Rva0047983AEnd *>(contain())->end();
        end.x=point->x; end.y=point->y; end.z=point->z;
        TheAI->pathfinder()->adjustToPossibleDestination(exitObj,ai->set(),&end);
        _STL::vector<Coord3D> path;
        path.push_back(end);
        const Coord3D *rallyPoint=rally();
        if (rallyPoint) {
            end=*rallyPoint;
            void *module=exitObj->rva0029439D();
            if (module) { reinterpret_cast<Rva0047983APassenger38 *>(module)->leaving(exitObj); reinterpret_cast<Rva0047983APassenger *>(module)->state(0); }
        }
        path.push_back(end);
        void *module=exitObj->rva0029439D();
        if (module) { reinterpret_cast<Rva0047983APassenger38 *>(module)->leaving(exitObj); reinterpret_cast<Rva0047983APassenger *>(module)->state(0); }
        ai->commands()->rva0047971C(*reinterpret_cast<const Rva0035149F *>(&path),object(),CMD_FROM_AI);
        exitObj->rva0028ACDC(&end);
    }
    reinterpret_cast<Rva0047983ATeam *>(contain())->recalc();
}


