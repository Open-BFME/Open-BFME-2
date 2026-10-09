// cl: /O2 /G6 /arch:SSE /MD
// ?rva006FB120@Rva006FB860@@QAEXHHHHD@Z retail 0x006FB120..0x006FB5AC (1164
// bytes: code through 0x006FB592 including the in-loop return path, then
// alignment and the six-entry case table at 0x006FB594), thiscall ret 0x14.
// Called only by 0x006FB860 (rva006FB860, declared with this signature).
// WB twin 0x017988B0 (Code\Libraries\Source\Apt\AptInput.cpp, asserts at
// lines 662..771) supplies the flow and the assert texts: walk the sparse
// input set at +0x28/+0x2A/+0x2C (count, size, maElements), skip pooled
// entries (0x006E3710), pick the topmost hit instance for +0x68, queue clip
// events through AptCIH::queueClipEvents (0x006E2010, returns bool) per
// input state, then for state 0 scan the button set at +0x8/+0xA/+0xC and
// queue the first matching key action on the action queue at +0xA0
// (0x006E4B80) and return. Otherwise finish with the focus transition
// 0x006FA7E0 and, for device 1, 0x006FAA20. Owner class and method name
// remain address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

// The inline-asm break keeps the two NOT_REACHED blocks apart as in retail
// (the intrinsic lets cl tail-merge them).
#define APT_ASSERT(cond, text, file, line)                                     \
    if (!(cond)) {                                                             \
        g_bfmeAptAssertAtE17734(text, file, line);                             \
        if (g_bfmeAptBreakOnAssertAtDDC01C) {                                  \
            __asm int 3                                                        \
        }                                                                      \
    }
#define APT_INPUT_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp"
#define APT_CIH_FILE "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"

class AptCIH;
class AptValue
{
public:
    bool isCIH(bool bUndefOK = false) const;    // 0x006DC580
    bool isUndefined() const;                   // 0x006DC010
    AptCIH *c_cih(bool bUndefOK = false) const; // 0x006DCF60
    int getVtblIndex() const;                   // 0x006DBB30
};
class BfmeAptValue006DCD20
{
public:
    bool rva006E02B0() const; // 0x006E02B0
};

struct AptButtonRecord
{
    int flags;  // key code in bits 9..15
    int action; // action block handed to the queue by address
};
struct AptButtonCharacterData
{
    char pad0[0x34];
    int nRecords;
    AptButtonRecord *aRecords;
};
struct AptButtonCharacter
{
    char pad0[0xC];
    AptButtonCharacterData *pData;
};

class AptCIH : public AptValue
{
public:
    bool rva006E0BF0() const;               // 0x006E0BF0
    int rva006E24D0();                      // 0x006E24D0 (tested as int)
    bool rva006E0C50(const AptCIH *) const; // 0x006E0C50
    bool rva006E2460(const AptCIH *) const; // 0x006E2460
    bool queueClipEvents(int mask, int value, int flag); // 0x006E2010
    __forceinline bool isButtonInst()
    {
        APT_ASSERT(this, "this", APT_CIH_FILE, 0xB5)
        return getVtblIndex() == 14 && !isUndefined();
    }
    char pad[0x48];
    AptCIH *mpParent;                // +0x48
    AptButtonCharacter *mpCharacter; // +0x4C
};

class AptActionQueueC
{
public:
    void rva006E4B80(void *actions, AptCIH *target, int flags, int arg); // 0x006E4B80
};

struct Rva006E3710Node;
class Rva006E3710
{
public:
    bool rva006E3710(Rva006E3710Node *node); // 0x006E3710
};
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
extern AptValue *gpUndefinedValue;
extern int g_00E17704;

class Rva006E1E30;
class Rva006F9FC0
{
public:
    bool rva006F9FC0(Rva006E1E30 *object, int value); // 0x006F9FC0
};

struct AptInputInstSet
{
    unsigned short mnCount;
    unsigned short mnSize;
    AptCIH **maElements;
    int GetSize() const { return mnSize; }
};

class Rva006FB860
{
public:
    char pad0[8];
    AptInputInstSet buttonSet;      // +0x08
    char pad10[0x28 - 0x10];
    AptInputInstSet inputSet;       // +0x28
    char pad30[0x68 - 0x30];
    AptValue *m68;                  // +0x68
    char pad6C[0xA0 - 0x6C];
    AptActionQueueC *mpActionQueue; // +0xA0
    void rva006FA7E0(bool first, bool enabled, int value);
    void rva006FAA20();
    void rva006FB120(int eType, int state, int value, int device, char isFirst);
};

void Rva006FB860::rva006FB120(int eType, int state, int value, int device, char isFirst)
{
    AptCIH *pInst = 0;
    bool bQueuedPress = false;
    AptValue *pHit = gpUndefinedValue;
    bool bReleased = false;
    bool bPressed = false;
    int n = 0;
    int i;
    for (i = 0; i < inputSet.GetSize(); ++i) {
        if (n == inputSet.mnCount)
            break;
        if (!inputSet.maElements[i])
            continue;
        pInst = inputSet.maElements[i];
        if (((Rva006E3710 *)g_bfmeAptPtrAtE176D0)->rva006E3710((Rva006E3710Node *)pInst))
            continue;
        APT_ASSERT(inputSet.maElements[i]->isCIH(), "inputSet.maElements[i]->isCIH()", APT_INPUT_FILE, 0x296)
        if (isFirst && pInst->rva006E0BF0() && pInst->rva006E24D0()
            && ((Rva006F9FC0 *)this)->rva006F9FC0((Rva006E1E30 *)pInst, value)) {
            if (pHit->isUndefined()
                || (!pInst->rva006E0C50(pHit->c_cih()) && pInst->rva006E2460(pHit->c_cih())))
                pHit = pInst;
        }
        if (device == 1) {
            switch (state) {
            case 0:
                APT_ASSERT(eType == 0, "eType == AptInputType_MouseButton0", APT_INPUT_FILE, 0x2AB)
                pInst->queueClipEvents(0x10, value, 1);
                bPressed = true;
                break;
            case 1:
                APT_ASSERT(eType == 0, "eType == AptInputType_MouseButton0", APT_INPUT_FILE, 0x2B1)
                pInst->queueClipEvents(0x20, value, 1);
                bReleased = true;
                break;
            case 3:
            case 4:
                break;
            case 5:
                if (!((BfmeAptValue006DCD20 *)pInst)->rva006E02B0())
                    pInst->queueClipEvents(8, value, 1);
                break;
            default:
                APT_ASSERT(0, "NOT_REACHED", APT_INPUT_FILE, 0x2C0)
                break;
            }
        } else {
            switch (state) {
            case 0:
                if (((value & 3) == 1 && ((unsigned)value >> 17 & 0x7FFF) == 0x1F6)
                    || ((unsigned)value >> 17 & 0x7FFF) == 0x1F5) {
                    APT_ASSERT(eType == 0x1F5 || eType == 0x1F6,
                               "(eType==AptInputType_LeftAnalogStick) || (eType==AptInputType_RightAnalogStick)",
                               APT_INPUT_FILE, 0x2CD)
                    pInst->queueClipEvents(0x40, value, 0);
                } else if ((value & 3) == 1) {
                    pInst->queueClipEvents(0x40, value, 0);
                    if (!bQueuedPress)
                        bQueuedPress = pInst->queueClipEvents(0x20000, value, 1);
                }
                break;
            case 1:
                if ((value & 3) == 1)
                    pInst->queueClipEvents(0x80, value, 0);
                break;
            default:
                APT_ASSERT(0, "NOT_REACHED", APT_INPUT_FILE, 0x2E6)
                break;
            }
        }
        ++n;
    }

    if (state == 0 && buttonSet.mnCount && !bQueuedPress) {
        n = 0;
        for (i = 0; i < buttonSet.GetSize(); ++i) {
            if (n == buttonSet.mnCount)
                break;
            if (!buttonSet.maElements[i])
                continue;
            AptCIH *pButton = buttonSet.maElements[i];
            if (((Rva006E3710 *)g_bfmeAptPtrAtE176D0)->rva006E3710((Rva006E3710Node *)pButton))
                continue;
            APT_ASSERT(pButton->isButtonInst(), "pInst->isButtonInst()", APT_INPUT_FILE, 0x303)
            AptButtonCharacterData *pData = pButton->mpCharacter->pData;
            for (int k = 0; k < pData->nRecords; ++k) {
                if (pButton->mpCharacter->pData->aRecords[k].flags & 0xFE00) {
                    int key = (pData->aRecords[k].flags & 0xFE00) >> 9;
                    if (eType == key) {
                        mpActionQueue->rva006E4B80(&pData->aRecords[k].action,
                                                   pButton->mpParent, 0x400000, g_00E17704);
                        return;
                    }
                }
            }
            ++n;
        }
    }

    if (isFirst)
        m68 = pHit;
    rva006FA7E0(bPressed, bReleased, value);
    if (device == 1)
        rva006FAA20();
}
