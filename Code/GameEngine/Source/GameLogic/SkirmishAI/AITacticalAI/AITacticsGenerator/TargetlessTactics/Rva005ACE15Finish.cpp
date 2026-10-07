// ?rva005ACE15@AIFarmKillSquad@@QAEMPBUCoord3D@@00@Z
// recovered 2026-10-05 from the 0.97 bank; exact 179/179
// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "FarmKillSquad" skirmish-AI tactic (vtable 0x00872474; ctor 0x005ACF38
// in Rva004ECECDTacticCtors.cpp, dtor 0x005ACCE4 and ??_G, slot 9 0x005ACFAB
// in Rva004ECECDTacticCreate.cpp). Base chain, all address-derived:
// Rva005DCC24 over AITacticOffensive over the AITactic.cpp object AITactic.
// Layout: +0x58 and +0x5C object ids, +0x60 "farm" (the ctor's one-in-five
// roll). The owner's TheSkirmishAIManager record keeps
// AIFarmKillSquad_IsRunning and AIFarmKillSquad_FrameNextRun.
//
//   0x005ACCEF  slot 1: farming or the record's +0x16C positive; not
//               running, the next run is due and 0x002C6ACB answers
//   0x005ACD51  slot 2: clear the running key and schedule the next run a
//               random 30..120 seconds on
//   0x005ACEC8  slot 5: xfer, version 1: the AITactic's, then both ids
//   0x005ACDD2  the distance between two points
//   0x005ACE15  the distance from a point to the line through two others
#include "ascii_string.h"

static inline float sqr(float x)
{
	return x * x;
}

extern int g_Va00DBA4E4;

// This unit's statics, built in this order (0x007B461B, 0x007B4636,
// 0x007B4651, 0x007B4662, 0x007B4670).
AsciiString AIFarmKillSquad_IsRunning("AIFarmKillSquad_IsRunning");
AsciiString AIFarmKillSquad_FrameNextRun("AIFarmKillSquad_FrameNextRun");
float g_00E06434 = sqr(1100.0f);
int g_00E06438 = g_Va00DBA4E4 * 30;
int g_00E0643C = g_Va00DBA4E4 * 120;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	float length() const;
};

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *id);

class GameLogic
{
public:
	unsigned int getFrame() const { return m_40; }
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40
};
extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	void *rva002C6ACB();
	char m_pad000[0x16C];
	int m_16C;			// +0x16C
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void initializeTeamTemplate();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x24 - 4];
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIFarmKillSquad : public AITacticOffensive
{
public:
	virtual ~AIFarmKillSquad();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void xfer(Xfer *xfer);
	float rva005ACDD2(const Coord3D *a, const Coord3D *b);
	float rva005ACE15(const Coord3D *point, const Coord3D *from, const Coord3D *to);
private:
	ObjectID m_58;		// +0x58
	ObjectID m_5C;		// +0x5C
	bool m_farm;		// +0x60
};

// AIFarmKillSquad::canRun is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIFarmKillSquad.cpp (0x005ACCEF).

// AIFarmKillSquad::cleanUp is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIFarmKillSquad.cpp (0x005ACD51).

// AIFarmKillSquad::rva005ACDD2 is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIFarmKillSquad.cpp (0x005ACDD2).

float AIFarmKillSquad::rva005ACE15(const Coord3D *point, const Coord3D *from, const Coord3D *to)
{
	float length = rva005ACDD2(to, from);
	// Naming the three products separately changes the CSE grouping: retail
	// keeps the z difference in the register the y product is multiplied by,
	// which a single inline sum never produces at any term order.
	const float px = (point->x - from->x) * (to->x - from->x);
	const float py = (point->y - from->y) * (to->y - from->y);
	const float pz = (point->z - from->z) * (to->z - from->z);
	float t = (px + py + pz) / (length * length);
	Coord3D foot;
	foot.x = (to->x - from->x) * t + from->x;
	foot.y = (to->y - from->y) * t + from->y;
	foot.z = (to->z - from->z) * t + from->z;
	return rva005ACDD2(point, &foot);
}

// AIFarmKillSquad::xfer is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIFarmKillSquad.cpp (0x005ACEC8).
