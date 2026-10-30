// cl: /DNDEBUG /MD
//
// ?xfer@ReplaceObjectUpdate@@MAEXPAVXfer@@@Z 33B @0x004B29DE: virtual slot 3
// (offset 0x0C) of vtable 0x00856BB0 installed by the ReplaceObjectUpdate
// ctor. Base SpecialAbilityUpdate xfer via rowed 0x0044F996, IsLightCRC
// early-out via Xfer slot 0x10, then rowed Version1. No members.

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
#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class ReplaceObjectUpdateModuleData;
class Rva004B2A9D;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();	// slot 17 (0x0045108D)
	Object *getObject() const { return m_object; }
protected:
	virtual void xfer(Xfer *xfer);
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class ReplaceObjectUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	void rva004B2C00(Object *obj, Rva004B2A9D *entry);	// 0x004B2C00
	void rva004B2A60(Object *obj);
private:
	const ReplaceObjectUpdateModuleData *getReplaceObjectData() const
	{
		return (const ReplaceObjectUpdateModuleData *)m_moduleData;
	}
	char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;		// +0x44
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void xfer(Xfer *xfer);
};

void ReplaceObjectUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
