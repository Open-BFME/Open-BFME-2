// cl: /O2 /MD /EHsc
// Later EA AptGlobalObject.cpp is the semantic guide; native101B and WB179E970
// assert69 establish the earlier extension-first lookup, without 2009 gperf.
#include "AptScriptFunction.h"
class BfmeN1034;
class Rva0070A5C0 {public:BfmeN1034 *rva0070A5C0(int);};
class Rva0070B380 {public:void *lookup(const EAStringC &);};
class BfmeAptValue006DCD20 {public:bool isUndefined()const;};
extern AptValue *g_shutdownAtE18360,*gpGlobalGlobalObject;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptGlobal : public AptObject {
public:virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;
 virtual bool objectMemberSet(AptValue *const,const EAStringC *const,AptValue *const);
};
AptValue *AptGlobal::objectMemberLookup(AptValue *const,const EAStringC *const name)const
{
 if(this!=gpGlobalGlobalObject) {
  g_bfmeAptAssertAtE17734("this == gpGlobalGlobalObject","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptGlobalObject.cpp",69);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 AptValue *value=reinterpret_cast<AptValue *>(reinterpret_cast<Rva0070A5C0 *>(g_shutdownAtE18360)->rva0070A5C0(reinterpret_cast<int>(name)));
 if(value&&!reinterpret_cast<BfmeAptValue006DCD20 *>(value)->isUndefined())return value;
 return reinterpret_cast<AptValue *>(reinterpret_cast<Rva0070B380 *>(reinterpret_cast<char *>(gpGlobalGlobalObject)+8)->lookup(*name));
}
bool AptGlobal::objectMemberSet(AptValue *const,const EAStringC *const name,AptValue *const value)
{
 if(this!=gpGlobalGlobalObject) {
  g_bfmeAptAssertAtE17734("this == gpGlobalGlobalObject","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptGlobalObject.cpp",102);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 if(!reinterpret_cast<Rva0070A5C0 *>(g_shutdownAtE18360)->rva0070A5C0(reinterpret_cast<int>(name)))mNativeHash.Set(name,value);
 return true;
}
