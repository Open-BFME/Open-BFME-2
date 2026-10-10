// cl: /O2 /MD /EHsc
// Primary semantic guide: original EA AptXml.cpp bcba297ca166ec14.
// Native named-WB lookup1788560 selects load6F1FD0 and parseXml6F2080.
// Both independent172B boundaries end at RET before INT3 padding; native
// calls and original reference prove cdecl context/count callbacks. Only
// observed XML interface slots are described; full interface ABI is unproven.
// XmlValuePrefix describes the native checked XML value's node pointer+32.
// Existing true constructor6D2F90 from URL recovery is called directly.
class EAStringC {void *data;public:EAStringC();~EAStringC();const char *rva00620090()const;};
class AptValue {public:void toString(EAStringC &)const;};
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
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32(const char *);
 virtual void slot33();
 virtual void slot34(const char *);
};
struct XmlValuePrefix {unsigned char prefix[32];XmlNativeInterface *node;};
class BfmeAptValue006DCD20 {public:int isXml()const;int isString()const;BfmeAptValue006DCD20 *rva006DD260();};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
class AptXml {public:static AptValue *sMethod_load(AptValue *,int);static AptValue *sMethod_parseXml(AptValue *,int);};
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
