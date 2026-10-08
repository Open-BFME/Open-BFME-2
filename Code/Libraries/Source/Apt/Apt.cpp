// cl: /O2 /MD /EHsc
// WorldBuilder174F1C0 identifies AptSetInternalVariable in Apt.cpp through
// its own debug refcount label. Native6CCA50..6CCAE1 is 145 bytes.
// Retail passes seven interpreter arguments; _AptGetAnimationAtLevel(0)
// is a separate one-argument cdecl call. Both helpers have existing owners.
// The string wrapper owns one data pointer and is destroyed on scope exit.
class EAStringC {
 void *data;
public:
 EAStringC(const char *);
 ~EAStringC();
};
class AptValue {
public:
 virtual void AddRef();
 virtual void Release();
 void SetString(const char *);
};
class AptCIH : public AptValue {};
class AptString : public AptValue {public:static AptString *Create();};
struct AptActionInterpreter {
 AptValue *getVariable(AptValue *,AptValue *,const EAStringC *,int,int,int);
 bool setVariable(AptValue *,AptValue *,const EAStringC *,AptValue *,int,int,int);
};
extern AptActionInterpreter g_aptDateInterpreter;
AptCIH *_AptGetAnimationAtLevel(int);
void AptSetInternalVariable(const char *name, const char *text) {
 AptString *value=AptString::Create();
 value->AddRef();
 value->SetString(text);
 EAStringC key(name);
 g_aptDateInterpreter.setVariable(_AptGetAnimationAtLevel(0),0,&key,value,1,1,0);
 value->Release();
}

// Native6CCAF0..6CCB7B; WB174F2E0's AptGetInternalVariable label.
// The two caller arguments are the source key and a mutable output buffer.
// Native6DE870 converts the AptValue to EAStringC and copies into that buffer.
class Rva006DCD20 {public:void rva006DE870(char *);};
void AptGetInternalVariable(const char *name,char *out) {
 EAStringC key(name);
 AptValue *value=g_aptDateInterpreter.getVariable(_AptGetAnimationAtLevel(0),0,&key,1,1,0);
 value->AddRef();
 ((Rva006DCD20 *)value)->rva006DE870(out);
 value->Release();
}

// Native6CBC40..6CBC46 is the standalone allocation-hook forwarder called
// by allocator setup6CC380. Keep its call boundary; the next pool's allocation
// is separately inlined in retail. Original function identity is unresolved.
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
__declspec(noinline) void *Rva006CBC40Allocate(unsigned int bytes) {
 return g_bfmeAptAllocAtE17728(bytes);
}
