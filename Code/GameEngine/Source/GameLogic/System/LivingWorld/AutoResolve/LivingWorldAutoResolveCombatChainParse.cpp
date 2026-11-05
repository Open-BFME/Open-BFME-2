// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// ?parseAutoResolveCombatChainDefinition@@YAXPAVINI@@@Z
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
#include "../../../../../Include/Common/INI/FieldParse.h"
void Rva00418F7DParse(INI*,void*,void*,const void*);
static const FieldParse combatChainFields[]={ {"Target",Rva00418F7DParse,0,0},{0,0,0,0} };
#include "../../../../../Include/Common/INI/INI.h"
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
Rva0022D214::Rva0022D214(const AsciiString&asciiString,const Rva004191E5&v):key(asciiString),value(v){}
#pragma pack(push,1)
struct InsertRet00419331 {void *node;void *owner;unsigned char found;};
#pragma pack(pop)
#include "../../../../../Include/GameLogic/Rva000427195.h"
__forceinline InsertRet00419331 Rva000427195::rva004193D1(const void *value) {return insertUnique(value);}
class Rva0041811D {public:void *rva00419154();unsigned char pad[12];Rva000427195 table;};
extern Rva0041811D *TheLivingWorldAutoResolveCombatChainStore;
void parseAutoResolveCombatChainDefinition(INI *ini)
{
 const char *token=ini->getNextToken();
 const Rva004190DA *defaults=static_cast<const Rva004190DA*>(TheLivingWorldAutoResolveCombatChainStore->rva00419154());
 const AsciiString *recordName,*pairName;
 InsertRet00419331 result=TheLivingWorldAutoResolveCombatChainStore->table.rva004193D1((recordName=&AsciiString(token),pairName=&AsciiString(token),&Rva0022D214(*pairName,*reinterpret_cast<const Rva004191E5*>(&Rva004190DA(*recordName,defaults)))));
 if(!result.found) throw INIException(8,"Duplicate AutoResolveCombatChain entries named %s",token);
 ini->initFromINI(static_cast<char*>(result.node)+8,combatChainFields);
}
