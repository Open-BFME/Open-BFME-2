// ?callback006FF750@@YAPAVAptValue@@PAV1@H@Z
// partial score=0.9863999504551928 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O2 /MD /EHsc
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#define check(ok,test,file,line) do{if(!(ok)){g_bfmeAptAssertAtE17734(test,file,line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}}while(0)
class EAStringC{void *data;public:EAStringC();~EAStringC();EAStringC&operator=(const EAStringC&);EAStringC&Rva006D4F00Append(const EAStringC&);};
class AptValue{public:bool isString()const;void toString(EAStringC&)const;};
class AptBasePtrStack{public:int nElements,nCapacity;AptValue**elements;AptValue*At(int n){check(nElements-n>0,"m_nElements - nPos > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h",266);return elements[nElements-n-1];}};
struct AptActionInterpreter{AptBasePtrStack stack;};extern AptActionInterpreter g_aptDateInterpreter;
class AptString{public:virtual void v0();int flags;EAStringC string;static AptString*Create();};
void rva006FD630(EAStringC*);void rva006FD4C0(EAStringC*);
AptValue*callback006FF660(AptValue*,int nParams){check(nParams<=1,"nParams <= 1","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x58F);AptString*result=AptString::Create();AptValue*value=g_aptDateInterpreter.stack.At(0);if(value->isString()){EAStringC temp;value->toString(temp);rva006FD630(&temp);result->string=temp;}return (AptValue*)result;}
AptValue*callback006FF750(AptValue*,int nParams){check(nParams<=1,"nParams <= 1","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x5A7);AptString *result=(nParams?AptString::Create():AptString::Create());_ReadWriteBarrier();if(nParams){AptValue*value=g_aptDateInterpreter.stack.At(0);if(value->isString()){EAStringC temp;value->toString(temp);rva006FD4C0(&temp);result->string.Rva006D4F00Append(temp);}}return (AptValue*)result;}
