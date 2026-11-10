// cl: /O2 /MD /EHsc
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

#include "AptValue.h"
#include "../../../GameEngine/Include/Common/AptInteger.h"
#include "BfmeAptValue006DCD20.h"
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"
class Rva006CFCD0 {
public:
    bool isSpriteInstBase() const;
};
struct AptCharacterInst {
    char unknown[0xc];
    void *unknown0C;
    char unknown10[0x18 - 0x10];
    int frame;
};
class AptCIH {
public:
    virtual void AddRef();
    virtual void Release();
    char unknown4[0x4c - 4];
    AptCharacterInst *inst;
    const AptCIH *rva006E0CB0() const;
    void *rva006E1170() const;
    AptCharacterInst *CharacterInst() const { HCHECK((unsigned char)((const BfmeAptValue006DCD20 *)this)->isCharacterInst(), 0xa5, "isCharacterInst()"); return inst; }
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
    void rva006E3AA0(int);
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
    void push(AptValue *aptValue) { PCHECK(count < capacity, 0x76, "m_nElements < m_nSize"); elements[count++] = aptValue; aptValue->AddRef(); }
    void pop() { PCHECK(count > 0, 0x7d, "size() > 0"); elements[count - 1]->Release(); --count; }
};
struct AptActionInterpreter {
    AptBasePtrStack stack;
    char unknownC[0x24 - 12];
    AptContextStack scope;
    void *currentFunction;
    int debugCallCount;
    char unknown38[0x48 - 0x38];
    void *PrepareForExecution(AptActionSetup *);
    void CleanupAfterExecution(void *, AptActionSetup *);
    void callFunction(AptValue *, AptValue *, int);
    const unsigned char *runStream(const unsigned char *, AptCIH *, int, AptCharacterInst *);
};
extern AptActionInterpreter g_aptDateInterpreter;
// The event word being dispatched (retail VA 0x00E18328, right after the
// interpreter's 72 bytes); AptKey decodes it (key >> 17, controller >> 2).
extern unsigned int Rva008A5250LastKey;

class Rva006E34D0 {
public:
    char unknown[0x68];
    AptValue *value68;
    char unknown6C[0xa8 - 0x6c];
    int maxIntervalTimers;
    int getMaxIntervalTimers() const { return maxIntervalTimers; }
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

extern AptValue *gpUndefinedValue;

struct AptIntervalTimerParams {
    int m_nElements, m_nCapacity;
    AptValue **m_aElements;
    int size() const { return m_nElements; }
    AptValue *peek(int nPos) const
    {
        PCHECK(m_nElements - nPos > 0, 0x89, "m_nElements - nPos > 0");
        return m_aElements[m_nElements - nPos - 1];
    }
};
struct AptScriptFunctionView {
    char unknown[0x20];
    BfmeAptValue006DCD20 *scope;
};
struct AptScriptFunctionOwnerView {
    char unknown[0x20];
    AptCIH *owner;
};
struct AptIntervalTimer {
    int active;
    BfmeAptValue006DCD20 *func;
    float interval;
    float remaining;
    AptValue *target;
    AptIntervalTimerParams params;
    void cleanParams();
};

// ?rva006E5050@Rva006E58D0@@QAEXPAX00@Z @0x006E5050 2123B (RET0C) plus its
// 12-entry switch jump table at 0x006E589C (extent 2172B): the loaded
// animation's offset fixup. Target evidence: retail AptAnimation.cpp asserts
// 0x28..0xb3 and WorldBuilder 0x1755AC0 (same file) give the field order,
// the per-type switch (shape/text/font/button/sprite/sound/bitmap/movie/
// static text) and the import lookup through the 0x00A176CC list at
// 0x006D0B40; sprite and movie characters forward to 0x0070E900 and button
// action streams to 0x006FD060. The receiver and record views are local
// data-format views, not a claimed donor layout. The import key temp needs
// /EHsc. With the canonical scalar headers, define the fixup after the pool
// members to preserve the character-loop pBase/pConstantFile load order.
#define AOFFSET(field) if(field)(unsigned &)(field)+=(unsigned)pBase
extern void *g_aptLoadRenderingUnitSlot;
extern void *g_aptLoadSoundSlot;
extern void *g_aptLoadTextureSlot;
typedef int (__cdecl *AptLoadIdFn)(void *,int);
typedef int (__cdecl *AptLoadSoundFn)(void *,int,const char *);
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
class Rva00894D80Accessor {public:static unsigned increment(unsigned *);};
#include "EAStringC.h"
class Rva006D07E0Key {
public:
 void *m_object;
 ~Rva006D07E0Key() {if(m_object && Rva006CFDF0DecRef((int *)m_object)==0)bfmeDropVGO(m_object);}
 Rva006D07E0Key &operator=(const Rva006D07E0Key &other) {
  if(&other!=this) {
   if(m_object && Rva006CFDF0DecRef((int *)m_object)==0)bfmeDropVGO(m_object);
   m_object=other.m_object;
   if(m_object)Rva00894D80Accessor::increment((unsigned *)m_object);
  }
  return *this;
 }
};
class Rva006D0A30List {public:Rva006D07E0Key rva006D0B40(const EAStringC &);};
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
void Rva006FD060Forward(void *,void *,void *,void *);
class Rva0070E900 {int nFrames;void *aFrames;void *phLabels;public:void rva0070E900(void *,void *,void *);};
struct AptExport {char *szName;int zID;};
struct AptImport {char *szFile;char *szName;int unknown;Rva006D07E0Key movie;};
struct AptActionCondition {unsigned flags;struct {void *aActionStream;} actions;};
struct AptStaticTextRecord {char pad[0x34];void *aGlyphs;};
struct AptCharacter {
 int type;
 AptCharacter *pParentAnim;
 union {
  struct {char pad[0x10];int zID;} shape;
  struct {char pad[0x2c];char *szInitialText;char *szVariable;} text;
  struct {char *szName;int pad;void *apGlyphs;} font;
  struct {char pad[0x1c];void *mHitTestVertexTable;void *mHitTestIndexTable;int pad2;void *aButtonRecords;int nActionConditions;AptActionCondition *aActionConditions;void *pButtonSound;} button;
  Rva0070E900 sprite;
  struct {int zID;} sound;
  struct {int zID;} bitmap;
  Rva0070E900 movie;
  struct {char pad[0x28];int nRecords;AptStaticTextRecord *aRecords;} statictext;
 };
};
class Rva006E58D0 {
 char pad0[0xc];
 int nCharacters;
 AptCharacter **apCharacters;
 char pad14[0xc];
 int nImports;
 AptImport *aImports;
 int nExports;
 AptExport *aExports;
 int m_field30;
public:
 void rva006E5050(void *pBase,void *pConstantFile,void *pLoadContext);
};
class AptAnimationPoolData {
public:
    char unknown[0x34];
    AptIntervalTimer *timers;
    int activeTimers;
    char unknown3C[0xa0 - 0x3c];
    AptActionQueueC *queue;
    void tickIntervalTimers(int);
    void removeTimerFunctions(AptCIH *);
    void _tickNewInsts();
    bool validateBIL();
    void rva006E6540();
};

void AptAnimationPoolData::rva006E6540()
{
    AptActionQueueC *aptActionQueueC = queue;
    Rva006E3230Action *p = aptActionQueueC->begin();
    while (!aptActionQueueC->isEnd(p)) {
        Rva006E3230Action *oldEnd = aptActionQueueC->getEnd();
        aptActionQueueC->setExecuting(p);
        if (p->type == 1) {
            Rva008A5250LastKey = p->event;
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
            Rva008A5250LastKey = p->event;
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
        if (oldEnd > aptActionQueueC->getEnd())
            p -= oldEnd - aptActionQueueC->getEnd();
        p = aptActionQueueC->next(p);
    }
    ACHECK(validateBIL(), 0x3ff, "validateBIL()");
    _tickNewInsts();
    aptActionQueueC->ClearActions();
}

// ?tickIntervalTimers@AptAnimationPoolData@@QAEXH@Z @0x006E4150 562B (RET4).
// WorldBuilder 0x17582E0 names it (AptAnimation.cpp, asserts 852..863) and
// gives the loop shape; retail keeps only the 0x354 stack-size assertion.
// Target: 32-byte timers at +0x34, active count +0x38, the limit read through
// E176D0+0xA8 every iteration, the timer's parameter stack at +0x14 peeked
// from the top (_AptValuePtrStack.h 0x89), the script scope at +0x20 of the
// checked cast (WB's debug layout has +0x24).
void AptAnimationPoolData::tickIntervalTimers(int interval)
{
    int left = activeTimers;
    for (int i = 0; i < g_bfmeAptPtrAtE176D0->getMaxIntervalTimers(); i++) {
        if (!timers[i].active)
            continue;
        timers[i].remaining -= interval;
        if (timers[i].remaining < 0.0f) {
            BfmeAptValue006DCD20 *func = timers[i].func;
            BfmeAptValue006DCD20 *scope = (unsigned char)func->isScriptFunction() ? ((AptScriptFunctionView *)func->rva006DCEE0())->scope : 0;
            if (func && ((unsigned char)func->isNativeFunction() || scope && !scope->isUndefined() && !(unsigned char)scope->rva006E03A0())) {
                AptValue *target = timers[i].target != gpUndefinedValue ? timers[i].target : (AptValue *)scope;
                int nParams = timers[i].params.size();
                AptActionSetup setup;
                setup.context = target;
                setup.value = (AptValue *)func;
                setup.name = "AptTimerFunc";
                setup.action = 0x80000;
                void *saved = g_aptDateInterpreter.PrepareForExecution(&setup);
                for (int j = 0; j < nParams; j++)
                    g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20 *)timers[i].params.peek(j));
                g_aptDateInterpreter.callFunction(target, (AptValue *)func, nParams);
                g_aptDateInterpreter.CleanupAfterExecution(saved, &setup);
                ACHECK(g_aptDateInterpreter.stack.count == 1, 0x354, "gAptActionInterpreter.stack.GetSize() == 1");
                g_aptDateInterpreter.stack.rva006E3AA0(g_aptDateInterpreter.stack.count);
                timers[i].remaining += timers[i].interval;
            } else {
                ((AptValue *)timers[i].func)->Release();
                timers[i].cleanParams();
                timers[i].active = 0;
                activeTimers--;
            }
        }
        if (--left == 0)
            break;
    }
}

// ?removeTimerFunctions@AptAnimationPoolData@@QAEXPAVAptCIH@@@Z @0x006E44F0
// 276B (RET4). WorldBuilder 0x17590C0 names it (AptAnimation.cpp 0x4AC):
// releases every live script-function timer whose owner has no character
// instance or shares the given instance's +0x0C root. The first character
// instance read expands inline (AptCIH.h 0xA5); later ones call 0x006E1170.
void AptAnimationPoolData::removeTimerFunctions(AptCIH *cih)
{
    int left = activeTimers;
    if (left == 0)
        return;
    for (int i = 0; i < g_bfmeAptPtrAtE176D0->getMaxIntervalTimers(); i++) {
        if (!timers[i].active)
            continue;
        if (cih->CharacterInst() && (unsigned char)timers[i].func->isScriptFunction()) {
            if (!((AptScriptFunctionOwnerView *)timers[i].func->rva006DCEE0())->owner->inst || ((AptCharacterInst *)((AptScriptFunctionOwnerView *)timers[i].func->rva006DCEE0())->owner->rva006E1170())->unknown0C == ((AptCharacterInst *)cih->rva006E1170())->unknown0C) {
                ((AptValue *)timers[i].func)->Release();
                timers[i].cleanParams();
                timers[i].active = 0;
                activeTimers--;
            }
        }
        if (--left == 0)
            break;
    }
}

void Rva006E58D0::rva006E5050(void *pBase,void *pConstantFile,void *pLoadContext)
{
 ACHECK((unsigned)apCharacters < 0xfffff,0x28,"(unsigned)apCharacters < 0xfffff");
 AOFFSET(apCharacters);
 ACHECK((unsigned)aExports < 0xfffff,0x2c,"(unsigned)aExports < 0xfffff");
 AOFFSET(aExports);
 int i;
 for(i=0;i<nExports;i++) {
  ACHECK((unsigned)aExports[i].szName < 0xfffff,0x2f,"(unsigned)aExports[i].szName < 0xfffff");
  AOFFSET(aExports[i].szName);
 }
 for(i=0;i<nCharacters;i++) {
  ACHECK((unsigned)apCharacters[i] < 0xfffff,0x35,"(unsigned)apCharacters[i] < 0xfffff");
  AOFFSET(apCharacters[i]);
  if(apCharacters[i]) {
   ACHECK((unsigned int)apCharacters[i]->pParentAnim == 0x09876543,0x38,"(unsigned int)apCharacters[i]->pParentAnim == 0x09876543");
   apCharacters[i]->pParentAnim=apCharacters[0];
   switch(apCharacters[i]->type) {
   case 1:
    ACHECK((int)apCharacters[i]->shape.zID == i,0x3f,"(int)apCharacters[i]->shape.zID == i");
    apCharacters[i]->shape.zID=((AptLoadIdFn)g_aptLoadRenderingUnitSlot)(pLoadContext,i);
    break;
   case 2:
    ACHECK((unsigned)apCharacters[i]->text.szInitialText < 0xfffff,0x45,"(unsigned)apCharacters[i]->text.szInitialText < 0xfffff");
    AOFFSET(apCharacters[i]->text.szInitialText);
    ACHECK((unsigned)apCharacters[i]->text.szVariable < 0xfffff,0x46,"(unsigned)apCharacters[i]->text.szVariable < 0xfffff");
    AOFFSET(apCharacters[i]->text.szVariable);
    break;
   case 3:
    ACHECK((unsigned)apCharacters[i]->font.szName < 0xfffff,0x4b,"(unsigned)apCharacters[i]->font.szName < 0xfffff");
    AOFFSET(apCharacters[i]->font.szName);
    ACHECK((unsigned)apCharacters[i]->font.apGlyphs < 0xfffff,0x4c,"(unsigned)apCharacters[i]->font.apGlyphs < 0xfffff");
    AOFFSET(apCharacters[i]->font.apGlyphs);
    break;
   case 4:
    {
    ACHECK((unsigned)apCharacters[i]->button.mHitTestVertexTable < 0xfffff,0x54,"(unsigned)apCharacters[i]->button.mHitTestVertexTable < 0xfffff");
    AOFFSET(apCharacters[i]->button.mHitTestVertexTable);
    ACHECK((unsigned)apCharacters[i]->button.mHitTestIndexTable < 0xfffff,0x55,"(unsigned)apCharacters[i]->button.mHitTestIndexTable < 0xfffff");
    AOFFSET(apCharacters[i]->button.mHitTestIndexTable);
    ACHECK((unsigned)apCharacters[i]->button.aButtonRecords < 0xfffff,0x57,"(unsigned)apCharacters[i]->button.aButtonRecords < 0xfffff");
    AOFFSET(apCharacters[i]->button.aButtonRecords);
    ACHECK((unsigned)apCharacters[i]->button.aActionConditions < 0xfffff,0x58,"(unsigned)apCharacters[i]->button.aActionConditions < 0xfffff");
    AOFFSET(apCharacters[i]->button.aActionConditions);
    for(int j=0;j<apCharacters[i]->button.nActionConditions;j++) {
     ACHECK((unsigned)apCharacters[i]->button.aActionConditions[j].actions.aActionStream < 0xfffff,0x5b,"(unsigned)apCharacters[i]->button.aActionConditions[j].actions.aActionStream < 0xfffff");
     AOFFSET(apCharacters[i]->button.aActionConditions[j].actions.aActionStream);
     Rva006FD060Forward(apCharacters[i]->button.aActionConditions[j].actions.aActionStream,pBase,pConstantFile,&m_field30);
    }
    ACHECK((unsigned)apCharacters[i]->button.pButtonSound < 0xfffff,0x5e,"(unsigned)apCharacters[i]->button.pButtonSound < 0xfffff");
    AOFFSET(apCharacters[i]->button.pButtonSound);
    }
    break;
   case 5:
    apCharacters[i]->sprite.rva0070E900(pBase,pConstantFile,&m_field30);
    break;
   case 6:
    {
    const char *szName=0;
    ACHECK((int)apCharacters[i]->sound.zID == i,0x6f,"(int)apCharacters[i]->sound.zID == i");
    for(int j=0;j<nExports;j++)
     if(aExports[j].zID==i)
      szName=aExports[j].szName;
    apCharacters[i]->sound.zID=((AptLoadSoundFn)g_aptLoadSoundSlot)(pLoadContext,i,szName);
    }
    break;
   case 7:
    ACHECK((int)apCharacters[i]->bitmap.zID == i,0x8c,"(int)apCharacters[i]->bitmap.zID == i");
    apCharacters[i]->bitmap.zID=((AptLoadIdFn)g_aptLoadTextureSlot)(pLoadContext,i);
    break;
   case 8:
    break;
   case 9:
    apCharacters[i]->movie.rva0070E900(pBase,pConstantFile,&m_field30);
    ACHECK(i == 0,0x97,"i == 0");
    break;
   case 10:
    ACHECK((unsigned)apCharacters[i]->statictext.aRecords < 0xfffff,0x9e,"(unsigned)apCharacters[i]->statictext.aRecords < 0xfffff");
    AOFFSET(apCharacters[i]->statictext.aRecords);
    for(int j=0;j<apCharacters[i]->statictext.nRecords;j++) {
     ACHECK((unsigned)apCharacters[i]->statictext.aRecords[j].aGlyphs < 0xfffff,0xa1,"(unsigned)apCharacters[i]->statictext.aRecords[j].aGlyphs < 0xfffff");
     AOFFSET(apCharacters[i]->statictext.aRecords[j].aGlyphs);
    }
    break;
   case 12:
    break;
   default:
    ACHECK(0,0xa9,"NOT_REACHED");
    break;
   }
  }
 }
 ACHECK((unsigned)aImports < 0xfffff,0xaf,"(unsigned)aImports < 0xfffff");
 AOFFSET(aImports);
 for(i=0;i<nImports;i++) {
  ACHECK((unsigned)aImports[i].szFile < 0xfffff,0xb2,"(unsigned)aImports[i].szFile < 0xfffff");
  AOFFSET(aImports[i].szFile);
  ACHECK((unsigned)aImports[i].szName < 0xfffff,0xb3,"(unsigned)aImports[i].szName < 0xfffff");
  AOFFSET(aImports[i].szName);
  aImports[i].movie=((Rva006D0A30List *)g_rva00893030Manager)->rva006D0B40(EAStringC(aImports[i].szFile));
 }
}
