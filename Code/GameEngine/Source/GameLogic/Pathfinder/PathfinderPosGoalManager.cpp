// Native 0x004DD8FA..0x004DD9E3, 233 bytes, RET4.
// Existing 18-byte slot flushes pass this receiver and slots at +04/+1C/+34.
// Native removal follows cell->info, five heads at info+14, and 12-byte nodes
// with next/cell/object at 0/4/8; slot list category/cell are +10/+14. The fallback
// traverses the native AI +10 map, ground cells +0C with dimensions +1C/+20,
// then sixteen 40-byte layers at +60. All offsets and extents are target facts.
// WB 01286E90 calls this operation PathfinderPosGoalManager::RemoveObjPtr and
// corroborates its loops, failure fallback, ReleaseInfo, and -666666 reset.
// Preserve the existing receiver/slot names; the original slot and node type
// names are unknown. BFME1 ba7ddda and ZH provide no clean class implementation.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oy- /Ireference/shims/bfme2_ascii
class Object;
struct Rva004DD8FAInfo;
class PathfindCell {
public:
    void ReleaseInfo();
    Rva004DD8FAInfo *m_info;
    unsigned char m_rest[12];
};
struct Rva004DD8FANode {
    Rva004DD8FANode *m_next;
    PathfindCell *m_cell;
    Object *m_object;
};
struct Rva004DD8FAInfo {
    unsigned char m_prefix[0x14];
    Rva004DD8FANode *m_heads[5];
};
struct Rva004DD843Slot {
    int m_value;
    int m_y;
    int m_angle;
    int m_pathLayer;
    int m_listKind;
    PathfindCell *m_cell;
};
struct Rva004DD8A6Entry;
void __cdecl rva004DD8A6(int key, Rva004DD8A6Entry *entries, int count);
void __cdecl rva004DD890(void *node);
struct Rva004DD8FALayer {
    PathfindCell *m_cells;
    unsigned char m_gap4[4];
    int m_width;
    int m_height;
    unsigned char m_tail[0x30];
};
struct Rva004DD8FAMap {
    unsigned char m_prefix[12];
    PathfindCell *m_cells;
    unsigned char m_gap10[12];
    int m_width;
    int m_height;
    unsigned char m_gap24[0x3c];
    Rva004DD8FALayer m_listKinds[16];
};
struct Rva004DD8FAAIView {
    unsigned char m_prefix[16];
    Rva004DD8FAMap *m_pathfinder;
};
class AI;
extern AI *TheAI;
class Rva004DD843 {
public:
    void rva004DD8FA(Rva004DD843Slot *slot);
    void rva004DE109(int position, float angle, int layer);
    void rva004DDF51(Rva004DD843Slot *slot);
    Object *m_object;
    Rva004DD843Slot m_position;
    Rva004DD843Slot m_goal;
    Rva004DD843Slot m_other;
};
void Rva004DD843::rva004DD8FA(Rva004DD843Slot *slot)
{
    PathfindCell *cur = slot->m_cell;
    while (cur) {
        if (!cur->m_info) break;
        Rva004DD8FANode **p = &cur->m_info->m_heads[slot->m_listKind];
        for (; *p; p = &(*p)->m_next) {
            if ((*p)->m_object == m_object) break;
        }
        if (!*p) {
            Rva004DD8FAMap *map = ((Rva004DD8FAAIView *)TheAI)->m_pathfinder;
            rva004DD8A6((int)m_object, (Rva004DD8A6Entry *)map->m_cells,
                       (map->m_width + 1) * (map->m_height + 1));
            for (int i = 0; i < 16; ++i) {
                Rva004DD8FALayer *layer = &map->m_listKinds[i];
                if (layer->m_cells) {
                    rva004DD8A6((int)m_object, (Rva004DD8A6Entry *)layer->m_cells,
                               layer->m_width * layer->m_height);
                }
            }
            break;
        }
        PathfindCell *next = (*p)->m_cell;
        Rva004DD8FANode *removed = *p;
        *p = removed->m_next;
        rva004DD890(removed);
        if (!cur->m_info->m_heads[slot->m_listKind]) {
            int i;
            for (i = 0; i < 5; ++i) {
                if (cur->m_info->m_heads[i]) break;
            }
            if (i == 5) cur->ReleaseInfo();
        }
        cur = next;
    }
    slot->m_cell = 0;
    slot->m_value = -666666;
}

// Native 004DD8A6..004DD8FA, 84 bytes, cdecl three-argument fallback.
// WB1286D20 ClearObjectPtr corroborates 16-byte cell traversal, five heads,
// key at node+8, and exactly one unlink per head. The sequenced node-key read
// preserves the observed cursor/key access order; no guessed owning type.
struct Rva004DD8A6Node
{
	Rva004DD8A6Node *m_next;
	int m_04;
	int m_key;
};

struct Rva004DD8A6Table
{
	char m_pad00[0x14];
	Rva004DD8A6Node *m_buckets[5];
};

struct Rva004DD8A6Entry
{
	Rva004DD8A6Table * volatile m_table;
	char m_pad04[0x0c];
};

void __cdecl rva004DD890(void *node);

__declspec(noinline) void __cdecl rva004DD8A6(volatile int key, Rva004DD8A6Entry *entries, int count)
{
	if (count <= 0)
		return;
	int remaining = count;

	do {
		if (entries->m_table != 0) {
			for (int offset = 0x14; offset < 0x28; offset += 4) {
				Rva004DD8A6Node **link =
					(Rva004DD8A6Node **)((char *)entries->m_table + offset);
                for (; *link; link = &(*link)->m_next) {
                    const int nodeKey = (*link)->m_key;
                    if (nodeKey == key) {
                        Rva004DD8A6Node *removed = *link;
                        *link = removed->m_next;
                        rva004DD890(removed);
                        break;
                    }
                }
			}
		}
		entries = (Rva004DD8A6Entry *)((char *)entries + 0x10);
	} while (--remaining != 0);
}

// Native004DD6CF..004DD722, 83B cdecl float-to-bin helper called by SetGoal.
// WB12875C0 corroborates normalizeAngle, positive wrap, twelve bins, half-up
// rounding, and wrap-to-zero above eleven. Native SSE retains two distinct
// float multiplies; sequencing the division and scale reproduces that rounding.
// Original helper name is unknown; use the existing investigation spelling.
float __cdecl normalizeAngle(float angle);
__declspec(noinline) int __cdecl Rva004DD6CFGet(float angle)
{
    angle = normalizeAngle(angle);
    if (angle < 0.0f)
        angle += 6.2831855f;
    float steps = angle / 6.2831855f;
    steps *= 12.0f;
    if (steps > 11.0f)
        return 0;
    return (int)(steps + 0.5f);
}

// Native004DE109..004DE24B, 322B RET12. Existing Object+0xA4 forwarders
// establish this receiver and (int,float,int) ABI. WB12861F0 SetGoal supports
// the operation and branch semantics. Template KindOf and Object status/AI
// offsets below are native; opaque virtual slots preserve the observed ABI.
// Slot +0C is the path layer; +10 is the node-list category used by removal.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct ICoord2DBase { int x,y; };
struct ICoord2D : ICoord2DBase { bool operator==(const ICoord2DBase &) const; };
template<int N> class NativeSlots : public NativeSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class NativeSlots<0> {};
class AIUpdateInterface : public NativeSlots<137> { public: virtual bool isDoingGroundMovement() const=0; bool isAircraftThatAdjustsDestination() const; };
class NativeGoalContain : public NativeSlots<50> { public: virtual void slot50()=0; };
struct NativeGoalTemplate { char pad[0x115]; unsigned char kind115; char gap[6]; union { unsigned kind11C; unsigned char kindBytes[4]; }; };
class Object { public:
 void *rva0028C197() const;
 char prefix[4]; NativeGoalTemplate *m_template;
 char gap08[0x44-8]; float m_angle;
 char gap48[0x250-0x48]; void *m_contain;
 char gap254[4]; AIUpdateInterface *m_ai;
 char gap25C[0x438-0x25c]; unsigned char m_status;
};

ICoord2D *__cdecl Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva004DD843::rva004DE109(int position,float angle,int layer)
{
 int bin;
 if (!(m_object->m_template->kind11C & 0x4000000)) bin=0; else bin=Rva004DD6CFGet(angle);
 if (m_object->m_status & 1) return;
 ICoord2D cell;
 Rva002EBC14Cell(&cell,m_object,(const Coord3D *)position);
 Object *obj=m_object;
 if ((obj->m_template->kind11C & 0x4000000) && cell==*(ICoord2DBase *)&m_position)
   bin=Rva004DD6CFGet(obj->m_angle);
 Rva004DD843Slot *goal=&m_goal;
 if (cell==*(ICoord2DBase *)goal && bin==m_goal.m_angle && layer==m_goal.m_pathLayer) return;
 Object *goalObject=m_object;
 if (goalObject->m_template->kind115 & 0x20) {
   *(ICoord2DBase *)goal=cell; m_goal.m_angle=bin; m_goal.m_pathLayer=layer;
   NativeGoalContain *contain=(NativeGoalContain *)goalObject->rva0028C197();
   if (contain) contain->slot50();
 } else {
   AIUpdateInterface *ai=goalObject->m_ai;
   int mode=0;
   if (ai && !ai->isDoingGroundMovement()) {
     if (!ai->isAircraftThatAdjustsDestination()) return;
     mode=2;
   }
   if (goal->m_value!=-666666) rva004DD8FA(goal);
   *(ICoord2DBase *)goal=cell; m_goal.m_angle=bin; m_goal.m_pathLayer=layer; m_goal.m_listKind=mode;
   rva004DDF51(goal);
 }
}





// Native004DDF51..004DE109, 440B RET4 with native GeometryShape string EH cleanup.
// WB12872B0 AddObjPtr corroborates geometry sizing, contained fraction, layer
// fallback and five-word visitor. Slot0C is path layer; slot10 is list category.
#include "ascii_string.h"
struct GeometryShape {
 int type; float height,major,minor; float offsetX,offsetY,offsetZ; AsciiString name; bool enabled,opaque21;
 GeometryShape() : type(0),height(1.0f),major(1.0f),minor(1.0f),offsetX(0),offsetY(0),offsetZ(0),enabled(true),opaque21(true) {}
};
class GeometryInfo { public: void rva006BD9C0(GeometryShape &) const; };
class NativeContain28 : public NativeSlots<28> { public: virtual int slot28()=0; };
class NativeContain31 : public NativeSlots<31> { public: virtual void *slot31()=0; };
class NativeContain69 : public NativeSlots<69> { public: virtual unsigned int slot69(int)=0; };
class Rva004DD9E3 { public: int rva004DD9E3(int,int,int); Rva004DD843Slot *slot; int category; Object *object; int layer,secondary; };
class Pathfinder { public: int rva004DDDA4(const ICoord2DBase *,const ICoord2DBase *,float,int,Rva004DD9E3 *); };
class AI { public: char pad[16]; Pathfinder *map; }; extern AI *TheAI;
class TerrainLogic : public NativeSlots<44> { public: virtual bool slot44(Object *,int)=0; }; extern TerrainLogic *TheTerrainLogic;
float __cdecl Rva004DD722Get(int);
int __cdecl Rva002E9B31Get(void *);
int __cdecl Rva002E6E6CGet(int);
void Rva004DD843::rva004DDF51(Rva004DD843Slot *slot)
{
 ICoord2DBase diameter;
 Object *obj=m_object;
 if (obj->m_template->kindBytes[3] & 4) {
   GeometryShape shape;
   ((GeometryInfo *)((char *)obj+0xa8))->rva006BD9C0(shape);
   diameter.x=(int)((shape.major*2.0f+4.0f)/10.0f);
   diameter.y=(int)((shape.minor*2.0f+4.0f)/10.0f);
   void *contain=m_object->m_contain;
   if (contain && ((NativeContain31 *)contain)->slot31()) {
     int capacity=((NativeContain28 *)contain)->slot28();
     if (capacity>0) {
       float ratio=(float)((NativeContain69 *)contain)->slot69(0)/capacity;
       diameter.x=(int)((diameter.x-2.0f)*ratio+2.0f);
       diameter.y=(int)((diameter.y-2.0f)*ratio+2.0f);
     }
   }
 } else diameter.x=diameter.y=Rva002E9B31Get(obj);
 Object *callbackObject=m_object;
 Rva004DD9E3 visitor;
 visitor.slot=slot; visitor.category=slot->m_listKind; visitor.object=callbackObject;
 visitor.secondary=0; visitor.layer=slot->m_pathLayer;
 if (!(unsigned char)Rva002E6E6CGet(slot->m_pathLayer) && TheTerrainLogic->slot44(callbackObject,slot->m_pathLayer)) visitor.secondary=1;
 TheAI->map->rva004DDDA4((ICoord2DBase *)slot,&diameter,Rva004DD722Get(slot->m_angle),slot->m_pathLayer,&visitor);
}



