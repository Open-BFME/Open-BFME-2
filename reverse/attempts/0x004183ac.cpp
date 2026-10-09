// ?Rva004183ACParse@@YAXPAVINI@@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native4193E5..4194D6 parser; registration7B00C7 names AutoResolveCombatChain.
// Native41926B..4192A4 constructs the24B string/record pair. Target's getter,
// constructors/copies and destructor callers establish data20/pair24 layouts.
// No matching clean BF1/ZH subsystem source was found at BF1 f989; existing
// target siblings supply the string/map insertion and INI exception guide.
#include "ascii_string.h"
class INI;
struct FieldParse {const char *name;void (*parse)(INI*,void*,void*,const void*);int offset;const void *data;};
void Rva00417EF9Parse(INI*,void*,void*,const void*);
void Rva00417FF0Parse(INI*,void*,void*,const void*);
static void parseBool(INI*,void*,void*,const void*);

class INI {public: const char *getNextToken(const char *seps=0);void initFromINI(void*,const FieldParse*);static void parseBool(INI*,void*,void*,const void*);};
static const FieldParse leadershipFields[]={ {"Affects",Rva00417EF9Parse,0,(const void*)4},{"AffectsHigherLevelFirst",INI::parseBool,0,(const void*)20},{"BonusForLevel",Rva00417FF0Parse,0,(const void*)8},{0,0,0,0} };
class INIException {public:char *message;int code;INIException(int,const char*,...);INIException(const INIException&);~INIException();};
class Rva0022CCB0 {public:~Rva0022CCB0();};
class Rva0022CFE6 {public:~Rva0022CFE6();};
class Rva00417F7C {
public:Rva00417F7C(const StringBase<char>&);
 __forceinline ~Rva00417F7C(){reinterpret_cast<Rva0022CCB0*>(this)->~Rva0022CCB0();}
private:unsigned char data[24];
};
class Rva004181A6 {public:Rva004181A6(const Rva004181A6&);private:unsigned char data[24];};
class Rva00418232 {
public:Rva00418232(const AsciiString&,const Rva004181A6&);
 __forceinline ~Rva00418232(){reinterpret_cast<Rva0022CFE6*>(this)->~Rva0022CFE6();}
private:unsigned char data[28];
};
class Rva004181F5;
struct OutIter004182F8 {void *node;void *table;unsigned char inserted;};
class Rva00418374 {public:OutIter004182F8 *rva00418374(OutIter004182F8*,const Rva004181F5*);};
class Rva0041811D {public:unsigned char pad[12];Rva00418374 table;};
extern Rva0041811D *g_Va00E030A8;
void Rva004183ACParse(INI *ini)
{
 const char *token=ini->getNextToken();
 const AsciiString *recordName,*pairName;
 OutIter004182F8 result;
 g_Va00E030A8->table.rva00418374(&result,(recordName=&AsciiString(token),pairName=&AsciiString(token),reinterpret_cast<const Rva004181F5*>(&Rva00418232(*pairName,*reinterpret_cast<const Rva004181A6*>(&Rva00417F7C(*reinterpret_cast<const StringBase<char>*>(recordName)))))));
 if(!result.inserted) throw INIException(8,"Duplicate AutoResolveLeadership entries named %s",token);
 ini->initFromINI(static_cast<char*>(result.node)+8,leadershipFields);
}
