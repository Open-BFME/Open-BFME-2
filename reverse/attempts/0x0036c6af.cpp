// ?rva0036C6AF@Rva0036C6AFState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9081320876667254 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib /I.
// Native 00368C7A..00368D12, 152B, RET12. The receiver's object at +08
// supplies its position Z at +40, matching the rowed Thing height setter.
// The +544 point and mask globals are also observed in GiantBirdAIUpdate's
// constructor; this method's original owner and name remain unknown.
#include "Coord3D.h"

extern unsigned char g_00E01EC0[4];
extern unsigned char g_00E01EC4[4];

struct Rva00368C7AObject
{
	char unknown00[0x38];
	Coord3D position;
	char unknown44[0xBC - 0x44];
	float valueBC;
};
class Rva0030A92C
{
public:
	void rva0030A92C(float z);
};
class Thing
{
public:
	float getHeightAboveTerrain() const;
};
class Object;
struct Rva00375A73Coord { float x, y, z; };
class Rva00375A73Context
{
public:
	unsigned char prefix00[0x24];
	bool valid24;
	unsigned char padding25[0x54 - 0x25];
};
class AerialPathfinder
{
public:
	bool rva00375A73(Rva00375A73Context *context, float value, Rva00375A73Coord *output);
	bool rva00375DFF(Object *obj, Rva00375A73Context *context, float distance, float clearance);
};
extern AerialPathfinder *TheAerialPathfinder;
struct Rva00368C7AMetrics
{
	char unknown00[0x48];
	float value48;
};
class Rva00368C7A
{
public:
	void rva00368C7A(float amount, const Coord3D *position, bool argument);
	int rva00368B51(float amount, bool argument);
	void rva003681F2(const Coord3D *position, const unsigned char *mask, const Coord3D *lookAhead, bool b);
	unsigned char rva00368271();
private:
	char unknown00[8];
	Rva00368C7AObject *object;
	char unknown0C[0x1F0 - 0x0C];
	Rva00368C7AMetrics *metrics;
	char unknown1F4[0x4C8 - 0x1F4];
	Rva00375A73Context context; // +0x4C8
	char unknown51C[0x530 - 0x51C];
	float value530;
	char unknown534[0x540 - 0x534];
	float value540;
	Coord3D previous;
};

void Rva00368C7A::rva00368C7A(float amount, const Coord3D *position, bool argument)
{
	int state = rva00368B51(amount, 0);
	if (state != 0) {
		Coord3D point;
		if (position)
			point = *position;
		else
			point = previous;
		if (state == 1) {
			reinterpret_cast<Rva0030A92C *>(object)->rva0030A92C(object->position.z + 5.0f);
			rva003681F2(&point, g_00E01EC4, 0, argument);
		} else if (state == 2) {
			reinterpret_cast<Rva0030A92C *>(object)->rva0030A92C(object->position.z - 1.0f);
			rva003681F2(&point, g_00E01EC0, 0, argument);
		}
	}
}

// Native 00368271..003682E2 RET0 returns AL containing zero or one.
// The rowed height getter and caller establish the object and byte result;
// the original receiver and method names remain unknown.
unsigned char Rva00368C7A::rva00368271()
{
	Rva00368C7AMetrics *data = metrics;
	Rva00368C7AObject *obj = object;
	if (!obj || !data)
		return 0;
	float threshold = data->value48 * 2.0f;
	float height = reinterpret_cast<Thing *>(obj)->getHeightAboveTerrain();
	unsigned char above = height > threshold;
	int also = obj->position.z > threshold && height > data->value48 * 0.3f;
	above |= also;
	return above;
}

int Rva00368C7A::rva00368B51(float amount, bool argument)
{
	Rva00368C7AObject *obj = object;
	if (!obj || !metrics)
		return 0;
	if (!context.valid24)
		return 2;
	Object *owner = reinterpret_cast<Object *>(obj);
	if (argument) {
		float height = obj->valueBC * 2.0 + value530;
		if (!TheAerialPathfinder->rva00375DFF(owner, &context, height, amount))
			return 1;
	} else {
		float base = value530 * 2.0f;
		if (!TheAerialPathfinder->rva00375DFF(owner, &context, base - obj->valueBC * 0.5f, amount)
			|| !TheAerialPathfinder->rva00375DFF(owner, &context, base, amount))
			return 1;
	}
	if (!rva00368271())
		return 0;
	Rva00375A73Coord point;
	if (!TheAerialPathfinder->rva00375A73(&context, value530 + 10.0f, &point))
		return 0;
	if (point.z - 2.0f > obj->position.z && obj->position.z > value540)
		return 2;
	return 0;
}

// BF1 f989 BfmeGiantBirdFollowThruStateOnEnter is the semantic spine; target offsets and flags below are native witnesses.
// WB F2F6F0 is named only by inlined BitFlags assertions; retain an address-derived state name.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
template<int N> class FollowSlots:public FollowSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class FollowSlots<0>{};
class Rva0036748E{public:void rva0036C897(bool);};
class FollowAI:public FollowSlots<142>{public:virtual void chooseLocomotorSet(int)=0;char pad4[0x1f0-4];Rva00368C7AMetrics*metrics;char pad1f4[0x4b8-0x1f4];unsigned flags;char pad4bc[8];ObjectID victim;char pad4c8[0x4ec-0x4c8];bool success;char pad4ed[0x558-0x4ed];bool follow;char pad559[3];int mode;bool test(int bit)const{return (flags>>bit)&1;}};
class FollowFlags{public:unsigned words[19];unsigned test(int bit)const{return words[bit>>5]&(1u<<(bit&31));}void set(int bit){words[bit>>5]|=1u<<(bit&31);}void reset(int bit){words[bit>>5]&=~(1u<<(bit&31));}};
class Object{public:void rva0028AE6D();char pad0[0x38];Coord3D position;char pad44[0x10c-0x44];FollowFlags flags;char pad158[0x258-0x158];FollowAI*ai;char pad25c[0x438-0x25c];unsigned char status;__forceinline void clear(int bit){if(flags.test(bit)){flags.reset(bit);rva0028AE6D();}}__forceinline void set(int bit){if(!flags.test(bit)){flags.set(bit);rva0028AE6D();}}};
class StateMachine{public:void setGoalPosition(const Coord3D*,float);char pad0[0x14];Object*owner;};
class FollowTerrain:public FollowSlots<6>{public:virtual float height(float,float,Coord3D*)=0;};class TerrainLogic;extern TerrainLogic*TheTerrainLogic;
enum StateReturnType{STATE_CONTINUE=0,STATE_FAILURE=-2};
class Rva0036C6AFState:public FollowSlots<4>{public:virtual StateReturnType rva0036C6AF();void rva0036C8A5(Coord3D*,bool*,bool);char pad4[0x18-4];StateMachine*machine;char pad1c[4];bool enabled;char pad21[3];int counter;};
StateReturnType Rva0036C6AFState::rva0036C6AF(){
 counter=0;Object*owner=machine->owner;owner->clear(155);FollowAI*ai=owner->ai;if(!ai)return STATE_FAILURE;ai->follow=true;if(owner->status&1)return STATE_FAILURE;
 ai->chooseLocomotorSet(0);Rva00368C7AMetrics*locomotor=ai->metrics;if(!locomotor)return STATE_FAILURE;
 Coord3D goal;bool result=false;rva0036C8A5(&goal,&result,enabled);float desired=goal.z+locomotor->value48;
 float ground=((FollowTerrain*)TheTerrainLogic)->height(goal.x,goal.y,0);float minimum=ground+locomotor->value48*1.25f;
 if(desired>minimum){desired=goal.z+locomotor->value48*0.25f;if(!(desired>minimum))desired=minimum;}goal.z=desired;
 if(ai->mode!=2){goal.z=ground+locomotor->value48;goal.x=(goal.x+owner->position.x)*0.5f;goal.y=(goal.y+owner->position.y)*0.5f;}
 machine->setGoalPosition(&goal,3.4028234663852886e+38f);
 if(!result&&!ai->test(3))((Rva00368C7A*)ai)->rva003681F2(&goal,g_00E01EC0,0,true);else((Rva00368C7A*)ai)->rva003681F2(&goal,g_00E01EC4,0,true);
 ((Rva0036748E*)ai)->rva0036C897(false);if(!ai->success)return STATE_FAILURE;
 if(ai->test(6)&&ai->victim!=INVALID_OBJECT_ID){Object*target=TheGameLogic->findObjectByID(ai->victim);if(target)target->set(72);}
 return STATE_CONTINUE;
}
