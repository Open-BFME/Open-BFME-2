// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// FireLogicSystem lifetime: native typed BurningCell tree construction,
// teardown and the sole use-counted registration object at VA DBB750.
// The wrapper destructor28691C is distinct from tree destructor28681A.
// Byte, vtable and initialized-data evidence is recorded under
// reverse/attempt_support/firelogic-lifetime-link-20261024/.
// Thing+0x04 under a template flag test.
#define COORD3D_VIEW_DTOR
#include "Lib/Coord3DCtorView.h"
#define COORD2D_VIEW_DTOR
#include "Lib/Coord2DCtorView.h"
#include "Lib/ICoord2D.h"

typedef int Int;

#include <math.h>
#include <set>

__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#include "../../../Include/GameLogic/Rva00065964ObjectPool.h"
extern Rva00065964ObjectPool g_pool00286136;
extern Rva00065964ObjectPool g_pool00286116;
void Rva00286116Free(void *node);

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class ThingTemplate;

struct BfmeVecVNB
{
	float x;
	float y;
	float z;
};
// A geometry shape (36 bytes): 0x006BD390 moves a point by the shape's
// offset rotated through the angle.
class BfmeXformVNB
{
public:
	void bfmeApplyVNB(BfmeVecVNB *out, float angle);
	Int m_type;			// +0x00, 0/1 circle, 2 box
	Int m_04;
	float m_major;		// +0x08
	float m_minor;		// +0x0C
	Coord3D m_offset;	// +0x10
	Int m_1C;
	bool m_active;		// +0x20
};
struct BfmeShapeE15 : public BfmeXformVNB
{
};
class BfmeObjE15
{
public:
	BfmeShapeE15 *getGeometryShape(int i);
	Int m_00;
	bool m_small;			// +0x04
	char m_pad05[0x10 - 0x05];
	float m_boundingRadius;	// +0x10
	char m_pad14[0x2C - 0x14];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
};
float Cos(float a);
float Sin(float a);
// The object FireLogicSystem's Register/UnregisterObject twins (0x00287C21
// and 0x00287C39) hand to 0x00287552.
struct Rva00287C21Other
{
	Int m_00;
	const ThingTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;						// +0x38
	float m_angle;						// +0x44
	char m_pad48[0x74 - 0x48];
	ObjectID m_id;						// +0x74
	char m_pad78[0xA8 - 0x78];
	BfmeObjE15 m_geometry;				// +0xA8
	ObjectID getID() const { return m_id; }
	char m_padDC[0x49C - 0xDC];
	Int m_watchCount;					// +0x49C, -1 when not watching
	void *m_watchList;					// +0x4A0
};
static inline unsigned int TemplateKindBits(const ThingTemplate *thingTemplate)
{
	return *(const unsigned int *)((const char *)thingTemplate + 0x108);
}

// The flammability a template gives its cell (WB reads it at +0x314).
struct FlammabilityData
{
	unsigned short m_fuel;	// +0x314
	Int m_field18;		// +0x318, 12-bit cell field
	Int m_flammability;	// +0x31C, 10-bit cell field
	Int m_field10;		// +0x320, 8-bit cell field
};

// A burning cell's key in m_cellsOnFire: the cell's world-centre
// coordinates (constructed at 0x00285B91, destroyed at 0x00285BEC).
#include "../../Common/Rva00285BEC.h"

// m_cellsOnFire's tree find (0x00286214) and erase (0x002860CF).
class Rva00285672;
struct Rva00286214Node;
struct Rva002860CFIterator
{
	Rva00286214Node *m_node;
	Rva002860CFIterator(Rva00286214Node *node) : m_node(node) {}
	Rva002860CFIterator(const Rva002860CFIterator &that) : m_node(that.m_node) {}
};
class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
};
struct Rva00287B2AResult;
struct Rva0028688AKey;
struct Rva0028688ANode;
typedef _STL::_Rb_tree<Rva00285BEC, Rva00285BEC,
    _STL::_Identity<Rva00285BEC>, _STL::less<Rva00285BEC>,
    _STL::allocator<Rva00285BEC> > FireCellTree;

namespace _STL {
template<> inline __declspec(noinline) FireCellTree::~_Rb_tree() { clear(); }
}

class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
 __declspec(noinline) Rva00287B2AResult rva00287B2A(const Rva00285672 *key);
	void erase(Rva002860CFIterator pos) { ((Rva002860CFHost *)this)->rva002860CF(pos); }
	__declspec(noinline) Rva00286214(); // empty-tree wrapper 242F01
	~Rva00286214() {} // inlines tree teardown; EH outlines wrapper28691C
	FireCellTree m_tree;
};


inline Rva00286214::Rva00286214()
    : m_tree(_STL::less<Rva00285BEC>(), FireCellTree::allocator_type())
{
}

// Coord3D's sub and dot as WorldBuilder calls them out of line (WB 0x40b88e
// and 0x40b7d0); retail inlines both and the canonical header lacks them.
// The area's shape (PolygonTrigger +8): its bounds come back through
// 0x0030B6E3 and 0x00285B66 tests a cell centre against it.
#include "../../../../Libraries/Include/Lib/Region2D.h"
bool __cdecl rva00285B66(const void *point, const void *region);
class PolygonTrigger;

// The subsystem base (ctor 0x001B4E63, dtor 0x001B4E74) and Snapshot at
// +0x0C, the second base whose vtable 0x00BBB554 the destructor restores.
typedef bool Bool;
#include "../../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// A material entry (0x18 bytes): the array constructor zeroes all six
// dwords (0x00286297) and the destructor releases the string at +4
// (0x0029D7C2, folded with CameraMarker's).
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct Rva00286297
{
	Rva00286297();
	~Rva00286297() {}
	Int unknown00;
	AsciiString unknown04;
	Int fuel;
	unsigned int field18, field00, field10;
};

// The FireLogicSystem block-parse registration (VA 0x00DBB750: vtable
// 0x00BFB730 and a use count at +4). The first live system registers it
// through 0x0020DFFB and the last
// one out removes it through 0x0020DAE0; only these two bodies touch it.
class ModuleData;
void __cdecl Rva0020DFFBRegister(const ModuleData *);
void __cdecl Rva0020DAE0(void *);
#include "FireLogicSystemParseRegistration.h"


// Keep the existing by-value descriptor identity; its twelve-byte view
// and copy operation come from the rowed getter at286356 and copy3ED658.
#include "../../../Include/GameLogic/Rva003ED658.h"
class Rva002862C9
{
public:
    LargeGroupAudioKeyMap *rva002862C9();
};
Rva00285D27::Rva00285D27()
{
}
Rva003ED658 Rva00285D27::rva00286356()
{
    return *reinterpret_cast<const Rva003ED658 *>(
        ((Rva002862C9 *)this)->rva002862C9());
}

// MSVC folds this visible constructor into initialized storage: native
// vfptr plus zero count, without a CRT startup function or a hand table.
FireLogicSystemParseRegistration theFireLogicSystemParseRegistration;

class FireLogicSystem : public SubsystemInterface, public Snapshot
{
public:
	FireLogicSystem();
	virtual ~FireLogicSystem();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void xfer(Xfer *xfer);
	void ChangeBurnRate(Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRate(const Coord3D *origin, const Coord3D *dir, float threshold, Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRateInArea(const Coord3D *pos, float radius, Int delta, bool onlyBurning);
	void ChangeBurnRateInArea(const Coord3D *pos, float radius, const Coord3D *dir, float threshold, Int delta, bool onlyBurning);
	void rva002872BA(const PolygonTrigger *area, Int delta, bool onlyBurning);
	void ChangeCellToObjectFlammability(Int x, Int y, const ThingTemplate *tmpl);
    void rva0028641F(unsigned int id, const Coord3D *pos);
    void ResetCellToOriginalFlammability(Int x, Int y);
	void rva00286373(Int id, const Coord3D *pos, const ThingTemplate *tmpl);
	void *rva00286D4E(ObjectID id, Int x, Int y, bool add);
	void rva00287552(Rva00287C21Other *obj, int add);
	bool rva00286772(const PolygonTrigger *area, Int minBurn);
	void rva00286CC4();
private:
	// A cell's watcher list (16-byte nodes from the 0xDFEC94 pool).
	struct WatcherNode
	{
		WatcherNode *m_next;
		WatcherNode *m_objectNext;	// +0x04, the watching object's own list
		ObjectID m_id;
		unsigned short m_x;
		unsigned short m_y;
	};
	struct ObjectNode
	{
		Int m_id;
		ObjectNode *m_next;
	};
	struct Cell
	{
		Int m_type;
		unsigned short m_fuel;
		unsigned short m_check;
		unsigned int m_flammability : 10;
        unsigned int m_field10 : 8;
        unsigned int m_field18 : 12;
        unsigned int m_field30 : 1;
        unsigned int m_field31 : 1;
		WatcherNode *m_0C;
		ObjectNode *m_objects; // +0x10
	};
	typedef Rva00286297 Material;
    Material m_materials[4];	// +0x10
	Cell **m_cells;
	Cell *m_storage;	// +0x74, the rows' shared cell block
	Int m_numRows;
	Int m_numCols;
	Int m_80;
	Rva00286214 m_cellsOnFire;
	Int m_90;
	Int m_94;
	Int m_98;
	Int m_9C;
};

// ??0FireLogicSystem@@QAE@XZ @0x00286EC8
FireLogicSystem::FireLogicSystem()
	: m_cells(0), m_storage(0), m_numRows(0), m_numCols(0), m_80(0),
	  m_90(0x7FFFFFFF), m_94(1), m_98(0), m_9C(0)
{
	if (theFireLogicSystemParseRegistration.m_registration.m_useCount == 0)
		Rva0020DFFBRegister((const ModuleData *)&theFireLogicSystemParseRegistration);
	++theFireLogicSystemParseRegistration.m_registration.m_useCount;
}

// ??1FireLogicSystem@@UAE@XZ @0x00286F8F
FireLogicSystem::~FireLogicSystem()
{
	rva00286CC4();
	if (--theFireLogicSystemParseRegistration.m_registration.m_useCount == 0)
		Rva0020DAE0(&theFireLogicSystemParseRegistration);
}
