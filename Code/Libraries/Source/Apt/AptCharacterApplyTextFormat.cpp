// cl: /O2 /DNDEBUG /MD /EHsc
// Native 6EF570..6EF6CD,349B, following the earlier function's tables.
// The format-state ABI comes from rowed6ECE30/6EB650 and AptTextFormat.cpp;
// native copies the optional32B state then updates font/size/alignment flags
// in the text instance. Callback name remains address-derived.
class Rva006DB160
{
public:
	void *allocBlock(int);
};
class Rva006DB270;extern Rva006DB270 *g_pChainBlockAllocator;
void Rva006D8680Free(void *,int);
class EAStringC {void *data;public:bool IsEmpty()const;EAStringC &operator=(const EAStringC&);};
class Rva006EB4B0 {
public:
 EAStringC font;union {float size;unsigned sizeBits;};int color,align;unsigned flags;int indent,left,right;
 Rva006EB4B0(const Rva006EB4B0&);
 static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
 // Declared only: the new-expression cleanup calls the rowed 0x006D8680 copy
 // (Rva006EF920TextFormat.cpp) instead of emitting a differing tail-jump one.
 static void operator delete(void *p,unsigned n);
};
class Rva006EB650 {public:void rva006EB650(const Rva006EB650&);};
struct TextInstance {
 char pad00[0x3c];int align;char pad40[0x20];float size;char pad64[4];Rva006EB4B0 *format;unsigned flags;
};
struct FormatPrefix {char pad[0x20];};
struct TextFormatValue:FormatPrefix,Rva006EB4B0 {};
class BfmeAptValue006DCD20 {public:bool getIsDefined()const;int isTextFormat()const;BfmeAptValue006DCD20 *rva006DCF60(bool);BfmeAptValue006DCD20 *rva006DD1A0();void *rva006E0F40()const;};
class AptValue {public:bool getIsDefined()const;};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
AptValue *Rva006EF570ApplyTextFormat(AptValue *self,int count) {
 if(count<=3) {
  BfmeAptValue006DCD20 *arg=g_aptDateInterpreter.stack.At(0);
  if(((AptValue *)arg)->getIsDefined() && (unsigned char)arg->isTextFormat()) {
   TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)self)->rva006DCF60(false)->rva006E0F40();
   TextFormatValue *input=(TextFormatValue*)arg->rva006DD1A0();
   unsigned combined;
   if(!text->format) {
    text->format=new Rva006EB4B0(*(Rva006EB4B0*)input);
    combined=input->flags|text->format->flags;
   } else {
    combined=text->format->flags|input->flags;
    ((Rva006EB650*)text->format)->rva006EB650(*(Rva006EB650*)(Rva006EB4B0*)input);
   }
   text->format->flags=combined;
   if(!input->font.IsEmpty())text->format->font=input->font;
   if(input->sizeBits!=0xbf800000) {
    text->size=input->size;
    if((int)text->size<=0)text->size=1.0f;
    text->flags=(text->flags&~1u)|0x10004;
   }
   if(input->align!=3) {
    text->align=input->align;
    text->flags=(text->flags&~1u)|0x20004;
   }
   if(input->color!=-1)text->flags|=0x400;
  }
 }
 return gpUndefinedValue;
}
