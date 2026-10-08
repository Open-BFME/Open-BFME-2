// ?rva004DE24B@Rva004DD843@@QAEXH@Z
// partial score=0.96 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oy-
#include "../Code/Libraries/Include/Lib/Coord3D.h"
struct ICoord2DBase { int x,y; };
struct ICoord2D : ICoord2DBase { bool operator==(const ICoord2DBase &) const; };
enum ObjectStatusTypes { OBJECT_STATUS_NATIVE_38=38 };
enum PathfindLayerEnum { PATHFIND_LAYER_GROUND=0 };
class Object { public: bool testStatus(ObjectStatusTypes) const; char pad[0x438]; unsigned char m_status; };
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *); }; extern TerrainLogic *TheTerrainLogic;
struct PathfindCell;
struct Rva004DD843Slot { int m_value,m_y,m_angle,m_pathLayer,m_listKind; PathfindCell *m_cell; };
class Rva004DD843 { public:
 void rva004DE24B(int);
 void rva004DD8FA(Rva004DD843Slot *);
 void rva004DDF51(Rva004DD843Slot *);
 Object *m_object; Rva004DD843Slot m_position,m_goal,m_other;
};
ICoord2D *__cdecl Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva004DD843::rva004DE24B(int position)
{
 Object *obj=m_object;
 if (obj->m_status & 1) {
   if(m_other.m_value!=-666666) rva004DD8FA(&m_other);
   return;
 }
 if (!obj->testStatus(OBJECT_STATUS_NATIVE_38)) {
   if(m_other.m_value!=-666666) rva004DD8FA(&m_other);
   return;
 }
 {
   ICoord2D cell;
   Rva002EBC14Cell(&cell,obj,(const Coord3D *)position);
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(m_object,(const Coord3D *)position);
   Rva004DD843Slot *other=&m_other;
   if (!(cell==*(ICoord2DBase *)other) || layer!=m_other.m_pathLayer) {
     if(other->m_value!=-666666) rva004DD8FA(other);
     other->m_value=cell.x; other->m_y=cell.y;
     m_other.m_pathLayer=layer; m_other.m_listKind=1;
     rva004DDF51(other);
   }
 }
}

