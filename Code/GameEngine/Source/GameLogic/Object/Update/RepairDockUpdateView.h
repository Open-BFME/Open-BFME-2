#ifndef BFME2_REPAIR_DOCK_UPDATE_VIEW_H
#define BFME2_REPAIR_DOCK_UPDATE_VIEW_H

// Shared RepairDockUpdate view. The transfer body proves the +0x88 ObjectID
// and +0x8C float after the DockUpdate base; the action body proves the
// update-module part (module data +0x04, owner +0x08) and the
// DockUpdateInterface subobject at +0x20. It does not establish the
// constructor (the hand-vptr ctor keeps its own satellite).
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class MultiIniFieldParse;

class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
private:
	unsigned char m_opaque[0x10];
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RepairDockUpdateModuleData : public DockUpdateModuleData
{
public:
	RepairDockUpdateModuleData();
	float m_framesForFullHeal; // +0x10 ("TimeForFullHeal")
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Update-module part of the dock: vptr, module data +0x04, owner +0x08,
// 0x20 bytes in all (the action body reads both at this-0x1C/-0x18).
class UpdateModuleBase
{
public:
	virtual ~UpdateModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	char m_pad0C[0x20 - 0x0C];
};

// Secondary base at +0x20: action is slot 12 of vtable 0x00851C30.
class DockUpdateInterface
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0; virtual void s03() = 0;
	virtual void s04() = 0; virtual void s05() = 0; virtual void s06() = 0; virtual void s07() = 0;
	virtual void s08() = 0; virtual void s09() = 0; virtual void s10() = 0; virtual void s11() = 0;
	virtual bool action(Object *docker, Object *drone) = 0; // slot 12
};

class __declspec(novtable) DockUpdate : public UpdateModuleBase, public DockUpdateInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad24[0x88 - 0x24];
};

class RepairDockUpdate : public DockUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual bool action(Object *docker, Object *drone);
protected:
	virtual void xfer(Xfer *xfer);

	const RepairDockUpdateModuleData *getRepairDockUpdateModuleData() const
	{
		return (const RepairDockUpdateModuleData *)m_moduleData;
	}

private:
	ObjectID m_lastRepair; // +0x88
	float m_healthToAddPerFrame; // +0x8C
};


#endif
