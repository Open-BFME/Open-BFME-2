// cl: /O2 /MD /EHsc
// Target6D75A0..6D7666: cdecl two-word callback; count in second arg,
// global checked stack at E182E0, integer->EAStringC codepoint append loop,
// returned AptString factory with text+8. Neutral function name: fromCharCode
// is a semantic lead, not independently established retail identity.
class AptValue;
class BfmeAptValue006DCD20 {public:int toInteger() const;};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
class EAStringC {
public:
 EAStringC(unsigned int);
 EAStringC(){clear();}
 ~EAStringC();
 EAStringC &clear();
 EAStringC &rva006D61E0(int);
 EAStringC &Rva006D4F00Append(const EAStringC &);
 EAStringC &operator=(const EAStringC &);
private:void *data;
};
class AptString {
public:static AptString *Create();
 char prefix[8]; EAStringC text;
};
AptValue *rva006D75A0(void *self,int argc) {
 EAStringC result(2*argc);
 for(int i=0;i<argc;++i) {
  int point=g_aptDateInterpreter.stack.At(i)->toInteger();
  EAStringC character;
  character.rva006D61E0(point);
  result.Rva006D4F00Append(character);
 }
 AptString *value=AptString::Create();
 value->text=result;
 return (AptValue *)value;
}
