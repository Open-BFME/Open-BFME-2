// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/iniexception
// Native00414F85..0041505A complete213B cdecl; WB12B53C0 independently
// names ScoredKillEvaAnnouncerController::iniParseScoredKillEvaAnnouncerBlock.
// Native reads registry10/14,48B records/name4, rejects duplicate names,
// appends a temporary and initializes the new last record from INI.
// ZH INIException/AsciiString behavior and STLport containers are semantic
// guides; no clean donor application body was available.
// Existing neutral constructor4148C0 and destructor414932 independently
// establish the48B temporary lifetime. Rva004147CF inherits the cleanup call
// view only to express that scope to the compiler, not to claim the original
// class hierarchy. novtable suppresses an extra local vptr reset absent from
// native; the existing constructor/destructor providers own actual vptr work.
// The registry name is descriptive recovery spelling; native absoluteE03074
// access establishes its role. Loader zero and COFF pointer extent are4B.
// stlport
#include "ascii_string.h"
#include "Common/INIException.h"
#include <vector>

class INI{public:const char *getNextToken(const char *separators=0);};
class Rva00414932{public:virtual ~Rva00414932();private:char data[44];};
class __declspec(novtable) Rva004147CF:public Rva00414932{public:Rva004147CF(const AsciiString&);__forceinline ~Rva004147CF(){};};
struct Rva00414BDBElement{char data[48];};
namespace _STL{template<>void vector<Rva00414BDBElement>::push_back(const Rva00414BDBElement&);}
class Rva0041430D{public:void rva0041430D(INI*);};
struct ParserRecord{void *vtable;AsciiString name;char rest[40];};
struct ParserRegistry{char pad[0x10];_STL::vector<ParserRecord> records;};
ParserRegistry *g_scoredKillEvaRegistry=0;
class ScoredKillEvaAnnouncerController{public:static void iniParseScoredKillEvaAnnouncerBlock(INI*);};
void ScoredKillEvaAnnouncerController::iniParseScoredKillEvaAnnouncerBlock(INI *ini){
 AsciiString name(ini->getNextToken());
 for(_STL::vector<ParserRecord>::iterator i=g_scoredKillEvaRegistry->records.begin(),end=g_scoredKillEvaRegistry->records.end();i!=end;++i){
  if(i->name.compare(name)==0)throw INIException(3,"Duplicate ScoredKillEvaAnnouncer names %s",name.str());
 }
 ((_STL::vector<Rva00414BDBElement>*)&g_scoredKillEvaRegistry->records)->push_back((const Rva00414BDBElement &)Rva004147CF(name));
 ((Rva0041430D*)&g_scoredKillEvaRegistry->records.back())->rva0041430D(ini);
}
