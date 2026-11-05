// Target facts: constructor RVA 0x006CBDE0 calls the eight-byte AptValue constructor 0x006DCD20, installs VA 0x00CE8C24 at +0 (0x006CBE12), and constructs EAStringC at +8 (0x006CBE18). Destructor 0x006E2A70 installs the same table, destroys the string at 0x006E2B0D and calls AptValue destruction 0x006DE350 at 0x006E2B1C; the latter restores VA 0x00CEAED0. The differently named lifecycle rows Rva006CBDE0 and Rva006CBF40 describe this object: allocation 0x006F6E21 and deleting destruction 0x006CBF55 both use sizeof 0x60.
// Target facts: VA 0x00CE8C24 has 15 slots, with RVAs 006DCAC0,006E05B0,006CBCD0,006E0500,006E0510,006CBED0,006CBEB0,006E0520,006E0560,006CBCF0,006E0440,006E0460,001826C0,006E11B0,006CBF40; assertion text starts at VA 0x00CE8C60. AptValue supplies the inherited slot names; slots 12/13 remain neutral. Constructor stores 0x006CBE34..0x006CBE61 prove four-byte fields +0x0C..+0x4C; property allocation/access at 0x006E06A0 proves floats +0x0C..+0x40 and the twelve-float pointer +0x44; 0x006E0B60 proves the +0x48 parent chain; 0x006F7B97/0x006F7BA4 prove list pointers +0x54/+0x50; 0x006F72F0 proves a signed 17-bit depth at +0x58; constructor 0x006CBE6A/0x006CBE75 proves the +0x5C flag word.
// Target facts: nonvirtual API declarations retain AptCIH ledger rows at 006E0B20/006E0B40,006E0B60/006E0B80,006E0BF0/006E0C50/006E0CB0,006E0FB0/006E1020/006E1090/006E1100/006E1170,006CFF40,006E11B0,006E1C40/006E1DD0/006E1F00/006E1F90,006E2010,006E2460/006E24D0/006E24E0/006E2560/006E2690/006E2C10/006E2D60/006E2EE0,006E06A0/006E0930. Existing retail-call bindings name predicates IsSpriteInstBase (006CFCD0), IsCharacterInst (006E0200), IsLevelInst (006E03A0), IsSpriteInst (006E01A0), IsAnimationInst (006CBEE0), GetRootAnimation (006E0CB0), GetSpriteInstBase (006CFF40), factoryGetProperty (006E0920), rva006E1540 (006E1540), and rva006dbd80 (006DBD80). Lifecycle and all rowed bodies stay out of line; no copy or assignment body is inferred.
#pragma once

#include "AptValue.h"
#include "EAStringC.h"

class AptRenderingContext;
struct AptSpriteInstBase;

class AptCIH : public AptValue
{
public:
    AptCIH(int type, void *instance, AptValue *parent);
    virtual ~AptCIH();

    virtual void Release();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const, const EAStringC *const, AptValue *const);
    virtual void PreDestroy();
    virtual void DestroyGCPointers();
    virtual bool IsGarbageCollected() const;
    virtual void RegisterReferences() const;

    void SetEventHandler(int);
    void RemoveEventHandler(int);
    int rva006E0B60() const;
    int rva006E0B80(int) const;
    bool rva006E0BF0() const;
    bool rva006E0C50(const AptCIH *) const;
    const AptCIH *rva006E0CB0() const;
    void *rva006E0FB0() const;
    void *rva006E1020() const;
    void *rva006E1090() const;
    void *rva006E1100() const;
    void *rva006E1170() const;
    void *rva006CFF40() const;
    void rva006E11B0();
    void rva006E1C40(AptRenderingContext *, int);
    void rva006E1DD0(void *);
    void rva006E1F00(int);
    int rva006E1F90(int);
    bool queueClipEvents(int, int, int);
    bool rva006E2460(const AptCIH *) const;
    int rva006E24D0();
    bool rva006E24E0() const;
    void rva006E2560(int);
    void ClearCIH(int);
    void jumpToFrame(int);
    void rva006E2D60();
    void rva006E2EE0();
    void factoryEnsureProperties();
    void factorySetProperty(int, float, bool);
    float factoryGetProperty(int) const;
    bool IsSpriteInstBase() const;
    bool IsCharacterInst() const;
    bool IsLevelInst() const;
    bool IsSpriteInst(bool = false) const;
    bool IsAnimationInst(bool = false) const;
    bool rva006CFCD0() const;
    AptCIH *GetRootAnimation();
    AptSpriteInstBase *GetSpriteInstBase() const;
    void rva006E1540();
    void rva006dbd80();

    EAStringC field08;
    float field0C;
    float field10;
    float field14;
    float field18;
    float field1C;
    float field20;
    float field24;
    float field28;
    float field2C;
    float field30;
    float field34;
    float field38;
    float field3C;
    float field40;
    float *field44;
    AptCIH *field48;
    void *field4C;
    AptCIH *field50;
    AptCIH *field54;
    unsigned int field58;
    unsigned int field5C;
};
