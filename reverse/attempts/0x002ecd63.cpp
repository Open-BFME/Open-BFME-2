// ??0Rva002ECE6AInfo@@QAE@PAVPathfinder@@PBVObject@@H_N222@Z
// partial score=0.9905438916 date=2026-10-10
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Native2ECD63..2ECE6A full263B RET28; ZH line-passability query semantics.
// WB D3DC10 and callers2F1AF4/2F1B66 independently establish the60B
// context, member order, and seven stack arguments. Existing pinned
// address-derived constructor signature is retained; bool tail types and
// original source method/field spellings remain structural inferences.
// A typed inline movement initializer calls the actual59B clear provider;
// all offsets and query16B extent come from native accesses.
// Full263B .99054: only zero-store5D versus final MOVSD scheduling differs.
typedef bool Bool;typedef int Int;
struct LineContextTemplate {
 char pad00[0x108];unsigned char kinds[24];char pad120[0x56C-0x120];
 Int priority;char pad570[0x634-0x570];Bool flag;
};
class Object {public:Bool rva0028AC62()const;Bool rva0028AFBB()const;
 void *vtable;LineContextTemplate *definition;char pad08[0x258-8];void *ai;
};
class Rva0006E009DwordField {public:Int get()const;};
class Rva002E6FDF {public:Rva002E6FDF *rva002E6FDF();};
void Rva002EBCA7Split(void *,Int *,unsigned char *);
struct LineContextQuery {
 Int surfaces;Bool flag4,flag5;Int priority8;Bool flagC;
};
class Pathfinder;
struct LineContextMovement {
 __forceinline LineContextMovement(){((Rva002E6FDF *)this)->rva002E6FDF();}
 Int x,y,layer,radius;Bool center;unsigned char flag11;char pad12[2];Int surfaces;unsigned ignored;
 LineContextQuery query;Int word2C;Bool flag30,flag31,flag32;char pad33;Int word34;
};
struct Rva002ECE6AInfo {
 Rva002ECE6AInfo(Pathfinder *,const Object *,Int,Bool,Bool,Bool,Bool);
 Pathfinder *pathfinder;const Object *object;unsigned char flag8;char pad9[3];
 LineContextMovement movement;char pad44[8];LineContextQuery query;
 unsigned char flag5C,flag5D;char pad5E[2];
};
Rva002ECE6AInfo::Rva002ECE6AInfo(Pathfinder *a,const Object *b,Int c,Bool d,Bool e,Bool f,Bool g):pathfinder(a),object(b),flag8(e)
{
 const Object *obj=b;
 Int priority=obj->definition->priority;Bool templateFlag=obj->definition->flag;
 Bool flagA=obj->rva0028AC62();Bool flagB=obj->rva0028AFBB();
 LineContextQuery &value=query;
 value.surfaces=c;value.flag4=!templateFlag;value.flag5=flagB;value.flagC=flagA;value.priority8=priority-1;
 *(LineContextQuery *)((char *)&movement+0x1C)=query;
 flag5C=(unsigned char)g;movement.flag11=d;flag5D=false;
 movement.surfaces=(*(const unsigned *)(obj->definition->kinds+8)&0x4000000)?1:0x10;
 movement.surfaces|=0xC;
 if(!(unsigned char)f || !(obj->definition->kinds[1]&8))movement.surfaces|=2;
 obj=object;
 const Rva0006E009DwordField *ai=(const Rva0006E009DwordField *)obj->ai;movement.ignored=ai?ai->get():0;
 obj=object;
 if(!(obj->definition->kinds[13]&0x20) && !(obj->definition->kinds[23]&0x80))
  Rva002EBCA7Split((void*)obj,&movement.radius,(unsigned char *)&movement.center);
 else {movement.radius=1;movement.center=true;}

}
