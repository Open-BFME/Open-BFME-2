// ?init@Rva002ECE6AInfo@@QAEPAU1@PAX000HHH@Z
// partial score=0.9595676971 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Native2ECD63..2ECE6A RET28 complete263. Existing init owner retained:
// callers2F1AF4 and2F1B66 construct this 60-byte context then pass it to
// the typed line walker2F0C78. Target facts are infoC, query4C, copy28,
// state5C/5D, Object template56C/634 and kind bits90/11/109/191.
// ZH line-passability queries guide purpose; original fields remain unnamed.
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
struct LineContextMovement {
 Int x,y,layer,radius;Bool center;unsigned char flag11;char pad12[2];Int surfaces;unsigned ignored;
 LineContextQuery query;Int word2C;Bool flag30,flag31,flag32;char pad33;Int word34;
};
struct Rva002ECE6AInfo {
 Rva002ECE6AInfo *init(void *,void *,void *,void *,Int,Int,Int);
 void *pathfinder;Object *object;unsigned char flag8;char pad9[3];
 LineContextMovement movement;char pad44[8];LineContextQuery query;
 unsigned char flag5C,flag5D;char pad5E[2];
};
Rva002ECE6AInfo *Rva002ECE6AInfo::init(void *a,void *b,void *c,void *d,Int e,Int f,Int g)
{
 pathfinder=a;object=(Object *)b;flag8=(unsigned char)e;
 ((Rva002E6FDF *)&movement)->rva002E6FDF();
 Object *obj=(Object *)b;
 Int priority=obj->definition->priority;Bool templateFlag=obj->definition->flag;
 Bool flagA=obj->rva0028AC62();Bool flagB=obj->rva0028AFBB();
 LineContextQuery &value=query;
 value.surfaces=(Int)c;value.flag4=!templateFlag;value.priority8=priority-1;
 value.flag5=flagB;value.flagC=flagA;
 movement.query=value;
 flag5C=(unsigned char)g;movement.flag11=(unsigned char)(unsigned long)d;flag5D=false;
 movement.surfaces=(*(const unsigned *)(obj->definition->kinds+8)&0x4000000)?1:0x10;
 movement.surfaces|=0xC;
 if(!(unsigned char)f || !(obj->definition->kinds[1]&8))movement.surfaces|=2;
 obj=object;
 const Rva0006E009DwordField *ai=(const Rva0006E009DwordField *)obj->ai;movement.ignored=ai?ai->get():0;
 obj=object;
 if(!(obj->definition->kinds[13]&0x20) && !(obj->definition->kinds[23]&0x80))
  Rva002EBCA7Split(obj,&movement.radius,(unsigned char *)&movement.center);
 else {movement.radius=1;movement.center=true;}
 return this;
}
