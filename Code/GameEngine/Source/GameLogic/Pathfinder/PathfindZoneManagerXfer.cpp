// cl: /O1 /G7 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
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
// qualified lookup ABI; its complete class extent is not claimed.
// Reusing the transferred count as the cell index matches WB source lifetime
// and native stack layout. The block's vector call retains its transfer chain.
struct ICoord2D
{
	int x, y;
};
struct IRegion2D
{
	ICoord2D lo, hi;
};
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool IsCRC()const;
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Xfer &xferIRegion2D(IRegion2D *);
	virtual void slot18();
	virtual Xfer &xferICoord2D(ICoord2D *);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(unsigned *);
	virtual Xfer &xferInt(int *);
	virtual Xfer &xferUnsignedShort(unsigned short *);
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferBool(bool *);
};

void XferWaypointID(Xfer *, int *);
Xfer *Rva005334DBXfer(Xfer *, void *);
struct ZonePortalView
{
	char unknown00[4];
	int id;
};
class Rva00531A44
{
public:
	void rva00531BA7(Xfer *);
	void rva00531ABB(unsigned short);
	unsigned short capacity, first;
	unsigned short *parents;
 unsigned char *ranks;
 unsigned short *next, *last;
 unsigned short rva00531AEE(unsigned short);
 void rva00531B3A(unsigned short);
};
class Rva00531E14
{
public:
	unsigned char rva00531E14(unsigned short);
 unsigned char rva00531DAE(unsigned short);
	unsigned short capacity, first, second, end;
	unsigned short *table;
};

class PathfindCell;
class PathfindLayer {public: char unknown00[0x2C]; unsigned short zone; char unknown2E[0x40-0x2E]; unsigned short getZone()const{return zone;} };
bool Rva001E3679(int);
class Rva005335B0 {public: void rva005335B0(unsigned short,unsigned short);};
// Existing four-byte vector erase ABI view; no application element identity claimed.
class Rva0014921EVector {public: void erase(int*,int*); int *first,*last,*limit;};
class BooleanBitmapSet {public: void SetBit(int); unsigned numBitsDiv32; int *bits; unsigned *summary; unsigned cursor,bit;};
class Rva00532DF6 {public: bool remove(unsigned short,unsigned short); bool add(unsigned short,unsigned short);};
class Rva00532330 {public: bool rva00532330(unsigned short*,unsigned short*);};

class PathfindZoneManager : public Rva00531E14
{
public:
	class CellType
	{
	public:
		void DoXfer(Xfer *);
		union { unsigned value; struct { unsigned type:3, id:6, secondary:6, unknown15:4, bridge:1, unknown20:12; }; };
	};
	class Block
	{
	public:
		void DoXfer(Xfer *);
		int portalCount;
		ZonePortalView *portals[12];
		bool flag34, flag35;
		char unknown36[2];
		char vector38[12];
	};
	void DoXfer(Xfer *);
	void CreateEquivalencySet(unsigned variant, unsigned equivalent);
 void rva005324D8(unsigned char incremental,unsigned short first,unsigned short second);
 bool InEquivSet(unsigned equivalent, unsigned first, unsigned second);
 bool CouldBeInEquivSet(unsigned equivalent, unsigned zone);

 unsigned char rva005316E0(unsigned short first,unsigned short second);
 void rva00532FEA(Block *,PathfindCell **,const IRegion2D&);
 void rva00533664(Block *,PathfindCell **,PathfindLayer *,const IRegion2D&,bool);
	// Accessed layout only. Cell storage's full element count is unproven.
	char unknown0C[0x1B594 - 0xC];
	Rva00531A44 unions[8][7], finalUnion;
	BooleanBitmapSet changed,affected;
	bool flag1BA30, flag1BA31;
	char unknown1BA32[2];
	void *allocation;
	Block **blocks;
	ICoord2D dimensions;
	IRegion2D extent;
};

void PathfindZoneManager::Block::DoXfer(Xfer *xfer)
{
	if (!xfer->IsCRC()) return;
	Rva005334DBXfer(&xfer->xferInt(&portalCount).xferBool(&flag34).xferBool(&flag35), vector38);
	for (int k = 0; k < portalCount; ++k) {
		int id = portals[k]->id;
		XferWaypointID(xfer, &id);
	}
}

void PathfindZoneManager::DoXfer(Xfer *xfer)
{
	if (!xfer->IsCRC()) return;
	xfer->xferBool(&flag1BA30).xferBool(&flag1BA31)
		.xferICoord2D(&dimensions).xferIRegion2D(&extent);
	for (int x = 0; x < dimensions.x; ++x) {
		for (int y = 0; y < dimensions.y; ++y) {
			blocks[x][y].DoXfer(xfer);
		}
	}
	unsigned short k = end;
	xfer->xferUnsignedShort(&k);
	for (k = 0; k < end; ++k) {
		// The established predicate provider is declared as a byte but returns
		// only0/1. Its representation is also the native transferred Bool;
		// this view avoids an unnecessary second boolean normalization.
		union { bool b; unsigned char raw; } value;
		value.raw = rva00531E14(k);
		bool &used = value.b;
		xfer->xferBool(&used);
		if (used) reinterpret_cast<CellType *>(unknown0C)[k].DoXfer(xfer);
	}
	for (unsigned i = 0; i < 8; ++i) {
		xfer->xferUnsignedInt(&i);
		for (unsigned j = 0; j < 7; ++j) {
			xfer->xferUnsignedInt(&j);
			unions[i][j].rva00531BA7(xfer);
		}
	}
	finalUnion.rva00531BA7(xfer);
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

class Rva00531720 {
public: unsigned char rva00531720(unsigned variant, unsigned zone);
};
class Rva00532165 {
public: void rva00532431(unsigned short first, unsigned short second);
};
// WB12D0FB0 names the entire native251B532708..532803 routine.
// Existing transfer bodies establish end+6 and unions1B594[8][7].
// The target uses the established mask predicates531720/531757/5317D7,
// MakeSet531ABB and LinkSets532431 and the concrete returned adjacency pair.
// CouldBeInEquivSet now has its WB-proven owner and exact128B provider.
// InEquivSet has its WB-proven owner and exact260B provider.
void PathfindZoneManager::CreateEquivalencySet(unsigned variant, unsigned equivalent) {
 unions[variant][equivalent].first=0;
 for (unsigned i=0; i<end; ++i)
  unions[variant][equivalent].rva00531ABB((unsigned short)i);
 for (unsigned zone=0; zone<end; ++zone) {
  if (!((Rva00531720 *)this)->rva00531720(variant,zone)) continue;
  if (!CouldBeInEquivSet(equivalent,zone)) continue;
  ZoneAdjacencyRange range=((ZoneAdjacencyTable *)((char *)this+0x1770C))->rva00532104((unsigned short)zone);
  for (; range.begin != range.end; ++range.begin) {
   unsigned short other=range.begin->zone;
   if (!((Rva00531720 *)this)->rva00531720(variant,other)) continue;
   if (!InEquivSet(equivalent,zone,other)) continue;
   ((Rva00532165 *)&unions[variant][equivalent])->rva00532431((unsigned short)zone,other);
  }
 }
}

// WB12D2AB0 names CouldBeInEquivSet. Native531757..5317D7 proves
// the4B cell type[0:2] and bridge bit19; native CellType::DoXfer531978
// independently transfers the3/6/6-bit fields. Names type/id/secondary/bridge
// describe their uses; original bitfield names remain unproven. A packed
// bitfield view reproduces every byte including shared true/false tails.
bool PathfindZoneManager::CouldBeInEquivSet(unsigned equivalent, unsigned zone) {
 CellType *c = reinterpret_cast<CellType *>(unknown0C)+zone;
switch (equivalent) {
case 0:
 break;
case 1:
 if (c->type != 0 && c->type != 2) return false;
 break;
case 2:
 if (c->type != 0 && c->type != 7 && c->type != 1) return false;
 break;
case 4:
 if (c->type != 7 && c->type != 1) return false;
 break;
case 3:
 if (c->type != 0 && c->type != 3) return false;
 break;
case 6:
 if (c->type != 0 && c->type != 3 && c->type != 4) return false;
 if (c->type == 4 && !c->bridge) return false;
 break;
case 5:
 if (c->type != 2) return false;
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
 CellType *a = reinterpret_cast<CellType *>(unknown0C)+first;
 CellType *c = reinterpret_cast<CellType *>(unknown0C)+second;
 if (a->type == c->type) {
 if (a->id == c->id || a->id == c->secondary || a->secondary == c->id || (a->secondary == 16 && c->secondary == 16)) return true;
 }
switch (equivalent) {
case 0:
 return false;
case 1:
 if (a->id != c->id) return false;
 if (c->type != 0 && c->type != 2) return false;
 break;
case 2:
 if (a->id != c->id) return false;
 if (c->type != 0 && c->type != 7 && c->type != 1) return false;
 break;
case 4:
 if (a->id != c->id) return false;
 if (c->type != 7 && c->type != 1) return false;
 break;
case 3:
 if (a->id != c->id) return false;
 if (c->type != 0 && c->type != 3) return false;
 break;
case 6:
 if (a->id != c->id) return false;
 if (c->type != 0 && c->type != 3 && c->type != 4) return false;
 if (c->type == 4 && !c->bridge) return false;
 break;
case 5:
 if (c->type != 2) return false;
 break;
}
 return true;
}

// Whole native109B531B3A..531BA7 and WB12D3B00 establish set reset.
// FindSet531AEE chooses the first member; each cyclic member becomes its
// own parent/next/last with rank0. WB uses a32-bit following index, then
// narrows when advancing the16-bit member; this reproduces native peeling.
// Original reset method name remains unknown; no getter identity inferred.
void Rva00531A44::rva00531B3A(unsigned short n) {
 n = rva00531AEE(n);
 do {
  int following = next[n];
  last[n] = n;
  next[n] = n;
  parents[n] = n;
  ranks[n] = 0;
  if (following == n) break;
  n = (unsigned short)following;
 } while (true);
}

// Native109B531C8C..531CF9 repeats the reset with FindSet531C5A.
// WB12D3B90 GetNextSetMember mapping is refuted by native writes;
// Update533BEC consumes no result. This remains an address-qualified
// reset with independently proven20B layout and existing FindSet provider.
class Rva00531C5A {
public: unsigned short rva00531C5A(unsigned short);
 void rva00531C8C(unsigned short);
 unsigned short capacity, first;
 unsigned short *parents;
 unsigned char *ranks;
 unsigned short *next, *last;
};
void Rva00531C5A::rva00531C8C(unsigned short n) {
 n = rva00531C5A(n);
 do {
  int following = next[n];
  last[n] = n;
  next[n] = n;
  parents[n] = n;
  ranks[n] = 0;
  if (following == n) break;
  n = (unsigned short)following;
 } while (true);
}

class Rva005321D1 { public: void rva00532455(unsigned short,unsigned short); };

// Full native560B5324D8..532708 and WB12D0B40 establish the typed
// cell-pair masks and eight-by-seven union dispatch. Incremental is tested
// as a byte boolean; starting variants0/1 and stepping2 preserves native.
// Shared type/ID/secondary/bridge bitfields reproduce the entire routine
// on the first direct trial, including repeated mode2 and mode6 merges.
// Original method name unknown; manager receiver follows independently
// verified cell/union layout and Update533BEC callers. No new pins.
void PathfindZoneManager::rva005324D8(unsigned char incremental,unsigned short first,unsigned short second) {
 CellType *a=reinterpret_cast<CellType *>(unknown0C)+first;
 CellType *b=reinterpret_cast<CellType *>(unknown0C)+second;
 unsigned mask=(1u<<a->type)|(1u<<b->type);
 for(int variant=incremental ? 1:0;variant<8;variant+=2) {
  if(!((Rva00531720 *)this)->rva00531720(variant,first) || !((Rva00531720 *)this)->rva00531720(variant,second))continue;
  bool joined=false;
  if(a->type==b->type && (a->id==b->id || a->id==b->secondary || a->secondary==b->id || (a->secondary==16 && b->secondary==16))) {
   joined=true;
   ((Rva00532165 *)&unions[variant][0])->rva00532431(first,second);
  }
  if(a->id==b->id || joined) {
   if(!(mask & ~5u)) ((Rva00532165 *)&unions[variant][1])->rva00532431(first,second);
   if(!(mask & ~3u)) ((Rva00532165 *)&unions[variant][2])->rva00532431(first,second);
   if(!(mask & ~0x81u)) ((Rva00532165 *)&unions[variant][2])->rva00532431(first,second);
   if(!(mask & ~0x82u)) ((Rva00532165 *)&unions[variant][2])->rva00532431(first,second);
   if(!(mask & ~0x82u)) ((Rva00532165 *)&unions[variant][4])->rva00532431(first,second);
   if(!(mask & ~9u)) {
    ((Rva00532165 *)&unions[variant][3])->rva00532431(first,second);
    ((Rva00532165 *)&unions[variant][6])->rva00532431(first,second);
   }
   if(!(mask & ~0x11u) && (a->type!=4 || a->bridge) && (b->type!=4 || b->bridge))
    ((Rva00532165 *)&unions[variant][6])->rva00532431(first,second);
  }
  if(mask==4) ((Rva00532165 *)&unions[variant][5])->rva00532431(first,second);
 }
 if(incremental && a->id==b->id && !(mask & ~0x11u))
  ((Rva005321D1 *)&finalUnion)->rva00532455(first,second);
}

class PathfindCell {
public:
 char unknown00[8]; unsigned short zone; char unknown0A[2];
 union { unsigned value; struct {
 unsigned type:4,id:6,secondary:6,unknown16:1,flag17:1,flag18:1,kind:2,unknown21:1,flag22:1,unknown23:9;
 }; };
 unsigned short getZone() const { return zone; }
 // Integer-promoted access matches native address selection in link creation.
 int getZoneInt()const{return zone;}

 unsigned char get17() const { return (unsigned char)flag17; }
 unsigned char get18() const { return (unsigned char)flag18; }
 unsigned char get22() const { return (unsigned char)flag22; }
};

bool Rva0053166DEqual(const PathfindCell *a,const PathfindCell *b) {
 return a->type==b->type && a->id==b->id && a->secondary==b->secondary &&
  a->get17()==b->get17() && a->get18()==b->get18() && a->kind==b->kind && a->get22()==b->get22();
}

// WB 0x012D0A40 and native 0x0053166D..0x005316E0 prove this comparison.
// The original function name is unknown. Packed DWORD fields are at cell+0x0C;
// byte-return flag accessors preserve retail promotion and the bool result ABI.


// Native 0x005316E0..0x00531720: exclude an identical zone; otherwise
// zones with the same six-bit id or three-bit type can be connected.
// CellType fields are independently supported by DoXfer and equivalency methods.
unsigned char PathfindZoneManager::rva005316E0(unsigned short first,unsigned short second) {
 if(first==second)return 0;
 CellType *a=(CellType*)((char*)this+0xC)+first;
 CellType *b=(CellType*)((char*)this+0xC)+second;
 unsigned av=a->value,bv=b->value;
 if(a->id==b->id)return 1;
 unsigned char type=av;
 type^=bv;
 return (type & 7)==0;
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
   changed.SetBit(first);changed.SetBit(second);
  }
 }
 }
 {
 int x,y;
 for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(x<bounds.hi.x && rva005316E0(map[x][y].getZone(),map[x+1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][y].getZone(),map[x+1][y].getZone())) {
     changed.SetBit(map[x][y].getZone());changed.SetBit(map[x+1][y].getZone());
    }
   }
   if(y<bounds.hi.y && rva005316E0(map[x][y].getZone(),map[x][y+1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][y].getZone(),map[x][y+1].getZone())) {
     changed.SetBit(map[x][y].getZone());changed.SetBit(map[x][y+1].getZone());
    }
   }
   if(rva00531DAE(map[x][y].getZone())) {
    changed.SetBit(map[x][y].getZone());
    for(int i=0;i<8;i+=2)for(int j=0;j<7;++j)unions[i][j].rva00531B3A(map[x][y].getZone());
   }
  }
 }
 }
 if(bounds.lo.x>extent.lo.x) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
     changed.SetBit(map[bounds.lo.x][y].getZone());changed.SetBit(map[bounds.lo.x-1][y].getZone());
    }
   }
  }
 }
 if(bounds.hi.x<extent.hi.x) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
     changed.SetBit(map[bounds.hi.x][y].getZone());changed.SetBit(map[bounds.hi.x+1][y].getZone());
    }
   }
  }
 }
 if(bounds.lo.y>extent.lo.y) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
     changed.SetBit(map[x][bounds.lo.y].getZone());changed.SetBit(map[x][bounds.lo.y-1].getZone());
    }
   }
  }
 }
 if(bounds.hi.y<extent.hi.y) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->remove(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
     changed.SetBit(map[x][bounds.hi.y].getZone());changed.SetBit(map[x][bounds.hi.y+1].getZone());
    }
   }
  }
 }
}

// Native 0x00533664..0x00533AF9 and WB0x012D12B0 establish block link
// creation including special layer links and selectively incremental borders.
// Manager/cell offsets and layer stride64 come from target access instructions.
void PathfindZoneManager::rva00533664(Block *block,PathfindCell **map,PathfindLayer *layers,const IRegion2D& bounds,bool incremental) {
 Rva0014921EVector *entries=(Rva0014921EVector*)block->vector38;
 entries->erase(entries->first,entries->last);
 {
 int x,y;
 for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   PathfindCell *cell=&map[x][y];
   if(x<bounds.hi.x) {
    unsigned short next=map[x+1][y].getZoneInt();
    if(rva005316E0(map[x][y].getZoneInt(),next)) {
     if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[x][y].getZoneInt(),next)) {
      changed.SetBit(map[x][y].getZoneInt());changed.SetBit(map[x+1][y].getZoneInt());
     }
    }
   }
   if(y<bounds.hi.y && rva005316E0(map[x][y].getZoneInt(),map[x][y+1].getZoneInt())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[x][y].getZoneInt(),map[x][y+1].getZoneInt())) {
     changed.SetBit(map[x][y].getZoneInt());changed.SetBit(map[x][y+1].getZoneInt());
    }
   }
   unsigned secondary=cell->secondary;
   if(Rva001E3679(secondary) && cell->type==0) {
    unsigned short goal=layers[secondary].getZone();
    ((Rva005335B0*)block)->rva005335B0(cell->getZone(),goal);
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(cell->getZone(),goal)) {
     changed.SetBit(cell->getZone());changed.SetBit(goal);
    }
   }
  }
 }
 }
 if(bounds.lo.x>extent.lo.x && incremental) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[bounds.lo.x][y].getZone(),map[bounds.lo.x-1][y].getZone())) {
     changed.SetBit(map[bounds.lo.x][y].getZone());changed.SetBit(map[bounds.lo.x-1][y].getZone());
    }
   }
  }
 }
 if(bounds.hi.x<extent.hi.x) {
  int y;
  for(y=bounds.lo.y;y<=bounds.hi.y;++y) {
   if(rva005316E0(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[bounds.hi.x][y].getZone(),map[bounds.hi.x+1][y].getZone())) {
     changed.SetBit(map[bounds.hi.x][y].getZone());changed.SetBit(map[bounds.hi.x+1][y].getZone());
    }
   }
  }
 }
 if(bounds.lo.y>extent.lo.y && incremental) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[x][bounds.lo.y].getZone(),map[x][bounds.lo.y-1].getZone())) {
     changed.SetBit(map[x][bounds.lo.y].getZone());changed.SetBit(map[x][bounds.lo.y-1].getZone());
    }
   }
  }
 }
 if(bounds.hi.y<extent.hi.y) {
  int x;
  for(x=bounds.lo.x;x<=bounds.hi.x;++x) {
   if(rva005316E0(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
    if(((Rva00532DF6*)((char*)this+0x1770C))->add(map[x][bounds.hi.y].getZone(),map[x][bounds.hi.y+1].getZone())) {
     changed.SetBit(map[x][bounds.hi.y].getZone());changed.SetBit(map[x][bounds.hi.y+1].getZone());
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
