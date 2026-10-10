// ?Rva0041999FParse@@YAXPAVINI@@@Z
// ?Rva0041999FParse@@YAXPAVINI@@@Z
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
struct FieldParse {const char* token; INIFieldParseProc parse; const void* data; int offset;};
class INI {public: const char* getNextToken(const char*); void initFromINI(void*,const FieldParse*); static void parseBool(INI*,void*,void*,const void*); static void parseInt(INI*,void*,void*,const void*);};
void Rva0041951DParse(INI*,void*,void*,const void*);
void Rva004195ECParse(INI*,void*,void*,const void*);
class Rva0022D094 {public: ~Rva0022D094(); private: char payload[0x3C];};
class Rva0022D249 {public: ~Rva0022D249(); private: char payload[0x40];};
struct Rva00419789 : Rva0022D094 {};
class Rva00419669 : public Rva00419789 {public: Rva00419669(const AsciiString&, const Rva00419669*);};
struct Rva004197E8 : Rva0022D249 {Rva004197E8(const AsciiString&, const Rva00419789&);};
struct InsertRet00419331 { void* m_node; void* m_owner; unsigned char m_found;};
class Rva000427195 {public: InsertRet00419331 rva00419967(const void*); __forceinline InsertRet00419331 rva0041998B(const void *value) {return rva00419967(value);}private:char bytes[0x14];};
class Rva0041811D {public: void* rva004196F8(); char prefix[0xC]; Rva000427195 table;};
extern Rva0041811D *g_Va00E030C0;
class INIException {public:char*message;int code;INIException(int,const char*,...);INIException(const INIException&);~INIException();};
void Rva0041999FParse(INI* ini) {
 static const FieldParse fields[] = {
 {"DamagePerRound", Rva0041951DParse,0,0x14},
 {"LevelBonus",Rva004195ECParse,0,4},
 {"ReduceAttackWhenHurt",INI::parseBool,0,0x34},
 {"MissPercentChance",INI::parseInt,0,0x10},
 {0,0,0,0}};
 const char* token=ini->getNextToken(0);
 const Rva00419669* defaults=(const Rva00419669*)g_Va00E030C0->rva004196F8();
 InsertRet00419331 result=g_Va00E030C0->table.rva0041998B(&Rva004197E8(token,Rva00419669(token,defaults)));
 if(!result.m_found) throw INIException(8,"Duplicate AutoResolveWeapon entries named %s",token);
 ini->initFromINI((char*)result.m_node+8,fields);
}
