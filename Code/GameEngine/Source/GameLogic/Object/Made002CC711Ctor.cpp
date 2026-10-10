// cl: /DNDEBUG /MD /EHsc
// ??0Made002CC711@@QAE@XZ @0x00508F51 59B: ParalyzeNugget ctor over rowed
// base Rva00507823; zeroes +0x128/+0x12c/+0x134, pi at +0x130 via 0x7C7468,
// vtable 0x8644A0. Caller parseParalyzeNugget 0x2CC736.

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Native508FA8..5091D6 RET8 and WB010A3180 establish source-ID lookup,
// arc rejection, duration/FX and contained-unit commands. BFME1 Vector3
// and Coord3D point methods provide the mathematical semantic guide;
// the source/target offsets and virtual list-pair slots are retail facts.
// Donor revision575ba2b04: game/Libraries/Source/WWVegas/WWMath/vector3.h;
// local set/sub mirror the referenced Coord3D point operations.
// Explicit local point set/sub preserve the native value order and both
// normalized vectors. Original helper and view names remain unproven.
class WWMath {public:static float __fastcall Inv_Sqrt(float);};
float Cos(float);
struct Vector3 {float X,Y,Z;
Vector3(){} Vector3(float x,float y,float z):X(x),Y(y),Z(z){}
Vector3(const Vector3&v):X(v.X),Y(v.Y),Z(v.Z){}
float Length2()const{return X*X+Y*Y+Z*Z;}
__forceinline void Normalize(){float len2=Length2();if(len2!=0.0f){float oolen=WWMath::Inv_Sqrt(len2);X*=oolen;Y*=oolen;Z*=oolen;}}
static float Dot_Product(const Vector3&a,const Vector3&b){return a.X*b.X+a.Y*b.Y+a.Z*b.Z;}
};
struct ParalyzeLocalPoint:Coord3D{__forceinline void set(const float*p){x=p[0];y=p[1];z=p[2];}
__forceinline void sub(const float*p){x-=p[0];y-=p[1];z-=p[2];}};
struct ParalyzeNode {ParalyzeNode *next,*previous;Object *object;};
struct ParalyzeList {ParalyzeNode *sentinel;};
struct ParalyzeListPair {void *m00;ParalyzeList *m04;};
class ParalyzeContainView {public:
virtual void s0()=0;
virtual void s1()=0;
virtual void s2()=0;
virtual void s3()=0;
virtual bool isContainer()=0;
virtual void s5()=0;
virtual void s6()=0;
virtual void s7()=0;
virtual void s8()=0;
virtual void s9()=0;
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
virtual void s38()=0;
virtual void s39()=0;
virtual void s40()=0;
virtual void s41()=0;
virtual void s42()=0;
virtual void s43()=0;
virtual void s44()=0;
virtual void s45()=0;
virtual void s46()=0;
virtual void s47()=0;
virtual void s48()=0;
virtual void s49()=0;
virtual void s50()=0;
virtual void s51()=0;
virtual void s52()=0;
virtual void s53()=0;
virtual void s54()=0;
virtual void s55()=0;
virtual void s56()=0;
virtual void s57()=0;
virtual void s58()=0;
virtual void s59()=0;
virtual void s60()=0;
virtual void s61()=0;
virtual void s62()=0;
virtual void s63()=0;
virtual void s64()=0;
virtual void s65()=0;
virtual void s66()=0;
virtual void s67()=0;
virtual void s68()=0;
virtual void s69()=0;
virtual void getItems(ParalyzeListPair &)=0;
};
enum DisabledType{PARALYZE=1};
enum CommandSourceType{CMD_FROM_PLAYER=0};
class AICommandInterface {public:void rva0037379B(Object *,CommandSourceType);void aiExit(Object *,CommandSourceType);};
struct ParalyzeAI {char pad[0x20];AICommandInterface commands;};
struct ParalyzeTemplate {char pad[0x115];unsigned char flags115;};
class Object {public:
char pad00[4];ParalyzeTemplate *m_template;float matrix08[12];float x38,y3C,z40;
char pad44[0x250-0x44];ParalyzeContainView *contain250;char pad254[4];ParalyzeAI *ai258;
void setDisabledUntil(DisabledType,unsigned int);bool rva002931BA();
};
class FXList {public:static void doFXObj(const FXList*,const Object*,const Object*);};
struct ParalyzeContext {char pad[8];ObjectID sourceID;};

class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
virtual bool accepts(const ParalyzeContext*,Object*)=0;
virtual void s08()=0;virtual void s0C()=0;virtual void s10()=0;
virtual void rva005091D6(const ParalyzeContext*,Object*)=0;
virtual void rva0050921D(const ParalyzeContext*,const Coord3D*)=0;

private:
	char m_pad[0x128 - 4];
};

class Made002CC711 : public Rva00507823
{
public:
	Made002CC711();
 void rva00508FA8(const ParalyzeContext*,Object*);
virtual void rva005091D6(const ParalyzeContext*,Object*);
virtual void rva0050921D(const ParalyzeContext*,const Coord3D*);

private:
	float m_128;
	int m_12C;
	float m_130;
	const FXList *m_134;
};

Made002CC711::Made002CC711()
{
	m_128 = 0.0f;
	m_12C = 0;
	m_130 = 3.1415927f;
	m_134 = 0;
}

void Made002CC711::rva00508FA8(const ParalyzeContext *context,Object *target)
{
Object *source=TheGameLogic->findObjectByID(context->sourceID);
if(m_130<3.1415927f && source){
ParalyzeLocalPoint delta;
delta.set(&target->x38);
delta.sub(&source->x38);
Vector3 forward(source->matrix08[0],source->matrix08[4],source->matrix08[8]);
Vector3 direction(delta.x,delta.y,delta.z);forward.Normalize();direction.Normalize();
float dot=Vector3::Dot_Product(direction,forward);
if(dot<Cos(m_130))return;
}
target->setDisabledUntil(PARALYZE,TheGameLogic->getFrame()+m_12C);
if(m_134)FXList::doFXObj(m_134,target,0);
ParalyzeContainView *contain=target->contain250;
if(contain && contain->isContainer()){
ParalyzeListPair items;contain->getItems(items);
for(ParalyzeNode *node=items.m04->sentinel->next;node!=items.m04->sentinel;node=node->next){
Object *object=node->object;
ParalyzeAI *ai=object?object->ai258:0;
if(!ai)continue;
if(object->m_template->flags115&0x20)ai->commands.rva0037379B(target,CMD_FROM_PLAYER);
else if(!object->rva002931BA())ai->commands.aiExit(target,CMD_FROM_PLAYER);
}
}
}

void Made002CC711::rva005091D6(const ParalyzeContext *context,Object *target)
{
if(accepts(context,target))rva00508FA8(context,target);
if(m_128>0.0f)rva0050921D(context,(const Coord3D*)&target->x38);
}
#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
void Made002CC711::rva0050921D(const ParalyzeContext *context,const Coord3D *position)
{
float range=m_128>1.0f?m_128:1.0f;
BfmeWideResult result=ThePartitionManager->rva006255D0(position,range,3,0);
for(Object *target=result.next();target;target=result.next())
if(accepts(context,target))rva00508FA8(context,target);
}
