// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /ICode
// Locomotor Z worker, retail 0x001E7ECA..0x001E84E5: 1527 code bytes
// and a nine-entry (36-byte) switch table. Method spelling is unproven.
// BFME1 cee35b7d8 handleBehaviorZ and ZH Locomotor.cpp:2220 are semantic
// guides; retail proves the receiver, offsets, routing, calls and ABI.
// Evidence: reverse/attempt_support/0x001e7eca-exact-20261022/readme.md.
// The identical branch arms below bound constant live ranges before C2's
// late tail merge. Hoisting either call changes retail's zero allocation.
#include "Coord3D.h"
#include "PartitionRangeQueryCallView.h"
class GameLogic;
extern GameLogic *TheGameLogic;
struct LocoFrameView
{
 char pad[0x40];
 unsigned frame;
 
}
;
class GlobalData;
extern GlobalData*TheWritableGlobalData;
struct LocoGlobalView
{
 char pad[0xc4];
 float falling;
 
}
;
extern int BfmeLogicFramesPerSecond;
enum KindOfType
{
 KINDOF_9A=0x9a
}
;
enum PathfindLayerEnum
{
 GROUND=1
}
;
struct LocoDefinition
{
 char pad[0x70];
 int behavior;
 
}
;
struct LocoObjectTemplate
{
 char pad[0x11f];
 unsigned char flags11f;
 
}
;
class Rva00373EC6;
struct ModelFlags {unsigned words[20];unsigned test(int bit)const{return words[bit>>5]&(1U<<(bit&31));}void set(int bit){words[bit>>5]|=1U<<(bit&31);}void clear(int bit){words[bit>>5]&=~(1U<<(bit&31));}};
class Object
{
 public:
 bool isKindOf(KindOfType)const;
 int rva0028B511()const;
 void*rva0029439D();
 Rva00373EC6*rva0028F4BC();
 void rva0028AE6D();
 void *vptr;
 LocoObjectTemplate *definition;
 char pad8[0x38-8];
 Coord3D pos;
 char pad44[0x10c-0x44];
 ModelFlags model10C;
 char pad15c[0x198-0x15c];
 Coord3D future;
 char pad1a4[2];
 bool futureFlag;
 char pad1a7[0x1c8-0x1a7];
 unsigned char disabled;
 char pad1c9[0x438-0x1c9];
 unsigned char flags438;
 
}
;
template<int N>class LocoSlots:public LocoSlots<N-1>
{
 public:virtual void gap(char(*)[N]);
 
}
;
template<>class LocoSlots<0>
{
 
}
;
class LocoInterface:public LocoSlots<142>
{
 public:virtual bool permits();
 
}
;
struct Rva001E41D3Result 
{
 float x,y,z;
 
}
;
class Rva001E41D3 
{
 public:Rva001E41D3Result rva001E41D3();
 
}
;
class Rva001E434A 
{
 public:void*rva001E434A();
 
}
;
class Rva0028E8D4 
{
 public:void rva0028E8D4(float*)const;
 
}
;
class Rva001E46E1 
{
 public:float rva001E46E1(Object*);
 bool rva001E5F1D(Object*,const Coord3D*,float*);
 
}
;
float __stdcall Rva001E40D9Get(float,float);
bool Rva001E3679(int);
class GeometryInfo
{
 public:float getMaxHeightAbovePosition()const;
 
}
;
class StealthUpdate
{
 public:void markAsDetected(unsigned,int,Object*,bool);
 
}
;
struct LocoStealthView
{
 char pad[0x3c];
 int active;
 
}
;
class TerrainLogic
{
 public:PathfindLayerEnum getHighestLayerForDestination(const Coord3D*,bool);
 
}
;
extern TerrainLogic*TheTerrainLogic;
class LocoTerrainView:public LocoSlots<6>
{
 public:
 virtual float ground(float,float,Coord3D*);
 virtual float layer(float,float,int,Coord3D*,bool);
 virtual void gap8();
 virtual void gap9();
 virtual void gap10();
 virtual void gap11();
 virtual void gap12();
 virtual void gap13();
 virtual void gap14();
 virtual void gap15();
 virtual void gap16();
 virtual void gap17();
 virtual void gap18();
 virtual bool underwater(float,float,float*,float*,unsigned char*);
 
}
;
class BfmeFixedStorage0004543D
{
 public:BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&)throw();
 unsigned bits[7];
 
}
;
template<int N>class BitFlags
{
 public:unsigned bits[7];
 
}
;
extern BitFlags<116>KINDOFMASK_NONE;
class Rva00045411BitSet
{
 public:Rva00045411BitSet(int,int);
 unsigned bits[7];
 
}
;
class Rva000421C8
{
 public:Rva000421C8():next(0)
 {
  
 }
 virtual ~Rva000421C8()
 {
  
 }
 virtual bool allow(Object*)=0;
 virtual int getPlayerMask()
 {
  return -1;
  
 }
 Rva000421C8*next;
 
}
;
class Rva0004584D:public Rva000421C8
{
 public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&);
 virtual ~Rva0004584D()
 {
  
 }
 virtual bool allow(Object*);
 BfmeFixedStorage0004543D required,excluded;
 
}
;
extern PartitionManager*ThePartitionManager;
struct LocoMatrix
{
 float values[12];
 void set(const Rva001E41D3Result&p)
 {
  values[3]=p.x;
  values[7]=p.y;
  values[11]=p.z;
  
 }
 
}
;
class Locomotor 
{
 public:
 bool rva001E7ECA(Object*,const Coord3D*);
 float rva001E6532(Object*,const Coord3D*,float);
 float getMaxSpeed(Object*)const;
 __forceinline float surfaceAt(float worldX,float worldY)
 {
  typedef float(Locomotor::*Member)(float,float);
  union Convert
  {
   float(__stdcall*fn)(float,float);
   Member member;
   
  }
  c;
  c.fn=Rva001E40D9Get;
  return(this->*c.member)(worldX,worldY);
  
 }
 void setTranslation(const Rva001E41D3Result&translation)
 {
  ((LocoMatrix*)matrix)->set(translation);
  
 }
 void*vptr;
 LocoDefinition*data;
 char pad8[0x40-8];
 float speed40;
 unsigned flags44;
 float height48,min4c,damping50;
 char pad54[0x68-0x54];
 float matrix[12];
 
}
;
bool Locomotor::rva001E7ECA(Object*object,const Coord3D*goal)
{
 bool requires=true;
 int mode=data->behavior;
 if(mode==9)
 {
  LocoInterface*iface=(LocoInterface*)object->rva0029439D();
  if(!iface||!iface->permits())mode=0;
  
 }
 Rva001E41D3Result pos=((Rva001E41D3*)this)->rva001E41D3();
 union ScratchPoint 
 {
  Coord3D normal;
  Coord3D future;
  
 }
 ;
 ScratchPoint work;
 switch(mode)
 {
  case 8:
  {
   pos.z=goal->z;
   object->futureFlag=true;
   *(Rva001E41D3Result*)&object->future=pos;
   float surface=0;
   ((Rva001E46E1*)this)->rva001E5F1D(object,(const Coord3D*)&pos,&surface);
   return false;
   
  }
  case 0:
  {
   if((object->disabled&8)||object->isKindOf(KINDOF_9A))break;
   float surface=0;
   int layer=object->rva0028B511();
   if(!((Rva001E46E1*)this)->rva001E5F1D(object,(const Coord3D*)&pos,&surface))
   {
    surface=((LocoTerrainView*)TheTerrainLogic)->layer(pos.x,pos.y,layer,0,true);
    if(((LocoFrameView*)TheGameLogic)->frame>(unsigned)BfmeLogicFramesPerSecond && (layer==16||Rva001E3679(layer)) && pos.z-surface>20.0f)surface=pos.z;
    
   }
   pos.z=surface;
   setTranslation(pos);
   requires=false;
   break;
   
  }
  case 1:
  {
   requires=false;
   if(object->disabled&8)break;
   float water;
   bool wet;
   if(flags44&1)
    wet=((LocoTerrainView*)TheTerrainLogic)->underwater(pos.x,pos.y,&water,0,0);
   else
    wet=((LocoTerrainView*)TheTerrainLogic)->underwater(pos.x,pos.y,&water,0,0);
   if(wet)pos.z=water;
   else pos.z=((LocoTerrainView*)TheTerrainLogic)->layer(pos.x,pos.y,object->rva0028B511(),0,true);
   if(object->definition->flags11f&8)
   {
    float speed=speed40;
    pos.z+=(speed/(getMaxSpeed(object)+0.1f)+1.0f)*height48;
    
   }
   else pos.z+=height48;
   setTranslation(pos);
   break;
   
  }
  case 4:case 5:
  {
   requires=true;
   bool relative=data->behavior==4;
   float surface=relative?surfaceAt(pos.x,pos.y):0.0f;
   pos.z=height48+(relative?surface:0.0f);
   setTranslation(pos);
   break;
   
  }
  case 6:
  {
   requires=true;
   if(object->disabled&1)
    pos.z=((LocoTerrainView*)TheTerrainLogic)->ground(pos.x,pos.y,0);
   else
    pos.z=((LocoTerrainView*)TheTerrainLogic)->ground(pos.x,pos.y,0);
   float highest=0.0f;
   BfmeWideResult result=ThePartitionManager->iterateObjectsInRange((const Coord3D*)&pos,1.0f,1,&Rva0004584D(*(const BfmeFixedStorage0004543D*)&Rva00045411BitSet(0,7),*(const BfmeFixedStorage0004543D*)&KINDOFMASK_NONE),0);
   Object*entry;
   while((entry=result.next())!=0)
   {
    float height=((GeometryInfo*)((char*)entry+0xa8))->getMaxHeightAbovePosition();
    if(height>highest)highest=height;
    
   }
   pos.z=height48+highest;
   setTranslation(pos);
   break;
   
  }
  case 7:
  {
   requires=true;
   if(height48!=0.0f || (bool)((flags44>>3)&1))
   {
    int layer=object->rva0028B511();
    if(layer==1)layer=TheTerrainLogic->getHighestLayerForDestination((const Coord3D*)&pos,0);
    Coord3D &normal=work.normal;
    float preferred=((LocoTerrainView*)TheTerrainLogic)->layer(pos.x,pos.y,layer,&normal,false)+height48;
    if((bool)((flags44>>3)&1))preferred=goal->z;
    float delta=((pos.z+(preferred-pos.z)*damping50)-pos.z)/((float)BfmeLogicFramesPerSecond*2.0f);
    if(delta!=0.0f)
    {
     pos.z+=delta;
     setTranslation(pos);
     
    }
    
   }
   break;
   
  }
  case 2:case 3:
  {
   requires=true;
   if(height48!=0.0f || (bool)((flags44>>3)&1))
   {
    float surface=data->behavior==2?surfaceAt(pos.x,pos.y):0.0f;
    float preferred=rva001E6532(object,goal,surface)+surface;
    if((bool)((flags44>>3)&1))preferred=goal->z;
    float delta;
    if(object->flags438&1)delta=((LocoGlobalView*)TheWritableGlobalData)->falling;
    else delta=((pos.z+(preferred-pos.z)*damping50)-pos.z)/((float)BfmeLogicFramesPerSecond*2.0f);
    if(delta!=0.0f)
    {
     pos.z+=delta;
     setTranslation(pos);
     
    }
    if(delta>0.5f)
    {
     if(!object->model10C.test(103))
     {
      object->model10C.set(103);
      object->rva0028AE6D();
      
     }
     Rva00373EC6*stealth=object->rva0028F4BC();
     if(stealth && ((LocoStealthView*)stealth)->active)((StealthUpdate*)stealth)->markAsDetected(0,1,0,true);
     
    }
    else if(object->model10C.test(103))
    {
     object->model10C.clear(103);
     object->rva0028AE6D();
     
    }
    
   }
   break;
   
  }
  
 }
 const Coord3D*anchor=(const Coord3D*)((Rva001E434A*)object)->rva001E434A();
 {
 Coord3D &future=work.future;
 future.x=anchor->x;
 future.y=anchor->y;
 Coord3D current;
 ((Rva0028E8D4*)object)->rva0028E8D4((float*)&current);
 future.z=pos.z*2.0f-current.z;
 object->futureFlag=true;
 object->future=future;
 }
 return requires;
 
}
