// ?rva006FAB40@@YGXPAVAptValue@@HH@Z
// partial score=0.72 date=2026-10-06
// cl: /O2 /MD
// ?rva006FAB40@@YGXPAVAptValue@@HH@Z @0x006FAB40 347B.
// The retail assertion identifies AptInput.cpp:0x483 and tests
// pValue->ContainsNativeHashVirtual(). The three stack inputs are a value,
// event mask, and an integer passed unchanged to the queued action; ret 0xC
// establishes the callee-cleanup ABI. The function and its role stay
// address-derived because no independent target evidence supplies the method
// name.
//
// Target behavior: for a CIH, admit only masks accepted by rva006E1F90; for a
// non-CIH, admit masks present in its native hash or its __proto__ hash. Walk
// the six retail event-mask/name pairs, find defined script-function values,
// duplicate a function whose +0x20 CIH differs from pValue, transfer the
// +0x24 parent-animation reference, set its GC root count, and enqueue the
// resulting action through the pool at VA 0x00E176D0+0xA0.
//
// The event tables and call sequence are target facts. The property mask/name
// records begin at VA 0x00DDC8EC; the action-code records begin at 0x00DDC2E8.
// AptValue/AptCIH helper identities come from matched target bodies.
// The +0x20/+0x24 fields and Duplicate/GetResult slots follow the established
// AptScriptFunction layout; no complete class layout or original AptInput
// method name is asserted.

class EAStringC;
struct AptNativeHash;
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    AptValue *findChild(const EAStringC *name, AptValue *defaultValue);
};

struct AptNativeHash
{
    int mnTotalSize;
    void *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
};
extern int g_00DDC8EC[];
extern int g_00DDC2E8[];
struct Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

class BfmeAptValue006DCD20
{
public:
    bool isCIH(bool allowUndefined) const;
    BfmeAptValue006DCD20 *rva006DCF60(bool allowUndefined);
    int isScriptFunction() const;
    BfmeAptValue006DCD20 *rva006DCEE0();
    void setGCRootCount(unsigned int count);
};

class AptCIH : public AptValue
{
public:
    bool rva006E1F90(int flag);
};

class Rva006DBB60ShrNAndField
{
public:
    int get() const;
};

class Rva006E0D40
{
public:
    void rva006E0D40();
};

class Rva006F97B0
{
public:
    void rva006F97B0();
};

class Rva006E3230
{
public:
    void rva006E3740(AptValue *context, AptValue *function,
                     AptValue *result, int eventMask, int eventCode);
};

struct AptPoolAtE176D0
{
    char _pad00[0xA0];
    Rva006E3230 *actionQueue;
};

class AptScriptFunctionSlotView
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual AptScriptFunctionSlotView *duplicate(AptCIH *context);
    virtual void slot40();
    virtual AptValue *slot44();
};

EAStringC *__cdecl Rva0070B4F0GetString(int index);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

void __stdcall rva006FAB40(AptValue *pValue, int eventMask, int eventCode)
{
    AptValue *context = pValue;
    int mask = eventMask;
    if (!context->ContainsNativeHashVirtual()) {
        g_bfmeAptAssertAtE17734(
            "pValue->ContainsNativeHashVirtual()",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",
            0x483);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }

    if (((BfmeAptValue006DCD20 *)context)->isCIH(false)) {
        int admitted = ((AptCIH *)((BfmeAptValue006DCD20 *)context)
                            ->rva006DCF60(false))
                           ->rva006E1F90(mask);
        if (!admitted)
            return;
    }

    if (!((BfmeAptValue006DCD20 *)context)->isCIH(false)) {
        if (!(context->GetNativeHashVirtual()->nEventHandlers & mask)) {
            AptValue *prototype = context->GetNativeHashVirtual()->mp__proto__;
            if (!(prototype->GetNativeHashVirtual()->nEventHandlers & mask))
                return;
        }
    }

    for (int offset = 0; offset < 0x30; offset += 8) {
        if (*(int *)((char *)g_00DDC8EC + offset) & mask) {
            int stringId = *(int *)((char *)g_00DDC8EC + offset + 4);
            AptValue *child = context->findChild(Rva0070B4F0GetString(stringId), 0);
            if (child && static_cast<unsigned char>(
                    ((Rva006DBB60ShrNAndField *)child)->get())) {
                BfmeAptValue006DCD20 *value = (BfmeAptValue006DCD20 *)child;
                if (static_cast<unsigned char>(value->isScriptFunction())) {
                    AptScriptFunctionSlotView *function =
                        (AptScriptFunctionSlotView *)value->rva006DCEE0();
                    AptCIH *oldCIH = *(AptCIH **)((char *)function + 0x20);
                    if (oldCIH != (AptCIH *)context) {
                        function = function->duplicate((AptCIH *)context);
                        ((Rva006E0D40 *)*(AptCIH **)((char *)function + 0x24))
                            ->rva006E0D40();
                        ((AptValue *)*(AptCIH **)((char *)function + 0x24))
                            ->Release();
                        *(AptCIH **)((char *)function + 0x24) = oldCIH;
                        ((Rva006F97B0 *)oldCIH)->rva006F97B0();
                        ((AptValue *)*(AptCIH **)((char *)function + 0x24))
                            ->AddRef();
                        ((BfmeAptValue006DCD20 *)function)->setGCRootCount(1);
                    }

                    AptPoolAtE176D0 *pool = (AptPoolAtE176D0 *)g_bfmeAptPtrAtE176D0;
                    AptValue *result = function->slot44();
                    pool->actionQueue->rva006E3740(
                        context, (AptValue *)function, result,
                        *(int *)((char *)g_00DDC2E8 + offset),
                        eventCode);
                }
            }
        }
    }
}
