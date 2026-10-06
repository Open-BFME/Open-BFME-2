// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GiantBirdAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0036B717,
// 388 bytes. BFME 2 only (no ZH counterpart; BFME 1 has only a byte
// lift). Target evidence: the body runs the pinned AIUpdateInterface ctor
// 0x0026E9BD, stores the five vtables (0x00817A80 primary) and builds three
// members: the 0xC4-byte member DeployStyleAIUpdate also keeps (ctor
// 0x0026AFDA, rowed dtor 0x0026B03D) at +0x3F0, a list at +0x4B4 (the
// ICF-folded STLport _List_base ctor 0x004EC36C; element type not
// established) and the 0x60-byte member at +0x4C8 (ctor 0x00312C95, vtable
// 0x007C7514), zeroing +0x4C4 between them. The body zeroes the scalars and
// four points (+0x3E4, +0x544, +0x560, +0x56C, each through its address),
// sets +0x55C to 2 and ORs bits into five 4-byte file-scope masks at VA
// 0x00E01EC0..0x00E01ED0 (memset by the rowed dynamic initializers
// 0x007AEDE7.., read by GiantBird code at 0x0036877F and 0x00368CD2; kept
// under the ledger's address names). Retail holds the first mask in a
// register and stores it last.
#include <list>
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

extern unsigned char g_00E01EC0[4];
extern unsigned char g_00E01EC4[4];
extern unsigned char g_00E01EC8[4];
extern unsigned char g_00E01ECC[4];
extern unsigned char g_00E01ED0[4];

inline UnsignedInt &maskWord(unsigned char (&mask)[4])
{
	return *(UnsignedInt *)mask;
}

class ObjectModule
{
public:
	virtual ~ObjectModule();
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

// The 0xC4-byte member DeployStyleAIUpdate keeps at +0x3E4 (ctor 0x0026AFDA,
// rowed dtor 0x0026B03D).
class Rva0026AFDAMember
{
public:
	Rva0026AFDAMember();
	~Rva0026AFDAMember();
private:
	unsigned char m_pad[0xC4];
};

// The 0x60-byte member at +0x4C8 (ctor 0x00312C95, vtable 0x007C7514).
class Rva00312C95
{
public:
	Rva00312C95();
	~Rva00312C95();
private:
	unsigned char m_pad[0x60];
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
public:
	GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~GiantBirdAIUpdate();
private:
	Coord3D m_3E4; // +0x3E4
	Rva0026AFDAMember m_3F0; // +0x3F0
	_STL::list<Int> m_4B4; // +0x4B4
	Int m_4B8; // +0x4B8
	Real m_4BC; // +0x4BC
	Int m_4C0; // +0x4C0
	Int m_4C4; // +0x4C4
	Rva00312C95 m_4C8; // +0x4C8
	Int m_528; // +0x528
	Real m_52C; // +0x52C
	Real m_530; // +0x530
	Bool m_534; // +0x534
	Real m_538; // +0x538
	Real m_53C; // +0x53C
	Real m_540; // +0x540
	Coord3D m_544; // +0x544
	Bool m_550; // +0x550
	Int m_554; // +0x554
	Bool m_558; // +0x558
	Int m_55C; // +0x55C
	Coord3D m_560; // +0x560
	Coord3D m_56C; // +0x56C
	Bool m_578; // +0x578
};

GiantBirdAIUpdate::GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData),
	  m_4C4(0)
{
	m_4B8 = 0;
	m_528 = 0;
	m_534 = false;
	m_52C = 0.0f;
	m_530 = 0.0f;
	m_4BC = 0.0f;
	m_538 = 0.0f;
	m_53C = 0.0f;
	m_540 = 0.0f;
	zeroCoord(m_544);
	m_550 = false;

	UnsignedInt mask = maskWord(g_00E01EC0) | 0x28;
	maskWord(g_00E01ECC) |= mask;
	maskWord(g_00E01EC4) |= mask;
	maskWord(g_00E01EC8) |= mask;
	maskWord(g_00E01ECC) |= 4;
	maskWord(g_00E01EC8) |= 2;
	maskWord(g_00E01ECC) |= 2;
	maskWord(g_00E01EC4) |= 4;
	maskWord(g_00E01ED0) |= 0x88;
	maskWord(g_00E01EC0) = mask;

	m_554 = 0;
	m_558 = false;
	m_55C = 2;
	zeroCoord(m_3E4);
	m_4C0 = 0;
	zeroCoord(m_560);
	zeroCoord(m_56C);
	m_578 = false;
}
