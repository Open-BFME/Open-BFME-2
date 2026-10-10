// cl: /O2 /MD /EHsc
// Native 6D7670..6D77AE AptString slice callback: optional start/end integers from the interpreter stack,
// receiver converted to a string, negative indices wrap by length, result boxed as a new AptString.
// Original method spelling follows the BFME2 sMethod_ naming used by the AptDate callbacks.
class EAStringC {
public:class StringDataC {public:unsigned short ref,size,maxSize,hash;};
private:StringDataC *data;
public:EAStringC();~EAStringC();EAStringC &operator=(const EAStringC &);EAStringC rva006d5f30(int,int)const;int rva006D5EC0();
};
extern EAStringC::StringDataC g_eaEmptyStringData;
__declspec(noinline) inline EAStringC::EAStringC(){data=&g_eaEmptyStringData;++data->ref;}
class AptValue {public:void toString(EAStringC &)const;};
class BfmeAptValue006DCD20 {public:int toInteger()const;};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
struct ScopedStringText {unsigned char prefix[8];EAStringC text;};
class AptString {public:static AptString *Create();static AptValue *sMethod_slice(AptValue *,int);};
AptValue *AptString::sMethod_slice(AptValue *self,int count)
{
 EAStringC text;
 int start=-1;
 int end=9999999;
 if(count==0)return gpUndefinedValue;
 if(count>=1)start=g_aptDateInterpreter.stack.At(0)->toInteger();
 if(count>=2)end=g_aptDateInterpreter.stack.At(1)->toInteger();
 self->toString(text);
 int length=text.rva006D5EC0();
 if(start<0)start=length+start;
 if(end<0)end=length+end;
 if(start<0)start=0;
 if(end<0)end=0;
 if(start>=length)start=length;
 if(end>=length)end=length;
 EAStringC sliced;
 sliced=text.rva006d5f30(start,end-start);
 AptString *result=AptString::Create();
 reinterpret_cast<ScopedStringText *>(result)->text=sliced;
 return reinterpret_cast<AptValue *>(result);
}
