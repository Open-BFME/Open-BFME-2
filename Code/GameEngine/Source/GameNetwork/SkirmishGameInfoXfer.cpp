// cl: /Ireference/shims/bfme2_ascii /EHsc

// ?xfer@SkirmishGameInfo@@UAEXPAVXfer@@@Z
// Retail 0x003FFA3C (272B): persists the skirmish setup through the Xfer
// virtuals (light-CRC guard, Version1 pair, preorder/mode ints and bools,
// the 8-slot array through each slot's own xfer, the +0x40 helper, the
// trailing int/uint runs, one +0x5C local, ten ints at +0x60, one uint
// at +0x88). The layout widens BFME1's SkirmishGameInfo past the slots:
// the string members are gone, replaced by the +0x40..0x88 int/uint runs.

// The shared headers declare these members with the access/virtual spelling
// retail's vftables reference; the ledger row keeps the spelling this TU
// compiled to. Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z=?xfer@SkirmishGameInfo@@UAEXPAVXfer@@@Z")
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

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

#include "../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
	int x;
	int y;
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
	int red;
	int green;
	int blue;
	int alpha;
};

class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

// Minimal string handle: one pointer field, so by-value temporaries take one
// stack slot. Only the shape matters here; construction and teardown happen
// in the string-unit bodies these declarations pin.
#include "ascii_string.h"

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &path) const;
	AsciiString portableMapPathToRealMapPath(const AsciiString &path) const;
};

extern GameState *TheGameState;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

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

	void xferAsciiString(AsciiString *value) { *this == *value; }

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

// Slot-3 xfer shape: the slot elements persist themselves through their own
// virtual (retail calls [eax+0x0C] on each element), so only the slot layout
// matters here, never the element body.
class GameSlot
{
public:
	virtual ~GameSlot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

void __cdecl xferMapName(Xfer *xfer, AsciiString *mapNameData);

#define MAX_SLOTS 8

class SkirmishGameInfo : public Snapshot
{
public:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[8];                // +0x04
	Int m_preorderMask;             // +0x0C
	Bool m_inGame;                  // +0x10
	Bool m_inProgress;              // +0x11
	Bool m_surrendered;             // +0x12
	char m_pad13[1];                // +0x13
	Int m_gameID;                   // +0x14
	GameSlot *m_slot[MAX_SLOTS];    // +0x18
	char m_pad38[8];                // +0x38
	Int m_bfme40;                   // +0x40 (helper block head)
	UnsignedInt m_bfme44;           // +0x44
	UnsignedInt m_bfme48;           // +0x48
	Int m_bfme4C;                   // +0x4C
	Int m_bfme50;                   // +0x50
	Int m_bfme54;                   // +0x54
	char m_pad58[4];                // +0x58
	Int m_bfme5C;                   // +0x5C
	Int m_bfme60[10];               // +0x60
	UnsignedInt m_bfme88;           // +0x88
};

// ?xfer@SkirmishGameInfo@@UAEXPAVXfer@@@Z
// Retail 0x003FFA3C (272B).
void SkirmishGameInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	xfer->Version1();

	*xfer == m_preorderMask;
	*xfer == m_inGame;
	*xfer == m_inProgress;
	*xfer == m_surrendered;
	*xfer == m_gameID;

	Int slot = MAX_SLOTS;
	*xfer == slot;
	slot = 0;
	do
	{
		m_slot[slot]->xfer(xfer);
		slot++;
	} while (slot < MAX_SLOTS);

	xferMapName(xfer, (AsciiString *)&m_bfme40);

	*xfer == m_bfme44;
	*xfer == m_bfme48;
	*xfer == m_bfme4C;
	*xfer == m_bfme50;
	*xfer == m_bfme54;

	Int fiveC = m_bfme5C;
	*xfer == fiveC;

	Int count = 10;
	Int *field = m_bfme60;
	do
	{
		*xfer == *field++;
	} while (--count);

	*xfer == m_bfme88;
}

// ?xferMapName@@YAXPAVXfer@@PAVAsciiString@@@Z (name to confirm against the
// emitted symbol before rowing)
// Retail 0x00306327 (130B): the save-game map path helper. On store, the
// portable path is made real-side into a temporary and transferred; on load,
// the transferred name is converted back over the caller's string. Follows
// the Open-BFME-1 XferMapName.cpp contract: the IsStoring predicate picks
// the direction and TheGameState owns both conversions.
void __cdecl xferMapName(Xfer *xfer, AsciiString *mapNameData)
{
	if (xfer->IsStoring())
	{
		AsciiString tmp = TheGameState->realMapPathToPortableMapPath(*mapNameData);
		xfer->xferAsciiString(&tmp);
	}
	else
	{
		xfer->xferAsciiString(mapNameData);
		*mapNameData = TheGameState->portableMapPathToRealMapPath(*mapNameData);
	}
}
