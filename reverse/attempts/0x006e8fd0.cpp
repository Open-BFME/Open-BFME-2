// ?Rva006E8FD0LoadVars@@YAPAVAptValue@@PAV1@H@Z
// partial score=0.8356584516 date=2026-10-09
// cl: /O2 /MD /EHsc
// Native E8FD0..E9104 callback checks LoadVars through owned DD2E0,
// clears loaded+20, erases non-prototype hash entries, loads variables and
// returns a pooled boolean. Address-derived callback name preserves uncertainty.
// No applicable BFME1/ZeroHour LoadVars source exists at the pinned revision.
class EAStringC { void *data;public:EAStringC();~EAStringC();bool IsEqualTo(const EAStringC *) const;};
class AsciiString;
class AptNativeHash {public: struct Entry;AsciiString *rva0070AA40();Entry *rva0070AAA0(Entry *);};
class AptValue {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual AptNativeHash *GetNativeHashVirtual();void toString(EAStringC &) const;};
class BfmeAptValue006DCD20 {public:BfmeAptValue006DCD20 *rva006DD2E0();};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
class AptActionInterpreter {public:AptBasePtrStack stack;void loadVariables(AptValue *,AptValue *,const EAStringC *);};
extern AptActionInterpreter g_aptDateInterpreter;
class AptBoolean {public:static AptValue *Create(bool);};
struct BfmeKey1279;
class BfmeLookup1279 {public:void bfmeErase1279(BfmeKey1279 &);};
EAStringC *Rva0070B4F0GetString(int);
AptValue *Rva006E8FD0LoadVars(AptValue *value,int n) {
 *(int *)((char *)((BfmeAptValue006DCD20 *)value)->rva006DD2E0()+0x20)=0;
 if(n>0 && n<=1) {
  AptValue *arg=(AptValue *)g_aptDateInterpreter.stack.At(0);
  EAStringC url;
  arg->toString(url);
  AptNativeHash *hash=value->GetNativeHashVirtual();
  bool result=false;
  if(hash) {
   AsciiString *key=hash->rva0070AA40();
   while(key) {
    EAStringC *str=(EAStringC *)key;
    if(!str->IsEqualTo(Rva0070B4F0GetString(0)) && !str->IsEqualTo(Rva0070B4F0GetString(0x78)))
     ((BfmeLookup1279 *)hash)->bfmeErase1279(*(BfmeKey1279 *)key);
    key=(AsciiString *)hash->rva0070AAA0((AptNativeHash::Entry *)key);
   }
   g_aptDateInterpreter.loadVariables(value,0,&url);
   *(int *)((char *)((BfmeAptValue006DCD20 *)value)->rva006DD2E0()+0x20)=1;
   result=true;
  }
  return AptBoolean::Create(result);
 }
 return AptBoolean::Create(false);
}
