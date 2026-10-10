// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Semantic donor: Open-BFME-1 575ba2b04, SubsystemLegend.cpp parseLoadSubsystem.
// Target1B4D7F..1B4E07 proves the complete136B RET4 member body. The native
// LoadSubsystem table and canonical TheSubsystemLegend global corroborate its
// purpose; the method name is carried from the donor. BFME2 adds two vector
// fields and moves loader/debug fields to40/44. Table7D7710 and constructors
// 1B4B92/1B4A39 establish the72B record independently of donor's48B record.
// Existing record/list providers keep their address-derived ABI names.
#include <vector>
#include <list>
#include <stddef.h>
#include "ascii_string.h"
class INI;
typedef void (*INIFieldParseProc)(INI*,void*,void*,const void*);
struct FieldParse {const char *token;INIFieldParseProc parse;const void *userData;int offset;};
class INI {public:
 const char *getNextToken(const char*);
 void initFromINI(void*,const FieldParse*);
 static void parseAsciiStringVectorAppend(INI*,void*,void*,const void*);
 static void parseLookupList(INI*,void*,void*,const void*);
 static void parseAsciiString(INI*,void*,void*,const void*);
};
struct BfmeVectorRecord001B4A39 {
 AsciiString text0;_STL::vector<AsciiString> names0,names1,names2,names3,names4;
 unsigned word40;AsciiString text1;
 BfmeVectorRecord001B4A39();~BfmeVectorRecord001B4A39();
};
struct BfmePod72 {int a[18];};
namespace _STL {template<>void list<BfmePod72>::push_back(const BfmePod72&);}
class SubsystemLegend {public:
 void parseLoadSubsystem(INI*);
 char prefix[12];_STL::list<BfmePod72> entries;
};
extern SubsystemLegend *TheSubsystemLegend;
struct LookupListRec {const char *name;int value;};
// The native lookup record contains pointer("STR") in the value word.
// Preserve those observed bytes and donor transcription, without interpreting
// that word as a normal loader enumeration value.
static const LookupListRec TheSubsystemLegendLoaderNames[]={{"INI",(int)"STR"},{0,0}};
const FieldParse TheSubsystemLegendFieldParse[]={
 {"InitFile",INI::parseAsciiStringVectorAppend,0,4},
 {"InitPath",INI::parseAsciiStringVectorAppend,0,0x10},
 {"Extension",INI::parseAsciiStringVectorAppend,0,0x1c},
 {"Loader",INI::parseLookupList,TheSubsystemLegendLoaderNames,0x40},
 {"ExcludePath",INI::parseAsciiStringVectorAppend,0,0x34},
 {"IncludePathCinematics",INI::parseAsciiStringVectorAppend,0,0x28},
 {"InitFileDebug",INI::parseAsciiString,0,0x44},
 {0,0,0,0}
};
void SubsystemLegend::parseLoadSubsystem(INI *ini){
 AsciiString name(ini->getNextToken(0));
 BfmeVectorRecord001B4A39 entry;
 entry.text0=name;
 ini->initFromINI(&entry,TheSubsystemLegendFieldParse);
 if(TheSubsystemLegend)TheSubsystemLegend->entries.push_back(reinterpret_cast<const BfmePod72&>(entry));
}

// Native1B4E07..1B4E1B20B follows the parser's RET4 and ends in RET0.
// Its registration node DB7034 names LoadSubsystem and points to this entry.
// The caller is a free cdecl INI block parser; donor name is retained.
void parseSubsystemLegendDefinition(INI *ini){
 if(TheSubsystemLegend)TheSubsystemLegend->parseLoadSubsystem(ini);
}
