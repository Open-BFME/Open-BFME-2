// ?rva006F99D0@@YAPAVAptCIH@@HPAV1@0@Z
// partial score=0.35 date=2026-10-06
// cl: /O2 /Oy /MD
// 0x006F99D0 is an AptInput focus traversal. Target strings at this boundary
// name AptInput.cpp and AptCIH.h; instructions establish CIH +0x48 parent,
// payload +0x4C/native hash +0x10, and focus-coordinate/key parsing. The
// owner and public method name remain address-derived. The two parser helpers
// use target-observed nonstandard register ABIs, isolated in the wrappers.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" void rva006F97F0Call();
extern "C" void rva006F98C0Call();
extern void *g_00E176D0;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptCIH;
class BfmeAptValue006DCD20
{
public:
    virtual void vtableSlot0();
    int isCIH(bool) const;
    bool isUndefined() const;
    BfmeAptValue006DCD20 *rva006DCF60(bool);
};
class Rva006CFCD0
{
public:
    bool isSpriteInstBase() const;
};
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
class AsciiString;
class AptNativeHash
{
public:
    struct Entry;
    AsciiString *rva0070AA40();
    Entry *rva0070AAA0(Entry *entry);
};
struct Rva006E3710Node;
class Rva006E3710
{
public:
    bool rva006E3710(Rva006E3710Node *candidate);
};
class AptCIH
{
public:
    virtual void vtableSlot0();
    unsigned char _pad04[0x48 - 4];
    AptCIH *parent;
    void *payload;
};

static __forceinline int rva006F99D0Parse(const void *text, int *x, int *y)
{
    int result;
    __asm {
        push x
        mov eax, text
        mov ebx, y
        call rva006F97F0Call
        add esp, 4
        movzx eax, al
        mov result, eax
    }
    return result;
}

static __forceinline float rva006F99D0Distance(int mode, int focusX, int focusY,
                                               int candidateX, int candidateY)
{
    float result;
    __asm {
        mov edx, focusY
        push focusX
        push mode
        mov eax, candidateY
        mov ecx, candidateX
        call rva006F98C0Call
        add esp, 8
        fstp result
    }
    return result;
}

AptCIH *__cdecl rva006F99D0(int mode, AptCIH *current, AptCIH *previous)
{
    if (current == 0)
        return 0;

    int focusX = 0;
    int focusY = 0;
    AptCIH *best = 0;
    float bestDistance = 1.0e9f;
    do
    {
        if (!((Rva006CFCD0 *)current)->isSpriteInstBase()) {
            g_bfmeAptAssertAtE17734("pCIH->isSpriteInstBase()",
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0xA3);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (previous != 0 && !rva006F99D0Parse((char *)previous + 8, &focusY, &focusX)) {
            g_bfmeAptAssertAtE17734("bRet",
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0xAB);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }

        AptNativeHash *hash = *(AptNativeHash **)((char *)current->payload + 0x10);
        void *entry = hash->rva0070AA40();
        while (entry != 0)
        {
            BfmeAptValue006DCD20 *value = *(BfmeAptValue006DCD20 **)((char *)entry + 4);
            if (value->isCIH(false)) {
                AptCIH *candidate = (AptCIH *)value->rva006DCF60(false);
                if (candidate != previous) {
                    if (!((Rva006CFCD0 *)candidate)->isSpriteInstBase()) {
                        if (candidate == 0) {
                            g_bfmeAptAssertAtE17734("this",
                                "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
                            if (g_bfmeAptBreakOnAssertAtDDC01C)
                                __debugbreak();
                        }
                        if (((Rva006DBB30SarDwordField *)candidate)->get() != 0xE
                            || ((BfmeAptValue006DCD20 *)candidate)->isUndefined())
                            goto next_entry;
                    }

                    int candidateX;
                    int candidateY;
                    if (!rva006F99D0Parse(entry, &candidateY, &candidateX))
                        goto next_entry;
                    if (((Rva006E3710 *)g_00E176D0)->rva006E3710((Rva006E3710Node *)candidate))
                        goto next_entry;
                    if (previous == 0) {
                        best = candidate;
                        goto next_entry;
                    }
                    if (focusX == candidateX && focusY == candidateY) {
                        g_bfmeAptAssertAtE17734("nFocusX != nX || nFocusY != nY",
                            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0xC3);
                        if (g_bfmeAptBreakOnAssertAtDDC01C)
                            __debugbreak();
                    }
                    float distance = rva006F99D0Distance(mode, focusX, focusY,
                                                         candidateX, candidateY);
                    if (distance < bestDistance) {
                        bestDistance = distance;
                        best = candidate;
                    }
                }
            }
        next_entry:
            entry = hash->rva0070AAA0((AptNativeHash::Entry *)entry);
        }

        if (best != 0) {
            if (((Rva006DBB30SarDwordField *)best)->get() != 0xD
                || ((BfmeAptValue006DCD20 *)best)->isUndefined())
                return best;
            previous = 0;
            current = best;
        } else {
            previous = current;
            current = current->parent;
        }
    } while (current != 0);
    return 0;
}
