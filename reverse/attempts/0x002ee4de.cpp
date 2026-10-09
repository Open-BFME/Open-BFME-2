// ?AdjustFlingDestination@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@PAU3@@Z
// partial score=0.939 date=2026-10-10
// ?AdjustFlingDestination@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@PAU3@@Z
// partial score=0.939 date=2026-10-09
// cl: /O1 /G7 /Oy- /arch:SSE /MD /GX- /ICode/Libraries/Include/Lib
#include "Coord3D.h"
struct FlingCoordP4 : Coord3D { __forceinline void set(const Coord3D &p) {x=p.x; y=p.y; z=p.z;} };
enum PathfindLayerEnum { LAYER_INVALID = 0 };
struct Rva0028AC4EQ { char pad00[0x14]; int value14; };
struct Rva0028AC4EEntry { char pad00[4]; Rva0028AC4EQ *next; };
struct FlingTemplateP4 { char pad00[0x56c]; int diameter; char pad570[0x634-0x570]; bool at634; };
class Object {
public:
 const Rva0028AC4EEntry *rva0028AC4E() const;
 bool rva0028AC62() const;
 bool rva0028AFBB() const;
 int rva0028B511() const;
 char pad00[4];
 FlingTemplateP4 *type;
 char pad08[0x438-8];
 unsigned char flags;
};
bool __cdecl Rva002EBBFBIsOdd(void *);
struct FlingInfoP4 {
 int value;
 bool notAt634;
 bool computer;
 int radius;
 bool atAC62;
 FlingInfoP4(int v, bool b, bool c, int r, bool a) :value(v),notAt634(b),computer(c),radius(r),atAC62(a) {}
};
class Pathfinder;
struct FlingVisitorP4 {
 Pathfinder *finder;
 Coord3D *found;
 PathfindLayerEnum layer;
 FlingInfoP4 info;
 bool alive;
 __forceinline FlingVisitorP4(Pathfinder *p, Coord3D *f, Object *object, const FlingInfoP4 &i, bool a) :finder(p),found(f),layer((PathfindLayerEnum)object->rva0028B511()),info(i),alive(a) {}
};
class Pathfinder {
public:
 void AdjustFlingDestination(Object *object, const Coord3D *start, Coord3D *end);
 int rva002EB4A0(const Coord3D *, const Coord3D *, PathfindLayerEnum, void *);
};
void Pathfinder::AdjustFlingDestination(Object *object, const Coord3D *start, Coord3D *end)
{
 bool centered = Rva002EBBFBIsOdd(object);
 FlingCoordP4 first;
 first.set(*start);
 if (!centered) {
  first.x += 5.0f;
  first.y += 5.0f;
  end->x += 5.0f;
  end->y += 5.0f;
 }
 const Rva0028AC4EEntry *entry = object->rva0028AC4E();
 int value = 1;
 if (entry) value = entry->next->value14;
 int diameter = object->type->diameter;
 bool at634 = object->type->at634;
 bool atAC62 = object->rva0028AC62();
 FlingInfoP4 info(value, !at634, object->rva0028AFBB(), diameter - 1, atAC62);
 FlingCoordP4 found;
 found.set(first);
 FlingVisitorP4 visitor(this, &found, object, info, !(object->flags & 1));
 if (rva002EB4A0(&first, end, (PathfindLayerEnum)1, &visitor)) *end = found;
 if (!centered) {
  end->x -= 5.0f;
  end->y -= 5.0f;
 }
}
