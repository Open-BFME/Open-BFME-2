// cl: /O2 /MD /EHsc
// Primary semantic guide: original EA AptXml.cpp bcba297ca166ec14.
// Native named-WB lookup1788560 selects load6F1FD0 and parseXml6F2080.
// Both independent172B boundaries end at RET before INT3 padding; native
// calls and original reference prove cdecl context/count callbacks. Only
// observed XML interface slots are described; full interface ABI is unproven.
// XmlValuePrefix describes the native checked XML value's node pointer+32.
// Existing true constructor6D2F90 from URL recovery is called directly.
// Lookup uses the native unconditional context type switch32/node-call/33;
// the later donor null-context guard is absent in this retail body. Its
// thirteen-entry table6F24A8..6F24DC is included in the complete940B extent.
// Existing neutral byte-count callbacks and owned BfmeS1082 cache globals
// retain their actual names and declarations. No second real name is pinned.
// Only the observed virtual operation slots are claimed, not their original
// interface owner. Unsupported reference cases fall through to native null.
class EAStringC {void *data;public:EAStringC();~EAStringC();const char *rva00620090()const;unsigned int rva006D3750()const;};
class AptValue {public:void toString(EAStringC &)const;void SetString(const char *);bool getIsDefined()const;};
class XmlNativeInterface {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual const char *slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual const char *slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual int slot31();
 virtual void slot32(const char *);
 virtual int slot33();
 virtual void slot34(const char *);
 virtual void slot35();
 virtual void slot36();
 virtual int slot37();
};
struct XmlValuePrefix {unsigned char prefix[32];XmlNativeInterface *node;};
class BfmeAptValue006DCD20 {friend class AptXml;private:void setTypeAt006DBBC0(int);public:void setGCRootCount(unsigned int);int isXml()const;int isString()const;BfmeAptValue006DCD20 *rva006DD260();};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
class AptXml {public:virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;static AptValue *sMethod_load(AptValue *,int);static AptValue *sMethod_parseXml(AptValue *,int);};
AptValue *AptXml::sMethod_load(AptValue *self,int count)
{
 if(count<1)return gpUndefinedValue;
 BfmeAptValue006DCD20 *value=reinterpret_cast<BfmeAptValue006DCD20 *>(self);
 if(static_cast<unsigned char>(value->isXml())) {
  BfmeAptValue006DCD20 *arg=g_aptDateInterpreter.stack.At(0);
  if(static_cast<unsigned char>(arg->isString())) {
   EAStringC text;
   reinterpret_cast<AptValue *>(arg)->toString(text);
   XmlNativeInterface *node=reinterpret_cast<XmlValuePrefix *>(value->rva006DD260())->node;
   if(node)node->slot32(text.rva00620090());
  }
 }
 return gpUndefinedValue;
}
AptValue *AptXml::sMethod_parseXml(AptValue *self,int count)
{
 if(count<1)return gpUndefinedValue;
 BfmeAptValue006DCD20 *value=reinterpret_cast<BfmeAptValue006DCD20 *>(self);
 if(static_cast<unsigned char>(value->isXml())) {
  BfmeAptValue006DCD20 *arg=g_aptDateInterpreter.stack.At(0);
  if(static_cast<unsigned char>(arg->isString())) {
   EAStringC text;
   reinterpret_cast<AptValue *>(arg)->toString(text);
   XmlNativeInterface *node=reinterpret_cast<XmlValuePrefix *>(value->rva006DD260())->node;
   if(node)node->slot34(text.rva00620090());
  }
 }
 return gpUndefinedValue;
}

class Rva006F1360 {public:AptValue *rva006F1600(AptValue *,const EAStringC *)const;};
class AptString {public:static AptString *Create();};
class AptInteger {public:static AptValue *Create(int);};
class AptBoolean {public:static AptValue *Create(bool);};
EAStringC *Rva0070B4F0GetString(int);
struct R4Word {const char *name;int id;};
const R4Word *Rva008D5DC0(const char *,unsigned int);
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6500 {unsigned char storage[36];public:Rva006D6500(int);static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}};
class BfmeS1082 {public:virtual void bfmeSlot1082S_0();virtual void bfmeSlot1082S_1();};
extern BfmeS1082 *g_bfmeS1082_0,*g_bfmeS1082_1,*g_bfmeS1082_2,*g_bfmeS1082_3;
void rva006F1F50(BfmeAptValue006DCD20 *);
void rva006F1F90(BfmeAptValue006DCD20 *);
AptValue *AptXml::objectMemberLookup(AptValue *const context,const EAStringC *const name)const
{
 reinterpret_cast<BfmeAptValue006DCD20 *>(context)->setTypeAt006DBBC0(32);
 AptValue *inherited=reinterpret_cast<const Rva006F1360 *>(this)->rva006F1600(context,name);
 reinterpret_cast<BfmeAptValue006DCD20 *>(context)->setTypeAt006DBBC0(33);
 if(inherited && inherited->getIsDefined())return inherited;
 const R4Word *prop=context?Rva008D5DC0(name->rva00620090(),name->rva006D3750()):0;
 if(prop) {
  XmlValuePrefix *xml=reinterpret_cast<XmlValuePrefix *>(reinterpret_cast<BfmeAptValue006DCD20 *>(const_cast<AptXml *>(this))->rva006DD260());
  XmlNativeInterface *node=xml->node;
  switch(prop->id) {
case 100:{
   AptString *result=AptString::Create();
   reinterpret_cast<AptValue *>(result)->SetString(Rva0070B4F0GetString(98)->rva00620090());
   if(xml->node){
    const char *text=node->slot22();
    if(text)reinterpret_cast<AptValue *>(result)->SetString(text);
   }
   return reinterpret_cast<AptValue *>(result);
  }
case 103:{
   AptString *result=AptString::Create();
   reinterpret_cast<AptValue *>(result)->SetString(Rva0070B4F0GetString(98)->rva00620090());
   if(xml->node){
    const char *text=node->slot26();
    if(text)reinterpret_cast<AptValue *>(result)->SetString(text);
   }
   return reinterpret_cast<AptValue *>(result);
  }
case 104:
   if(!g_bfmeS1082_0){
    g_bfmeS1082_0=reinterpret_cast<BfmeS1082 *>(new Rva006D6500(reinterpret_cast<int>(&rva006F1F50)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_bfmeS1082_0)->setGCRootCount(1);
    g_bfmeS1082_0->bfmeSlot1082S_0();
   }
   return reinterpret_cast<AptValue *>(g_bfmeS1082_0);
case 105:
   if(!g_bfmeS1082_1){
    g_bfmeS1082_1=reinterpret_cast<BfmeS1082 *>(new Rva006D6500(reinterpret_cast<int>(&rva006F1F90)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_bfmeS1082_1)->setGCRootCount(1);
    g_bfmeS1082_1->bfmeSlot1082S_0();
   }
   return reinterpret_cast<AptValue *>(g_bfmeS1082_1);
case 106:return AptBoolean::Create(node->slot31()!=0);
case 107:
   if(!g_bfmeS1082_2){
    g_bfmeS1082_2=reinterpret_cast<BfmeS1082 *>(new Rva006D6500(reinterpret_cast<int>(&AptXml::sMethod_load)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_bfmeS1082_2)->setGCRootCount(1);
    g_bfmeS1082_2->bfmeSlot1082S_0();
   }
   return reinterpret_cast<AptValue *>(g_bfmeS1082_2);
case 108:return AptBoolean::Create(node->slot33()!=0);
case 109:
   if(!g_bfmeS1082_3){
    g_bfmeS1082_3=reinterpret_cast<BfmeS1082 *>(new Rva006D6500(reinterpret_cast<int>(&AptXml::sMethod_parseXml)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_bfmeS1082_3)->setGCRootCount(1);
    g_bfmeS1082_3->bfmeSlot1082S_0();
   }
   return reinterpret_cast<AptValue *>(g_bfmeS1082_3);
case 112:return AptInteger::Create(node->slot37());
  }
 }
 return 0;
}
