// cl: /O1 /MD /Ireference/shims/bfme2_ascii
// ??_GMonitorConditionUpdate@@UAEPAXI@Z @0x00491750 28B
// Deleting dtor slot 0 of vtable 0x0084DAD8; calls rowed ??1 at 0x004916AC then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

// Native ctor 0x491633 and dtor 0x4916AC establish bases at 0/C/10,
// with the string at 0x20. Match their inheritance when emitting tables.
class Thing;
class ModuleData;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };


#include "ascii_string.h"

// The primary table starts with the deleting destructor: retail table
// RVA 0x0084DAD8 slot 0 is the owned callback 0x00491750. Inheriting an
// unrelated virtual here shifted the destructor into slot 1 and emitted
// a wrong first virtual slot. The deleting-wrapper unit uses these same
// base views, including the native three-entry update interface.
#include "../../Include/GameLogic/Module/UpdateModule.h"



class MonitorConditionUpdate : public UpdateModule
{
public:
	MonitorConditionUpdate(EmitVtableTag *);
	virtual ~MonitorConditionUpdate();
	virtual UpdateSleepTime update();
	// Retail 0x0084DAD8 slots 3 and 4: the rowed overrides 0x004915C6 and 0x00491667
	// (MonitorConditionUpdate.cpp), so both units emit one primary table.
	virtual void xfer(Xfer *xfer);
	virtual NameKeyType getModuleNameKey() const;

private:
	AsciiString m_str; // +0x20
};
// ?<MonitorConditionUpdate::MonitorConditionUpdate> absent-from-retail
MonitorConditionUpdate::MonitorConditionUpdate(EmitVtableTag *) : UpdateModule(0, 0) {}
// ??_GDamageFieldUpdateModuleData@@UAEPAXI@Z @0x0049114E 28B
// Deleting dtor slot 0 of vtable 0x0084D8E8; calls rowed ??1 at 0x0049116A then rowed operator delete at 0x0002FD60.
class DamageFieldUpdateModuleData : public ModuleData { public: DamageFieldUpdateModuleData(EmitVtableTag *); virtual ~DamageFieldUpdateModuleData(); };
// ?<DamageFieldUpdateModuleData::DamageFieldUpdateModuleData> absent-from-retail
DamageFieldUpdateModuleData::DamageFieldUpdateModuleData(EmitVtableTag *) {}
