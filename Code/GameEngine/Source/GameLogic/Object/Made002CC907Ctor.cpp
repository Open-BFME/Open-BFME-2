// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ??0Made002CC907@@QAE@XZ retail 0x0050AA97 83B Grab ctor.
// Evidence: pin; base Rva00507823 0x0050775B; vtable 0x00864AC0; float 1.0 via 0x007BB8D8;
// caller parseGrabNugget 0x002CC92C news 0x140.
// Native table C64A30 proves the containment flags at128/129/12A and
// ShockWaveAmount/Radius/TaperOff/Speed/ZMult at12C/130/134/138/13C.
// WB010A7720 and010A7830 provide callback and shock-wave flow; original
// member names/signatures remain unasserted. Native boundaries349/165 end
// at50A98F and50AA97 respectively, both RET8. Reference Damage.h supplies
// shock-wave purpose, while BFME2 offsets and conditionals come from retail.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class DamageInfo;
class Player
{
public:
    char pad[0x54];
    int index;
};
class Object;
class GrabContainView {public:virtual void s00()=0;
virtual void s01()=0;
virtual void s02()=0;
virtual void s03()=0;
virtual void s04()=0;
virtual void s05()=0;
virtual void s06()=0;
virtual void s07()=0;
virtual void s08()=0;
virtual void s09()=0;
virtual void s10()=0;
virtual void s11()=0;
virtual void s12()=0;
virtual void s13()=0;
virtual void s14()=0;
virtual void s15()=0;
virtual void s16()=0;
virtual void s17()=0;
virtual void s18()=0;
virtual void s19()=0;
virtual void s20()=0;
virtual void s21()=0;
virtual void s22()=0;
virtual void s23()=0;
virtual void s24()=0;
virtual void s25()=0;
virtual void s26()=0;
virtual void s27()=0;
virtual void s28()=0;
virtual void s29()=0;
virtual void s30()=0;
virtual void s31()=0;
virtual void s32()=0;
virtual void s33()=0;
virtual void s34()=0;
virtual void s35()=0;
virtual void s36()=0;
virtual void s37()=0;
virtual bool accept(Object *,bool,int)=0;virtual void add(Object *)=0;virtual void s40()=0;virtual void remove(Object *,bool)=0;};
class Object
{
public:
    Player *getControllingPlayer() const;
    void attemptDamage(DamageInfo *);
    char pad00[0x38];
    Coord3D position;
    char pad44[0x74-0x44];
    unsigned int id;
    char pad78[0x250-0x78];
    GrabContainView *contain;
    char pad254[0x274-0x254];
    Object *containedBy;
};
// Same 0x7C damage descriptor constructed by the owned45-byte provider.
// Accessed offsets are native facts; input/output field meanings below remain
// structural views guided by the reference DamageInfo shock-wave fields.
class Rva00263895Member
{
public:
    Rva00263895Member() throw();
    virtual void rva00263895_dummy();
    char pad04[4];
    unsigned int id08,mask0C;
    char pad10[0x18];
    float delay28;
    char pad2C[4];
    unsigned int id30;
    Coord3D direction34;
    float amount40,radius44,taper48,factor4C;
    char pad50[0x2c];
};
typedef char GrabDamageExtent[sizeof(Rva00263895Member)==0x7c ? 1 : -1];

class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
private:
	char m_pad[0x128 - 4];
};

struct Rva0050A9F2Context {char pad[8];unsigned int sourceId;};
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Made002CC907 : public Rva00507823
{
public:
	Made002CC907();
void rva0050A832(Object *,Object *);
void rva0050A9F2(const Rva0050A9F2Context *,Object *);
private:
	bool m_containOnEffect;
	bool m_impactOnEffect;
	bool m_removeFromOtherContain;char m_pad12B;
	float m_shockWaveAmount;
	float m_shockWaveRadius;
	float m_shockWaveTaper;
	float m_shockWaveSpeed;
	float m_shockWaveZMultiplier;
};

Made002CC907::Made002CC907()
{
	m_containOnEffect = true;
	m_impactOnEffect = false;
	m_shockWaveAmount = 0.0f;
	m_shockWaveRadius = 0.0f;
	m_shockWaveTaper = 0.0f;
	m_shockWaveSpeed = 0.0f;
	m_shockWaveZMultiplier = 1.0f;
}

void Made002CC907::rva0050A832(Object *source,Object *target) {
 Rva00263895Member info;
 info.amount40=m_shockWaveAmount;
 Coord3D direction={target->position.x,target->position.y,target->position.z};
 direction.x-=source->position.x;direction.y-=source->position.y;direction.z-=source->position.z;
 if(fabs(direction.x)<0.0001f && fabs(direction.y)<0.0001f && fabs(direction.z)<0.0001f)direction.z=1.0f;
 info.direction34=direction;
 info.radius44=m_shockWaveRadius;info.taper48=m_shockWaveTaper;info.factor4C=m_shockWaveZMultiplier;
 if(m_shockWaveSpeed>0.0f)info.delay28=direction.length()/m_shockWaveSpeed;
 info.id30=source->id;
 if(source && source->getControllingPlayer())info.mask0C=1u<<source->getControllingPlayer()->index;
 info.id08=source->id;
 info.mask0C=source ? (1u<<source->getControllingPlayer()->index):0;
 target->attemptDamage((DamageInfo *)&info);
}

void Made002CC907::rva0050A9F2(const Rva0050A9F2Context *context,Object *target) {
 if(!context)return;
 Object *source=TheGameLogic->findObjectByID(static_cast<ObjectID>(context->sourceId));
 if(!source || !target)return;
 GrabContainView *contain=source->contain;
 if(m_containOnEffect && contain && contain->accept(target,true,0)) {
  if(m_removeFromOtherContain) {Object *previous=target->containedBy;if(previous)previous->contain->remove(target,false);}
  contain->add(target);
 } else if(m_impactOnEffect)rva0050A832(source,target);
}
