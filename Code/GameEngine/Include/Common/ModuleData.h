// Target facts (code addresses are RVAs, table addresses are VAs):
// Snapshot's constructor 0x000053A6 and destructor 0x0049B47C store 0x00BBB554; ModuleData's rowed destructor folds with the latter, and LargeGroupAudioUpdateModuleData's 0x004ABFD9 restores that table at 0x004AC011 after its own 0x00C549F8 table. The four-slot table belongs to Snapshot teardown, not ModuleData's live interface.
// ModuleFactory::newModuleDataFromINI stores the nameToKey result at +4 (0x00257232..0x00257237). The factories at 0x0024CCF4 and 0x0024F141 allocate eight bytes and call DelayedLuaEventUpdateModuleData's 0x000B28BF, which only stores 0x00C4ED70. RadarMarkerClientUpdateModuleData's 0x004C9C98 starts its own data at +8 and its factory 0x00252B11 allocates twelve bytes. Snapshot occupies +0..+3 and the module tag occupies +4..+7: ModuleData is eight bytes.
// The tables 0x00C4ED70 and 0x00C549F8 have 31 slots. Slots 0..3 are the deleting destructor, loadPostProcess (0x000B3FD0), GetSnapshotName (0x00065212, returning the literal at 0x00BC5AFC), and xfer (0x0047A69C, ret 4). Slots 4..13 and 15 return false (0x0047A699); slot 14 returns an AsciiString by value with one int argument (0x000B69A1, ret 8); slots 16..29 return null (0x000D43D0); slot 30 returns true (0x0050B5C6). 0x00C549F8 ends at 0x00C54A74; 0x00C4ED70 ends at 0x00C4EDEC. Unknown slot names remain neutral.
// Zero Hour Common/Module.h supplies the Snapshot inheritance, tag accessor names, and loadPostProcess/xfer spellings. The destructor and GetSnapshotName have ledger rows and remain out of line.
// Zero Hour's ModuleData names isAiModuleData, getAsW3DModelDrawModuleData and getMinimumRequiredGameLOD; their slots come from callers: ThingTemplate::friend_getAIModuleInfo (0x0033B387) tests slot 4 (+0x10), the stats dump at 0x0050CBA2 reads model-draw data from slot 18 (+0x48), W3DTerrainVisual::addProp (0x0009257A) reads prop-draw data from slot 19 (+0x4C), and Drawable's constructor (0x002797BD) compares slot 22 (+0x58) with the static LOD. Their defaults are 0x0047A699 (false) and 0x000D43D0 (null/0).
// Carryover's 0x0037E00C calls slot 21 (+0x54), then walks the returned horde data's members at +0xA4; getHordeModuleData names that evidenced accessor. Its default in the common tables is 0x000D43D0.
#pragma once

#ifndef BFME2_MODULEDATA_H
#define BFME2_MODULEDATA_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class AsciiString;
class HordeModuleData;
class MultiIniFieldParse;
class W3DModelDrawModuleData;
class W3DPropDrawModuleData;
enum NameKeyType;

class ModuleData : public Snapshot
{
public:
    virtual ~ModuleData();
    virtual void loadPostProcess() {}
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *) {}

    virtual bool isAiModuleData() const { return false; }
    virtual bool slot05() const { return false; }
    virtual bool slot06() const { return false; }
    virtual bool slot07() const { return false; }
    virtual bool slot08() const { return false; }
    virtual bool slot09() const { return false; }
    virtual bool slot10() const { return false; }
    virtual bool slot11() const { return false; }
    virtual bool slot12() const { return false; }
    virtual bool slot13() const { return false; }
    virtual AsciiString slot14(int) const;
    virtual bool slot15() const { return false; }
    virtual const void *slot16() const { return 0; }
    virtual const void *slot17() const { return 0; }
    virtual const W3DModelDrawModuleData *getAsW3DModelDrawModuleData() const { return 0; }
    virtual const W3DPropDrawModuleData *getAsW3DPropDrawModuleData() const { return 0; }
    virtual const void *slot20() const { return 0; }
    virtual const HordeModuleData *getHordeModuleData() const { return 0; }
    virtual int getMinimumRequiredGameLOD() const { return 0; }
    virtual const void *slot23() const { return 0; }
    virtual const void *slot24() const { return 0; }
    virtual const void *slot25() const { return 0; }
    virtual const void *slot26() const { return 0; }
    virtual const void *slot27() const { return 0; }
    virtual const void *slot28() const { return 0; }
    virtual const void *slot29() const { return 0; }
    virtual bool slot30() const { return true; }

    void setModuleTagNameKey(NameKeyType key) { m_moduleTagNameKey = key; }
    NameKeyType getModuleTagNameKey() const { return m_moduleTagNameKey; }
    static void buildFieldParse(MultiIniFieldParse &) {}

private:
    NameKeyType m_moduleTagNameKey;
};

#endif
