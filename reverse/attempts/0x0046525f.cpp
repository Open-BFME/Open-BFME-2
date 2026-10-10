// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.8 date=2026-10-10
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.80 date=2026-10-10 G5-r2: shapes match retail exactly (x87 fld/fsub/fstp
// delta interleave, inline mulss/addss 50.0, component-wise inits, no dx50 locals, ai in
// reg+home like retail); remaining is a UNIFORM one-DWORD home shift (frame 0x54 vs 0x50)
// across all 12B locals + vector#2 at -0x24 not overlaid on end/delta@-0x38. Tried: theAI
// removal, position/targetSource struct-copy (kept: -12 diffs), hoist ai/angle (worse 0x5C,
// reverted), scope flatten (worse 0x78/272, reverted). Retail home map from full disasm:
// vec/elsestart -0x44, end/delta/vec2 -0x38, target -0x2c, saved -0x50, ifstart/displ -0x5c,
// angle -0x18, ai -0x1c. Next: find the extra DWORD (all op totals match 86/86) or force
// vec2 overlay.
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@PAVCoord3D@@@Z
// partial score=0.858652976664883 date=2026-10-10
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.83 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#include <vector>
#include <stdlib.h>
#include "Lib/Coord3D.h"
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
enum ExitDoorType { DOOR_1=0 };
enum CommandSourceType { CMD_FROM_AI=2 };
enum PathfindLayerEnum { LAYER_INVALID=0 };
class LocomotorSet;
class Object;
class Matrix3D;
double Rva000422A0Atan2(float,float);
class Rva0035149F;
class AICommandInterface { public: void rva0036EE16(const Rva0035149F *,Object *,CommandSourceType); void rva0036EF09(const Rva0035149F *,Object *,float,CommandSourceType); };
class AIUpdateInterface {
public:
    void ignoreObstacle(const Object *);
    const LocomotorSet &locomotors() const { return *reinterpret_cast<const LocomotorSet *>(reinterpret_cast<const char *>(this)+0x1CC); }
    void ignoreTime(unsigned frame) { *reinterpret_cast<unsigned *>(reinterpret_cast<char *>(this)+0x178)=frame; }
    AICommandInterface *commands() { return reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this)+0x20); }
    const Coord3D &goal() const { return *reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(*reinterpret_cast<void *const *>(reinterpret_cast<const char *>(this)+0x30))+0x24); }
    __forceinline float goalX() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(*reinterpret_cast<void *const *>(reinterpret_cast<const char *>(this)+0x30))+0x24); }
    __forceinline float goalY() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(*reinterpret_cast<void *const *>(reinterpret_cast<const char *>(this)+0x30))+0x28); }
    __forceinline float goalZ() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(*reinterpret_cast<void *const *>(reinterpret_cast<const char *>(this)+0x30))+0x2C); }
    const Coord3D &position148() const { return *reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this)+0x148); }
};
class Thing { public: void setPosition(const Coord3D *); void setOrientation(float); };
class Object:public Thing {
public:
    bool getSingleLogicalBonePosition(const char *,Coord3D *,Matrix3D *) const;
    int rva0028B511() const; void rva0028B4CE(PathfindLayerEnum);
    void rva0028AE6D(); bool rva002931BA(); void rva0028ACDC(const Coord3D *);
    const Coord3D *position() const { return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this)+0x38); }
    float orientation() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this)+0x44); }
    AIUpdateInterface *ai() const { return *reinterpret_cast<AIUpdateInterface *const *>(reinterpret_cast<const char *>(this)+0x258); }
    bool landKind() const { return (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(*reinterpret_cast<void *const *>(reinterpret_cast<const char *>(this)+4))+0x11F)&0x80)!=0; }
    __forceinline void doorFlags() {
        union ModelWord{unsigned word;unsigned char bytes[4];};
        ModelWord *word=reinterpret_cast<ModelWord*>(reinterpret_cast<char*>(this)+0x10C);
        unsigned flags=word->word;
        if((flags&(1U<<22)) || !(flags&(1U<<21))){word->bytes[2] &= 0xBF;word->word|=1U<<21;rva0028AE6D();}
    }
};
class Pathfinder { public: void AddObjectToPathfindMap(Object *); bool adjustToPossibleDestination(Object *,const LocomotorSet &,Coord3D *); bool getClosestPointOnLand(const Coord3D *,Object *,Coord3D *); };
class AI { public: char unknown00[0x10]; Pathfinder *pathfinder; };
extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern bool g_00E03624;
extern unsigned g_00DBA4E4;
template<int N> class Rva0046525FSlots:public Rva0046525FSlots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva0046525FSlots<0> {};
class Rva0046525FContain:public Rva0046525FSlots<41> { public: virtual void remove(Object *,bool); };
struct Rva0046525FData { char unknown00[0x74]; int exits; unsigned doorTime; };
class OpenContain {
public:
    virtual void exitObjectViaDoor(Object *,ExitDoorType);
    Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x28); }
    Rva0046525FData *data() const { return *reinterpret_cast<Rva0046525FData *const *>(reinterpret_cast<const char *>(this)-0x2C); }
    int &which() { return *reinterpret_cast<int *>(reinterpret_cast<char *>(this)+0x3C); }
    unsigned &countdown() { return *reinterpret_cast<unsigned *>(reinterpret_cast<char *>(this)+0x40); }
    bool rallyExists() const { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this)+0xAC); }
    const Coord3D &rally() const { return *reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this)+0xA0); }
};
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D &); }
void __cdecl Rva00030830FreeAllocation(void*);
namespace _STL { template<> __forceinline void allocator<Coord3D>::deallocate(Coord3D *p, unsigned) const { if (p) Rva00030830FreeAllocation(p); } }
template<> __forceinline void StringBase<char>::concat(char c) { concat(&c,1); }
void OpenContain::exitObjectViaDoor(Object *exitObj,ExitDoorType)
{
    reinterpret_cast<Rva0046525FContain *>(reinterpret_cast<char *>(this)-0x10)->remove(exitObj,false);
    Object *me=object();
    countdown()=data()->doorTime;
    if (countdown()) me->doorFlags();
    int number=data()->exits;
    if (number>0) {
        AsciiString startBone("ExitStart"),endBone("ExitEnd");
        Coord3D end;AIUpdateInterface *ai;
        {Coord3D start;
        if (number>1) {
            char suffix[8]; itoa(which(),suffix,10);
            if (which()<10) { startBone.concat('0'); endBone.concat('0'); }
            which()=which()%number+1;
            startBone.concat(suffix); endBone.concat(suffix);
        }
        me->getSingleLogicalBonePosition(startBone.str(),&start,0);
        me->getSingleLogicalBonePosition(endBone.str(),&end,0);
        float angle=me->orientation();
        exitObj->setPosition(&start); exitObj->setOrientation(angle);
        exitObj->rva0028B4CE((PathfindLayerEnum)me->rva0028B511());
        ai=exitObj->ai();
        TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
        if (ai) {
            ai->ignoreObstacle(exitObj);
            ai->ignoreTime(TheGameLogic->getFrame()+g_00DBA4E4);
            TheAI->pathfinder->adjustToPossibleDestination(exitObj,ai->locomotors(),&end);
        }
        }
        _STL::vector<Coord3D> path;
        path.push_back(end); path.push_back(end);
        if (rallyExists()) path.push_back(rally());
        if (ai) { ai->commands()->rva0036EE16(reinterpret_cast<const Rva0035149F *>(&path),me,CMD_FROM_AI); exitObj->rva0028ACDC(&end); }
    } else {
        if (me->landKind()) {
            AIUpdateInterface *ai;Coord3D saved,target;float angle;
            {Coord3D start; start.x=me->position()->x; start.y=me->position()->y; start.z=me->position()->z;
            if (!TheAI->pathfinder->getClosestPointOnLand(me->position(),me,&start))goto afterLand;
                ai=exitObj->ai();
                if (!ai)goto afterLand;
                    {Coord3D delta,displacement;
                    delta.x=start.x-me->position()->x;
                    saved.x=ai->goalX(); saved.y=ai->goalY();
                    delta.y=start.y-me->position()->y;
                    saved.z=ai->goalZ();
                    delta.z=start.z-me->position()->z;
                    angle=(float)Rva000422A0Atan2(delta.y,delta.x);
                    target.x=me->ai()->position148().x; displacement.x=target.x-me->position()->x;
                    target.y=me->ai()->position148().y; displacement.y=target.y-me->position()->y;
                    target.z=me->ai()->position148().z; displacement.z=target.z-me->position()->z;
                    if (displacement.length()<50.0f) {
                        delta.normalize(); target=start;
                        target.x+=50.0f*delta.x; target.y+=50.0f*delta.y; target.z+=50.0f*delta.z;
                    }
                    }
                    exitObj->setPosition(&start); exitObj->setOrientation(angle);
            }
                    if (!exitObj->rva002931BA()) {
                        _STL::vector<Coord3D> path;
                        path.push_back(target); path.push_back(target); path.push_back(saved);
                        if (g_00E03624) ai->commands()->rva0036EF09(reinterpret_cast<const Rva0035149F *>(&path),me,angle,CMD_FROM_AI);
                        else ai->commands()->rva0036EE16(reinterpret_cast<const Rva0035149F *>(&path),me,CMD_FROM_AI);
                        target=saved;
                    }
                    exitObj->rva0028ACDC(&target);
            afterLand:;
        }
        TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
    }
}
