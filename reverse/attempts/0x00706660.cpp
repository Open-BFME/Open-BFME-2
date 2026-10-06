// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// partial score=0.926 date=2026-10-06
// cl: /O2 /MD /EHsc /ICode/Libraries/Source/Apt/AptObject
#include "AptScriptFunction.h"
class BfmeAptValue006DCD20 { public: bool isNativeFunction() const; bool isScriptFunction() const; BfmeAptValue006DCD20 *rva006DCF20(); BfmeAptValue006DCD20 *rva006DCEE0(); };
struct NativeFunctionView { char opaque[0x20]; AptValue *(__cdecl *function)(AptValue *,int); };
class AptCIH : public AptValue { char opaque[0x5c-8]; public: unsigned int state; bool IsLevelInst() const; AptCIH *GetRootAnimation(); void *GetAnimationInst(); };
extern AptValue *gpUndefinedValue;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptBasePtrStack { public: int count,capacity; AptValue **items; AptValue *At(int); void Pop(int); void PopAndPush(int,AptValue *); void PushNoInc(AptValue *v) {if(count>=capacity){g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h",0x90);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}items[count++]=v;} };
struct AptValuePtrStack { int count,capacity; AptValue **items; void push(AptValue *); void pop(){if(count<=0){g_bfmeAptAssertAtE17734("size() > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}items[count-1]->Release();--count;} };
struct AptActionInterpreter {
 AptBasePtrStack stack; char pad[0x24-12]; AptValuePtrStack thisStack; AptScriptFunctionBase *mpCurrentFunction; char debug[12]; AptConstantPool constantPool; char pad2[0x60-0x48]; int unwind;
 void runStream(const unsigned char *,AptCIH *,int,void *);
 void callFunction(AptValue *,AptValue *,int);
};
void AptActionInterpreter::callFunction(AptValue *context,AptValue *function,int nParams) {
 int before=stack.count-nParams;
 if(function && ((BfmeAptValue006DCD20 *)function)->isNativeFunction()) {
  AptConstantPool old=constantPool;
  NativeFunctionView *fn=(NativeFunctionView *)((BfmeAptValue006DCD20 *)function)->rva006DCF20();
  AptValue *result=fn->function(context,nParams);
  stack.PopAndPush(nParams,result);constantPool=old;
 } else if(function && ((BfmeAptValue006DCD20 *)function)->isScriptFunction()) {
  AptConstantPool old=constantPool; AptScriptFunctionBase *previous=mpCurrentFunction;
  mpCurrentFunction=(AptScriptFunctionBase *)((BfmeAptValue006DCD20 *)function)->rva006DCEE0();constantPool=mpCurrentFunction->GetConstantPool();
  if(mpCurrentFunction->mpCIH->isUndefined() || (mpCurrentFunction->mpCIH->IsLevelInst() && (mpCurrentFunction->mpCIH->state&0xc0000)==0) || (mpCurrentFunction->mpCIH->IsLevelInst() && (mpCurrentFunction->mpCIH->state&0xc0000)==0x80000)) {
   stack.Pop(nParams);stack.PushNoInc(gpUndefinedValue);mpCurrentFunction->mpCIH=(AptCIH *)gpUndefinedValue;
  } else {
   thisStack.push(context); _AptScriptFunctionState state;mpCurrentFunction->AddRef();mpCurrentFunction->SetupBeforeExecution(&state,context);
   int expected=mpCurrentFunction->GetNumArguments();int count=expected;if(nParams<count)count=nParams;int i;
   for(i=0;i<count;++i){AptValue *param=stack.At(i);mpCurrentFunction->SetArgument(param,i);}
   for(;i<expected;++i)mpCurrentFunction->SetArgument(gpUndefinedValue,i);
   stack.Pop(nParams);
   AptCIH *root=mpCurrentFunction->mpParentAnim->GetRootAnimation();void *character=root?root->GetAnimationInst():0;
   runStream(mpCurrentFunction->GetByteCodeBase(),mpCurrentFunction->mpCIH,mpCurrentFunction->GetByteCodeSize(),character);
   mpCurrentFunction->CleanupAfterExecution(&state);mpCurrentFunction->Release();thisStack.pop();
  }
  mpCurrentFunction=previous;constantPool=old;
 } else {stack.Pop(nParams);stack.PushNoInc(gpUndefinedValue);}
 int after=stack.count;
 if(unwind){if(after>before)stack.Pop(after-before);}
 else if(!(after==before || after==before+1)){g_bfmeAptAssertAtE17734("nStackElementsPost == nStackElementsPre || nStackElementsPost == (nStackElementsPre+1)","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.cpp",0x837);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
}


