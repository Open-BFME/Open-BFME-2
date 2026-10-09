// ?rva00149002@@YAXPAVINI@@PAXPAV?$vector@W4NameKeyType@@V?$allocator@W4NameKeyType@@@_STL@@@_STL@@PBX@Z
// partial score=0.96 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Target149002..149101 RET0 and WB728720 identify NameKey list parser.
// ZH NameKeyGenerator scalar parser supplies name-key semantics; target and
// WB supply list/macro preprocessing and optional uniqueness behavior.
#include <vector>
#include <algorithm>
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class INI { public: const char *getNextTokenOrNull(const char *);static const char *preprocessMacro(const char *); };
class NameKeyGenerator {public: NameKeyType nameToKey(const AsciiString&);NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
unsigned char containsNameKey(_STL::vector<NameKeyType> *,NameKeyType);
const char *rva0002D145(const char*);
void rva00149002(INI *ini,void *,_STL::vector<NameKeyType> *keys,const void *userData) {
 bool unique=userData ? *(const bool*)userData : false;
 const char *token=ini->getNextTokenOrNull(0);
 if(token) {
  do {
   const char *expanded=rva0002D145(token);
   if(expanded!=token) {
    AsciiString text(expanded);AsciiString item;
    while(text.nextToken(&item,0)) {
     NameKeyType key=TheNameKeyGenerator->nameToKey(item);
     if(!unique || !containsNameKey(keys,key))keys->push_back(key);
    }
   } else {
    NameKeyType key=TheNameKeyGenerator->nameToKey(token);
    if(!unique || !containsNameKey(keys,key))keys->push_back(key);
   }
   token=ini->getNextTokenOrNull(0);
  } while(token);
 }
}

__declspec(noinline) const char *rva0002D145(const char *token) { return INI::preprocessMacro(token); }
