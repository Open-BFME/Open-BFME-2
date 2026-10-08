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
