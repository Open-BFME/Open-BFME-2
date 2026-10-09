// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// StrafeAreaUpdate factory/ctor3A4D23 and native3A4F21..3A4FDA RET8
// establish the receiver. WB matching helper initializes two coordinates,
// phase word, state and orientation then moves the aircraft AI returned
// by slot98; original helper and AI-view names remain unasserted.
// No clean BF1/ZH counterpart exists for this BFME strafe helper; WB and
// adjacent matched BFME2 layout are the reconstruction evidence.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
enum CommandSourceType {CMD_FROM_AI=2};
class AICommandInterface {public:void aiMoveToPosition(const Coord3D *,CommandSourceType);};
template<int N> class StrafeAISlots:public StrafeAISlots<N-1> {public:virtual void gap(char (*)[N])=0;};template<> class StrafeAISlots<0> {};
class AIUpdateInterface;
class AIUpdateInterface:public StrafeAISlots<98> {public:virtual AIUpdateInterface *rvaSlot98()=0;char pad[0x1C];AICommandInterface commands;};
class Thing {public:void setOrientation(float);};
class Object:public Thing {public:char pad[0x258];AIUpdateInterface *ai;};
extern "C" float atan2f(float,float);
struct StrafeAreaUpdateModuleData {char pad[0x1C];unsigned word1C;};
struct StrafeDirection {float x,y,z;
 __forceinline StrafeDirection(const Coord3D &v):x(v.x),y(v.y),z(v.z) {}
 __forceinline void sub(const Coord3D &v){x-=v.x;y-=v.y;z-=v.z;}
};
class StrafeAreaUpdate {public:
 bool rva003A4F21(const Coord3D *,const Coord3D *);
 char pad00[4];const StrafeAreaUpdateModuleData *data;Object *object;char pad0C[0x14];Coord3D target,start;unsigned word38,state;bool started;
};
bool StrafeAreaUpdate::rva003A4F21(const Coord3D *from,const Coord3D *to) {
 const StrafeAreaUpdateModuleData *d=data;
 AIUpdateInterface *ai=object->ai;
 if(!ai) return false;
 AIUpdateInterface *aircraft=ai->rvaSlot98();
 if(!aircraft) return false;
 target=*to;start=*from;word38=d->word1C;state=0;started=false;
 StrafeDirection direction(target);direction.sub(start);
 float angle=atan2f(direction.y,direction.x);
 object->setOrientation(angle);
 aircraft->commands.aiMoveToPosition(&target,CMD_FROM_AI);
 return true;
}
