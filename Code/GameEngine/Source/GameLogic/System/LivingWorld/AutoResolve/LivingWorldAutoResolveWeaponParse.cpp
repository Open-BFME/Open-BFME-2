// ?parseAutoResolveWeaponDefinition@@YAXPAVINI@@@Z
// ?parseAutoResolveWeaponDefinition@@YAXPAVINI@@@Z
// Native41999F..419A99 AutoResolveWeapon parser; table names and
// independently owned60B record/64B pair constructors establish behavior.
// Result transport needs natural4-byte alignment (12B stack home); inline
// insert wrapper preserves native ADD-before-PUSH. Ordinary C++ throw emits
// the native INIException handling without runtime-call declarations.
// Original pair/template names remain unknown.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
#include "ascii_string.h"
class INI;
typedef void (*INIFieldParseProc)(INI*,void*,void*,const void*);
#include "../../../../../Include/Common/INI/FieldParse.h"
#include "../../../../../Include/Common/INI/INI.h"
class LivingWorldAutoResolveWeaponTemplate
{
public:
	static void parseDamagePerRoundIntoTable(INI*,void*,void*,const void*);
};
void Rva004195ECParse(INI*,void*,void*,const void*);
class Rva0022D094 {public: ~Rva0022D094(); private: char payload[0x3C];};
class Rva0022D249 {public: ~Rva0022D249(); private: char payload[0x40];};
struct Rva00419789 : Rva0022D094 {};
class Rva00419669 : public Rva00419789 {public: Rva00419669(const AsciiString&, const Rva00419669*);};
struct Rva004197E8 : Rva0022D249 {Rva004197E8(const AsciiString&, const Rva00419789&);};
struct InsertRet00419331 { void* m_node; void* m_owner; unsigned char m_found;};
#include "../../../../../Include/GameLogic/Rva000427195.h"
__forceinline InsertRet00419331 Rva000427195::rva0041998B(const void *value) {return rva00419967(value);}
class Rva0041811D {public: void* rva004196F8(); char prefix[0xC]; Rva000427195 table;};
extern Rva0041811D *TheLivingWorldAutoResolveWeaponStore;
void parseAutoResolveWeaponDefinition(INI* ini) {
 static const FieldParse fields[] = {
 {"DamagePerRound", LivingWorldAutoResolveWeaponTemplate::parseDamagePerRoundIntoTable,0,0x14},
 {"LevelBonus",Rva004195ECParse,0,4},
 {"ReduceAttackWhenHurt",INI::parseBool,0,0x34},
 {"MissPercentChance",INI::parseInt,0,0x10},
 {0,0,0,0}};
 const char* token=ini->getNextToken(0);
 const Rva00419669* defaults=(const Rva00419669*)TheLivingWorldAutoResolveWeaponStore->rva004196F8();
 InsertRet00419331 result=TheLivingWorldAutoResolveWeaponStore->table.rva0041998B(&Rva004197E8(token,Rva00419669(token,defaults)));
 if(!result.m_found) throw INIException(8,"Duplicate AutoResolveWeapon entries named %s",token);
 ini->initFromINI((char*)result.m_node+8,fields);
}
