// cl: /O1 /G7 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /EHsc /arch:SSE
// Native EH action 0x7973C8 destroys the destructor lifetime of 56 twenty-byte union-find objects at +0x1B594; the complete parent EH graph proves this 24B lifetime.
// Native EH action 0x797360 destroys the constructor lifetime of 56 twenty-byte union-find objects at +0x1B594; the complete parent EH graph proves this 24B lifetime.
// stlport
#include <algorithm>
#include <vector>
struct Rva005334A4Element {unsigned short first, second;};
// WB12D3020 and12D3290 name PathfindZoneManager::DoXfer and Block::DoXfer
// in GameLogic/Pathfinder/pathfinder_zonemanager.cpp. Complete target bodies
// 5342CB..53442A (351B) and533AF9..533B74 (123B) independently prove fields,
// CRC gating, twelve portal pointers, block stride68, and eight-by-seven
// union-find views of20B. Existing CellType/union-find transfer providers
// at531978/531BA7 and predicate531E14 corroborate these layouts.
// BF1 ba7ddda PathfindZoneManagerConstructor/PathfindZoneBlockQueries offer
// subsystem structure only; BF2's extents, fields and transfer shape are
// target reconstructions, not asserted BF1 layout or lifted instructions.
// Xfer's native table7BB910 establishes IRegion2D17/ICoord2D19/int31/
// ushort32/bool36. The accessed manager prefix retains the existing address-
// qualified lookup ABI; the canonical header supplies the complete accessed extent.
// Reusing the transferred count as the cell index matches WB source lifetime
// and native stack layout. The block's vector call retains its transfer chain.
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
static __forceinline void zeroICoord2D(ICoord2D &zoneCell) {zoneCell.x=0;zoneCell.y=0;}
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

void XferWaypointID(Xfer *, int *);
Xfer *Rva005334DBXfer(Xfer *, void *);
struct ZonePortalView
{
	char unknown00[4];
	int id;
};
#include "../../../Include/GameLogic/PathfindZoneManager.h"

#include "../../../Include/GameLogic/PathfindCell.h"
#include "../../../Include/GameLogic/PathfindLayer.h"
bool Rva001E3679(int);
class Rva005335B0 {public: void rva005335B0(unsigned short,unsigned short);};
class Rva00532DF6 {public: bool remove(unsigned short,unsigned short); bool add(unsigned short,unsigned short);};
class Rva00532330 {public: bool rva00532330(unsigned short*,unsigned short*);};

class PathfindZoneManager::Block
{
public:
    void DoXfer(Xfer *);
    int portalCount;
    ZonePortalView *portals[12];
    bool flag34, flag35;
    char unknown36[2];
    char vector38[12];
};

void PathfindZoneManager::Block::DoXfer(Xfer *xfer)
{
	if (!xfer->IsCRC()) return;
	Rva005334DBXfer(&xfer->operator==(portalCount).operator==(flag34).operator==(flag35), vector38);
	for (int k = 0; k < portalCount; ++k) {
		int id = portals[k]->id;
		XferWaypointID(xfer, &id);
	}
}

void PathfindZoneManager::DoXfer(Xfer *xfer)
{
	if (!xfer->IsCRC()) return;
	xfer->operator==(reinterpret_cast<bool &>(field1BA30)).operator==(reinterpret_cast<bool &>(field1BA31))
		.operator==(reinterpret_cast<ICoord2D &>(field1BA3C)).operator==(field1BA44);
	for (int x = 0; x < field1BA3C; ++x) {
		for (int y = 0; y < field1BA40; ++y) {
			reinterpret_cast<Block **>(field1BA38)[x][y].DoXfer(xfer);
		}
	}
	unsigned short k = end;
	xfer->operator==(k);
	for (k = 0; k < end; ++k) {
		// The established predicate provider is declared as a byte but returns
		// only0/1. Its representation is also the native transferred Bool;
		// this view avoids an unnecessary second boolean normalization.
		union { bool b; unsigned char raw; } value;
		value.raw = IsUsed_SlowMethod(k);
		bool &used = value.b;
		xfer->operator==(used);
		if (used) field0C[k].DoXfer(xfer);
	}
	for (unsigned i = 0; i < 8; ++i) {
		xfer->operator==(i);
		for (unsigned j = 0; j < 7; ++j) {
			xfer->operator==(j);
			field1B594[i][j].rva00531BA7(xfer);
		}
	}
	field1B9F4.rva00531BA7(xfer);
}

// Native97B532104..532165 and WB12D5350 establish a hidden-return
// iterator pair rather than the older void/out-parameter probe. The table
// has4001 buckets and next/key/count nodes. Count>1 selects a dynamic
// four-byte neighbor array; count0/1 retains the embedded singleton view.
// Neighbor first-word purpose comes from CreateEquivalencySet532708.
// These view names are structural labels; original template names remain
// unproven. BF1 reference34f59164f6 has no clean equivalent lookup body.
// Native532104..532165; WB12D5350 returns an iterator pair by value.
struct ZoneNeighborRecord { unsigned short zone, count; };
struct ZoneAdjacencyRange {
 ZoneAdjacencyRange(ZoneNeighborRecord *first, ZoneNeighborRecord *last):begin(first),end(last) {}
 ZoneNeighborRecord *begin, *end;
};
struct ZoneAdjacencyNode {
 ZoneAdjacencyNode *next;
 unsigned short key, count;
 union { ZoneNeighborRecord one; ZoneNeighborRecord *many; } values;
};
class ZoneAdjacencyTable {
public:
 ZoneAdjacencyRange rva00532104(unsigned short key);
 ZoneAdjacencyNode *buckets[4001];
 ZoneAdjacencyNode *freeNodes;
 bool Remove(unsigned short,unsigned short);
};
ZoneAdjacencyRange ZoneAdjacencyTable::rva00532104(unsigned short key) {
 ZoneAdjacencyNode *node = buckets[key % 4001u];
 for (; node; node=node->next) {
  if (node->key != key) continue;
  if (node->count > 1) {
   ZoneNeighborRecord *first = node->values.many;
   return ZoneAdjacencyRange(first, first+node->count);
  }
  return ZoneAdjacencyRange(&node->values.one, &node->values.one+1);
 }
 return ZoneAdjacencyRange(0,0);
}

class Rva00532165 {
public: void LinkSets(unsigned short first, unsigned short second);
};
// WB12D0FB0 names the entire native251B532708..532803 routine.
// Existing transfer bodies establish end+6 and unions1B594[8][7].
// The target uses the established mask predicates531720/531757/5317D7,
// MakeSet531ABB and LinkSets532431 and the concrete returned adjacency pair.
// CouldBeInEquivSet now has its WB-proven owner and exact128B provider.
// InEquivSet has its WB-proven owner and exact260B provider.
void PathfindZoneManager::CreateEquivalencySet(unsigned variant, unsigned equivalent) {
 field1B594[variant][equivalent].first=0;
 for (unsigned i=0; i<end; ++i)
  field1B594[variant][equivalent].MakeSet((unsigned short)i);
 for (unsigned zone=0; zone<end; ++zone) {
  if (!rva00531720(variant,zone)) continue;
  if (!CouldBeInEquivSet(equivalent,zone)) continue;
  ZoneAdjacencyRange range=((ZoneAdjacencyTable *)((char *)this+0x1770C))->rva00532104((unsigned short)zone);
  for (; range.begin != range.end; ++range.begin) {
   unsigned short other=range.begin->zone;
   if (!rva00531720(variant,other)) continue;
   if (!InEquivSet(equivalent,zone,other)) continue;
   ((Rva00532165 *)&field1B594[variant][equivalent])->LinkSets((unsigned short)zone,other);
  }
 }
}

// WB12D2AB0 names CouldBeInEquivSet. Native531757..5317D7 proves
// the4B cell type[0:2] and bridge bit19; native CellType::DoXfer531978
// independently transfers the3/6/6-bit fields. Names type/id/secondary/bridge
// describe their uses; original bitfield names remain unproven. A packed
// bitfield view reproduces every byte including shared true/false tails.
bool PathfindZoneManager::CouldBeInEquivSet(unsigned equivalent, unsigned zone) {
 CellType *zoneCell = field0C+zone;
switch (equivalent) {
case 0:
 break;
case 1:
 if (zoneCell->type != 0 && zoneCell->type != 2) return false;
 break;
case 2:
 if (zoneCell->type != 0 && zoneCell->type != 7 && zoneCell->type != 1) return false;
 break;
case 4:
 if (zoneCell->type != 7 && zoneCell->type != 1) return false;
 break;
case 3:
 if (zoneCell->type != 0 && zoneCell->type != 3) return false;
 break;
case 6:
 if (zoneCell->type != 0 && zoneCell->type != 3 && zoneCell->type != 4) return false;
 if (zoneCell->type == 4 && !zoneCell->bridge) return false;
 break;
case 5:
 if (zoneCell->type != 2) return false;
 break;
}
 return true;
}

// WB12D2C50 names InEquivSet. Native5317D7..5318DB proves type3bits,
// two6-bit IDs and bridgebit19. Equal type permits the three cross-ID
// comparisons or two secondary IDs equal16. Modes1/2/3/4/6 additionally
// require equal primary IDs; mode5 only requires second type2. Default
// succeeds and mode0 fails after the equal-type early path. Packed fields
// reproduce native XOR/TEST AX primary-ID checks and full260B body.

bool PathfindZoneManager::InEquivSet(unsigned equivalent, unsigned first, unsigned second) {
 CellType *firstCell = field0C+first;
 CellType *zoneCell = field0C+second;
 if (firstCell->type == zoneCell->type) {
 if (firstCell->id == zoneCell->id || firstCell->id == zoneCell->secondary || firstCell->secondary == zoneCell->id || (firstCell->secondary == 16 && zoneCell->secondary == 16)) return true;
 }
switch (equivalent) {
case 0:
 return false;
case 1:
 if (firstCell->id != zoneCell->id) return false;
 if (zoneCell->type != 0 && zoneCell->type != 2) return false;
 break;
case 2:
 if (firstCell->id != zoneCell->id) return false;
 if (zoneCell->type != 0 && zoneCell->type != 7 && zoneCell->type != 1) return false;
 break;
case 4:
 if (firstCell->id != zoneCell->id) return false;
 if (zoneCell->type != 7 && zoneCell->type != 1) return false;
 break;
case 3:
 if (firstCell->id != zoneCell->id) return false;
 if (zoneCell->type != 0 && zoneCell->type != 3) return false;
 break;
case 6:
 if (firstCell->id != zoneCell->id) return false;
 if (zoneCell->type != 0 && zoneCell->type != 3 && zoneCell->type != 4) return false;
 if (zoneCell->type == 4 && !zoneCell->bridge) return false;
 break;
case 5:
 if (zoneCell->type != 2) return false;
 break;
}
 return true;
}

// Whole native109B531B3A..531BA7 and WB12D3B00 establish set reset.
// FindSet531AEE chooses the first member; each cyclic member becomes its
// own parent/next/last with rank0. WB uses a32-bit following index, then
// narrows when advancing the16-bit member; this reproduces native peeling.
// Original reset method name remains unknown; no getter identity inferred.
void Rva00531A44::rva00531B3A(unsigned short index) {
 index = FindSet(index);
 do {
  int following = next[index];
  last[index] = index;
  next[index] = index;
  parents[index] = index;
  ranks[index] = 0;
  if (following == index) break;
  index = (unsigned short)following;
 } while (true);
}

// Native109B531C8C..531CF9 repeats the reset with FindSet531C5A.
// WB12D3B90 GetNextSetMember mapping is refuted by native writes;
// Update533BEC consumes no result. This remains an address-qualified
// reset with independently proven20B layout and existing FindSet provider.
class Rva00531C5A {
public: unsigned short rva00531C5A(unsigned short);
 void rva00531C8C(unsigned short);
 unsigned short GetNextSetMember(unsigned short n) { return next[n]; }
 unsigned short capacity, first;
 unsigned short *parents;
 unsigned char *ranks;
 unsigned short *next, *last;
};
void Rva00531C5A::rva00531C8C(unsigned short index) {
 index = rva00531C5A(index);
 do {
  int following = next[index];
  last[index] = index;
  next[index] = index;
  parents[index] = index;
  ranks[index] = 0;
  if (following == index) break;
  index = (unsigned short)following;
 } while (true);
}

class Rva005321D1 { public: void LinkSets(unsigned short,unsigned short); };

// Full native560B5324D8..532708 and WB12D0B40 establish the typed
// cell-pair masks and eight-by-seven union dispatch. Incremental is tested
// as a byte boolean; starting variants0/1 and stepping2 preserves native.
// Shared type/ID/secondary/bridge bitfields reproduce the entire routine
// on the first direct trial, including repeated mode2 and mode6 merges.
// Original method name unknown; manager receiver follows independently
// verified cell/union layout and Update533BEC callers. No new pins.
void PathfindZoneManager::rva005324D8(unsigned char incremental,unsigned short first,unsigned short second) {
 CellType *firstCell=field0C+first;
 CellType *cellType=field0C+second;
 unsigned mask=(1u<<firstCell->type)|(1u<<cellType->type);
 for(int variant=incremental ? 1:0;variant<8;variant+=2) {
  if(!rva00531720(variant,first) || !rva00531720(variant,second))continue;
  bool joined=false;
  if(firstCell->type==cellType->type && (firstCell->id==cellType->id || firstCell->id==cellType->secondary || firstCell->secondary==cellType->id || (firstCell->secondary==16 && cellType->secondary==16))) {
   joined=true;
   ((Rva00532165 *)&field1B594[variant][0])->LinkSets(first,second);
  }
  if(firstCell->id==cellType->id || joined) {
   if(!(mask & ~5u)) ((Rva00532165 *)&field1B594[variant][1])->LinkSets(first,second);
   if(!(mask & ~3u)) ((Rva00532165 *)&field1B594[variant][2])->LinkSets(first,second);
   if(!(mask & ~0x81u)) ((Rva00532165 *)&field1B594[variant][2])->LinkSets(first,second);
   if(!(mask & ~0x82u)) ((Rva00532165 *)&field1B594[variant][2])->LinkSets(first,second);
   if(!(mask & ~0x82u)) ((Rva00532165 *)&field1B594[variant][4])->LinkSets(first,second);
   if(!(mask & ~9u)) {
    ((Rva00532165 *)&field1B594[variant][3])->LinkSets(first,second);
    ((Rva00532165 *)&field1B594[variant][6])->LinkSets(first,second);
   }
   if(!(mask & ~0x11u) && (firstCell->type!=4 || firstCell->bridge) && (cellType->type!=4 || cellType->bridge))
    ((Rva00532165 *)&field1B594[variant][6])->LinkSets(first,second);
  }
  if(mask==4) ((Rva00532165 *)&field1B594[variant][5])->LinkSets(first,second);
 }
 if(incremental && firstCell->id==cellType->id && !(mask & ~0x11u))
  ((Rva005321D1 *)&field1B9F4)->LinkSets(first,second);
}

// The cell's packed word at +0x0C as the zone code reads it; byte-return flag
// accessors preserve retail promotion.
struct ZoneCellBits {
 unsigned type:4,id:6,secondary:6,unknown16:1,flag17:1,flag18:1,kind:2,unknown21:1,flag22:1,unknown23:9;
 unsigned char get17() const { return (unsigned char)flag17; }
 unsigned char get18() const { return (unsigned char)flag18; }
 unsigned char get22() const { return (unsigned char)flag22; }
};
static __forceinline const ZoneCellBits &cellBits(const PathfindCell *cell) { return *(const ZoneCellBits *)&cell->m_0C; }
// Integer-promoted zone access matches native address selection in link creation.
struct ZoneCellZoneView { char unknown00[8]; unsigned short zone; int getZoneInt() const { return zone; } };
static __forceinline int cellZoneInt(const PathfindCell &cell) { return ((const ZoneCellZoneView *)&cell)->getZoneInt(); }

bool Rva0053166DEqual(const PathfindCell *firstCell,const PathfindCell *pathfindCell) {
 return cellBits(firstCell).type==cellBits(pathfindCell).type && cellBits(firstCell).id==cellBits(pathfindCell).id && cellBits(firstCell).secondary==cellBits(pathfindCell).secondary &&
  cellBits(firstCell).get17()==cellBits(pathfindCell).get17() && cellBits(firstCell).get18()==cellBits(pathfindCell).get18() && cellBits(firstCell).kind==cellBits(pathfindCell).kind && cellBits(firstCell).get22()==cellBits(pathfindCell).get22();
}

// WB 0x012D0A40 and native 0x0053166D..0x005316E0 prove this comparison.
// The original function name is unknown. Packed DWORD fields are at cell+0x0C;
// byte-return flag accessors preserve retail promotion and the bool result ABI.


// Native 0x005316E0..0x00531720: exclude an identical zone; otherwise
// zones with the same six-bit id or three-bit type can be connected.
// CellType fields are independently supported by DoXfer and equivalency methods.
unsigned char PathfindZoneManager::rva005316E0(unsigned short first,unsigned short second) {
 if(first==second)return 0;
 CellType *firstCell=(CellType*)((char*)this+0xC)+first;
 CellType *cellType=(CellType*)((char*)this+0xC)+second;
 unsigned av=firstCell->value,bv=cellType->value;
 if(firstCell->id==cellType->id)return 1;
 unsigned char type=av;
 type^=bv;
 return (type & 7)==0;
}

// Native 0x005329C8..0x00532C75 (685 bytes) and WB 0x012D0400: label the
// cells of one region with provisional zones through a 256-entry local
// union-find (UnionFindSimpleStatic in WB), give each root a fresh manager
// zone (0x00531D52) marked changed and made a set in every union, then write
// the final zones back and link neighbouring zones (0x005324D8). The WB body
// recomputes the left neighbour and takes the lower neighbour only after the
// equality test; that shape fixes the register choice in the first loop.
// Original method name unknown.
class Rva00531ED3 { public: unsigned short rva00531ED3(unsigned short); };
class Rva0053222F {
public: void rva00532479(unsigned short,unsigned short);
 unsigned short parents[256]; unsigned char ranks[256];
 void MakeSet(unsigned short n) { parents[n]=n; ranks[n]=0; }
};
class Rva00531196 { public: void rva00531196(unsigned int *); };

void PathfindZoneManager::rva005329C8(PathfindCell **map,const IRegion2D &region) {
 unsigned short mappedID[256];
 bool initialized[256];
 Rva0053222F local;
 unsigned count=0;
 PathfindCell *cell;
 int x;
 for(x=region.lo.x;x<=region.hi.x;++x) {
  for(int y=region.lo.y;y<=region.hi.y;++y) {
   cell=&map[x][y];
   cell->m_zone=0xFFFF;
   if(x>region.lo.x && Rva0053166DEqual(cell,&map[x-1][y]))
    cell->m_zone=map[x-1][y].m_zone;
   if(y>region.lo.y && Rva0053166DEqual(cell,&map[x][y-1])) {
    PathfindCell *down=&map[x][y-1];
    {
     if(cell->m_zone==0xFFFF)cell->m_zone=down->m_zone;
     else local.rva00532479(down->m_zone,cell->m_zone);
    }
   }
   if(cell->m_zone==0xFFFF) {
    unsigned index=count++;
    local.MakeSet((unsigned short)index);
    cell->m_zone=(unsigned short)index;
   }
  }
 }
 for(unsigned index=0;index<count;++index) {
  if(((Rva00531ED3 *)&local)->rva00531ED3((unsigned short)index)!=index)continue;
  initialized[index]=false;
  mappedID[index]=GetAndUseNew();
  field1BA08.SetBit(mappedID[index]);
  for(int variant=0;variant<8;variant+=2)
   for(int equivalent=0;equivalent<7;++equivalent)
    field1B594[variant][equivalent].MakeSet(mappedID[index]);
  field1B9F4.MakeSet(mappedID[index]);
 }
 for(x=region.lo.x;x<=region.hi.x;++x) {
  for(int y=region.lo.y;y<=region.hi.y;++y) {
   cell=&map[x][y];
   unsigned root=((Rva00531ED3 *)&local)->rva00531ED3(cell->m_zone);
   if(!initialized[root]) {
    initialized[root]=true;
    ((Rva00531196 *)(field0C+mappedID[root]))->rva00531196((unsigned int *)cell);
   } else ++table[mappedID[root]];
   cell->m_zone=mappedID[root];
   if(x>region.lo.x && cell->m_zone!=map[x-1][y].m_zone)
    rva005324D8(0,cell->m_zone,map[x-1][y].m_zone);
   if(y>region.lo.y) {
    unsigned short other=map[x][y-1].m_zone;
    if(cell->m_zone!=other)rva005324D8(0,cell->m_zone,other);
   }
  }
 }
}

// Native 0x00532FEA..0x005334A4 and WB0x012D1CE0 establish zone-link
// removal over a changed block and its four borders. Original name unknown.
// The ZH updateZonesForModify routine supports subsystem purpose only;
// BFME2's counted adjacency graph and four-by-seven invalidation are native facts.
void PathfindZoneManager::rva00532FEA(Block *block,PathfindCell **map,const IRegion2D& bounds) {
 {
 unsigned short first,second;
 while(((Rva00532330*)block)->rva00532330(&first,&second)) {
  if(((Rva00532DF6*)((char*)this+0x1770C))->remove(first,second)) {
   field1BA08.SetBit(first);field1BA08.SetBit(second);
  }
 }
 }
 {
 int x,y;
 for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(x<bounds.hi.x && rva005316E0(map[x][y].getZone(),map[x+1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][y].getZone(),map[x+1][y].getZone())) {
     field1BA08.SetBit(map[x][y].getZone());field1BA08.SetBit(map[x+1][y].getZone());
    }
   }
   if(y<bounds.hi.y && rva005316E0(map[x][y].getZone(),map[x][y+1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][y].getZone(),map[x][y+1].getZone())) {
     field1BA08.SetBit(map[x][y].getZone());field1BA08.SetBit(map[x][y+1].getZone());
    }
   }
   if(ReleaseUse(map[x][y].getZone())) {
    field1BA08.SetBit(map[x][y].getZone());
    for(int i=0;i<8;i+=2)for(int j=0;j<7;++j)field1B594[i][j].rva00531B3A(map[x][y].getZone());
   }
  }
 }
 }
 if(bounds.lo.x>field1BA44.lo.x) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
     field1BA08.SetBit(map[bounds.lo.x][y].getZone());field1BA08.SetBit(map[bounds.lo.x-1][y].getZone());
    }
   }
  }
 }
 if(bounds.hi.x<field1BA44.hi.x) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
     field1BA08.SetBit(map[bounds.hi.x][y].getZone());field1BA08.SetBit(map[bounds.hi.x+1][y].getZone());
    }
   }
  }
 }
 if(bounds.lo.y>field1BA44.lo.y) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
     field1BA08.SetBit(map[x][bounds.lo.y].getZone());field1BA08.SetBit(map[x][bounds.lo.y-1].getZone());
    }
   }
  }
 }
 if(bounds.hi.y<field1BA44.hi.y) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
     field1BA08.SetBit(map[x][bounds.hi.y].getZone());field1BA08.SetBit(map[x][bounds.hi.y+1].getZone());
    }
   }
  }
 }
}

// Native 0x00533664..0x00533AF9 and WB0x012D12B0 establish block link
// creation including special layer links and selectively incremental borders.
// Manager/cell offsets and layer stride64 come from target access instructions.
void PathfindZoneManager::rva00533664(Block *block,PathfindCell **map,PathfindLayer *layers,const IRegion2D& bounds,bool incremental) {
 // The native block-pair vector now has its verified typed erase below.
 _STL::vector<Rva005334A4Element> *entries=(_STL::vector<Rva005334A4Element>*)block->vector38;
 entries->erase(entries->begin(),entries->end());
 {
 int x,y;
 for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   PathfindCell *cell=&map[x][y];
   if(x<bounds.hi.x) {
    unsigned short next=cellZoneInt(map[x+1][y]);
    if(rva005316E0(cellZoneInt(map[x][y]),next)) {
     if(((Rva00532DF6*)((char*)this+0x1770C))->add(cellZoneInt(map[x][y]),next)) {
      field1BA08.SetBit(cellZoneInt(map[x][y]));field1BA08.SetBit(cellZoneInt(map[x+1][y]));
     }
    }
   }
   if(y<bounds.hi.y && rva005316E0(cellZoneInt(map[x][y]),cellZoneInt(map[x][y+1]))) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(cellZoneInt(map[x][y]),cellZoneInt(map[x][y+1]))) {
     field1BA08.SetBit(cellZoneInt(map[x][y]));field1BA08.SetBit(cellZoneInt(map[x][y+1]));
    }
   }
   unsigned secondary=cellBits(cell).secondary;
   if(Rva001E3679(secondary) && cellBits(cell).type==0) {
    unsigned short goal=(unsigned short)layers[secondary].m_zone;
    ((Rva005335B0*)block)->rva005335B0(cell->getZone(),goal);
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(cell->getZone(),goal)) {
     field1BA08.SetBit(cell->getZone());field1BA08.SetBit(goal);
    }
   }
  }
 }
 }
 if(bounds.lo.x>field1BA44.lo.x && incremental) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
     field1BA08.SetBit(map[bounds.lo.x][y].getZone());field1BA08.SetBit(map[bounds.lo.x-1][y].getZone());
    }
   }
  }
 }
 if(bounds.hi.x<field1BA44.hi.x) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
     field1BA08.SetBit(map[bounds.hi.x][y].getZone());field1BA08.SetBit(map[bounds.hi.x+1][y].getZone());
    }
   }
  }
 }
 if(bounds.lo.y>field1BA44.lo.y && incremental) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
     field1BA08.SetBit(map[x][bounds.lo.y].getZone());field1BA08.SetBit(map[x][bounds.lo.y-1].getZone());
    }
   }
  }
 }
 if(bounds.hi.y<field1BA44.hi.y) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
     field1BA08.SetBit(map[x][bounds.hi.y].getZone());field1BA08.SetBit(map[x][bounds.hi.y+1].getZone());
    }
   }
  }
 }
}
struct ZoneNeighborLess {
 bool operator()(const ZoneNeighborRecord &a,unsigned short b)const {return a.zone<b;}
};

// STLport 4.5.3 __lower_bound retains its actual five-argument template ABI.
// Native 0x0053249D..0x005324D8 is a complete 59B byte-and-relocation twin
// of the existing three-argument address-qualified recovery. WB12D6010
// and counted-pair callers prove record stride4 and low-word ordering;
// WB12D5080 and retail532DF6 pass an empty comparator plus int distance tag.
// ZoneNeighborRecord/ZoneNeighborLess remain structural labels, not asserted
// original type spellings. Explicit instantiation has no wrapper or new pin.
template ZoneNeighborRecord *_STL::__lower_bound<ZoneNeighborRecord *,unsigned short,ZoneNeighborLess,int>(ZoneNeighborRecord *,ZoneNeighborRecord *,const unsigned short &,ZoneNeighborLess,int *);
// The block's vector stores4B pairs (WB12D3630 and native5335B0).
// STLport4.5.3 emits the full42B forward-copy body at31B031..31B05B;
// it is a byte-and-relocation twin of the existing ScienceType copy provider.
// These typed dependencies preserve the observed vector ABI without a pin.
// The address-derived element label is retained from the existing push_back;
// its two words follow the block helper's independently observed writes.
template Rva005334A4Element *_STL::__copy<Rva005334A4Element *,Rva005334A4Element *,int>(Rva005334A4Element *,Rva005334A4Element *,Rva005334A4Element *,const _STL::random_access_iterator_tag &,int *);
// Full29B25BF40..25BF5D copy_ptrs delegates to the verified forward copy
// with the real STLport tag-reference and int-distance ABI. The block erase
// native532803 call fixes this target; every relocation now binds through
// a verified provider rather than a new pin.
template Rva005334A4Element *_STL::__copy_ptrs<Rva005334A4Element *,Rva005334A4Element *>(Rva005334A4Element *,Rva005334A4Element *,Rva005334A4Element *,const _STL::__false_type &);
// Complete38B532803..532829 range erase uses the two verified copy providers.
// Block rebuild533664 passes begin/end for its4B pair vector; its actual
// typed specialization is a full byte-and-relocation twin of the existing
// enum-vector erase. This is a real STLport instantiation, not a wrapper.
template Rva005334A4Element *_STL::vector<Rva005334A4Element>::erase(Rva005334A4Element *,Rva005334A4Element *);

PathfindZoneManager::~PathfindZoneManager() { rva005335D3(); }

// Native37B53442A..53444F: signed two-cell division with8B hidden return.
// Rowed caller534557 proves the empty-base record ABI. Read each source
// coordinate once in native order before writing either output coordinate.
struct Rva00534557EmptyBase{};
struct Rva00534557Record : Rva00534557EmptyBase { Rva00534557Record(int a,int b):x(a),y(b){}
 int x,y; };
Rva00534557Record rva0053442A(const int *src) {
 const volatile int &x=src[0], &y=src[1]; int firstCell=x/16;
 int b=y/16;
 return Rva00534557Record(firstCell,b);
}


// WB constructor identity and native532361..53241F prove the24000 capacity,
// 56 union records, both20B bitmaps, flag bytes1BA30/31 and null owners34/38.
// BF1 supplies subsystem relationships only; all dimensions and stores are
// target evidence. The member construction view preserves full layout.
PathfindZoneManager::PathfindZoneManager()
 : Rva00531E14(24000),field1BA08(24000),field1BA1C(24000),field1BA30(false),field1BA31(true),field1BA34(0),field1BA38(0)
{
 zeroICoord2D(reinterpret_cast<ICoord2D &>(field1BA3C));
}

// BooleanBitmapSet::DoEnum (WB Source/common/BitmapSet.h; retail 0x0053104A,
// 153 bytes). Retail's Update was compiled with this body visible: it keeps
// the enumerated index in a register across the union-find calls and reads
// the cell type through the live index, which only an earlier definition in
// this unit reproduces (the same body is byte-exact here).
bool BooleanBitmapSet::DoEnum(int *out)
{
	while (cursor < numBitsDiv32) {
		unsigned int word = summary[cursor >> 5];
		if (word != 0) {
			unsigned int shifted = word >> (cursor & 31);
			if (shifted != 0) {
				while ((shifted & 1) == 0) {
					shifted >>= 1;
					++cursor;
				}
				unsigned int d = ((unsigned int *)bits)[cursor] >> bit;
				while (true) {
					if (d == 0) {
						bit = 0;
						++cursor;
						break;
					}
					if (d & 1) {
						*out = (cursor << 5) + bit;
						if (++bit == 32) {
							bit = 0;
							++cursor;
						}
						return true;
					}
					d >>= 1;
					++bit;
				}
				continue;
			} else {
				cursor = (cursor + 31) & ~31u;
			}
		} else {
			cursor += 32;
		}
	}
	return false;
}
class Rva0036667B { public: void rva0036667B(int); };
// WB 0x012CDDE0 names PathfindZoneManager::Update (pathfinder_zonemanager.cpp,
// asserts 550..629); native 0x00533BEC..0x005342CB (1759 bytes, RET 12). A set
// rebuild flag regenerates every zone, block and equivalency union; otherwise
// only blocks flagged at +0x35 are relinked and the unions of the changed
// zones are reset and rejoined. All callees are existing rows in this unit or
// rowed providers; the region labeller 0x005329C8 is defined above.
void PathfindZoneManager::Update(PathfindCell **map, PathfindLayer *layers, const IRegion2D &bounds) {
 if (!field1BA31 && !field1BA30) return;
 if (field1BA31) {
 int x,v,k;
  field1BA31=false;
  field1BA30=false;
  end=0; first=0; second=capacity;
  field1770C.rva00531E74();
  for (int layer=2; layer<=15; ++layer) {
   int zone=GetAndUseNew();
   CellType &cell=field0C[zone];
   cell.id=layer; cell.unknown15=0; cell.secondary=0; cell.type=0; cell.bridge=0;
   ((Rva0036667B *)&layers[layer])->rva0036667B(zone);
  }
  for(v=0; v<8; v+=2) for(int e=0;e<7;++e) for(unsigned k=0;k<14;++k)
   field1B594[v][e].MakeSet((unsigned short)k);
  field1B9F4.first=0;
  for(k=0;k<end;++k) field1B9F4.MakeSet((unsigned short)k);
  for(v=1;v<8;v+=2) for(int e=0;e<7;++e) {
   field1B594[v][e].first=0;
   for(unsigned k=0;k<end;++k) field1B594[v][e].MakeSet((unsigned short)k);
  }
  for(x=0;x<field1BA3C;++x) {
   IRegion2D region;
   region.lo.x=bounds.lo.x+x*16;
   region.hi.x=region.lo.x+15;
   if(region.hi.x>bounds.hi.x)region.hi.x=bounds.hi.x;
   for(int y=0;y<field1BA40;++y) {
    Block *block=&reinterpret_cast<Block **>(field1BA38)[x][y];
    region.lo.y=bounds.lo.y+y*16;
    region.hi.y=region.lo.y+15;
    if(region.hi.y>bounds.hi.y)region.hi.y=bounds.hi.y;
    rva005329C8(map,region); block->flag35=false;
   }
  }
  for(x=0;x<field1BA3C;++x) {
   IRegion2D region;
   region.lo.x=bounds.lo.x+x*16;
   region.hi.x=region.lo.x+15;
   if(region.hi.x>bounds.hi.x)region.hi.x=bounds.hi.x;
   for(int y=0;y<field1BA40;++y) {
    Block *block=&reinterpret_cast<Block **>(field1BA38)[x][y];
    region.lo.y=bounds.lo.y+y*16;
    region.hi.y=region.lo.y+15;
    if(region.hi.y>bounds.hi.y)region.hi.y=bounds.hi.y;
    rva00533664(block,map,layers,region,false);
   }
  }
  for(v=1;v<8;v+=2) for(int e=0;e<7;++e) {
   field1B594[v][e].first=0;
   for(unsigned k=0;k<end;++k)field1B594[v][e].MakeSet((unsigned short)k);
  }
  field1B9F4.first=0;
  for(k=0;k<end;++k)field1B9F4.MakeSet((unsigned short)k);
  for(k=0;k<end;++k) {
   ZoneAdjacencyRange range=((ZoneAdjacencyTable *)((char *)this+0x1770C))->rva00532104((unsigned short)k);
   for(;range.begin!=range.end;++range.begin) rva005324D8(1,(unsigned short)k,range.begin->zone);
  }
 } else {
  field1BA30=false;
  unsigned oldEnd=end;
  field1BA08.rva00530FC5();
  for(int x=0;x<field1BA3C;++x) {
   IRegion2D region;
   region.lo.x=bounds.lo.x+x*16;
   region.hi.x=region.lo.x+15;
   if(region.hi.x>bounds.hi.x)region.hi.x=bounds.hi.x;
   for(int y=0;y<field1BA40;++y) {
    Block *block=&reinterpret_cast<Block **>(field1BA38)[x][y];
    if(!block->flag35)continue;
    region.lo.y=bounds.lo.y+y*16;
    region.hi.y=region.lo.y+15;
    if(region.hi.y>bounds.hi.y)region.hi.y=bounds.hi.y;
    rva00532FEA(block,map,region);
    rva005329C8(map,region);
    rva00533664(block,map,layers,region,true);
    block->flag35=false;
   }
  }
  for(int v=1;v<8;v+=2)for(int e=0;e<7;++e) {
   field1BA1C.rva00530FC5();
   field1BA08.ResetEnum();
   {
   int index;
   while(field1BA08.DoEnum(&index)) {
    if((unsigned)index<oldEnd) {
     unsigned short member=field1B594[v][e].FindSet((unsigned short)index);
     for(;;) {
      field1BA1C.SetBit(member);
      unsigned short next=field1B594[v][e].GetNextSetMember(member);
      if(next==member)break;
      member=next;
     }
     field1B594[v][e].rva00531B3A((unsigned short)index);
    } else {field1B594[v][e].MakeSet((unsigned short)index);field1BA1C.SetBit(index);}
   }
   }
   field1BA1C.ResetEnum();
   {
   int zone;
   while(field1BA1C.DoEnum(&zone)) {
    if(!rva00531720(v,zone))continue;
    if(!CouldBeInEquivSet(e,zone))continue;
    ZoneAdjacencyRange range=((ZoneAdjacencyTable *)((char *)this+0x1770C))->rva00532104((unsigned short)zone);
    for(;range.begin!=range.end;++range.begin) {
     unsigned short other=range.begin->zone;
     if(!rva00531720(v,other))continue;
     if(!InEquivSet(e,zone,other))continue;
     ((Rva00532165 *)&field1B594[v][e])->LinkSets((unsigned short)zone,other);
    }
   }
   }
  }
  field1BA1C.rva00530FC5();
  field1BA08.ResetEnum();
  {
  int index;
  while(field1BA08.DoEnum(&index)) {
   if((unsigned)index<oldEnd) {
    unsigned short member=((Rva00531C5A *)&field1B9F4)->rva00531C5A((unsigned short)index);
    for(;;) {
     field1BA1C.SetBit(member);
     unsigned short next=((Rva00531C5A *)&field1B9F4)->GetNextSetMember(member);
     if(next==member)break;
     member=next;
    }
    ((Rva00531C5A *)&field1B9F4)->rva00531C8C((unsigned short)index);
   } else {field1B9F4.MakeSet((unsigned short)index);field1BA1C.SetBit(index);}
  }
  }
  field1BA1C.ResetEnum();
  {
  int zone;
  while(field1BA1C.DoEnum(&zone)) {
   CellType &cell=field0C[zone];
   if(cell.type!=0 && cell.type!=4)continue;
   ZoneAdjacencyRange range=((ZoneAdjacencyTable *)((char *)this+0x1770C))->rva00532104((unsigned short)zone);
   for(;range.begin!=range.end;++range.begin) {
    unsigned short other=range.begin->zone;
    CellType &target=field0C[other];
    if(cell.id!=target.id)continue;
    if(target.type!=0 && target.type!=4)continue;
    ((Rva005321D1 *)&field1B9F4)->LinkSets((unsigned short)zone,other);
   }
  }
  }
  while(rva00531DE1()!=24000) {}
 }
}

