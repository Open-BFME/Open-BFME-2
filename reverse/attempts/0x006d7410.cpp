// ?sMethod_charCodeAt@AptString@@SAPAVAptValue@@PAV2@H@Z
// partial score=0.9076923076923077 date=2026-10-10
// cl: /O2 /MD /EHsc
class EAStringC {void *data;public:EAStringC(const char *);~EAStringC();EAStringC &operator=(const EAStringC &);};
class AptValue;
class BfmeAptValue006DCD20 {public:int toInteger()const;BfmeAptValue006DCD20 *checkedString();unsigned char prefix[8];EAStringC text;};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
struct ScopedStringText {unsigned char prefix[8];EAStringC text;};
class AptString {public:static AptString *Create();static AptValue *sMethod_charCodeAt(AptValue *,int);};
void *rva006d4d40(void *,int);
class Rva006D5E70String {void *data;public:void *rva006d5e70ptr(int);};
__declspec(noinline) inline void *Rva006D5E70String::rva006d5e70ptr(int index){return rva006d4d40(static_cast<char *>(data)+8,index);}
int rva006d3e40(const char *);
extern "C" int __cdecl sprintf(char *,const char *,...);
AptValue *AptString::sMethod_charCodeAt(AptValue *self,int)
{
 int index=g_aptDateInterpreter.stack.At(0)->toInteger();
 BfmeAptValue006DCD20 *string=reinterpret_cast<BfmeAptValue006DCD20 *>(self)->checkedString();
 if(index<0)return gpUndefinedValue;
 EAStringC *local=&string->text;
 const char *buffer=static_cast<const char *>(reinterpret_cast<Rva006D5E70String *>(local)->rva006d5e70ptr(index));
 if(!buffer)return gpUndefinedValue;
 int code=rva006d3e40(buffer);
 char out[8];
 sprintf(out,"%d",code);
 EAStringC temp(out);
 AptString *result=AptString::Create();
 reinterpret_cast<ScopedStringText *>(result)->text=temp;
 return reinterpret_cast<AptValue *>(result);
}
