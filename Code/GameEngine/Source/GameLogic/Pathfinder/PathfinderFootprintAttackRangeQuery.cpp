// ?rva002EC479@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@0@Z
// cl: /I. /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /ICode/Libraries/Include/Lib /I.
// Native 2EC479..2EC8C3: 1098 bytes, RET12, frame 4C. WB D3A7D0 supplies
// the footprint-perimeter/range semantics, lexical scopes and coordinate copies.
// The original callable name remains unproven. All offsets are target evidence.
// Keep the already-rowed coordinate and portal providers visible: their escape
// analysis determines stack homes even though all three calls stay out of line.
// These inline COMDAT copies match each entire owner body (162/32/288 bytes)
// and its resolved calls; they leave the existing source ownership unchanged.
// Reuses the established floor/FISTP blocker, with no new assembly reconstruction.
// Evidence: reverse/attempt_support/crack-x-wave4-handoff.json.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "Coord3D.h"
#include <math.h>
#include "Code/Libraries/Include/Lib/ICoord2D.h"
enum PathfindLayerEnum {OBSERVED_LAYER_1=1};
enum WeaponSlotType {OBSERVED_SLOT_0=0};
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Object;class Module;class Weapon;
class Rva002C9400ByteField {public:unsigned char get()const;};
class Weapon {public:float getAttackRange(const Object*)const;void *vptr;Rva002C9400ByteField *definition;};
struct AttackQueryTemplate {char pad[0x108];unsigned kind[8];unsigned kindOf(unsigned k)const{return kind[k>>5]&(1U<<(k&31));}};
class Object {
 friend class Pathfinder;
public:
 const Weapon *getCurrentWeapon(WeaponSlotType*)const;
 int rva0028B511()const;
 unsigned char rva002957FC();
 float rva00263763(const void*)const;
 float rva0028EFB8(const Coord3D*,const Object*,const Coord3D*)const;
 void *vptr;AttackQueryTemplate *definition;char pad8[0x38-8];Coord3D position;
 char pad44[0x74-0x44];int id;char pad78[0xB8-0x78];float observedSize;
protected:
 Module *findModule(NameKeyType)const;
};
class Rva00460C73FloatChase32Field {public:float get()const;};
class Rva004C5772CmpBoolField {public:bool get()const;};
#include "../../Common/Thing/thing.h"
class DynamicPortalBehaviourModuleData {public:char pad[0x144];Coord3D m_144;};
class DynamicPortalBehaviour {public:static Module *rva004608E0(Object*);void rva00460CBA(Coord3D*);void *m_vptr;const DynamicPortalBehaviourModuleData *m_moduleData;Object *m_object;};
template<int N> class QueryTerrainSlots:public QueryTerrainSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<>class QueryTerrainSlots<0>{};
class TerrainLogic:public QueryTerrainSlots<44>{public:virtual bool querySurface(Object*,int)=0;};
extern TerrainLogic *TheTerrainLogic;
struct QueryCellInfo {char pad[0x28];int structure;};
enum CellType {CELL_IMPASSABLE=5};
class PathfindCell {public:QueryCellInfo *info;char pad4[8];unsigned flags;int layer()const{return(flags>>4)&63;}unsigned char type()const{return(unsigned char)(flags&15);}};
ICoord2D *Rva002EBC14Cell(ICoord2D*,void*,const Coord3D*);
int Rva002E9B31Get(void*);
int isGroundOrBridgeLayer(int);
int Rva002E6E8AGet(int);
// The already matched callback family demonstrates the floor-to-FISTP
// compiler blocker; this tiny inline x87 conversion preserves native rounding.
static __forceinline int queryFloor(float f){float floored=(float)floor(f);int i;__asm {
 fld [floored]
 fistp [i]
 }return i;}
class Pathfinder {public:bool rva002EC479(Object*,const Coord3D*,Object*);PathfindCell *getCell(PathfindLayerEnum,int,int);};

inline __declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = queryFloor(pos->x * (1.0f / 10.0f));
		iy = queryFloor(pos->y * (1.0f / 10.0f));
	} else {
		ix = queryFloor(pos->x * (1.0f / 10.0f) + 0.5f);
		iy = queryFloor(pos->y * (1.0f / 10.0f) + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}

bool Rva002EBBFBIsOdd(void *);
inline __declspec(noinline) ICoord2D *__cdecl Rva002EBC14Cell(ICoord2D *out,void *p,const Coord3D *pos) {
 Rva002E7875WorldToCell(out,Rva002EBBFBIsOdd(p),pos);return out;
}
static __forceinline void moveBy(ICoord2D &point,int amount){point.x+=amount;point.y+=amount;}
inline __declspec(noinline) void DynamicPortalBehaviour::rva00460CBA(Coord3D *out)
{
	Coord3D tmp1;
	Coord3D tmp2;
	Coord3D tmp3;
	tmp2.x = 1.0f;
	tmp2.y = 0.0f;
	tmp2.z = 0.0f;
	const DynamicPortalBehaviourModuleData *data = m_moduleData;
	((Thing *)m_object)->transformPoint(&tmp2, &tmp1);
	Coord3D *pPos = &m_object->position;
	tmp1.x -= pPos->x;
	tmp1.y -= pPos->y;
	tmp1.z -= pPos->z;
	float fdy = (float)fabs(tmp1.y);
	float fdx = (float)fabs(tmp1.x);
	const float *pick = fdx > fdy ? &fdx : &fdy;
	float scale = 1.0f / *pick;
	tmp1.x = scale * tmp1.x;
	tmp1.y = scale * tmp1.y;
	tmp1.z = scale * 0.0f;
	double len = tmp1.length();
	tmp2 = data->m_144;
	tmp2.x *= len;
	tmp2.y *= len;
	((Thing *)m_object)->transformPoint(&tmp2, &tmp3);
	out->x = tmp3.x;
	out->y = tmp3.y;
	out->z = tmp3.z;
}

bool Pathfinder::rva002EC479(Object *attacker,const Coord3D *from,Object *target)
{
 const Weapon *weapon=attacker->getCurrentWeapon(0);
 if(!weapon || !weapon->definition->get())return false;
 ICoord2D base;Rva002EBC14Cell(&base,attacker,from);
 int diameter=Rva002E9B31Get(attacker);
 int half=diameter/-2;base.x+=half;base.y+=half;
 float cellRange=weapon->getAttackRange(target)/10.0f;
 int radius=queryFloor(cellRange+0.1f);
 if(target->definition->kindOf(7)){
  int layers[2];layers[0]=attacker->rva0028B511();int count=1;
  if(!(unsigned char)isGroundOrBridgeLayer(layers[0]) && TheTerrainLogic->querySurface(attacker,layers[0])){layers[1]=1;count=2;}
  bool foundWall=false;
  while(radius-->=0){
   for(int j=diameter;j>=0;--j){
    for(int side=0;side<4;++side){
     int px,py;
     switch(side){
      case 0:px=base.x+j;py=base.y-1;break;
      case 1:px=base.x+diameter;py=base.y+j;break;
      case 2:px=base.x+diameter-j-1;py=base.y+diameter;break;
      case 3:px=base.x-1;py=base.y+diameter-j-1;break;
     }
     for(int l=0;l<count;++l){
      PathfindCell *cell=getCell((PathfindLayerEnum)layers[l],px,py);
      if(cell){
       unsigned flags=cell->flags;
       int cellLayer=(flags>>4)&63;
       if(cellLayer!=layers[0] && (unsigned char)Rva002E6E8AGet(cellLayer)){
        unsigned type=(unsigned)(flags&15);
        if(type==5)foundWall=true;
       }
       int structure=cell->info?cell->info->structure:0;
       if(structure==target->id)return true;
      }
     }
    }
   }
   diameter+=2;--base.x;--base.y;
  }
  if(target->definition->kindOf(0x3C)){
   float size=attacker->observedSize;
   if(target->definition->kindOf(0x96))size=0.0f;
   size+=20.0f;
   if(target->rva0028EFB8(&target->position,attacker,from)<size*size && (target->definition->kindOf(0x96)||foundWall))return true;
  }
  return false;
 }
 if(target->definition->kindOf(0xB8) && target->rva002957FC())return attacker->rva00263763(target)<5.0;
 ICoord2D targetBase;Rva002EBC14Cell(&targetBase,target,&target->position);
 int targetDiameter=Rva002E9B31Get(target);
 int targetHalf=targetDiameter/-2;targetBase.x+=targetHalf;targetBase.y+=targetHalf;
 ICoord2D targetHi=targetBase;moveBy(targetHi,targetDiameter);
 ICoord2D hi=base;moveBy(hi,diameter+radius);
 moveBy(base,-radius);
 if(base.x<=targetHi.x && targetBase.x<=hi.x && base.y<=targetHi.y && targetBase.y<=hi.y)return true;
 if(target->definition->kindOf(0x5D)){
  Module *portal=DynamicPortalBehaviour::rva004608E0(target);
  static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
  Module *module=target->findModule(key);
  if(portal && module && ((Rva004C5772CmpBoolField*)module)->get()){
   Coord3D offset;((DynamicPortalBehaviour*)portal)->rva00460CBA(&offset);
   offset.x-=from->x;
   offset.y-=from->y;
   // Retail retains an FST of the Z difference while testing its rounded value.
   volatile float &storedZ=offset.z;
   double z=offset.z-from->z;
   storedZ=(float)z;
   if(fabs((float)z)<20.0f){
    float size=attacker->observedSize;
    size+=((Rva00460C73FloatChase32Field*)portal)->get();
    if(fabs(offset.x)<size && fabs(offset.y)<size)return true;
   }
  }
 }
 return false;
}
