// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// BFME1 semantic donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameLogic/System/INI_parseVictorySystemDefinition.cpp.
// WorldBuilder b6cb00 names this callback and INIVictorySystem.cpp:39;
// retail 215C54..215D0B proves the one-pointer string lifetime, singleton
// E02F3C and diagnostic slots60/6C/38/4C. View types describe only those
// observed dispatch slots. The field table at C387C0 contains four float
// parsers at offsets10/18/1C/24 and a complete null terminator.
// The singleton name is independently witnessed by GameEngine::init's
// TheVictorySystem registration and GameState's CHUNK_VictorySystem.

#include "ascii_string.h"
struct FieldParse;
class INI {public: const char *getNextToken(const char *separators=0); void initFromINI(void *,const FieldParse *); static void parseReal(INI *,void *,void *,const void *);};
struct FieldParse {const char *name;void (*parse)(INI *,void *,void *,const void *);const void *user;int offset;};
class VictorySystem;extern VictorySystem *TheVictorySystem;
extern "C" const FieldParse VictorySystemFieldParse[]={
 {"CellSize",INI::parseReal,0,0x10},
 {"ScalePerLogicFrame",INI::parseReal,0,0x18},
 {"SubtractPerLogicFrame",INI::parseReal,0,0x1C},
 {"CellBonusRadius",INI::parseReal,0,0x24},
 {0,0,0,0}
};
class Debug {public:class Format {public:Format(const char *,...);operator const char *()const{return m_buffer;}char m_buffer[512];};};
extern Debug *theDebug;
class VictoryDiagnosticStreamView {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
 virtual void s30();virtual void s34();virtual void Put_String(const char *);
 virtual void s3C();virtual void s40();virtual void s44();virtual void s48();
 virtual void Finish(int);
};
class VictoryDiagnosticView {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
 virtual void s30();virtual void s34();virtual void s38();virtual void s3C();
 virtual void s40();virtual void s44();virtual void s48();virtual void s4C();
 virtual void s50();virtual void s54();virtual void s58();virtual void s5C();
 virtual void Begin_Report();virtual void s64();virtual void s68();
 virtual VictoryDiagnosticStreamView *Get_Stream(int,int,int);
};
void _bfme_debugRecordCallsite(int);
void iniParseVictorySystemDefinition(INI *ini) {
 AsciiString name;
 name=ini->getNextToken();
 if(!TheVictorySystem){
  _bfme_debugRecordCallsite(1);
  ((VictoryDiagnosticView*)theDebug)->Begin_Report();
  const char *text=name.str();
  VictoryDiagnosticStreamView *stream=((VictoryDiagnosticView*)theDebug)->Get_Stream(0,0,0);
  stream->Put_String(Debug::Format("TheVictorySystem has not been initialized!.\n",text));
  stream->Finish(1);
 }else ini->initFromINI(TheVictorySystem,VictorySystemFieldParse);
}
