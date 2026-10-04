// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptActions::doUnitGarrisonNearestBuilding, retail 0x003C8F86, 299 bytes
// (called from the action dispatcher 0x003CA4BE at 0x003CC1DF). Zero Hour's
// body without the money-hacker internet-centre switch and the locomotor
// reset, over BFME2's linked filters: walking objects of kinds 7 and 118
// that share the unit's map status from near to far, the unit enters (the
// AI command 0x0026C347) the first whose contain module (+0x250) is free or
// already entered by the unit's player, skipping one whose slot-1 record
// exists with +0xDE clear.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
#include "ascii_string.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// A KindOfMaskType with two kinds set (0x0006EE7A).
struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int bit1, int bit2);
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class Player
{
public:
	unsigned int getPlayerMask() const { return 1 << m_index; }
	char m_pad00[0x54];
	int m_index;	// +0x54
};

struct Rva003C8F86Contained
{
	char m_pad000[0xDE];
	bool m_DE;	// +0xDE
};

// The +0x250 contain module interface; only the slots this action calls.
class ContainModuleInterface
{
public:
	virtual void v00() = 0;
	virtual const Rva003C8F86Contained *getContained() const = 0;	// slot 1
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v0A() = 0;
	virtual void v0B() = 0;
	virtual void v0C() = 0;
	virtual void v0D() = 0;
	virtual void v0E() = 0;
	virtual void v0F() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v1A() = 0;
	virtual void v1B() = 0;
	virtual void v1C() = 0;
	virtual void v1D() = 0;
	virtual void v1E() = 0;
	virtual void v1F() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v2A() = 0;
	virtual void v2B() = 0;
	virtual void v2C() = 0;
	virtual void v2D() = 0;
	virtual void v2E() = 0;
	virtual void v2F() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v3A() = 0;
	virtual void v3B() = 0;
	virtual void v3C() = 0;
	virtual void v3D() = 0;
	virtual void v3E() = 0;
	virtual void v3F() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v4A() = 0;
	virtual void v4B() = 0;
	virtual void v4C() = 0;
	virtual void v4D() = 0;
	virtual void v4E() = 0;
	virtual void v4F() = 0;
	virtual void v50() = 0;
	virtual unsigned int getPlayerWhoEntered() const = 0;	// slot 81 (+0x144)
};

class AICommandInterface
{
public:
	void rva0026C347(Object *obj, CommandSourceType source);	// 0x0026C347
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;	// +0x20
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	ContainModuleInterface *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x250 - 0x44];
	ContainModuleInterface *m_contain;	// +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;	// +0x258
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class ScriptEngine
{
public:
	Object *getUnitNamed(const AsciiString &name);	// 0x003588E7
};
extern ScriptEngine *TheScriptEngine;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doUnitGarrisonNearestBuilding(const AsciiString &unitName);
};

void ScriptActions::doUnitGarrisonNearestBuilding(const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit)
		return;

	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai)
		return;

	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(theUnit->getPosition(), REALLY_FAR, 2,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 7, 118),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(&Rva002611BFFilter(theUnit)), 1);

	Object *theBuilding;
	while ((theBuilding = iter.next()) != 0) {
		ContainModuleInterface *contain = theBuilding->getContain();
		if (!contain)
			continue;
		if (contain->getContained() && !contain->getContained()->m_DE)
			continue;
		unsigned int player = theBuilding->getContain()->getPlayerWhoEntered();
		if (player != 0 && player != theUnit->getControllingPlayer()->getPlayerMask())
			continue;
		ai->m_commands.rva0026C347(theBuilding, CMD_FROM_SCRIPT);
		return;
	}
}
