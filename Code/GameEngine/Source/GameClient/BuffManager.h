#pragma once
// Native tables C16FE8/C17068/C17088 identify this family through their
// class-name getters. All have Snapshot's four slots: deleting destructor,
// post-load, name, transfer. Constructors and the nine-entry manager prove
// sizes 14/44/26C hex; transfer and lifecycle bodies prove the field offsets.
#if !defined(__SNAPSHOT_H_)
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
// Drawable.cpp already obtains the same three-float RGBColor from donor
// BaseType.h. Preserve that existing definition in this consumer.
#ifndef _BASE_TYPE_H_
#include "../../../Libraries/Include/Lib/RGBColor.h"
#endif
class Rva00419BA5;
class ThingTemplate;
class Drawable;
class BuffInstance;
class BuffManager;
class GlowMaterial : public Snapshot {
    friend class BuffInstance;
public:
    GlowMaterial() throw();
    virtual ~GlowMaterial();
    unsigned char __declspec(noinline) IsActive();
protected:
    // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
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
public:
    void *m_04;
    void *m_08;
    unsigned int m_0C;
    unsigned int m_10;
};
class BuffInstance : public Snapshot {
    friend class BuffManager;
public:
    BuffInstance() throw();
    virtual ~BuffInstance();
    void TurnOff(bool immediate);
    void Update(unsigned int frame);
    bool MakeNormalBuff(int type, int subtype, void *thingTemplate, void *drawable, int duration);
    bool MakeGlowOutlineBuff(int type, int subtype, void *drawable, int duration, int color, float intensity);
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
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
public:
    bool m_active;                       // +04
    int m_type;                          // +08
    int m_subType;                       // +0C
    int m_duration;                      // +10
    unsigned int m_frameLimit;           // +14, unsigned native comparison
    Rva00419BA5 *m_glow;                  // +18
    const ThingTemplate *m_thing;        // +1C
    RGBColor m_color;                    // +20
    float m_intensity;                   // +2C
    GlowMaterial m_material;             // +30
};
class BuffManager : public Snapshot {
    friend class Drawable;
public:
    BuffManager(int owner);
    virtual ~BuffManager();
    void TurnOffBuff(int type, bool immediate);
    void TurnOnBuff(int type, void *thingTemplate, int duration, int color, float intensity);
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
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
public:
    void *m_drawable;                     // +04
    BuffInstance m_buffs[9];              // +08, stride44 hex
};
typedef char GlowMaterialRetailSize[(sizeof(GlowMaterial)==0x14)?1:-1];
typedef char BuffInstanceRetailSize[(sizeof(BuffInstance)==0x44)?1:-1];
typedef char BuffManagerRetailSize[(sizeof(BuffManager)==0x26C)?1:-1];
