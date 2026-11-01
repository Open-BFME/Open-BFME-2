// Target facts (addresses are retail RVAs unless labelled VA):
// AptPlayer's constructor 0x00224E10 calls SubsystemInterface 0x001B4E63,
// then stores VA 0x00BE6E80 at +0; its destructor 0x00224A90 restores the
// same table and calls ~SubsystemInterface 0x001B4E74. The concrete wrapper
// 0x000628EB calls that constructor, then installs VA 0x00BC57E0 instead.
// sizeof is 0x32C: allocation 0x00041E75 reserves 0x32C bytes, and the
// four-byte-aligned object is written through +0x329 at 0x00224F27.
// The wrapper's only post-base store writes its vptr. Base size is 0x0C.
// There are 21 table slots:
// 0-13 are the SubsystemInterface dispatch prefix, 14 is 0x0022274A,
// 15-19 are pure in AptPlayer, and 20 is AddLevel at 0x00224710.
// The wrapper implements slots 15/16 at 0x00062972/0x00062977. Retail
// 0x0056C801 calls slot 15 and reads two floats through its returned pointer.
// The neutral caller spelling v15 exposes that same pointer-returning slot.
// Slot 16 is called at 0x00577CFB and also returns two floats by pointer.
// The getter thunks jump to 0x000A8F58 and 0x000A8F5E, returning VA
// 0x00DB4CF0 and VA 0x00DB4CF8 respectively.
// Slots 17-19 use the signatures rowed at 0x0006297C (four float pointers),
// 0x00062A1C (int) and 0x00062A29 (bool). Slot 20 uses AddLevel's signature
// at 0x00224710; caller 0x0042D8D4 dispatches +0x50 with two strings and
// two zero arguments. Its neutral spelling v20 is retained here.
// Own overrides 1/9/10/12 are 0x00224296/0x00222471/0x002251E5/0x0022244D.
// This class is polymorphic; unnamed slots retain neutral spellings.
// Constructor 0x00224E10 builds fourteen 0x28-byte records at +0xCC and a
// vector at +0x2FC; it writes +0x30C (4 bytes), +0x310/+0x311/+0x312
// (1 byte each), +0x314/+0x318/+0x31C/+0x320/+0x324 (4 bytes each), and
// +0x328/+0x329 (1 byte each). The remaining storage stays opaque.
// 0x00222A53 reads +0x300/+0x314 as pointers and +0x329 as a byte;
// 0x00222BCD/0x00222C12 read +0x312, write +0x328, and dispatch slot 10.
// 0x0051BF47 and 0x0044C205 also dispatch +0x28; v10 and slot28 expose
// that same slot under the neutral spellings their callers use.
// 0x00224818 reads vector pointers +0x2FC/+0x300/+0x304 and byte +0x308.
// 0x00222A8B formats "/_level%d", calls 0x006CCB80, returns its buffer in
// EAX and pops 0x20 bytes. 0x00222B19 also appends a prefix and pops 0x24;
// these are fixed-argument APT calls, with unused ECX, not variadic logging.
// Method spellings and signatures below follow their ledger rows, the
// 0x00222B19 member pin, and the 0x00225301/0x00225375 retail text calls.
#ifndef CANONICAL_RVA00222A8BTARGET_H
#define CANONICAL_RVA00222A8BTARGET_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class UnicodeString;
struct Rva00222A8BScale;
struct ScalePair;

class Rva00222A8BTarget : public SubsystemInterface
{
public:
    virtual ~Rva00222A8BTarget();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
#endif
    virtual void vslot12();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual void vslot13(int);
#endif
    virtual void slot14();
    virtual Rva00222A8BScale *slot3C() = 0;
    virtual Rva00222A8BScale *slot40() = 0;
    virtual void slot17(const float *, const float *, float *, float *) = 0;
    virtual void slot18(int) = 0;
    virtual void slot19(bool) = 0;
    virtual int v20(AsciiString, AsciiString, bool, int);

    __forceinline void v10() { update(); }
    __forceinline void slot28() { update(); }
    __forceinline ScalePair *v15() { return reinterpret_cast<ScalePair *>(slot3C()); }

    int invoke(void *level, const char *function, int argc, const char *a0,
        void *a1, void *a2, void *a3, void *a4); // 0x00222A8B
    int rva00222B19(void *level, const char *prefix, const char *function, int argc,
        const char *a0, void *a1, void *a2, void *a3, void *a4); // 0x00222B19
    unsigned char rva00222A53(); // 0x00222A53
    int rva00222BCD(void *level, const char *function, int argc, const char *a0,
        void *a1, void *a2, void *a3, void *a4); // 0x00222BCD
    int rva00222C12(void *level, const char *prefix, const char *function, int argc,
        const char *a0, void *a1, void *a2, void *a3, void *a4); // 0x00222C12
    void rva00222F55(bool); // 0x00222F55
    void rva002233A6(int); // 0x002233A6
    void rva002239FA(const AsciiString &, const AsciiString &); // 0x002239FA
    void rva00224818(); // 0x00224818
    void rva002251E5(); // 0x002251E5
    void bfmeSetText(const AsciiString &, const UnicodeString &, bool); // 0x00225301
    void rva00225375(const AsciiString &, const AsciiString &, bool); // 0x00225375

    char m_opaque0C[0x2FC - 0x0C];
    int *m_2FC;
    int *m_300;
    int *m_304;
    bool m_308;
    char m_opaque309[3];
    unsigned long m_30C;
    bool m_310;
    bool m_311;
    unsigned char m_312;
    void *m_314;
    int m_318;
    int m_31C;
    int m_320;
    void *m_324;
    unsigned char m_328;
    unsigned char m_329;
};

#endif
