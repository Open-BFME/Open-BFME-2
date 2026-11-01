// ParticleSystemManager: canonical BFME2 interface and constructor-owned storage.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x001FA69F (ledger ??0Rva001F9D98) calls SubsystemInterface 0x001B4E63 at 0x001FA6B4, stores Snapshot's 0x00BBB554 at +0xC at 0x001FA6BE, then installs 0x00BE18C8/+0 and 0x00BE18B8/+0xC at 0x001FA6D0/0x001FA6D6. Destructor 0x001F9D98 first restores the same own tables at 0x001F9DAD/0x001F9DB3; its later 0x00BBB554 store at 0x001F9E8C and call to 0x001B4E74 at 0x001F9E93 destroy the bases. The differing base-phase tables do not belong to the complete manager.
// Primary table 0x00BE18C8 has twenty code pointers followed by text at 0x00BE1918. Slots 0-13 retain SubsystemInterface's order: 0=0x001FA779, 1=0x001F3FEA, 2=0x001B5384, 3/8/12=0x000B3FD0, 4/11=0x005CB9FF, 5=0x0047A699, 6=0x000D43D0, 7/13=0x0047A69C, 9=0x001F636C, 10=0x001F5923. Slots 14/16/17/18 are purecall 0x0003B810; 15=0x003FF0E7; 19 is rowed rva001F9F66 at 0x001F9F66. This class is polymorphic.
// Snapshot table 0x00BE18B8 has four slots: 0=0x001F9EA7 (subtracts 0xC before deleting), 1=0x000B3FD0, 2=0x0004CE28 (returns "FXParticleSystemManager"), 3=0x001F9105. The derived tables 0x00BC4C70/0x00BC4C5C, installed by 0x0004CDCD after calling 0x001FA69F, belong to a different class. Its primary slots 14/16/17/18 are 0x0008BB81/0x0004CF9A/0x0004D47D/0x0004CB16.
// Constructor 0x001FA718..0x001FA73C proves the dword +0x48, two seven-word arrays +0x10/+0x2C, dwords +0x50/+0x54/+0x58/+0x5C/+0x64, and float +0x60. It constructs a list at +0x4C via 0x00280A8D, clears the twelve-byte handle +0x68 at 0x001FA6E2..0x001FA6EA, clears dwords +0x74/+0x78/+0x7C/+0x80 and byte +0x84, and constructs the map at +0x88 via 0x001FA440. Map helper 0x001F9387 clears its last dword at +0x10, bounding the map to twenty bytes before the storage at +0x9C. Storage constructor 0x001F81BF delegates to 0x00211E58, which clears +0/+4 at 0x00211E65/0x00211E67 and passes +8 to the four-byte store at 0x0014F3CA. This twelve-byte region ends at +0xA8, where derived constructor 0x0004CE15 begins its flag; sizeof is 0xA8. Unnamed storage remains opaque.
// Nonvirtual ledger methods: findTemplate 0x001F90DA, newTemplate 0x001FC25A, findParentTemplate 0x001F9F08, rva001F9343 0x001F9343, createParticleSystem 0x001F5A6A, private findParticleSystemByID 0x001F5B0A, destroyParticleSystemByID 0x001F5B79, rva001F5AA4 0x001F5AA4, bfmeStopCW 0x001F9EAF and rva001FCF11 0x001FCF11. Their decorated names prove types and access; creation/lookup return a twelve-byte BfmeParticleSystemHandle, not ParticleSystem*. Lifetime methods remain declarations because retail calls their bodies out of line.
// Zero Hour's ParticleSys.h supplies getOnScreenParticleCount/setOnScreenParticleCount, doParticles/queueParticleRender and m_templateMap names. The derived getter/setter 0x0008BB81/0x003FF0E7 access +0x5C; the RenderInfoClass-reference rows 0x0004CF9A/0x0004D47D prove the argument of primary slots 16/17. Slot 17 keeps a neutral name because the donor does not name that extra pass.
// Snapshot must select its const name-getter surface: slot 2's ledger getter 0x0004CE28 returns a string pointer and RET consumes no argument. The parent's legacy crc(Xfer*) surface contradicts that slot's return and stack contract.
#ifndef BFME2_PARTICLESYS_H
#define BFME2_PARTICLESYS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#error ParticleSystemManager requires Snapshot's const name getter.
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class ParticleSystem;
class ParticleSystemTemplate;
class BfmeParticleSystemHandle;
class BFMERetailAsciiString;
class Object;
class RenderInfoClass;
enum ParticleSystemID;
namespace FXParticleSystem { class ParticleSystemTemplate; class CPUParticle; }

class ParticleSystemManager : public SubsystemInterface, public Snapshot
{
    friend class ParticleSystem;
    friend class FXParticleSystem::CPUParticle;
    friend class W3DModelDraw;
    friend class W3DScriptedModelDraw;
    friend class BeaconClientUpdate;
    friend class LaserUpdate;
    friend class Rva0020453CHolderBase;
    friend class Rva000B75FF;

public:
    ParticleSystemManager();
    virtual ~ParticleSystemManager();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual int getOnScreenParticleCount() = 0;
    virtual void setOnScreenParticleCount(int count);
    virtual void doParticles(RenderInfoClass &rinfo) = 0;
    virtual void slot17(RenderInfoClass &rinfo) = 0;
    virtual void queueParticleRender() = 0;
    virtual void rva001F9F66();

    ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
    ParticleSystemTemplate *newTemplate(const AsciiString &name);
    ParticleSystemTemplate *findParentTemplate(const AsciiString &name, int parentNum) const;
    ParticleSystemTemplate *rva001F9343(const AsciiString &name, int unused) const;
    BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves = true);
    void destroyParticleSystemByID(ParticleSystemID id);
    int rva001F5AA4(const ParticleSystemTemplate *sysTemplate, const Object *object, bool createSlaves);
    void bfmeStopCW(const BFMERetailAsciiString &name);
    void rva001FCF11(const AsciiString &name, FXParticleSystem::ParticleSystemTemplate *system);

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

private:
    BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
    unsigned char field10[0x78];
    char m_templateMap[0x14];
    unsigned char field9C[0x0C];
};

extern ParticleSystemManager *TheParticleSystemManager;

#endif
