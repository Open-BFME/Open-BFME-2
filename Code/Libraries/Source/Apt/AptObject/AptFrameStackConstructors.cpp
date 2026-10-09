// cl: /O2 /DNDEBUG /MD /EHsc
// WB175D190/175D330 identify FrameStack constructors. PC32B class uses
// inherited AptValueWithHash28B and parent+1C, type20, own vtableCED880.
// Existing destructor/GC owner spelling retained; WB parent+20 is a donor
// layout fact, whereas PC parent+1C and the AddRef sequence are target facts.
#include "AptScriptFunction.h"
// ?AptValueGC::AptValueGC present-unmatched
inline AptValueGC::AptValueGC(AptVirtualFunctionTable_Indices t):AptValue(t){}
// ?AptValueWithHash::AptValueWithHash present-unmatched
inline AptValueWithHash::AptValueWithHash(AptVirtualFunctionTable_Indices t,int n):AptValueGC(t),mNativeHash(n){}
class Rva006FBC90Owner:public AptValueWithHash {
 AptValue *parent;
public:
 Rva006FBC90Owner(AptValue *);
 Rva006FBC90Owner(AptValue *,int);
 virtual ~Rva006FBC90Owner();
 bool rva006FBBA0(const EAStringC *,AptValue *);
};
Rva006FBC90Owner::Rva006FBC90Owner(AptValue *p):AptValueWithHash((AptVirtualFunctionTable_Indices)20,4),parent(p){if(p)p->AddRef();}
Rva006FBC90Owner::Rva006FBC90Owner(AptValue *p,int n):AptValueWithHash((AptVirtualFunctionTable_Indices)20,n),parent(p){if(p)p->AddRef();}

class Rva0070B380 {public:void *lookup(const EAStringC &);};
bool Rva006FBC90Owner::rva006FBBA0(const EAStringC *key,AptValue *value) {
 Rva006FBC90Owner *scope=this;
 while(scope) {
  if(((Rva0070B380 *)&scope->mNativeHash)->lookup(*key)) {
   scope->mNativeHash.Set(key,value);return true;
  }
  scope=(Rva006FBC90Owner *)scope->parent;
 }
 return false;
}
