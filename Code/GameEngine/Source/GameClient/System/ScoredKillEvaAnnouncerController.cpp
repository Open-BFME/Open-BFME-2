// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/iniexception
// Native00414F85..0041505A complete213B cdecl; WB12B53C0 independently
// names ScoredKillEvaAnnouncerController::iniParseScoredKillEvaAnnouncerBlock.
// Native reads registry10/14,48B records/name4, rejects duplicate names,
// appends a temporary and initializes the new last record from INI.
// ZH INIException/AsciiString behavior and STLport containers are semantic
// guides; no clean donor application body was available.
// Existing neutral constructor4148C0 and destructor414932 independently
// establish the48B temporary lifetime. The native cleanup calls the same
// physical object's rowed destructor directly; its neutral class name is
// shared with the constructor and deleting-destructor providers.
// Native absoluteE03074 establishes the registry role. Use the existing
// data_ledger canonical TheScoredKillEvaAnnouncerController symbol and class
// pointer spelling through an accessed-prefix view. COFF pointer extent4B
// and loader zero are verified; the next datum is not part of this pointer.
// stlport
#include "ascii_string.h"
#include "Common/INIException.h"
#include <vector>

#include "../../../Include/Common/INI/INI.h"
class Rva004147CF{public:Rva004147CF(const AsciiString&);virtual ~Rva004147CF();private:char data[44];};
struct Rva00414BDBElement{char data[48];};
namespace _STL{template<>void vector<Rva00414BDBElement>::push_back(const Rva00414BDBElement&);}
class Rva0041430D{public:void rva0041430D(INI*);};
struct ParserRecord{void *vtable;AsciiString name;char rest[40];};
struct ParserRegistry{char pad[0x10];_STL::vector<ParserRecord> records;};
class Rva0022C22CSubsystem;
Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController=0;
class ScoredKillEvaAnnouncerController{public:static void iniParseScoredKillEvaAnnouncerBlock(INI*);};
void ScoredKillEvaAnnouncerController::iniParseScoredKillEvaAnnouncerBlock(INI *ini){
 AsciiString name(ini->getNextToken());
 for(_STL::vector<ParserRecord>::iterator i=reinterpret_cast<ParserRegistry *>(TheScoredKillEvaAnnouncerController)->records.begin(),end=reinterpret_cast<ParserRegistry *>(TheScoredKillEvaAnnouncerController)->records.end();i!=end;++i){
  if(i->name.compare(name)==0)throw INIException(3,"Duplicate ScoredKillEvaAnnouncer names %s",name.str());
 }
 ((_STL::vector<Rva00414BDBElement>*)&reinterpret_cast<ParserRegistry *>(TheScoredKillEvaAnnouncerController)->records)->push_back((const Rva00414BDBElement &)Rva004147CF(name));
 ((Rva0041430D*)&reinterpret_cast<ParserRegistry *>(TheScoredKillEvaAnnouncerController)->records.back())->rva0041430D(ini);
}

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte link
// (retail .CRT$XCU 0x007B0010, node 0x00DC20B0; the node opens this unit's .data after the 36-byte
// header name lists and closes its .text$yc run before the pool-init marker 0x007B0025).
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theScoredKillEvaAnnouncerBlockParse( "ScoredKillEvaAnnouncer", ScoredKillEvaAnnouncerController::iniParseScoredKillEvaAnnouncerBlock );
