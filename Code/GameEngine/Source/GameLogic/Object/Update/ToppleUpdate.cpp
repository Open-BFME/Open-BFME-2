// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// BF1 ToppleUpdateApplyTopplingForce.cpp9cbfb551 and ZH ToppleUpdate.cpp
// guide purpose/control flow; target4A83D7..4A86E7 supplies784B and all
// BFME2 layouts/model masks. Target ctor4A8201/xfer4A86E7 prove58B module.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "matrix3d.h"
#pragma function(memset)
extern "C" void *memset(void *,int,unsigned);
#include <math.h>
extern "C" float atan2f(float,float);
float normalizeAngle(float);float Cos(float);float Sin(float);
static const float PI=3.14159265359f;
static const float ANGULAR_LIMIT=PI/2-PI/64;
inline float stdAngleDiff(float a1,float a2){return normalizeAngle(a1-a2);}
static float angleClosestTo(float a1,float a2,float desired) {
 a1=normalizeAngle(a1);a2=normalizeAngle(a2);
 return fabs(stdAngleDiff(desired,a1))<fabs(stdAngleDiff(desired,a2))?a1:a2;
}
// The donor and retail use x87 current-mode rounding; a C cast emits a
// different conversion sequence. Only this two-instruction helper needs asm.
__forceinline long fast_float2long_round(float f) {
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((float)floor(x)))
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
enum DamageType {DAMAGE_UNRESISTABLE=8};enum DeathType {DEATH_NORMAL=0};
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};extern NameKeyGenerator *TheNameKeyGenerator;
class Object;class Team;class ThingTemplate;
class ClientUpdateModule {public:virtual void s0()=0;virtual void s1()=0;virtual void s2()=0;virtual void s3()=0;virtual NameKeyType getModuleNameKey()const=0;char pad04[0x1E];bool sway;};
class Drawable {public:void rva00272A02(bool);char pad[0x150];ClientUpdateModule **modules;char pad154[0x10E];unsigned char flags262;};
class Thing {public:const Matrix3D *getTransformMatrix()const{return (const Matrix3D*)((const char*)this+8);}void setTransformMatrix(const Matrix3D*);Drawable *getDrawable()const;void setPosition(const Coord3D *);void setOrientation(float);};
class ToppleBits {public:unsigned words[19];
 __forceinline unsigned mask(int bit)const{return words[bit>>5]&(1U<<(bit&31));}
 __forceinline bool test(int bit)const{return mask(bit)!=0;}
 __forceinline void set(int bit){words[bit>>5]|=1U<<(bit&31);}
};
class Object:public Thing {public:
 void kill(DamageType,DeathType);void rva0028AE6D();
 char pad00[0x38];Coord3D position;float angle;char pad48[0x2C];unsigned id;char pad78[0x94];ToppleBits conditions;char pad158[0x2E0];unsigned char status438;
 __forceinline void setCondition0(){if(!conditions.mask(0)){conditions.set(0);rva0028AE6D();}}
};
class ScriptEngine {public:void rva00357340(void *,Coord3D *);};extern ScriptEngine *TheScriptEngine;
class Pathfinder {public:void RemoveObjectFromPathfindMap(Object *);};
class AI {public:char pad[0x10];Pathfinder *pathfinder;};extern AI *TheAI;
class FXList {public:static void doFXObj(const FXList *,const Object *,const Object *);};
struct CreateMask {unsigned words[4];};
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString &);Object *newObject(const ThingTemplate *,Team *,const CreateMask *,bool);};extern ThingFactory *TheThingFactory;
struct ToppleUpdateModuleData {char pad[8];const FXList *toppleFX,*bounceFX;AsciiString stump;float initialVelocity,initialAccel,bounceVelocity,minSpeed;bool killWhenToppled,killWhenStart,killStump,leftRight,reorient;};
class ObjectModule {public:virtual ~ObjectModule();const ToppleUpdateModuleData *data;Object *object;};
class BehaviorModuleInterface {public:virtual void behaviorModuleInterfaceSlot();};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class UpdateModule:public ObjectModule,public BehaviorModuleInterface,public UpdateModuleInterface {public:virtual ~UpdateModule();char pad14[0xC];protected:__forceinline Object *getObject()const{return object;}void setWakeFrame(Object *,UpdateSleepTime);};
class CollideModuleInterface {public:virtual void onCollide(Object *,const Coord3D *,const Coord3D *)=0;};
class ToppleUpdate:public UpdateModule,public CollideModuleInterface {public:virtual UpdateSleepTime update();virtual void onCollide(Object *,const Coord3D *,const Coord3D *);void applyTopplingForce(const Coord3D *,float,unsigned);float velocity,acceleration;Coord3D direction;int state;float accumulation,angleDelta;int countDelta;bool bounceFX;unsigned options,stumpID;float state54;};
void ToppleUpdate::applyTopplingForce(const Coord3D *toppleDirection,float toppleSpeed,unsigned opts) {
 if(object->status438&1)return;
 const ToppleUpdateModuleData *d=data;
 if(toppleSpeed<d->minSpeed)toppleSpeed=d->minSpeed;
 Drawable *draw=object->getDrawable();setWakeFrame(getObject(),UPDATE_SLEEP_NONE);
 if(d->killWhenStart){setWakeFrame(object,UPDATE_SLEEP_FOREVER);object->kill(DAMAGE_UNRESISTABLE,DEATH_NORMAL);return;}
 direction=*toppleDirection;direction.normalize();TheScriptEngine->rva00357340(getObject(),&direction);
 velocity=toppleSpeed*d->initialVelocity;acceleration=toppleSpeed*d->initialAccel;state=1;options=opts;
 static NameKeyType sway=TheNameKeyGenerator->nameToKey("SwayClientUpdate");
 ClientUpdateModule **modules=draw->modules;
 if(modules){while(*modules){if((*modules)->getModuleNameKey()==sway)(*modules)->sway=0;++modules;}}
 float currentAngle=normalizeAngle(object->angle);
 float toppleAngle=normalizeAngle(atan2f(direction.y,direction.x));
 if(d->leftRight){toppleAngle=angleClosestTo(currentAngle+PI/2,currentAngle-PI/2,toppleAngle);direction.x=Cos(toppleAngle);direction.y=Sin(toppleAngle);TheAI->pathfinder->RemoveObjectFromPathfindMap(object);}
 float desiredAngle=angleClosestTo(toppleAngle+PI/2,toppleAngle-PI/2,currentAngle);
 countDelta=REAL_TO_INT_FLOOR(ANGULAR_LIMIT/(velocity*(float)2));
 if(countDelta<1)countDelta=1;
 angleDelta=(desiredAngle-currentAngle)/countDelta;object->setCondition0();FXList::doFXObj(d->toppleFX,object,0);
 if(!d->stump.isEmpty()) {
  const ThingTemplate *t=TheThingFactory->findTemplate(d->stump);
  CreateMask mask;memset(&mask,0,sizeof(mask));Object *stump=TheThingFactory->newObject(t,0,&mask,false);
  if(stump){stump->setPosition(&object->position);stump->setOrientation(object->angle);stumpID=stump->id;
   Drawable *ownerDraw=object->getDrawable();
   if(ownerDraw && (ownerDraw->flags262&1)) {
    if(!stump->conditions.mask(80)){stump->conditions.set(80);stump->rva0028AE6D();}
   }
  }
 }
}

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class GeometryInfo {public:float getMaxHeightAbovePosition()const;};
void Rva004A82BAAttemptDamage(Object *);
// BF1 ToppleUpdateBfme.cpp at donor575ba2b04743f190f069805fbdc59936123c45da
// supplies the update's semantic/control-flow spine and progressive bounce
// damping, consistent with WB121EB00 ToppleUpdate::update. Native BFME2
// independently supplies matrix8, geometryA8, module/subobject offsets, and
// all calls. ObjectModule / Behavior / Update / Collide interfaces are the
// same target-proven graph as StructureToppleUpdate; update receives +10.
// Whole native boundary is 4A878F..4A8D06 (1399B), ending in RET. The older
// 1416B inventory extent also includes the separate 17B field parser at
// 4A8D06 (argument load / MultiIniFieldParse::add / RET).
UpdateSleepTime ToppleUpdate::update()
{
	if ((state == 0) || (state == 2))
		return UPDATE_SLEEP_FOREVER;

	const ToppleUpdateModuleData *d = data;
	const float VELOCITY_BOUNCE_LIMIT = 0.01f;
	const float VELOCITY_BOUNCE_SOUND_LIMIT = 0.03f;

	Object *obj = object;
	if (countDelta)
	{
		Matrix3D xfrm = *obj->getTransformMatrix();
		xfrm.In_Place_Pre_Rotate_Z(angleDelta);
		obj->setTransformMatrix(&xfrm);
		--countDelta;
	}

	float curVelToUse = velocity;
	if (accumulation + curVelToUse > ANGULAR_LIMIT)
		curVelToUse = ANGULAR_LIMIT - accumulation;

	float minimumBounceVelocity;
	Matrix3D xfrm = *obj->getTransformMatrix();
	xfrm.In_Place_Pre_Rotate_X(-curVelToUse * direction.y);
	xfrm.In_Place_Pre_Rotate_Y(curVelToUse * direction.x);
	obj->setTransformMatrix(&xfrm);

	accumulation += curVelToUse;
	if ((accumulation >= ANGULAR_LIMIT) && (velocity > 0))
	{
		float bounceVelocity = d->bounceVelocity - state54;
		minimumBounceVelocity = 0.05f;
		const float *bounceVelocityToUse =
			(0.05f > bounceVelocity) ?
			&minimumBounceVelocity : &bounceVelocity;

		velocity *= -(*bounceVelocityToUse);
		state54 += 0.025f;

		if ((options & 1) != 0 ||
			fabs(velocity) < VELOCITY_BOUNCE_LIMIT)
		{
			velocity = 0;
			state = 2;

			if (d->killWhenToppled)
			{
				Rva004A82BAAttemptDamage(obj);
				if (d->reorient)
				{
					Vector3 pos;
					pos.X = 0;
					pos.Y = 0;
					pos.Z = ((GeometryInfo *)((char *)obj + 0xa8))->getMaxHeightAbovePosition();
					Matrix3D::Transform_Vector(*obj->getTransformMatrix(), pos, &pos);

					Coord3D tmp;
					tmp.x = pos.X;
					tmp.y = pos.Y;
					tmp.z = pos.Z;
					obj->setPosition(&tmp);
					obj->setOrientation(obj->angle);
				}
			}

			if (d->killStump)
			{
				Object *stump = TheGameLogic->findObjectByID(static_cast<ObjectID>(stumpID));
				if (stump)
				{
					Rva004A82BAAttemptDamage(stump);
				}
			}
		}
		else if (fabs(velocity) >= VELOCITY_BOUNCE_SOUND_LIMIT)
		{
			if ((options & 2) == 0)
				FXList::doFXObj(d->bounceFX, obj, 0);
		}
	}
	else
	{
		velocity += acceleration;
	}

	Drawable *draw = obj->getDrawable();
	if (draw)
		draw->rva00272A02(false);

	return UPDATE_SLEEP_NONE;
}
