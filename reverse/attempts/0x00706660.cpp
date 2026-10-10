// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// partial score=0.9568449696701077 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// partial score=0.949378714 date=2026-10-10
// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// partial score=0.926 date=2026-10-06
// cl: /O2 /MD /EHsc /ICode/Libraries/Source/Apt/AptObject
#include "AptScriptFunction.h"
class BfmeAptValue006DCD20 { public: int isNativeFunction() const; int isScriptFunction() const; bool isUndefined() const;int rva006E03A0() const; BfmeAptValue006DCD20 *rva006DCF20(); BfmeAptValue006DCD20 *rva006DCEE0(); };
class Rva006CD650{public:void*rva006CD650();};
struct NativeFunctionView { char opaque[0x20]; AptValue *(__cdecl *function)(AptValue *,int); };
class AptCIH : public AptValue { char opaque[0x5c-8]; public: unsigned int state; const AptCIH *rva006E0CB0() const; };
extern AptValue *gpUndefinedValue;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptBasePtrStack { public: int count,capacity; AptValue **items; BfmeAptValue006DCD20 *At(int); void rva006E3AA0(int); void PopAndPush(int,BfmeAptValue006DCD20 *); void rva006FDF30(BfmeAptValue006DCD20*);void PushNoInc(AptValue *v) {if(count>=capacity){g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h",0x90);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}items[count++]=v;} };
template<class T>struct AptValuePtrStack { int count,capacity; AptValue **items; void push(AptValue *); void pop(){if(count<=0){g_bfmeAptAssertAtE17734("size() > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}items[count-1]->Release();--count;} };
struct AptActionInterpreter {
 AptBasePtrStack stack; char pad[0x24-12]; AptValuePtrStack<AptValue> thisStack; AptScriptFunctionBase *mpCurrentFunction; char debug[12]; AptConstantPool constantPool; char pad2[0x60-0x48]; int unwind;
 const unsigned char *runStream(const unsigned char *,AptCIH *,int,struct AptCharacterInst*);
 void callFunction(AptValue *,AptValue *,int);
};
void AptActionInterpreter::callFunction(AptValue *context,AptValue *function,int nParams) {
 int before=stack.count-nParams;function=*(AptValue*volatile*)&function;
 if(function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isNativeFunction()) {
  AptConstantPool old=constantPool;
  NativeFunctionView *fn=(NativeFunctionView *)((BfmeAptValue006DCD20 *)function)->rva006DCF20();
  AptValue *result=fn->function(context,nParams);
  stack.PopAndPush(nParams,(BfmeAptValue006DCD20*)result);constantPool=old;
 } else if(function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isScriptFunction()) {
  AptConstantPool old=constantPool; AptScriptFunctionBase *previous=mpCurrentFunction;
  mpCurrentFunction=(AptScriptFunctionBase *)((BfmeAptValue006DCD20 *)function)->rva006DCEE0();constantPool=mpCurrentFunction->GetConstantPool();
  if(((BfmeAptValue006DCD20*)mpCurrentFunction->mpCIH)->isUndefined() || ((unsigned char)((BfmeAptValue006DCD20*)mpCurrentFunction->mpCIH)->rva006E03A0() && (mpCurrentFunction->mpCIH->state&0xc0000)==0) || ((unsigned char)((BfmeAptValue006DCD20*)mpCurrentFunction->mpCIH)->rva006E03A0() && (mpCurrentFunction->mpCIH->state&0xc0000)==0x80000)) {
   stack.rva006E3AA0(nParams);stack.rva006FDF30((BfmeAptValue006DCD20*)gpUndefinedValue);mpCurrentFunction->mpCIH=(AptCIH *)gpUndefinedValue;
  } else {
   thisStack.push(context); _AptScriptFunctionState state;mpCurrentFunction->AddRef();mpCurrentFunction->SetupBeforeExecution(&state,context);
   int expected=mpCurrentFunction->GetNumArguments();int count=expected;if(nParams<count)count=nParams;int i;
   for(i=0;i<count;++i){AptValue *param=(AptValue*)stack.At(i);mpCurrentFunction->SetArgument(param,i);}
   for(;i<expected;++i)mpCurrentFunction->SetArgument(gpUndefinedValue,i);
   stack.rva006E3AA0(nParams);
   const AptCIH *root=mpCurrentFunction->mpParentAnim->rva006E0CB0();AptCharacterInst *character=root?(AptCharacterInst*)((Rva006CD650*)root)->rva006CD650():0;
   runStream(mpCurrentFunction->GetByteCodeBase(),mpCurrentFunction->mpCIH,mpCurrentFunction->GetByteCodeSize(),character);
   mpCurrentFunction->CleanupAfterExecution(&state);mpCurrentFunction->Release();thisStack.pop();
  }
  mpCurrentFunction=previous;constantPool=old;
 } else {stack.rva006E3AA0(nParams);stack.PushNoInc(gpUndefinedValue);}
 int after=stack.count;
 if(unwind){if(after>before)stack.rva006E3AA0(after-before);}
 else if(!(after==before || after==before+1)){g_bfmeAptAssertAtE17734("nStackElementsPost == nStackElementsPre || nStackElementsPost == (nStackElementsPre+1)","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x837);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
}


