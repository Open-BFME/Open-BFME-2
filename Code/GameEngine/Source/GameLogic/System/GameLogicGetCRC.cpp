// cl: /DNDEBUG /MD /EHsc -Ireference/shims/moduledata
//
// ?getCRC@GameLogic@@QAEIH@Z @0x0023CB2C 542B
// Evidence: LINK BONUS 1 file 51B; donor BFME1 GameLogicCRC.cpp getCRC plus BFME2 BFMECRCWriter ctor 0x00225A2D; callers 0x0024583A 0x00245861 0x002CEA44 0x002CEA8D; neighbours 0x0023CAD2 0x0023CD97 same class GameLogic first at +0xAC.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
void setFPMode();
unsigned int GetGameLogicRandomSeedCRC();

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/Thing/thing.h"
#include "Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };
class Module;
class Drawable;
class Player;
class AIGroup;
class Pathfinder;
class Rva002E2903Player;
class Rva0020E6B7RegionManager;

class SystemBase
{
public:
	virtual ~SystemBase();
private:
	char m_pad[8];
};

// PartitionRangeQueryCallView.h pads this manager's two bases over +0x00..+0x10;
// this view spells them for the Snapshot upcast.
class PartitionManager;
class PartitionManagerSnapshotView : public SystemBase, public Snapshot
{
};

class CollisionManager : public SystemBase, public Snapshot
{
};

class ShroudManager : public SystemBase, public Snapshot
{
};

class TaintManager : public SystemBase, public Snapshot
{
};

class SkirmishAIManager : public SystemBase, public Snapshot
{
};

class PlayerList : public SystemBase, public Snapshot
{
public:
	Player *Rva002A7A6F(int index);
	Player *getEachPlayerFromMask(int &mask);
	Player *getNthPlayer(int i);
};

class AI : public SystemBase, public Snapshot
{
public:
	AIGroup *createGroup(void);
	void destroyGroup(AIGroup *group); // destroyGroup
	Pathfinder *m_pf; // +0x10
};

class Rva002BA8F1Logic : public SystemBase, public Snapshot
{
public:
	Rva002E2903Player *find(int,unsigned*);

	char pad[0xB0 - 0x10];
	Rva0020E6B7RegionManager *regions; // +0xB0
	char padB4[4];
	int currentRegion; // +0xB8
};

class Object : public Thing, public Snapshot
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType key) const {return findModule(key);}
	bool isMassSelectable() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
	void friend_bindToDrawable( Drawable *draw );
	void rva0028B31A(int val);
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }

	char m_pad64[0x74 - 0x64];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
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

class XferSave
{
public:
	XferSave();
	virtual ~XferSave();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int beginBlock(const char *name);
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
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
	virtual void xferUnsignedInt(unsigned int *value);
	virtual void slot31();
	virtual void slot32();
private:
	char m_data[0x3C];
};

class BFMECRCWriter : public XferSave
{
public:
	BFMECRCWriter(bool full);
	bool m_full;
	unsigned int m_crc;
};

class Rva0060D4C9
{
public:
	unsigned char rva0060D4C9(Xfer *stream);
};

class Rva002CEC0A
{
public:
	void rva002CED26(Xfer *xfer);
};

class Gen009D6DD0
{
public:
	void bfmeClose();
};

class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};

extern "C" void *theLogicRandomLogFile;
extern bool TheLiteCRC;
extern bool TheLiteCRC;
// g_00E02D7C is only an alias of the owned global TheXObjectCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXObjectCRC;
#define g_00E02D7C (*(unsigned char *)&TheXObjectCRC)
// g_00E02D7D is only an alias of the owned global TheXPartitionCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXPartitionCRC;
#define g_00E02D7D (*(unsigned char *)&TheXPartitionCRC)
// g_00E02D7E is only an alias of the owned global TheXCollisionCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXCollisionCRC;
#define g_00E02D7E (*(unsigned char *)&TheXCollisionCRC)
// g_00E02D7F is only an alias of the owned global TheXShroudCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXShroudCRC;
#define g_00E02D7F (*(unsigned char *)&TheXShroudCRC)
// g_00E02D80 is only an alias of the owned global TheXTaintCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXTaintCRC;
#define g_00E02D80 (*(unsigned char *)&TheXTaintCRC)
// Native byte gate read by GameLogic::getCRC; original identifier unknown.
unsigned char BfmeGameLogicCRCModeFlag = 0;
// g_00E02D83 is only an alias of the owned global TheXPlayerCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXPlayerCRC;
#define g_00E02D83 (*(unsigned char *)&TheXPlayerCRC)
// g_00E02D84 is only an alias of the owned global TheXAICRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXAICRC;
#define g_00E02D84 (*(unsigned char *)&TheXAICRC)
// g_00E02D88 is only an alias of the owned global TheXLWCRC (ledger names column); this unit reads the owner through its own view type.
extern bool TheXLWCRC;
#define g_00E02D88 (*(unsigned char *)&TheXLWCRC)
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern PlayerList *ThePlayerList;
extern CollisionManager *TheCollisionManager;
class BfmeTaintManager;
extern BfmeTaintManager *TheTaintManager;
// TheSkirmishAIManager is only an alias of the owned global TheSkirmishAIManager (ledger names column); this unit reads the owner through its own view type.
extern class Rva002A8F24 *TheSkirmishAIManager;
extern class AI *TheAI;

unsigned int GameLogic::getCRC(int mode)
{
	setFPMode();
	BFMECRCWriter writer(TheLiteCRC);
	BFMECRCWriter *xfer = &writer;
	if (mode != 0)
		((Rva0060D4C9 *)&writer)->rva0060D4C9((Xfer *)mode);
	if (theLogicRandomLogFile != 0)
		((Rva002CEC0A *)theLogicRandomLogFile)->rva002CED26((Xfer *)&writer);
	if (TheLiteCRC != 0 || g_00E02D7C == 0)
	{
		for (Object *obj = m_firstObject; obj != 0; obj = obj->getNextObject())
			xfer->xferSnapshot(obj);
	}
	unsigned int seed = GetGameLogicRandomSeedCRC();
	xfer->xferUnsignedInt(&seed);
	if (TheLiteCRC != 0 || g_00E02D7D == 0)
		xfer->xferSnapshot(*(PartitionManagerSnapshotView **)&ThePartitionManager);
	if (TheLiteCRC != 0 || g_00E02D7E == 0)
		xfer->xferSnapshot(TheCollisionManager);
	if (TheLiteCRC != 0 || g_00E02D7F == 0)
		xfer->xferSnapshot(*(PartitionManagerSnapshotView **)&TheShroudManager);
	if (TheLiteCRC != 0 || g_00E02D80 == 0)
		xfer->xferSnapshot((TaintManager *)TheTaintManager);
	if (TheLiteCRC != 0 || BfmeGameLogicCRCModeFlag == 0)
		xfer->xferSnapshot(*(SkirmishAIManager **)&TheSkirmishAIManager);
	if (TheLiteCRC != 0 || g_00E02D83 == 0)
		xfer->xferSnapshot(ThePlayerList);
	if (TheLiteCRC != 0 || g_00E02D84 == 0)
		xfer->xferSnapshot(TheAI);
	if ((TheLiteCRC != 0 || g_00E02D88 == 0) && ((Rva00210C66CmpBoolField *)this)->get())
		xfer->xferSnapshot((*(Rva002BA8F1Logic **)&TheLivingWorldLogic));
	((Gen009D6DD0 *)&writer)->bfmeClose();
	return writer.m_crc;
}
