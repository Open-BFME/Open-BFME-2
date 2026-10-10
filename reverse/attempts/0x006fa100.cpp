// ?rva006FA100@Rva006FB860@@QAEXPAVAptCIH@@H@Z
// partial score=0.76445 date=2026-10-10
// ?rva006FA100@Rva006FB860@@QAEXPAVAptCIH@@H@Z
// partial score=0.35 date=2026-10-06
// cl: /O2 /G6 /MD
// The BFME 1 AptInput.cpp donor routine BfmeBroadcast1282::bfmeBroadcast1282
// at submodule revision 6583b3c1ff21db4a561285717028fdafc780b7db supplies the
// route-mask, string lookup, action queue, and audio-switch semantics. Its TU
// compiled under BFME 2 settings yielded no byte placements. Target evidence
// independently establishes this AptInput.cpp body at 0x006FA100, the +0x48
// parent, descriptor +0x34/+0x38/+0x3C fields, vtable slot 3 flag object, and
// queue/callee addresses. Owner and source-level method names remain unknown.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptCIH;
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
class BfmeAptValue006DCD20
{
public:
    bool isUndefined() const;
    void *rva006E04A0() const;
};
class Rva006FA100InstFlags
{
public:
    unsigned char _pad00[0x10];
    unsigned int flags;
};
class AptCIH
{
public:
    virtual void vtableSlot0();
    virtual void vtableSlot1();
    virtual void vtableSlot2();
    virtual Rva006FA100InstFlags *vtableSlot3();
    unsigned char _pad04[0x48 - 4];
    AptCIH *pParent;
    void *payload;
};
struct Rva006FA100Record
{
    int mask;
    void *payload;
};
struct Rva006FA100Audio
{
    unsigned char _pad00[8];
    void *handle;
};
struct Rva006FA100Descriptor
{
    unsigned char _pad00[0x34];
    int count;
    Rva006FA100Record *records;
    Rva006FA100Audio **audio;
};
struct Rva006FA100Source
{
    unsigned char _pad00[0x0c];
    Rva006FA100Descriptor *descriptor;
};
class AptValue;
class AptActionQueueC {public:
 void rva006E4B80(void *,AptCIH*,int,int);
 void rva006E3810(AptValue*,AptValue*,AptValue*,int,int);
};
class AptAnimationPoolData
{
public:
    void rva006E6540();
};
class EAStringC;
EAStringC *Rva0070B4F0GetString(int index);
class Rva0070B380
{
public:
    void *lookup(const EAStringC &key);
};
class Rva006FB860
{
public:
    void rva006FA100(AptCIH *pInst, volatile int mode);
};

void Rva006FB860::rva006FA100(AptCIH *pInst, volatile int mode)
{
    if (!pInst) {
        g_bfmeAptAssertAtE17734("pInst",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0x101);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (!pInst) {
        g_bfmeAptAssertAtE17734("this",
            "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)pInst)->get() != 0xE ||
        ((const BfmeAptValue006DCD20 *)pInst)->isUndefined()) {
        g_bfmeAptAssertAtE17734("pInst->isButtonInst()",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0x102);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }

    Rva006FA100Descriptor *descriptor =
        ((Rva006FA100Source *)((char *)pInst->payload))->descriptor;
    for (int i = 0; i < descriptor->count; ++i) {
        if ((descriptor->records[i].mask & mode) != 0) {
            if (!pInst->pParent) {
                g_bfmeAptAssertAtE17734("pInst->pParent",
                    "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0x10B);
                if (g_bfmeAptBreakOnAssertAtDDC01C)
                    __debugbreak();
            }
            AptActionQueueC *queue = *(AptActionQueueC **)((char *)this + 0xA0);
            queue->rva006E4B80(&descriptor->records[i].payload, pInst->pParent, 0x400000,
                *(int *)0x00E17704);
        }
    }

    int routeMask = 0;
    if ((mode & 0x08) != 0) routeMask = 0x800;
    if ((mode & 0x04) != 0) routeMask |= 0x400;
    if ((mode & 0x40) != 0) routeMask |= 0x1000;
    if ((mode & 0x01) != 0) routeMask |= 0x2000;
    if ((mode & 0x02) != 0) routeMask |= 0x4000;
    if ((mode & 0x20) != 0) routeMask |= 0x8000;
    if ((mode & 0x10) != 0) routeMask |= 0x10000;

    if ((pInst->vtableSlot3()->flags & routeMask) != 0) {
        int *route = (int *)0x00DDC89C;
        int *eventCode = (int *)0x00DDC2E8;
        for (; (int)route < 0x00DDC8F0; route += 3, eventCode += 2) {
            if ((route[-1] & routeMask) != 0) {
                EAStringC *key = Rva0070B4F0GetString(route[0]);
                void *lookup = ((BfmeAptValue006DCD20 *)pInst)->rva006E04A0();
                void *found = ((Rva0070B380 *)lookup)->lookup(*key);
                if (found) {
                    int encoded = ((route[1] & 0x7f) << 10) | 5;
                    void *pool = *(void **)0x00E176D0;
                    AptActionQueueC *submit =
                        *(AptActionQueueC **)((char *)pool + 0xA0);
                    submit->rva006E3810((AptValue*)pInst, (AptValue*)found, 0, *eventCode, encoded);
                }
            }
        }
    }

    if (descriptor->audio) {
        switch (mode) {
        case 1:
            if (descriptor->audio[1])
                (*(void (__cdecl **)(void *, int))0x00E17784)(descriptor->audio[1]->handle, 0);
            break;
        case 2:
            if (descriptor->audio[0])
                (*(void (__cdecl **)(void *, int))0x00E17784)(descriptor->audio[0]->handle, 0);
            break;
        case 4:
            if (descriptor->audio[2])
                (*(void (__cdecl **)(void *, int))0x00E17784)(descriptor->audio[2]->handle, 0);
            break;
        case 8:
            if (descriptor->audio[3])
                (*(void (__cdecl **)(void *, int))0x00E17784)(descriptor->audio[3]->handle, 0);
            break;
        }
    }
    ((AptAnimationPoolData *)this)->rva006E6540();
}
