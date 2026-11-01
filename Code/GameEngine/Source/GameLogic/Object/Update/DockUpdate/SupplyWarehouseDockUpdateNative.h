#pragma once

// Target facts: 004A7DEA installs four tables at +0/+0C/+10/+20 and
// copies ModuleData+10 to +88. 004A7D55 restores those same four tables.
// The factory allocates 8C bytes. Primary 00853790 has 13 slots; the
// +0C table 00851B20 has 47, +10/00851D68 has 3 and +20/00853740 has 20.
// All non-pure slots are real methods or the native constant/empty folds.
// Donor facts: ZH names the docking interface and the boxes/dock flags.
// The opaque storage and the extra interface slot retain neutral names.
#include "../../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType { NK_UNKNOWN = 0 };
class MultiIniFieldParse;

// The native ModuleData family has the same 31-slot folded ObjectHelper
// table. These two constructors are out-of-line; model the stored pointer
// explicitly instead of synthesizing a distinct table/destructor family.
class DockUpdateModuleData
{
public:
    DockUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &);
    const void *m_vftable;
    unsigned int m_moduleTagNameKey;
    int m_numberApproachPositionsData;
    bool m_isAllowPassthrough;
};
class SupplyWarehouseDockUpdateModuleData : public DockUpdateModuleData
{
public:
    SupplyWarehouseDockUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &);
    int m_startingBoxesData; // +10
    bool m_deleteWhenEmpty; // +14
};

class DockUpdateInterface
{
public:
    virtual bool isClearToApproach(const Object *) const = 0;
    virtual bool reserveApproachPosition(Object *, Coord3D *, int *) = 0;
    virtual bool advanceApproachPosition(Object *, Coord3D *, int *) = 0;
    virtual bool isClearToEnter(const Object *) const = 0;
    virtual bool isClearToAdvance(const Object *, int) const = 0;
    virtual void getEnterPosition(Object *, Coord3D *) = 0;
    virtual void getDockPosition(Object *, Coord3D *) = 0;
    virtual void getExitPosition(Object *, Coord3D *) = 0;
    virtual void onApproachReached(Object *) = 0;
    virtual void onEnterReached(Object *) = 0;
    virtual void onDockReached(Object *) = 0;
    virtual void onExitReached(Object *) = 0;
    virtual bool rva004A7E67(Object *, int) = 0;
    virtual void cancelDock(Object *) = 0;
    virtual bool isDockOpen() = 0;
    virtual void setDockOpen(bool) = 0;
    virtual bool dockSlot16(int) = 0;
    virtual void setDockCrippled(bool) = 0;
    virtual bool isAllowPassthroughType() = 0;
    virtual bool isRallyPointAfterDockType() = 0;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
    DockUpdate(Thing *, const ModuleData *);
    virtual ~DockUpdate();
    virtual bool isClearToApproach(const Object *) const;
    virtual bool reserveApproachPosition(Object *, Coord3D *, int *);
    virtual bool advanceApproachPosition(Object *, Coord3D *, int *);
    virtual bool isClearToEnter(const Object *) const;
    virtual bool isClearToAdvance(const Object *, int) const;
    virtual void getEnterPosition(Object *, Coord3D *);
    virtual void getDockPosition(Object *, Coord3D *);
    virtual void getExitPosition(Object *, Coord3D *);
    virtual void onApproachReached(Object *);
    virtual void onEnterReached(Object *);
    virtual void onDockReached(Object *);
    virtual void onExitReached(Object *);
    virtual void cancelDock(Object *);
    virtual bool isDockOpen() { return m_dockOpen; }
    virtual void setDockOpen(bool open) { m_dockOpen = open; }
    virtual bool dockSlot16(int) { return false; }
    virtual void setDockCrippled(bool);
    virtual bool isAllowPassthroughType()
    {
        return ((const DockUpdateModuleData *)m_moduleData)->m_isAllowPassthrough;
    }
    virtual bool isRallyPointAfterDockType() { return false; }
    virtual UpdateSleepTime update();
    virtual void *slot22() { return static_cast<DockUpdateInterface *>(this); }
protected:
    virtual void loadPostProcess();
    virtual void xfer(Xfer *);
    unsigned char m_unmodelled24[0x80 - 0x24];
    unsigned int m_activeDocker; // +80
    bool m_dockerInside; // +84
    bool m_dockCrippled; // +85
    bool m_dockOpen; // +86
};

class SupplyWarehouseDockUpdate : public DockUpdate
{
public:
    SupplyWarehouseDockUpdate(Thing *, const ModuleData *);
    virtual ~SupplyWarehouseDockUpdate();
    virtual void loadPostProcess();
    virtual NameKeyType getModuleNameKey() const;
    virtual void onObjectCreated();
    virtual void setDockCrippled(bool);
    virtual bool rva004A7E67(Object *, int);
    void rva004A7F78(int);
protected:
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    int m_boxesStored; // +88
};
