// cl: /O2 /MD /EHs-c-
// AptAnimation.cpp: AptAnimationPoolData's queued-action run.
// ?rva006E6540@AptAnimationPoolData@@QAEXXZ @0x006E6540 1260B (RET0; the
// extent includes the cold back edge at 0x006E6A27 Ghidra's 1255B boundary
// omits). For each 24-byte action of the root queue (+0xA0) it runs a
// sprite's action stream ("AptRun-Actions", type 1) or calls a function with
// its scope pushed ("AptRun-Functions", type 2), then checks the interpreter
// stacks, steps back when the queue shrank under it, wraps at the pool end,
// and finally validates the BIL, ticks new instances and clears the queue.
// Target evidence: retail assertion strings and lines (AptAnimation.cpp
// 0x3AC 0x3EA 0x3F0 0x3F3 0x3FF; _Apt.h 0x4E0 0x4E1; AptCIH.h 0x7D 0xD8;
// _AptValuePtrStack.h 0x76 0x7D; _AptBasePtrStack.h 0x98) and rowed callees.
// WorldBuilder 0x1758910 (AptAnimation.cpp, asserts 940..1023) gives the
// loop shape: queue accessors begin / isEnd / getEnd / setExecuting / next,
// next wrapping at the pool end and checking the cursor (_Apt.h 0x4E0/0x4E1),
// oldEnd > getEnd() stepping back by oldEnd - getEnd().
// Callees: validateBIL is a thiscall member of the pool at 0x006FA020 (retail
// loads ECX = this before the call; WB 0x179A5A0 in AptInput.cpp moves ECX
// too); _AptValidate is Apt.cpp's 3-byte return-true body, ICF-folded at
// 0x001826C0 (WB 0x174DF60 sits between Apt.cpp functions).
// Must build at /O2 without /arch:SSE (the region default emits cmov).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#define ACHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define HCHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define PCHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define QCHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}

class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
};
class BfmeAptValue006DCD20 {
public:
    bool isUndefined() const;
};
class Rva006DBB30SarDwordField {
public:
    int get() const;
};
class Rva006CFCD0 {
public:
    bool isSpriteInstBase() const;
};
struct AptCharacterInst {
    char unknown[0x18];
    int frame;
};
class AptCIH {
public:
    virtual void AddRef();
    virtual void Release();
    char unknown4[0x4c - 4];
    AptCharacterInst *inst;
    const AptCIH *rva006E0CB0() const;
    AptCharacterInst *Sprite() { HCHECK(((Rva006CFCD0 *)this)->isSpriteInstBase(), 0x7d, "isSpriteInstBase()"); return inst; }
    bool isUndefined() const { return ((const BfmeAptValue006DCD20 *)this)->isUndefined(); }
    int type() const { HCHECK(this, 0xd8, "this"); return ((const Rva006DBB30SarDwordField *)this)->get(); }
};
class Rva006CD650 {
public:
    void *rva006CD650();
};
struct AptActionSetup {
    AptValue *context, *value;
    const char *name;
    int action;
};
class AptBasePtrStack {
public:
    int count, capacity;
    BfmeAptValue006DCD20 **elements;
    void Push(BfmeAptValue006DCD20 *);
    void rva006FE920();
    void pop()
    {
        if (count <= 0) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x98);
            if (g_bfmeAptBreakOnAssertAtDDC01C) {__asm int 3}
        } else {
            ((AptValue *)elements[count - 1])->Release();
            --count;
        }
    }
};
struct AptContextStack {
    int count, capacity;
    AptValue **elements;
    void push(AptValue *p) { PCHECK(count < capacity, 0x76, "m_nElements < m_nSize"); elements[count++] = p; p->AddRef(); }
    void pop() { PCHECK(count > 0, 0x7d, "size() > 0"); elements[count - 1]->Release(); --count; }
};
struct AptActionInterpreter {
    AptBasePtrStack stack;
    char unknownC[0x24 - 12];
    AptContextStack scope;
    void *currentFunction;
    int debugCallCount;
    char unknown38[0x48 - 0x38];
    unsigned dispatchWord;
    void *PrepareForExecution(AptActionSetup *);
    void CleanupAfterExecution(void *, AptActionSetup *);
    void callFunction(AptValue *, AptValue *, int);
    const unsigned char *runStream(const unsigned char *, AptCIH *, int, AptCharacterInst *);
};
extern AptActionInterpreter g_aptDateInterpreter;

class AptInteger {
public:
    static AptValue *Create(int);
};
class Rva006E34D0 {
public:
    char unknown[0x68];
    AptValue *value68;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

struct Rva006E3230Action {
    int type, flags, event;
    union { int frame; AptValue *context; };
    union { const unsigned char **stream; AptValue *function; };
    union { AptCIH *target; int nArgs; };
};
class AptActionQueueC {
public:
    Rva006E3230Action *pool, *current, *end, *executing;
    int capacity;
    // rva006E3230 is the out-of-line copy of the cursor check (_Apt.h
    // 0x4E0/0x4E1) that next() expands inline.
    void rva006E3230(Rva006E3230Action *);
    void ClearActions();
    Rva006E3230Action *begin() { rva006E3230(current); return current; }
    bool isEnd(Rva006E3230Action *p) { return p == end; }
    Rva006E3230Action *getEnd() { return end; }
    void setExecuting(Rva006E3230Action *p) { executing = p; }
    void checkCur(Rva006E3230Action *pCur)
    {
        QCHECK(pCur >= pool, 0x4e0, "pCur >= &m_aActionPool[0]");
        QCHECK(pCur < pool + capacity, 0x4e1, "pCur < &m_aActionPool[ m_iActionPoolSize ]");
    }
    Rva006E3230Action *next(Rva006E3230Action *p)
    {
        Rva006E3230Action *n = p + 1;
        if (n == pool + capacity)
            n = pool;
        checkCur(n);
        return n;
    }
};

bool _AptValidate();

class AptAnimationPoolData {
public:
    char unknown[0xa0];
    AptActionQueueC *queue;
    void _tickNewInsts();
    bool validateBIL();
    void rva006E6540();
};

void AptAnimationPoolData::rva006E6540()
{
    AptActionQueueC *q = queue;
    Rva006E3230Action *p = q->begin();
    while (!q->isEnd(p)) {
        Rva006E3230Action *oldEnd = q->getEnd();
        q->setExecuting(p);
        if (p->type == 1) {
            g_aptDateInterpreter.dispatchWord = p->event;
            if (!p->target->isUndefined()) {
                AptCIH *target = p->target;
                if ((target->type() != 0x13 || target->isUndefined()) && p->target->Sprite()) {
                    if (p->frame >= 0 || -p->frame == p->target->Sprite()->frame) {
                        AptActionSetup setup = {(AptValue *)p->target, 0, "AptRun-Actions", p->flags};
                        void *saved = g_aptDateInterpreter.PrepareForExecution(&setup);
                        void *character = p->target ? ((Rva006CD650 *)p->target->rva006E0CB0())->rva006CD650() : 0;
                        g_aptDateInterpreter.runStream(*p->stream, p->target, -1, (AptCharacterInst *)character);
                        g_aptDateInterpreter.CleanupAfterExecution(saved, &setup);
                        ACHECK(_AptValidate(), 0x3ac, "_AptValidate()");
                        _tickNewInsts();
                    }
                }
            }
        } else if (p->type == 2) {
            g_aptDateInterpreter.dispatchWord = p->event;
            g_aptDateInterpreter.scope.push(p->context);
            AptActionSetup setup = {p->context, p->function, "AptRun-Functions", p->flags};
            void *saved = g_aptDateInterpreter.PrepareForExecution(&setup);
            if (p->event && (p->event & 3) == 1 && (p->event & 0x3fc) == 4) {
                int key = (int)((unsigned)p->event >> 17);
                unsigned flags = ((unsigned)p->event >> 10) & 0x7f;
                if (p->nArgs > 0 && (flags & 7)) {
                    if (p->nArgs > 1)
                        g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20 *)g_bfmeAptPtrAtE176D0->value68);
                    if (flags == 4)
                        g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20 *)AptInteger::Create(-key));
                    else
                        g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20 *)AptInteger::Create(key));
                }
            }
            g_aptDateInterpreter.callFunction(p->context, p->function, p->nArgs);
            g_aptDateInterpreter.CleanupAfterExecution(saved, &setup);
            g_aptDateInterpreter.scope.pop();
            g_aptDateInterpreter.stack.pop();
        } else
            ACHECK(0, 0x3ea, "0");
        if (g_aptDateInterpreter.stack.count > 0) {
            g_aptDateInterpreter.stack.rva006FE920();
            ACHECK(g_aptDateInterpreter.stack.count == 0, 0x3f0, "gAptActionInterpreter.stack.GetSize() == 0");
        }
        ACHECK(g_aptDateInterpreter.debugCallCount == 0, 0x3f3, "gAptActionInterpreter.debugCallStack.GetSize() == 0");
        if (oldEnd > q->getEnd())
            p -= oldEnd - q->getEnd();
        p = q->next(p);
    }
    ACHECK(validateBIL(), 0x3ff, "validateBIL()");
    _tickNewInsts();
    q->ClearActions();
}
