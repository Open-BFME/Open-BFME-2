// cl: /O1 /G7 /MD
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
	char unknown04[16];
};
class Rva00531E14
{
public:
	unsigned char rva00531E14(unsigned short);
	unsigned short capacity, first, second, end;
	unsigned short *table;
};

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
 bool CouldBeInEquivSet(unsigned equivalent, unsigned zone);

	// Accessed layout only. Cell storage's full element count is unproven.
	char unknown0C[0x1B594 - 0xC];
	Rva00531A44 unions[8][7], finalUnion;
	char unknown1BA08[0x28];
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
struct ZoneNeighborRecord { unsigned short zone, unknown; };
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
class Rva002E99F9Sub460 {
public:
 bool rva005317D7(unsigned equivalent, unsigned first, unsigned second);
};
class Rva00532165 {
public: void rva00532431(unsigned short first, unsigned short second);
};
// WB12D0FB0 names the entire native251B532708..532803 routine.
// Existing transfer bodies establish end+6 and unions1B594[8][7].
// The target uses the established mask predicates531720/531757/5317D7,
// MakeSet531ABB and LinkSets532431 and the concrete returned adjacency pair.
// CouldBeInEquivSet now has its WB-proven owner and exact128B provider.
// InEquivSet remains a neutral view until its own body is admitted.
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
   if (!((Rva002E99F9Sub460 *)this)->rva005317D7(equivalent,zone,other)) continue;
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
