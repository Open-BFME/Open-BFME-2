// cl: /O1

// Labelled-enum transfer helpers: each one moves a 4-byte enum through the
// text-mode Xfer's slot-37 XferEnum virtual with its field-name label (the
// label strings live in .rdata next to neighbouring enum labels). The bodies
// are free cdecl functions taking (Xfer*, value*) with no other dependencies,
// so all helpers share this TU. The Xfer declaration below is Xfer.cpp's
// model verbatim so the XferEnum call lands on the shipped slot.

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct ICoord3D
{
	int x;
	int y;
	int z;
};

class Coord2D
{
public:
	float x;
	float y;
};

struct ICoord2D
{
	int x;
	int y;
};

struct Region3D
{
	Coord3DBase lo;
	Coord3DBase hi;
};

struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct RealRange
{
	float lo;
	float hi;
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct RGBAColorInt
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	// Slot order proven by GameSlot::xfer's two guards: slot 1 (0x04) runs
	// the original-info save-off (true on load), slot 4 (0x10) skips the
	// whole body (true in light-CRC mode). Xfer.cpp lists IsStoring first,
	// which its folded mode-predicate rows cannot distinguish; the guards
	// here can, so this TU uses the BFME1 Xfer.h order.
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

// ?XferSlotState@@YAXPAVXfer@@PAW4SlotState@@@Z
// Retail 0x003FF0B4 (24B): sole caller is GameSlot::xfer at 0x003FF649,
// passing &m_state with the "SlotState" label for the text-dump Xfer.
void XferSlotState(Xfer *xfer, SlotState *state)
{
	xfer->XferEnum("SlotState", state, 4);
}

// ?XferLivingWorldPlayerID@@YAXPAVXfer@@PAH@Z
// Retail 0x002034C4 (24B): shared helper used by 19 callers (team, player
// and slot xfer methods), moving a 4-byte Living World player ID through
// XferEnum with the "LivingWorldPlayerID" label.
void XferLivingWorldPlayerID(Xfer *xfer, int *playerID)
{
	xfer->XferEnum("LivingWorldPlayerID", playerID, 4);
}

// Retail 0x003060B2 (24B): labelled-enum helper moving a 4-byte ObjectID
// through XferEnum with the "ObjectID" label (string at 0x00807CC8 next to
// DrawableID). 40+ callers including FoundationAIUpdate::xfer at 0x00455141
// passing &m_28.
void XferObjectID(Xfer *xfer, ObjectID *objectID)
{
	xfer->XferEnum("ObjectID", objectID, 4);
}

// Retail 0x0045ED66 (24B): labelled-enum helper moving a 4-byte stances value
// through XferEnum with the "StancesEnum" label. Callers include
// StancesBehavior::xfer at 0x0045EDC8 passing &m_30 (rowed int at +0x30).
void XferStancesEnum(Xfer *xfer, int *stances)
{
	xfer->XferEnum("StancesEnum", stances, 4);
}

// Retail 0x00305F92 (24B): labelled-enum helper moving a 4-byte distribution
// type through XferEnum with the "GameClientRandomVariable::DistributionType"
// label (string at 0x00807BBC). Sole caller is FUN_00706183 at 0x003061E7.
void XferDistributionType(Xfer *xfer, int *value)
{
	xfer->XferEnum("GameClientRandomVariable::DistributionType", value, 4);
}

// Retail 0x00306082 (24B): labelled-enum helper moving a 4-byte rotation type
// through XferEnum with the "RotationType" label (string at 0x00807CA8).
// Callers include DoXfer bodies at 0x0055F6DB 0x0055F7D1 0x00562226 0x0056233E.
void XferRotationType(Xfer *xfer, int *value)
{
	xfer->XferEnum("RotationType", value, 4);
}

// Two version bytes, stored back to back: the retail Version1 body writes 1 to
// both of them in a four-byte stack slot before handing their address to the
// slot-10 transfer operator. Xfer.cpp's model verbatim.
class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// TU-scoped strings: 4-byte ref-counted handles, the MapMetaData TU pattern
// stripped to the layout (no methods, so no extra literals or code).
template <typename T> class StringBase
{
public:
	~StringBase() {}

private:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
};

class UnicodeString : private StringBase<unsigned short>
{
};

// The +0x64 member's own type is unidentified: its default constructor
// (retail 0x00229557) calls BFME2NativeNetwork::baseConstruct, its vtable
// (retail 0x00BE73E8) carries an empty slot-3 virtual, and GameSlot::xfer
// only ever invokes that slot. Model the proven four-virtual shape with the
// call at slot 3 and pad to the next accessed member (+0x1A4).
class BfmeSlotNetState
{
public:
	virtual ~BfmeSlotNetState();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x1A4 - 0x64 - 4];
};

// BFME2 GameSlot layout: BFME1's LANGameSlot_copy.cpp donor shifted +8 past
// +0x10 (two inserted ints at +0x14/+0x20), then BFME2-only tail members.
// Every offset below is proven by retail: the xfer call sequence, the
// copy constructor at 0x002295D7 and the destructor at 0x002294FD.
class GameSlot
{
public:
	virtual void _bfme_gs0() = 0;
	virtual void _bfme_gs1() = 0;
	virtual void _bfme_gs2() = 0;
	virtual void xfer(Xfer *xfer);

	SlotState m_state;                  // +0x04
	Bool m_isAccepted;                  // +0x08
	Bool m_hasMap;                      // +0x09
	Bool m_isMuted;                     // +0x0A
	Int m_color;                        // +0x0C
	Int m_startPos;                     // +0x10
	Int m_bfme14;                       // +0x14 (BFME2-new int, xferred)
	Int m_playerTemplate;               // +0x18
	Int m_teamNumber;                   // +0x1C
	Int m_bfme20;                       // +0x20 (BFME2-new int, xferred)
	Int m_origColor;                    // +0x24
	Int m_origStartPos;                 // +0x28
	Int m_origPlayerTemplate;           // +0x2C
	UnicodeString m_name;           // +0x30 (donor BfmeWideSlotString)
	AsciiString m_ip;               // +0x34 (donor BfmeAsciiSlotString)
	UnsignedInt m_bfme38;               // +0x38 (copied, not xferred)
	UnsignedInt m_bfme3C;               // +0x3C (copied, not xferred)
	UnsignedInt m_bfme40;               // +0x40 (copied, not xferred)
	UnsignedInt m_bfme44;               // +0x44 (copied, not xferred)
	UnsignedByte m_bfme48;              // +0x48 (copied, not xferred)
	Int m_bfme4C;                       // +0x4C (Living World player ID)
	Int m_bfme50;                       // +0x50 (xferred via local when version >= 2)
	UnsignedInt m_bfme54;               // +0x54
	UnsignedInt m_bfme58;               // +0x58
	Int m_bfme5C;                       // +0x5C
	Bool m_bfme60;                      // +0x60
	BfmeSlotNetState m_netState;        // +0x64
	Bool m_bfme1A4;                     // +0x1A4
	AsciiString m_bfme1A8;          // +0x1A8
};

// ?xfer@GameSlot@@UAEXPAVXfer@@@Z
// Retail 0x003FF616 (384B): persists the slot through the Xfer virtuals
// (light-CRC guard, version {1,2}, labelled SlotState enum, original-info
// save-off on load, version-gated +0x50, member xfer at +0x64).
void GameSlot::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	XferSlotState(xfer, &m_state);
	*xfer == m_isAccepted;
	*xfer == m_hasMap;
	*xfer == m_isMuted;
	*xfer == m_color;
	*xfer == m_startPos;
	*xfer == m_bfme14;
	*xfer == m_playerTemplate;
	*xfer == m_teamNumber;
	*xfer == m_bfme20;

	if (xfer->IsLoading())
	{
		m_origPlayerTemplate = m_playerTemplate;
		m_origStartPos = m_startPos;
		m_origColor = m_color;
	}

	*xfer == m_origColor;
	*xfer == m_origStartPos;
	*xfer == m_origPlayerTemplate;
	*xfer == m_name;
	*xfer == m_ip;
	XferLivingWorldPlayerID(xfer, &m_bfme4C);
	*xfer == m_bfme54;
	*xfer == m_bfme58;
	*xfer == m_bfme5C;
	*xfer == m_bfme60;

	if (version.m_minimum >= 2)
	{
		Int bfme50 = m_bfme50;
		*xfer == bfme50;
		m_bfme50 = bfme50;
	}

	m_netState.xfer(xfer);
	*xfer == m_bfme1A4;
	*xfer == m_bfme1A8;
}
