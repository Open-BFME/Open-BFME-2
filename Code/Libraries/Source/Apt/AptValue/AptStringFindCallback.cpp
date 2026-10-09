// cl: /O2 /MD /EHsc
// Native6D6EF0..6D700E callback converts receiver and argument0 to strings,
// optional argument1 is a nonnegative numeric offset, then returns a pooled
// integer from EAStringC find. WB177F130 supplies the readable body guide;
// target assertion, exact callees, stack ABI and two string lifetimes agree.
// Address-derived callback name does not claim an original private name.
class EAStringC {void *data;public:EAStringC();~EAStringC();const char *rva00620090() const;int rva006d6070(const char *,int);};
class AptValue {public:void toString(EAStringC &) const;};
class BfmeAptValue006DCD20 {public:int isInteger() const;int isFloat() const;int toInteger() const;};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
class AptInteger {public:static AptValue *Create(int);};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
AptValue *Rva006D6EF0Find(AptValue *value,int argc) {
 EAStringC a,b;
 int offset=0;
 value->toString(a);
 AptValue *result;
 if(!argc) result=gpUndefinedValue;
 else {
  AptValue *argument=(AptValue *)g_aptDateInterpreter.stack.At(0);
  argument->toString(b);
  if(argc==2) {
   BfmeAptValue006DCD20 *start=g_aptDateInterpreter.stack.At(1);
   if(!((unsigned char)start->isInteger() || (unsigned char)start->isFloat())) {
    g_bfmeAptAssertAtE17734("pStartOffset->isInteger() || pStartOffset->isFloat()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptString.cpp",0x116);
    if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
   }
   offset=start->toInteger();if(offset<0)offset=0;
  }
  result=AptInteger::Create(a.rva006d6070(b.rva00620090(),offset));
 }
 return result;
}
