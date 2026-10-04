// cl: /O1 /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "AIStartWoTRBattleTactic" skirmish-AI tactic (vtable 0x00872224; ctor
// 0x005AB1B4 in Rva004ECECDTacticCtors.cpp, dtor 0x005AB125 and ??_G, slot 9
// in Rva004ECECDTacticCreate.cpp). Base chain, all address-derived:
// Rva005DCC24 (ctor 0x005DCC0A) over Rva005DC73C over the AITactic.cpp
// object Rva004ECECD.
//
// It runs once per AI owner: the owner's TheSkirmishAIManager record keeps
// this unit's global key (0x00E0640C, built by 0x007B4513 and released by
// 0x007B961C).
//
//   0x005AB130  slot 1: not run yet, the game is not in mode 3 and past
//               frame 5
//   0x005AB188  slot 5: xfer, version 1, then the AITactic's
//   0x005AB235  slot 6: mark it run, then order every live unit of the
//               owner's that is of kind 3 or 0x5A to the owner's base
//               (0x004EBF4B) and finish
#include "ascii_string.h"

// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString StartWoTRBattleTacticHasRun("StartWoTRBattleTacticHasRun");
#pragma inline_depth()

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
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

template <int N> class BitFlags
{
public:
	unsigned m_words[7];
};

struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *where, int a, int b);
};

struct Rva005AB125AI
{
	char m_pad00[0x20];
	Rva00295A0FCommands m_commands;	// +0x20
};

class Object : public Thing
{
public:
	char m_pad000[0x258];
	Rva005AB125AI *m_ai;		// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_438;		// +0x438
};

enum ObjectID
{
	INVALID_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40, the frame
	char m_pad044[0x114 - 0x44];
	int m_114;			// +0x114
};
extern GameLogic *TheGameLogic;

class Rva004EBF4B
{
public:
	void rva004EBF4B(Coord3D *out);
};

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
};

struct Rva005AB125IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

class Player;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual Rva004ECECD *create();
	void rva004ED748(int a, int b);
};

class Rva005DC73C : public Rva004ECECD
{
public:
	virtual ~Rva005DC73C();
	char m_pad04[0x24 - 4];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class Rva005AB125 : public Rva005DC73C
{
public:
	virtual ~Rva005AB125();
	virtual bool appliesTo(void *request);
	virtual void xfer(Xfer *xfer);
	virtual void v6();
};

bool Rva005AB125::appliesTo(void *)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	return !record->rva002C7196(StartWoTRBattleTacticHasRun)
		&& TheGameLogic->m_114 != 3
		&& TheGameLogic->m_40 > 5;
}

void Rva005AB125::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	Rva004ECECD::xfer(xfer);
}

void Rva005AB125::v6()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (!record->rva002C7196(StartWoTRBattleTacticHasRun)) {
		record->rva002C717E(StartWoTRBattleTacticHasRun, 1);
		Rva005AB125IDs *ids = (Rva005AB125IDs *)(*(Rva005C4AD1LeaField **)g_00DFEEF8->rva002A8F24(m_owner))->get();
		Coord3D base;
		((Rva004EBF4B *)record)->rva004EBF4B(&base);
		ObjectID *end = ids->m_end;
		for (ObjectID *it = ids->m_begin; it != end; ++it) {
			Object *obj = TheGameLogic->findObjectByID(*it);
			if (obj && !(obj->m_438 & 1) && obj->isAnyKindOf(Rva0006EE7A(0, 3, 0x5A)))
				obj->m_ai->m_commands.Rva00295A0FCommand(&base, 0x7FFFFFFF, 0);
		}
		rva004ED748(1, 0);
	} else {
		rva004ED748(0, 0);
	}
}
