// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/ini
// stlport
// Target reconstruction: Ghidra [0x00424185,0x00424307), 386 bytes.
// Registration writes at 0x00425C91/98 pair "FormationSelection" with this
// callback. Original C++ owner/name are unknown; the name below is descriptive.
// Registration is a four-argument FieldParse callback; only INI* is consumed.
// Target literals establish purpose, field labels and +4/+8 offsets. Native
// callees establish quoted string, filename, line, name-key and INI parsing.
// BFME1/ZH source searches found no corresponding formation-selection parser.
// The 12-byte appended record is int template index / float limit / int count,
// independently observed in the native local stores; no original type claimed.
// Append is the complete rowed 41-byte STLport 12-byte-record push_back body
// at 0x00423BFD, independently byte-verified. Its call-only view avoids emitting
// a second family of allocator/template definitions for an unknown original type.
#include "ascii_string.h"
#include <map>
#include <float.h>
#include "Common/INIException.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class INI;
typedef void (*Parser)(INI*,void*,void*,const void*);
struct FieldParse {const char* name;Parser parse;const void* data;unsigned offset;};
class INI {public:
 AsciiString getNextQuotedAsciiString();
 AsciiString getFilename()const;
 int getLineNum()const;
 void initFromINI(void*,const FieldParse*);
 static void parseReal(INI*,void*,void*,const void*);
 static void parseInt(INI*,void*,void*,const void*);
};
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};
extern NameKeyGenerator* TheNameKeyGenerator;
struct Rva00424185Criteria {int templateIndex;float maxDragLength;int maxUnitsSelected;};
class Rva00424185Deque {public:void append(const Rva00424185Criteria&);};
// Native map header and deque storage occupy zero-filled .bss here. These
// address-derived names describe storage, not the original global identities.
// The map's 12-byte view agrees with the rowed lookup at 0x00422D1C;
// the 40-byte deque layout comes from its independently recovered STLport bodies.
unsigned int g_Va00E0319C[3];
unsigned int g_Va00E031A8[10];
#define criteriaTemplates (*reinterpret_cast<_STL::map<int,int>*>(g_Va00E0319C))
#define criteriaEntries (*reinterpret_cast<Rva00424185Deque*>(g_Va00E031A8))
void parseFormationSelectionCriteriaRva00424185(INI* ini,void*,void*,const void*) {
 AsciiString name=ini->getNextQuotedAsciiString();
 if(name.isEmpty())throw INIException(3,"Must specify name of formation template for selection criteria at %s:%d",ini->getFilename().str(),ini->getLineNum());
 int key=TheNameKeyGenerator->nameToKey(name);
 _STL::map<int,int>::iterator it=criteriaTemplates.find(key);
 if(it==criteriaTemplates.end())throw INIException(3,"Invalid formation template name : %s at %s:%d",name.str(),ini->getFilename().str(),ini->getLineNum());
 // Native 0x00424278/283 initialize only index and length. The third word
 // is written by the MaxUnitsSelected parser and has no retail default.
 struct Limits {int index;float length;int count;} limits; limits.index=it->second; limits.length=FLT_MAX;
 FieldParse fields[]={
 {"MaxDragLength",INI::parseReal,0,4},
 {"MaxUnitsSelected",INI::parseInt,0,8},
 {0,0,0,0}};
 ini->initFromINI(&limits,fields);
 Rva00424185Criteria entry={limits.index,limits.length,limits.count};
 criteriaEntries.append(entry);
}

#pragma comment(linker, "/alternatename:?append@Rva00424185Deque@@QAEXABURva00424185Criteria@@@Z=?push_back@?$deque@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAEXABUBfmeE12@@@Z")
