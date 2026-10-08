// cl: /O1 /arch:SSE /G7 /ICode/Libraries/Include /DNDEBUG /MD /EHsc
// Retail 0x00284AC6..0x00284DD2: complete780-byte free cdecl helper.
// Primary clean donor: Open-BFME1 40e7f2f21f0011b42a5654697cdedbc2658b6d9b,
// game/GameEngine/Source/GameLogic/Map/FindPosition001AEA80.cpp.
// WB C4CFB0 and verified ring-search caller285202 place it in TerrainLogic.cpp.
// Original helper name/qualification remains unproved; preserve address identity.
// Target: AI pathfinder+10; template kind mask+108; filter ctor27C2C9;
// clear-cell option100; five-argument underwater slot4C; path-query ABI.
// Donor supplies option and relationship semantics. Native bit tests establish
// infantry8, vehicle9, structure7 and ENEMIES0, not original declarations.
// GeometryInfo is an opaque5C allocation/call view: its constructor/dtor
// providers are rowed; this TU defines neither their fields nor their vtable.
// The template prefix models observed mask words only. kindMask returns the
// mask directly, and the C++ conditions perform the boolean conversion.
#include <math.h>
#include "Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"
typedef bool Bool;
typedef float Real;
enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
enum PathfindLayerEnum { LAYER_GROUND = 1 };
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
enum FindPositionFlags {
 FPF_IGNORE_WATER=1, FPF_WATER_ONLY=2, FPF_IGNORE_ALL_OBJECTS=4,
 FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS=8, FPF_IGNORE_ALLY_OR_NEUTRAL_STRUCTURES=16,
 FPF_IGNORE_ENEMY_UNITS=32, FPF_IGNORE_ENEMY_STRUCTURES=64,
 FPF_USE_HIGHEST_LAYER=128, FPF_CLEAR_CELLS_ONLY=256
};
struct TerrainTryTemplatePrefix { char unknown[0x108]; unsigned int kindOf[7]; };
class Object {
public:
 Relationship getRelationship(const Object *) const;
 const TerrainTryTemplatePrefix *getTemplate() const {
  return *(const TerrainTryTemplatePrefix *const *)((const char *)this+4);
 }
 __forceinline unsigned int kindMask(int kind) const { return getTemplate()->kindOf[kind/32] & (1U << (kind%32)); }
 const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this+0x38); }
};
struct FindPositionOptions {
 unsigned int flags;
 Real minRadius,maxRadius,startAngle,maxZDelta;
 const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
class GeometryInfo {
public:
 GeometryInfo(GeometryType,Bool,Real,Real,Real);
 virtual ~GeometryInfo();
 char unknown[0x58];
};
class Rva000421C8 {
public:
 virtual ~Rva000421C8() {}
 virtual Bool allow(Object *)=0;
 virtual int getPlayerMask();
 Rva000421C8 *m_next;
};
class Rva00261603Filter: public Rva000421C8 {
public:
 Rva00261603Filter(const Coord3D &,const GeometryInfo &,Real,Bool);
 virtual Bool allow(Object *);
 Coord3D position;
 const GeometryInfo &geometry;
 Real angle;
 Bool desired;
};
class Pathfinder {
public:
 Bool IsImpassableCell(int,int);
 Bool rva002F477E(Object *,const Coord3D *,const Coord3D *,int);
};
class AI {
public:
 char unknown[0x10];
 Pathfinder *path;
 Pathfinder *pathfinder() const { return path; }
};
extern AI *TheAI;
class TerrainLogic {
public:
 PathfindLayerEnum getHighestLayerForDestination(const Coord3D *,Bool=false);
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual Real getGroundHeight(Real,Real,Coord3D * =0);
 virtual Real getLayerHeight(Real,Real,PathfindLayerEnum,Coord3D * =0,Bool=true);
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
 virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
 virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual Bool isUnderwater(Real,Real,Real * =0,Real * =0,Real * =0);
 virtual Bool isCliffCell(Real,Real);
};
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *ThePartitionManager;
Real Cos(Real); Real Sin(Real);
typedef char GeometrySizeCheck[sizeof(GeometryInfo)==0x5c ? 1:-1];
typedef char FilterSizeCheck[sizeof(Rva00261603Filter)==0x20 ? 1:-1];
Bool Rva00284AC6TryPosition(const Coord3D *center,Real dist,Real angle,
 const FindPositionOptions *options,Coord3D *result)
{
 Coord3D pos;
 pos.x=dist*Cos(angle)+center->x;
 pos.y=dist*Sin(angle)+center->y;
 PathfindLayerEnum layer=LAYER_GROUND;
 if (options->flags & FPF_USE_HIGHEST_LAYER) {
  pos.z=99999.0f;
  layer=TheTerrainLogic->getHighestLayerForDestination(&pos);
  pos.z=TheTerrainLogic->getLayerHeight(pos.x,pos.y,layer);
  if (layer!=LAYER_GROUND) pos.z+=1.0f;
 } else pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y);
 if (fabs(pos.z-center->z)>options->maxZDelta) return false;
 if (!(options->flags & FPF_CLEAR_CELLS_ONLY) && layer==LAYER_GROUND &&
     TheTerrainLogic->isCliffCell(pos.x,pos.y)) return false;
 if (TheAI->pathfinder()->IsImpassableCell((int)&pos,(int)layer)) return false;
 if (!(options->flags & FPF_IGNORE_WATER)) {
  Bool underwater=TheTerrainLogic->isUnderwater(pos.x,pos.y);
  if ((options->flags & FPF_WATER_ONLY) && (!underwater || layer!=LAYER_GROUND)) return false;
  else if (underwater==true && layer==LAYER_GROUND) return false;
 }
 if (!(options->flags & FPF_IGNORE_ALL_OBJECTS)) {
  BfmeWideResult iterator=ThePartitionManager->iterateObjectsInRange(&pos,5.5f,1,
   &Rva00261603Filter(pos,GeometryInfo(GEOMETRY_SPHERE,true,5.0f,5.0f,5.0f),angle,true),0);
  Object *them;
  while ((them=iterator.next())!=0) {
   if (them==options->ignoreObject) continue;
   if (options->relationshipObject) {
    if ((options->flags & FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS) &&
      options->relationshipObject->getRelationship(them)!=ENEMIES &&
      (them->kindMask(8)||them->kindMask(9))) continue;
    if ((options->flags & FPF_IGNORE_ALLY_OR_NEUTRAL_STRUCTURES) &&
      options->relationshipObject->getRelationship(them)!=ENEMIES &&them->kindMask(7)) continue;
    if ((options->flags & FPF_IGNORE_ENEMY_UNITS) &&
      options->relationshipObject->getRelationship(them)==ENEMIES &&
      (them->kindMask(8)||them->kindMask(9))) continue;
    if ((options->flags & FPF_IGNORE_ENEMY_STRUCTURES) &&
      options->relationshipObject->getRelationship(them)==ENEMIES &&them->kindMask(7)) continue;
   }
   if (them==options->sourceToPathToDest) continue;
   return false;
  }
 }
 if (options->sourceToPathToDest &&
   !TheAI->pathfinder()->rva002F477E(const_cast<Object *>(options->sourceToPathToDest),
   options->sourceToPathToDest->getPosition(),&pos,0)) return false;
 *result=pos;
 return true;
}
