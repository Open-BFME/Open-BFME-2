// cl: /DNDEBUG /MD
//
// ?xfer@StatusBitsUpgradeIfEldestKindof@@MAEXPAVXfer@@@Z, retail 0x004B4B7C, 37 bytes.
// Slot 3 of the vftable 0x00C57ADC whose slot-2 name getter returns
// "StatusBitsUpgradeIfEldestKindof" (installed by 0x004B49E2). Version1, the
// StatusBitsUpgrade::xfer (pinned at the ICF-shared upgrade xfer 0x004B8710),
// then the frame cache at +0x1C through the rowed Rva00485BB8::xfer.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
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
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva00485BB8
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned int m_00;
};

class Xfer;

class __declspec(novtable) StatusBitsUpgrade
{
public:
	StatusBitsUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual ~StatusBitsUpgrade();

protected:
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);

	unsigned char m_pad04[0x08];
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x04];
	const void *m_slot18;
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

struct Rva00485C19Data;

struct StatusBitsEldestFrame
{
public:
	StatusBitsEldestFrame *cacheGameLogicFrame(void);
	bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame; // +0x00
};

class __declspec(novtable) StatusBitsUpgradeIfEldestKindof : public StatusBitsUpgrade
{
public:
	StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData);

	virtual ~StatusBitsUpgradeIfEldestKindof();
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);

private:
	StatusBitsEldestFrame m_eldestFrame;
};

// 0x004B8710 is rowed as ArmorUpgrade::xfer (27B; ICF-shared with the
// StatusBitsUpgrade spelling per the header note); the qualified call goes
// through a TU-local view so it resolves to the rowed body instead of the
// unrowed spelling (sole U on this unit).
class ArmorUpgrade
{
protected:
	virtual void xfer(Xfer *xfer);
	friend class StatusBitsUpgradeIfEldestKindof;
};

// ?xfer@StatusBitsUpgradeIfEldestKindof@@MAEXPAVXfer@@@Z @0x004B4B7C
void StatusBitsUpgradeIfEldestKindof::xfer(Xfer *xfer)
{
	xfer->Version1();
	((ArmorUpgrade *)this)->ArmorUpgrade::xfer(xfer);
	((Rva00485BB8 *)&m_eldestFrame)->xfer(xfer);
}
