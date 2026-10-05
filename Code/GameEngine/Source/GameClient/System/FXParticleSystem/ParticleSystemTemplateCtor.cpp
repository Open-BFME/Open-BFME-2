// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// ??0Rva001FBF37@@QAE@XZ @0x001FBF37 22B
// ??0Rva001FBA45@@QAE@XZ @0x001FBA45 22B
// ??0Rva001FA5A5@@QAE@XZ @0x001FA5A5 22B
// NOTE: the 81B ParticleSystemTemplate ctor @0x001FC1E0 that seeded this TU
// now lives in ParticleSystemTemplateCopyCtor.cpp on master; this TU keeps
// only the three honest 22B Rva tail ctors below.
// Evidence (TARGET facts, re-read at 5f22f3ba + seat-52-r14/r17 + seat-53-r20):
// - export row 302 at 0x001FC1E0 = ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABVAsciiString@@@Z;
//   Ghidra 0x1FC1E0 81B ParticleSystemTemplate agrees.
// - retail 81B: SEH prolog (mov eax,0xB6B8B1 + call 0x629188), base call 0x1F4E82 at +0x11,
//   StringBase copy 0x365F0 at +0x29 with dest lea [esi+0x9C] (m_name), derived vtable
//   0xBE1A28 store (VA 0x00BE1A28 = RVA 0x7E1A28), tail call 0x1FBF37 with lea [esi+0xA4],
//   and-zero [esi+0xA0] (m_slave), leave + ret 4. Base-then-derived vtable install proves
//   ParticleSystemTemplate : ParticleSystemInfo; factory 0x1FCBD7 (rowed) constructs the
//   same 0xD4-sized template at 0xDFDF40 from '--nullsystem' via this ctor.
// - base ctor head stores 0xBBB5C8 (RVA 0x7BB5C8); derived overwrites with 0xBE1A28.
// - donor BFME1 6583b3c1 ParticleSystemTemplateCtorThunk: m_name(name) + m_a0[11]=0 +
//   m_slave=0 with base m_pad[0x94] (donor offsets +0x98/+0x9C/+0xA0). Retail dests are
//   +0x9C/+0xA0/+0xA4 (+4 shift: retail base is 0x9C, re-derived from InfoCtor layout +
//   retail REL32, never copied verbatim). Donor order (tail-then-slave) kept.
// - tail 0x1FBF37 22B = and [esi],0 + and [esi+4],0 + lea [esi+8] + call 0x1FBA45;
//   same shape chains via 0x1FA5A5 to rowed 0x1F9060 (row 45763, 22B) which wraps
//   rowed ObjectCreationList 0x1F81BF (row 5687, 19B). Honest Rva names, TU-local
//   wrappers mirroring rowed Rva001F9060Ctor.cpp pattern.
// - RECONCILED r16 (seat-52-r17 + seat-53-r20): canonical Snapshot.h (0x00BBB554 =
//   [0x401750 + 3x 0x43B810 abort], crc/xfer/loadPostProcess, NO string slot) is a
//   DIFFERENT family from FX base 0x007BB5C8 ([0x4025B2 dtor, 0x4B3FD0 void-ret,
//   0x401272 string, 0x1F4F5A Xfer-complex]) and derived 0x007E1A28 (same 4 +
//   0x1FC3A3/0x1F6201/0x1FC179/0x5FAA8D, all unrowed). Including canonical adds
//   wrong virtual slots even when the byte gate stays green, so it is NOT
//   included here. FX base uses its own spelling (FXSnapshot) with retail slot
//   order dtor/LoadPostProcess/GetSnapshotName/DoXfer, TU-scoped.
// - OCL r16: rowed 0x1F81BF constructs exactly one STLport vector via 0x211E58
//   Vector_base (3 pointers = 12B), so sizeof(ObjectCreationList) = 12 (TARGET
//   fact). Three 8B levels + 12 = 44B; retail tail needs 48B (0xD4-0xA4), so the
//   remaining 4B at +0xD0 is an untouched tail gap modeled in the containing
//   Template class, not inside OCL. No fabricated member semantics.
// Sibling flags: Make001FCBD7 /O1 /MD /EHsc /DNDEBUG tried first per seat-52-r14
// shortlist; canonical AsciiString via ascii_string.h (StringBase copy => rowed 0x365F0).
#include "ascii_string.h"

class Xfer;

// Retail FX base vtable 0x007BB5C8 is 4 entries (TARGET fact, seat-53-r20):
// slot0 0x4025B2 dtor-shape, slot1 0x4B3FD0 shared void-ret, slot2 0x401272
// string-ret, slot3 0x1F4F5A Xfer-complex. Derived 0x007E1A28 shares slots 0-3
// then adds 4 Template slots (0x1FC3A3 scalar-dtor shape, 0x1F6201 EH-complex,
// 0x1FC179 6B string-ret to 'FXParticle...', 0x5FAA8D Xfer-taker; all unrowed,
// stay unrowed here). Canonical 0x00BBB554 ([0x401750 + 3x abort 0x43B810],
// crc/xfer/loadPostProcess) is a different abstract family and is NOT used.
// Concrete provider ABI (all declare-only here, definitions in rowed TUs, no
// purecalls emitted by this TU which defines only ctors):
// - dtor: rowed ??1ParticleSystemInfo 0x240E 75B + ??_G 0x2596 28B (concrete).
// - LoadPostProcess: shared ret stub 0x4B3FD0, void(void) thiscall, SHARED across
//   10+ ModuleData-family vtables; never pinned as FX-exclusive.
// - GetSnapshotName: rowed 0x1272 6B (row 48502, export 1205), string(void)
//   returning 'FXParticleSystemInfo'.
// - DoXfer: rowed 0x1F4F5A 354B (row 56335, export 1171), Xfer-taker.
class FXSnapshot
{
public:
    virtual ~FXSnapshot();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);
};

// Bottom OCL is honest 12B: a single 3-pointer STLport vector (TARGET fact:
// rowed 0x1F81BF 19B calls 0x211E58 Vector_base; ZH + BFME2 headers agree the
// class carries exactly one m_nuggets vector, no virtuals, no second member).
// Modeled as 3-pointer storage with no fabricated member names or semantics.
// Genuine provider is rowed ??0ObjectCreationList 19B @0x001F81BF; this TU
// declares only (throw() so no EH residue, like rowed Rva001F9060Ctor pattern).
class ObjectCreationList
{
public:
    ObjectCreationList() throw();
private:
    void *m_vectorStorage[3];
};

class Rva001F9060
{
public:
    Rva001F9060() throw();
private:
    int m_00;
    int m_04;
    ObjectCreationList m_08;
};

class Rva001FA5A5
{
public:
    Rva001FA5A5() throw();
private:
    int m_00;
    int m_04;
    Rva001F9060 m_08;
};

Rva001FA5A5::Rva001FA5A5() throw()
    : m_00(0)
    , m_04(0)
{
}

class Rva001FBA45
{
public:
    Rva001FBA45() throw();
private:
    int m_00;
    int m_04;
    Rva001FA5A5 m_08;
};

Rva001FBA45::Rva001FBA45() throw()
    : m_00(0)
    , m_04(0)
{
}

class Rva001FBF37
{
public:
    Rva001FBF37() throw();
private:
    int m_00;
    int m_04;
    Rva001FBA45 m_08;
};

Rva001FBF37::Rva001FBF37() throw()
    : m_00(0)
    , m_04(0)
{
}

struct IntFloatFloat
{
    unsigned int a;
    float b;
    float c;
    IntFloatFloat()
    {
        b = 0.0f;
        c = 0.0f;
        a = 0;
    }
};

struct FxCoord3D
{
    float x;
    float y;
    float z;
};

struct FxRegion2D
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

// FX base uses the TU-scoped FXSnapshot above (retail 4-slot order
// dtor/LoadPostProcess/GetSnapshotName/DoXfer), never the canonical Snapshot
// (different family, different slots, class_gate). ParticleSystemInfo's genuine
// target providers below are declare-only: definitions live in rowed TUs (dtor
// 0x240E, GetSnapshotName 0x1272 export 1205, DoXfer 0x1F4F5A, deleting 0x2596;
// LoadPostProcess is the shared 0x4B3FD0 ret, never FX-pinned). No fake virtual
// bodies are emitted here. Declaration order below matches retail BBB5C8 raw
// order (LoadPostProcess before GetSnapshotName), not donor order.

namespace FXParticleSystem
{

class ParticleSystemInfo : public FXSnapshot
{
public:
    ParticleSystemInfo();
    virtual ~ParticleSystemInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);

private:
    unsigned char m_isOneShot;
    unsigned int m_shaderType;
    unsigned int m_particleType;
    AsciiString m_particleTypeName;
    IntFloatFloat m_angleZ;
    unsigned int m_systemLifetime;
    unsigned int m_volumeParticleDepth;
    IntFloatFloat m_angularRateZ;
    IntFloatFloat m_angularDamping;
    unsigned int m_windMotion;
    IntFloatFloat m_velDamping;
    IntFloatFloat m_lifetime;
    IntFloatFloat m_startSize;
    AsciiString m_slaveSystemName;
    FxCoord3D m_slavePosOffset;
    AsciiString m_attachedSystemName;
    unsigned int m_emissionVelocityType;
    unsigned char m_isEmissionVolumeHollow;
    unsigned char m_isGroundAligned;
    unsigned char m_isEmitAboveGroundOnly;
    unsigned char m_isParticleUpTowardsEmitter;
    unsigned char m_windMotionMovingToEndAngle;
    FxRegion2D m_uv;
    unsigned int m_unknown98;
};

class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
    ParticleSystemTemplate(const AsciiString &name);
    // Declared, never defined here: suppresses the implicit dtor + ??_G
    // emission in THIS obj (unverified bodies; the true dtor TU owns them
    // when copy/dtor work un-withholds). Vtable stays 4-slot with genuine
    // EXTERNs; no link surface beyond the 4 rowed ctors + vtable COMDAT.
    ~ParticleSystemTemplate();
    // Derived slots 4-7 (retail BE1A28, seat-53-r22 per-slot verdicts).
    // Declare-only, zero definitions in ANY TU yet: grant NO genuine names
    // (identifiers below are address-derived placeholders, never identities),
    // keep the shared slot1 ret stub unpinned, introduce no copy/dtor TU.
    // - slot4 0x005FC3A3: 28B scalar-dtor shape, void*(unsigned); WITHHELD:
    //   its body calls 0x001FC0F1 which installs BE1A38 (different table),
    //   so fold-vs-suffix-alias is UNRESOLVED and no Template name exists.
    //   Positional placeholder only; never pinned, never rowed from here.
    // - slot5 0x005F6201: 142B EH-frame complex, void(void); genuine new
    //   virtual by ABI (no dtor/string/Xfer shape); name UNRESOLVED
    //   (blocked partial 0.95 kept at reverse/attempts/0x001f6201.cpp).
    // - slot6 0x005FC179: 6B string(void) -> 'FXParticle'; genuine new
    //   virtual by ABI; genuine Template name UNRESOLVED (only rowed name
    //   is placeholder ?name@Rva001FC179Named in another TU, not granted).
    // - slot7 0x005FAA8D: 145B Xfer-taker, void(Xfer*) POINTER (distinct
    //   overload vs base DoXfer void(Xfer&)); genuine new virtual by ABI;
    //   name UNRESOLVED (0.98 partials kept under honest Rva name).
    virtual void *Rva001FC3A3_Slot4(unsigned int flags);
    virtual void Rva001F6201_Slot5();
    virtual const char *Rva001FC179_Slot6();
    virtual void Rva001FAA8D_Slot7(Xfer *xfer);

private:
    AsciiString m_name;
    int m_slaveTemplate;
    Rva001FBF37 m_tail;
    // Target-proven 4B tail gap at +0xD0 (TARGET fact, seat-52-r17): template is
    // 0xD4 (rowed vector-deleting dtor 0x1FC052 element + factory 0x1FCBD7 data);
    // base 0x9C + name 4 + slave 4 + tail 44 (8+8+8+20 with honest OCL12) = 0xD0,
    // so 4B remain with no observed store in default/copy/dtor walks. Honest pad,
    // no semantics invented; left uninitialized so the ctor emits no code for it.
    unsigned int m_unknownD0;
};

// ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABVAsciiString@@@Z
// Emitted-object size proof (compile-time, not declaration counting): retail
// allocation sizes are 0xD4 (vector-dtor 0x1FC052 element push + operator-new
// arg at 0x1FC27D), OCL is exactly one 3-pointer vector (12B), and the Rva
// tail chain is 8B per level over a 20B bottom (rowed 0x1F9060 = 8 + OCL12).
// Pre-C++11 TU: negative-size typedef fails the compile if a size drifts.
typedef int OCL12_Check[sizeof(ObjectCreationList) == 12 ? 1 : -1];
typedef int Tail44_Check[sizeof(Rva001FBF37) == 0x2C ? 1 : -1];

}
