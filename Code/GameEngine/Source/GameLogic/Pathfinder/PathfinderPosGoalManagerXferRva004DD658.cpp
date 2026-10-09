// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva004DD658@Rva004DD843@@QAEXPAVXfer@@@Z
// Retail 0x004DD658 90 bytes RET4. PathfinderPosGoalManager (the 0x4C-byte
// object Object::DoXfer 0x00297684 allocates at Object+0x44 through ctor
// 0x004DD7E3 and serializes with this call; WB twin 0x01286B40). Version 1
// through the rowed Xfer::Version1 0x000053EE then for the position slot
// (+4) and the goal slot (+0x1C): the cell (ICoord2D) through Xfer slot 0x4C
// the footprint angle through the rowed Rva004DD619Footprint 0x004DD619 and
// the pathfind layer through the rowed XferPathfindLayerEnum 0x00305D0A.
// Each helper returns the Xfer for the next transfer: the goal slot is
// transferred through the layer helper's returned Xfer (WB keeps it too).
// Slot layout follows PathfinderPosGoalManager.cpp's Rva004DD843Slot.

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

#include "../../../../Libraries/Include/Lib/Coord2D.h"

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

class Snapshot;

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

Xfer * __cdecl Rva004DD619Footprint(Xfer *xfer, int *value);
Xfer * __cdecl XferPathfindLayerEnum(Xfer *xfer, int *value);

class Object;
class PathfindCell;

struct Rva004DD843Slot
{
	ICoord2D m_cell;
	int m_angle;
	int m_pathLayer;
	int m_listKind;
	PathfindCell *m_pathCell;
};

class Rva004DD843
{
public:
	void rva004DD658(Xfer *xfer);

	Object *m_object;
	Rva004DD843Slot m_position;
	Rva004DD843Slot m_goal;
	Rva004DD843Slot m_other;
};

void Rva004DD843::rva004DD658(Xfer *xfer)
{
	xfer->Version1();
	Xfer *next = XferPathfindLayerEnum(
		Rva004DD619Footprint(&(*xfer == m_position.m_cell), &m_position.m_angle),
		&m_position.m_pathLayer);
	XferPathfindLayerEnum(
		Rva004DD619Footprint(&(*next == m_goal.m_cell), &m_goal.m_angle),
		&m_goal.m_pathLayer);
}
