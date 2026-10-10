// cl: /O2 /G6 /arch:SSE /MD /EHsc
// ?queueClipEvents@AptCIH@@QAE_NHHH@Z retail 0x006E2010..0x006E2452 (1090
// bytes; the ghidra extent of 1084 stops inside the shared epilogue before
// add esp 0x28 / ret 0xC), thiscall returning bool.
// WB twin 0x01796F50 AptCIH::queueClipEvents (Apt/AptCIH.cpp, asserts at
// lines 1806..1809) supplies the name and flow; the
// caller 0x006FB120 (AptInput.cpp) reads the bool. Retail inlines the WB
// helpers: the isTextInst predicate 0x006E02B0 (type 15; this assert at
// AptCIH.h:0xC4; named by the 0x006FFD80 getVariable assert text), the
// sprite-character accessor 0x006CFF40 (isSpriteInstBase assert AptCIH.h:0x7D)
// and the action-queue wrappers on the global at 0x00E176D0 (+0xA0 queue).
// Flow: walk the sprite character clip-action set at +0x20 (count / 12-byte
// records flags/key/actions), queue matching records by event mask (key press
// compares bits 17.. of value; load/unload/enterFrame-like masks 0x200/4/
// 0x40000 run the actions now through a pooled 0x44-byte
// AptScriptFunctionByteCodeBlock named by string id 0x6B/0x75 under
// PrepareForExecution/callFunction/CleanupAfterExecution with the
// "AptClipEvents" setup and the refcount assert at AptCIH.cpp:0x710); then,
// when flag is set, map the mask through the 17-entry table 0x00DDC2E8 to an
// event-name string and queue the hash handler or the named child function
// (duplicated for a foreign CIH via vtable slot 15 Duplicate). The unwind
// funclet passes the new block and 0x44 to 0x006F12F0. Field names are
// descriptive; offsets are target facts.
// Needs two canonical-header lines in AptObject/AptScriptFunction.h: in
// class AptValue "unsigned int getRefCount() const;" and in class
// AptScriptFunctionByteCodeBlock "static void *operator new(unsigned int);"
// plus "static void operator delete(void *,unsigned int);" (as in
// AptScriptFunction1/2).
#include "AptObject/AptScriptFunction.h"
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)

#define APT_ASSERT(cond, text, file, line)                                     \
    if (!(cond)) {                                                             \
        g_bfmeAptAssertAtE17734(text, file, line);                             \
        if (g_bfmeAptBreakOnAssertAtDDC01C)                                    \
            __debugbreak();                                                    \
    }
#define APT_CIH_H "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
#define APT_CIH_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp"

class Rva006D2A60 { public: void *allocBlock(int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
void Rva006F12F0Free(void *, int);
__forceinline void *AptScriptFunctionByteCodeBlock::operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
__forceinline void AptScriptFunctionByteCodeBlock::operator delete(void *p, unsigned int n) { Rva006F12F0Free(p, n); }

class EAStringC
{
public:
    const char *rva00620090() const; // 0x00620090
};
EAStringC *Rva0070B4F0GetString(int id);

class Rva006DBB30SarDwordField
{
public:
    int get() const; // 0x006DBB30
};
class BfmeAptValue006DCD20
{
public:
    BfmeAptValue006DCD20 *rva006DCEE0(); // 0x006DCEE0
    void setGCRootCount(unsigned int);   // 0x006DBC70
};

struct AptClipActionRecord
{
    unsigned int flags;
    unsigned int keyCode;
    const unsigned char *actions;
};
struct AptClipActionSet
{
    int count;
    AptClipActionRecord *items;
};
struct AptSpriteCharacter
{
    char pad0[0x20];
    AptClipActionSet *mpClipActions; // +0x20
};

class AptCIH : public AptValue
{
public:
    bool IsSpriteInstBase() const; // 0x006CFCD0
    int rva006E1F90(int mask);     // 0x006E1F90
    bool queueClipEvents(int mask, int value, int flag);
    __forceinline bool isTextInst() const
    {
        APT_ASSERT(this, "this", APT_CIH_H, 0xC4)
        return ((const Rva006DBB30SarDwordField *)this)->get() == 15 && !isUndefined();
    }
    __forceinline AptSpriteCharacter *getSpriteCharacter() const
    {
        APT_ASSERT(IsSpriteInstBase(), "isSpriteInstBase()", APT_CIH_H, 0x7D)

        return mpCharacter;
    }
    char pad8[0x4C - 8];
    AptSpriteCharacter *mpCharacter; // +0x4C
};

class AptActionQueueC
{
public:
    void rva006E3740(AptValue *, AptValue *, AptValue *, int, int); // 0x006E3740
    void rva006E3810(AptValue *, AptValue *, AptValue *, int, int); // 0x006E3810
    void rva006E4B80(void *actions, AptCIH *target, int type, int value); // 0x006E4B80
    void rva006E4C70(void *actions, AptCIH *target, int type, int value); // 0x006E4C70
};
class Rva006E34D0
{
public:
    char pad0[0xA0];
    AptActionQueueC *mpActionQueue; // +0xA0
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
extern int g_00E17704;

struct Rva006E0AC0Entry
{
    int m_mask;
    int m_str;
};
extern Rva006E0AC0Entry g_00DDC2E8[];

template<class T> class AptValuePtrStack
{
    int m_nElements;
    int m_nCapacity;
    T **m_aElements;
public:
    void push(T *value);
    void pop();
};
struct AptActionSetup
{
    AptValue *context, *value;
    const char *name;
    int action;
};
struct AptActionInterpreter
{
    char pad0[0x24];
    AptValuePtrStack<AptValue> thisStack; // +0x24
    char pad30[0x40 - 0x30];
    AptConstantPool constantPool;         // +0x40
    void *PrepareForExecution(AptActionSetup *);
    void CleanupAfterExecution(void *, AptActionSetup *);
    void callFunction(AptValue *, AptValue *, int);
};
extern AptActionInterpreter g_aptDateInterpreter;

bool AptCIH::queueClipEvents(int mask, int value, int flag)
{
    if (isTextInst())
        return false;
    AptSpriteCharacter *pChar = getSpriteCharacter();
    if (!rva006E1F90(mask))
        return false;
    bool bQueued = false;
    if (pChar->mpClipActions) {
        for (int i = 0; i < pChar->mpClipActions->count; ++i) {
            if (!(pChar->mpClipActions->items[i].flags & mask))
                continue;
            switch (mask) {
            case 2:
                g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E4C70(&pChar->mpClipActions->items[i].actions, this, 2, g_00E17704);
                bQueued = true;
                break;
            case 0x200:
            case 4:
            case 0x40000: {
                EAStringC *name = Rva0070B4F0GetString(mask == 0x200 ? 0x6B : 0x75);
                AptScriptFunctionByteCodeBlock *pFunc = new AptScriptFunctionByteCodeBlock(
                    pChar->mpClipActions->items[i].actions, -1, g_aptDateInterpreter.constantPool,
                    name->rva00620090(), this, 0);
                AptActionSetup setup;
                setup.context = this;
                setup.value = pFunc;
                setup.name = "AptClipEvents";
                setup.action = mask;
                void *saved = g_aptDateInterpreter.PrepareForExecution(&setup);
                g_aptDateInterpreter.thisStack.push(this);
                pFunc->AddRef();
                g_aptDateInterpreter.callFunction(this, pFunc, 0);
                APT_ASSERT(pFunc->getRefCount() == 1, "pFuncValue->getRefCount() == 1", APT_CIH_CPP, 0x710)
                pFunc->Release();
                g_aptDateInterpreter.thisStack.pop();
                g_aptDateInterpreter.CleanupAfterExecution(saved, &setup);
                bQueued = true;
                break;
            }
            case 0x20000:
                if (pChar->mpClipActions->items[i].keyCode == ((unsigned int)value >> 17)) {
                    g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E4C70(&pChar->mpClipActions->items[i].actions, this, 0x20000, value);
                    bQueued = true;
                }
                break;
            default:
                g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E4B80(&pChar->mpClipActions->items[i].actions, this, mask, value);
                bQueued = true;
                break;
            }
        }
    }
    if (flag) {
        int idx = 0;
        for (int j = 0; j < 17; ++j) {
            if (g_00DDC2E8[j].m_mask & mask) {
                idx = j;
                break;
            }
        }
        AptNativeHash *hash = GetNativeHashVirtual();
        AptValue *handler = hash->Lookup(Rva0070B4F0GetString(g_00DDC2E8[idx].m_str));
        if (handler) {
            int m = g_00DDC2E8[idx].m_mask;
            if (m == 0x4000 || m == 0x2000)
                g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E3740(this, handler, 0, m, value);
            else
                g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E3810(this, handler, 0, m, value);
            bQueued = true;
        } else {
            AptValue *child = findChild(Rva0070B4F0GetString(g_00DDC2E8[idx].m_str), 0);
            if (child && child->getIsDefined()) {
                AptScriptFunctionBase *fn = (AptScriptFunctionBase *)((BfmeAptValue006DCD20 *)child)->rva006DCEE0();
                if (*(AptCIH **)((char *)fn + 0x20) != this) {
                    child = fn->Duplicate(this);
                    ((BfmeAptValue006DCD20 *)child)->setGCRootCount(1);
                }
                int m = g_00DDC2E8[idx].m_mask;
                if (m == 0x4000 || m == 0x2000)
                    g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E3740(this, child, 0, m, value);
                else
                    g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E3810(this, child, 0, m, value);
                if (g_00DDC2E8[idx].m_mask == 1)
                    g_bfmeAptPtrAtE176D0->mpActionQueue->rva006E3740(this, child, 0, g_00DDC2E8[idx].m_mask, value);
                bQueued = true;
            }
        }
    }
    return bQueued;
}
