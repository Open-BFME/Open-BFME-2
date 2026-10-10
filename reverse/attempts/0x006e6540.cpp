// ?rva006E6540@AptAnimationPoolData@@QAEXXZ
// partial score=0.9825904761904762 date=2026-10-10
// cl: /O2 /MD /EHs-c-
// Native6E6540..6E6A2C (1260B incl. cold backedge), RET0: queue+20, 24-byte actions, root queueA0.
// Bank: raw1258/374ops versus retail1260/375ops; four q/end spill homes,
// packed-event shift scheduling, Push setup order and validator bindings remain.
// _AptValidate label comes from the retail assertion; its 3B true body folds at
//1826C0 under existing codecvt owners, so this declaration is not a verified name pin.
// Rva006FA020 thiscall receiver is a call-site inference; current owned224B
// source remains cdecl and must be reconciled before any recovery. Field48 is
// an accessed interpreter-prefix word, not a proven constant-pool member.
// The action/function labels and assertions identify AptAnimation dispatch;
// matched root constructor/dtor and queue members constrain the prefix views.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#define ACHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define HCHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define PCHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define QCHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
class AptValue { public:virtual void AddRef();virtual void Release();};
class BfmeAptValue006DCD20 { public:bool isUndefined() const;};
class Rva006DBB30SarDwordField { public:int get()const;};
class Rva006CFCD0 {public:bool isSpriteInstBase()const;};
struct AptCharacterInst {char unknown[0x18];int frame;};
class AptCIH {public:virtual void AddRef();virtual void Release();char unknown4[0x4c-4];AptCharacterInst*inst;const AptCIH*rva006E0CB0()const;
 AptCharacterInst*Sprite(){HCHECK(((Rva006CFCD0*)this)->isSpriteInstBase(),0x7d,"isSpriteInstBase()");return inst;}
 bool isUndefined()const{return ((const BfmeAptValue006DCD20*)this)->isUndefined();}
 int type()const{HCHECK(this,0xd8,"this");return ((const Rva006DBB30SarDwordField*)this)->get();}
};
class Rva006CD650 {public:void*rva006CD650();};
struct AptActionSetup {AptValue*context,*value;const char*name;int action;};
class AptBasePtrStack {public:int count,capacity;BfmeAptValue006DCD20**elements;void Push(BfmeAptValue006DCD20*);void rva006FE920();
 void pop(){if(count<=0){g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h",0x98);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
 else{((AptValue*)elements[count-1])->Release();--count;}}
};
struct AptContextStack {int count,capacity;AptValue**elements;
 void push(AptValue*p){PCHECK(count<capacity,0x76,"m_nElements < m_nSize");elements[count++]=p;p->AddRef();}
 void pop(){PCHECK(count>0,0x7d,"size() > 0");elements[count-1]->Release();--count;}
};
struct AptActionInterpreter {AptBasePtrStack stack;char unknownC[0x24-12];AptContextStack scope;void*currentFunction;int debugCallCount;char unknown38[0x48-0x38];unsigned dispatchWord;
 void*PrepareForExecution(AptActionSetup*);void CleanupAfterExecution(void*,AptActionSetup*);void callFunction(AptValue*,AptValue*,int);
 const unsigned char*runStream(const unsigned char*,AptCIH*,int,AptCharacterInst*);
};
extern AptActionInterpreter g_aptDateInterpreter;

class AptInteger {public:static AptValue*Create(int);};
class Rva006E34D0 {public:char unknown[0x68];AptValue*value68;};
extern Rva006E34D0*g_bfmeAptPtrAtE176D0;
struct Rva006E3230Action {int type,flags,event;union{int frame;AptValue*context;};union{const unsigned char**stream;AptValue*function;};union{AptCIH*target;int nArgs;};};
class AptActionQueueC {public:Rva006E3230Action*pool,*current,*end,*executing;int capacity;void rva006E3230(Rva006E3230Action*);void ClearActions();};
class Rva006FA020 {public:bool rva006FA020();};
bool _AptValidate();
class AptAnimationPoolData {public:char unknown[0xa0];AptActionQueueC*queue;void _tickNewInsts();void rva006E6540();};
void AptAnimationPoolData::rva006E6540(){
 AptActionQueueC*q=queue;q->rva006E3230(q->current);
 Rva006E3230Action*p=q->current;
 if(p!=q->end){
  do{
   _ReadWriteBarrier(); Rva006E3230Action*oldEnd=q->end;q->executing=p;
   if(p->type==1){
    g_aptDateInterpreter.dispatchWord=p->event;
    if(!p->target->isUndefined()){
    AptCIH*target=p->target;
    if((target->type()!=0x13 || target->isUndefined()) && p->target->Sprite()){
     if(p->frame>=0 || -p->frame==p->target->Sprite()->frame){
      AptActionSetup setup={(AptValue*)p->target,0,"AptRun-Actions",p->flags};
      void*saved=g_aptDateInterpreter.PrepareForExecution(&setup);
      void*character=p->target?((Rva006CD650*)p->target->rva006E0CB0())->rva006CD650():0;
      g_aptDateInterpreter.runStream(*p->stream,p->target,-1,(AptCharacterInst*)character);
      g_aptDateInterpreter.CleanupAfterExecution(saved,&setup);
      ACHECK(_AptValidate(),0x3ac,"_AptValidate()");
      _tickNewInsts();
     }
    }
    }
   }else if(p->type==2){
    g_aptDateInterpreter.dispatchWord=p->event;
    g_aptDateInterpreter.scope.push(p->context);
    AptActionSetup setup={p->context,p->function,"AptRun-Functions",p->flags};
    void*saved=g_aptDateInterpreter.PrepareForExecution(&setup);
    if(p->event && (p->event&3)==1 && (p->event&0x3fc)==4){
     unsigned flags=((unsigned)p->event>>10)&0x7f;int key=(int)((unsigned)p->event>>17);
     if(p->nArgs>0 && (flags&7)){
      if(p->nArgs>1)g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20*)g_bfmeAptPtrAtE176D0->value68);
      if(flags==4)key=-key;
      g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20*)AptInteger::Create(key));
     }
    }
    g_aptDateInterpreter.callFunction(p->context,p->function,p->nArgs);
    g_aptDateInterpreter.CleanupAfterExecution(saved,&setup);
    g_aptDateInterpreter.scope.pop();g_aptDateInterpreter.stack.pop();
   }else ACHECK(false,0x3ea,"NOT_REACHED");
   if(g_aptDateInterpreter.stack.count>0){g_aptDateInterpreter.stack.rva006FE920();ACHECK(g_aptDateInterpreter.stack.count==0,0x3f0,"gAptActionInterpreter.stack.GetSize() == 0");}
   ACHECK(g_aptDateInterpreter.debugCallCount==0,0x3f3,"gAptActionInterpreter.debugCallStack.GetSize() == 0");
   if(oldEnd>q->end)p+=oldEnd-q->end;
   if(++p==q->pool+q->capacity)p=q->pool;
   QCHECK(p>=q->pool,0x4e0,"pCur >= &m_aActionPool[0]");QCHECK(p<q->pool+q->capacity,0x4e1,"pCur < &m_aActionPool[ m_iActionPoolSize ]");
  }while(p!=q->end);
 }
 ACHECK(((Rva006FA020*)this)->rva006FA020(),0x3ff,"validateBIL()");_tickNewInsts();q->ClearActions();
}
