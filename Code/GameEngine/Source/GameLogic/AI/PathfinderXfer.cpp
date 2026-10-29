// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Pathfinder::xfer, native 002F21F9..002F23A6 (429B), thiscall RET4.
// Its vtable slot (00805404) follows the snapshot name getter at 002F21EB
// that returns "Pathfinder". A light CRC transfers nothing. A CRC walk
// covers the extent (+10), the two flags (+04, +34), the ObjectID at +44,
// the counters and the 64-float table (+1BEB4, +1BEB8 through rowed
// 002E7FED), +38, the two bytes at +1BEB0/+1BEB1, every live cell of the
// column map (+0C, bounded by the extent's high corner), the sixteen 0x40
// byte layers at +5C and the zone manager at +45C. A save or load writes
// version 3: the four ints at +28 +2C +20 +24, a dropped int for versions
// before 3, the set<int> at +1C1BC (rowed 002F1CDD), the int at +1C1B8 and,
// from version 2, the two 0x808-byte request rings at +1C1DC and +1C9E4
// (unrowed 002EAC9F). BFME1's 003E38F0 Pathfinder::xfer has the same CRC
// order without the BFME2 additions. Field names stay offset-derived.

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"

enum ObjectID { INVALID_OBJECT_ID = 0 };

class UnicodeString;
class AsciiString;
class PooledString;
struct XferUnknown11;
struct Coord3D;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
struct Coord2D;
struct ICoord2D;
struct Region2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
class Snapshot;

class Coord3DBase;
struct IRegion2D;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char minimum, unsigned char current)
		: m_minimum(minimum), m_current(current) {}

	unsigned char m_minimum;
	unsigned char m_current;
};

void XferObjectID(Xfer *xfer, ObjectID *value);

// Rowed 002E7FED keeps its address-derived receiver spelling for Xfer.
class Rva002E7FED;
Rva002E7FED *Rva002E7FEDGet(Rva002E7FED *xfer, int *values);

namespace _STL {
template <class T> struct less;
template <class T> class allocator;
template <class K, class C, class A> class set;
}
typedef _STL::set<int, _STL::less<int>, _STL::allocator<int> > PathfinderIntSet;
Xfer *Rva002F1CDDXfer(Xfer *xfer, PathfinderIntSet *values);

class PathfindCell
{
public:
	void DoXfer(Xfer *xfer);

	void *m_info;		// +00
	int m_04;
	int m_08;
	int m_0C;
};

class PathfindLayer
{
public:
	void ClassifyWallCells();
	void ClassifyBridgeCells();
	void allocateCells(const IRegion2D *extent);
	__declspec(noinline) void rva000B3FD0();
	bool setDestroyed(bool destroyed);
	void rva003666FD(Xfer *xfer);
	void rva00366DEC();
	PathfindCell *getCell(int,int);
private:
	char storage[0x40]; // +0x00
};

class PathfindZoneManager
{
public:
	void DoXfer(Xfer *xfer);
};

class PathfindRequestRing
{
public:
	enum { RING_SIZE = 512 };
	bool hasRoom() const;
	void push(const ObjectID &id);
	bool contains(const ObjectID &id) const;
private:
	static int next(int slot) { return slot != RING_SIZE - 1 ? slot + 1 : 0; }
public:
	void rva002EAC9F(Xfer *xfer);
private:
	ObjectID m_requests[RING_SIZE]; // +0x00
	int m_head; // +0x800
	int m_tail; // +0x804
};

class Pathfinder
{
public:
	virtual void xfer(Xfer *xfer);

	bool m_04;				// +04
	char m_pad05[0x0C - 0x05];
	PathfindCell **m_map;			// +0C
	IRegion2D m_extent;			// +10
	int m_20;				// +20
	int m_24;				// +24
	int m_28;				// +28
	int m_2C;				// +2C
	char m_pad30[0x34 - 0x30];
	bool m_34;				// +34
	char m_pad35[0x38 - 0x35];
	int m_38;				// +38
	char m_pad3C[0x44 - 0x3C];
	ObjectID m_44;				// +44
	char m_pad48[0x5C - 0x48];
	PathfindLayer m_layers[16];		// +5C
	PathfindZoneManager m_zoneManager;	// +45C
	char m_pad45D[0x1BEB0 - 0x45D];
	bool m_1BEB0;				// +1BEB0
	bool m_1BEB1;				// +1BEB1
	char m_pad1BEB2[0x1BEB4 - 0x1BEB2];
	int m_1BEB4;				// +1BEB4
	int m_1BEB8[64];			// +1BEB8
	char m_pad1BFB8[0x1C1B8 - 0x1BFB8];
	int m_1C1B8;				// +1C1B8
	char m_set1C1BC[0x1C1DC - 0x1C1BC];	// +1C1BC, set<int>
	PathfindRequestRing m_ring1C1DC;	// +1C1DC
	PathfindRequestRing m_ring1C9E4;	// +1C9E4
};

void Pathfinder::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	if (xfer->IsCRC()) {
		*xfer == m_extent;
		*xfer == m_04;
		*xfer == m_34;
		XferObjectID(xfer, &m_44);
		*xfer == m_1BEB4;
		Rva002E7FEDGet((Rva002E7FED *)xfer, m_1BEB8);
		*xfer == m_38;
		*xfer == m_1BEB0;
		*xfer == m_1BEB1;
		if (m_map != 0) {
			for (int y = 0; y <= m_extent.hi.y; ++y) {
				for (int x = 0; x <= m_extent.hi.x; ++x) {
					if (m_map[x][y].m_info != 0)
						m_map[x][y].DoXfer(xfer);
				}
			}
		}
		for (int i = 0; i < 16; ++i)
			m_layers[i].rva003666FD(xfer);
		m_zoneManager.DoXfer(xfer);
	} else {
		Xfer::Version version(1, 3);
		*xfer == version;
		*xfer == m_28;
		*xfer == m_2C;
		*xfer == m_20;
		*xfer == m_24;
		if (version.m_current < 3) {
			int dropped = 0;
			*xfer == dropped;
		}
		Rva002F1CDDXfer(xfer, (PathfinderIntSet *)m_set1C1BC);
		*xfer == m_1C1B8;
		if (version.m_current >= 2) {
			m_ring1C1DC.rva002EAC9F(xfer);
			m_ring1C9E4.rva002EAC9F(xfer);
		}
	}
}
