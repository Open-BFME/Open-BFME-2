// ?Rva004193E5Parse@@YAXPAVINI@@@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native4193E5..4194D6 parser; registration7B00C7 names AutoResolveCombatChain.
// Native41926B..4192A4 constructs the24B string/record pair. Target's getter,
// constructors/copies and destructor callers establish data20/pair24 layouts.
// No matching clean BF1/ZH subsystem source was found at BF1 f989; existing
// target siblings supply the string/map insertion and INI exception guide.
// Inline rva004193D1 preserves the known provider call and closes native
// ADD receiver before PUSH result; target bytes and all EH states verified.
#include "ascii_string.h"
class INI;
struct FieldParse {const char *name;void (*parse)(INI*,void*,void*,const void*);const void *data;int offset;};
void Rva00418F7DParse(INI*,void*,void*,const void*);
static const FieldParse combatChainFields[]={ {"Target",Rva00418F7DParse,0,0},{0,0,0,0} };
class INI {public: const char *getNextToken(const char *seps=0);void initFromINI(void*,const FieldParse*);};
class INIException {public:char *message;int code;INIException(int,const char*,...);INIException(const INIException&);~INIException();};
class Rva0022D05F {public:~Rva0022D05F();};
class Rva004190DA {
public:Rva004190DA(const AsciiString&,const Rva004190DA*);
 __forceinline ~Rva004190DA(){reinterpret_cast<Rva0022D05F*>(this)->~Rva0022D05F();}
private:unsigned char data[20];
};
struct Rva004191E5 {Rva004191E5(const Rva004191E5&);unsigned char data[20];};
class Rva0022D214 {
public:Rva0022D214(const AsciiString&,const Rva004191E5&);~Rva0022D214();
private:AsciiString key;Rva004191E5 value;
};
Rva0022D214::Rva0022D214(const AsciiString&n,const Rva004191E5&v):key(n),value(v){}
#pragma pack(push,1)
struct InsertRet00419331 {void *node;void *owner;unsigned char found;};
#pragma pack(pop)
class Rva000427195 {public:InsertRet00419331 rva004193AD(const void*); __forceinline InsertRet00419331 rva004193D1(const void *value) {return rva004193AD(value);}};
class Rva0041811D {public:void *rva00419154();unsigned char pad[12];Rva000427195 table;};
extern Rva0041811D *g_Va00E030B8;
void Rva004193E5Parse(INI *ini)
{
 const char *token=ini->getNextToken();
 const Rva004190DA *defaults=static_cast<const Rva004190DA*>(g_Va00E030B8->rva00419154());
 const AsciiString *recordName,*pairName;
 InsertRet00419331 result=g_Va00E030B8->table.rva004193D1((recordName=&AsciiString(token),pairName=&AsciiString(token),&Rva0022D214(*pairName,*reinterpret_cast<const Rva004191E5*>(&Rva004190DA(*recordName,defaults)))));
 if(!result.found) throw INIException(8,"Duplicate AutoResolveCombatChain entries named %s",token);
 ini->initFromINI(static_cast<char*>(result.node)+8,combatChainFields);
}
