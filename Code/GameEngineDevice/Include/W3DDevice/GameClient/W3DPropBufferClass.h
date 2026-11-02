/* Target facts (BFME 2 1.06, RVAs unless marked VA): constructor 0x000EF008 stores VA 0x00BCEECC at +0 (0x000EF037); destructor 0x000EEEF4 restores that table at 0x000EEF07, then Snapshot VA 0x00BBB554 at 0x000EEFD5 after member teardown. The latter is the base's teardown table, not another W3DPropBuffer table. VA 0x00BCEECC contains exactly four code pointers followed by the class-name string: deleting destructor 0x000EEFEC (calls 0x000EEEF4), empty loadPostProcess 0x000B3FD0, const GetSnapshotName 0x000EEFE6 (returns VA 0x00BCEEDC), and xfer 0x000EE901. Snapshot at +0 contributes those four slots and no data beyond its vptr. Allocation 0x0006CB85..0x0006CBAD requests 0x2F728 bytes and calls 0x000EF008.
Target layout: 0x000EF01C..0x000EF03D constructs 4000 records of stride 0x30 at +4; 0x000EF048..0x000EF05A clears count +0x2EE04 and byte flags +0x2EE08/+0x2EE09/+0x2EE0A. The +0x2EE0C member calls the 12-byte holder constructor 0x001F81BF at 0x000EF060 and destructor 0x0008B470 at 0x000EEFB3 (unwind wrapper 0x0008B4CD); its original type and name are unproved. 0x000EF065..0x000EF07E constructs 96 type records of stride 0x18 at +0x2EE18 with AsciiString at record +4 (ctor 0x004B9910, dtor 0x0029D7C2); 0x000EF0A7..0x000EF0C1 writes the pointer and sphere at record +8/+0xC/+0x10/+0x14. Count +0x2F718 and integer +0x2F720 are cleared at 0x000EF08C/0x000EF092; 0x000EE479..0x000EE49C compares, wraps and increments +0x2F720 as a prop index. LightClass constructor 0x00130AC0 feeds +0x2F724 at 0x000EF0F7; W3DShroudMaterialPassClass constructor 0x0006E29F feeds +0x2F71C at 0x000EF11C. addProp 0x000EEBF7, updatePropPosition 0x000EE203 and xfer 0x000EE901 access record pointer +0, id +4, location +8/+0xC/+0x10, type +0x14, shroud status +0x18, visible byte +0x1C and sphere +0x20. The record constructors/destructors are empty callbacks 0x0047A6A9/0x000B3FD0. notifyShroudChanged 0x000EE132 clears status words; rva000EE15B passes the +0x2EE0C holder to 0x000E488F. All W3DPropBuffer rowed methods below remain out of line.
Donor facts: Zero Hour GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DPropBuffer.h names Snapshot, TProp, TPropType, their fields, the two array bounds and the common buffer members and methods. BFME 2's additional holder and index retain neutral field names; its addProp/addPropType trailing bool arguments and three snapshot signatures follow the ledger rows, not the donor's differing interface. */
#pragma once

#ifndef BFME2_W3D_PROP_BUFFER_CLASS_H
#define BFME2_W3D_PROP_BUFFER_CLASS_H

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_REFERENCE_XFER) || (defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT))
#error W3DPropBuffer requires Snapshot loadPostProcess, const GetSnapshotName, and xfer(Xfer *) slots
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/SphereClass.h"

class RenderObjClass;
class RenderInfoClass;
class LightClass;
class W3DShroudMaterialPassClass;
class GeometryInfo;

struct TProp
{
    TProp() {}
    ~TProp() {}
    RenderObjClass *m_robj;
    int id;
    Coord3D location;
    int propType;
    int ss;
    bool visible;
    SphereClass bounds;
};

struct TPropType
{
    RenderObjClass *m_robj;
    AsciiString m_robjName;
    SphereClass m_bounds;
};

class Rva00174753Allocation
{
public:
    Rva00174753Allocation() throw();
private:
    void *field00[3];
};

class Rva0008B470
{
public:
    ~Rva0008B470();
};

struct Rva0008B4CD : public Rva00174753Allocation
{
    ~Rva0008B4CD() { reinterpret_cast<Rva0008B470 *>(this)->~Rva0008B470(); }
};

class W3DPropBuffer : public Snapshot
{
public:
    W3DPropBuffer(); // 0x000EF008
    virtual ~W3DPropBuffer(); // 0x000EEEF4
    void addProp(int id, Coord3D location, float angle, float scale, const AsciiString &modelName, bool distanceFog); // 0x000EEBF7
    int addPropType(const AsciiString &modelName, bool distanceFog); // 0x000EE822
    void removeProp(int id); // 0x000EDFCE
    bool updatePropPosition(int id, const Coord3D &location, float angle, float scale); // 0x000EE203
    void notifyShroudChanged(); // 0x000EE132
    void removePropsForConstruction(const Coord3D *position, const GeometryInfo &geometry, float angle); // 0x000EF154
    void drawProps(RenderInfoClass &rinfo); // 0x000EE452
    void rva000EE04A(const Coord3D *position, float radius); // 0x000EE04A
    void rva000EE15B(); // 0x000EE15B

protected:
    virtual void loadPostProcess(); // slot 1, 0x000B3FD0
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const; // slot 2, 0x000EEFE6
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer); // slot 3, 0x000EE901

    enum { MAX_PROPS = 4000, MAX_TYPES = 96 };
    TProp m_props[MAX_PROPS];
    int m_numProps;
    bool m_anythingChanged;
    bool m_initialized;
    bool m_doCull;
    Rva0008B4CD field2EE0C;
    TPropType m_propTypes[MAX_TYPES];
    int m_numPropTypes;
    W3DShroudMaterialPassClass *m_propShroudMaterialPass;
    int field2F720;
    LightClass *m_light;
};

#endif
