// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Native 0x149002..0x149101 and WB 0x728720 establish the NameKey list
// parser, its optional uniqueness flag, macro splitting and cleanup lifetimes.
// A local copy of the incoming list makes its argument home available for
// the item string, matching native storage reuse without explicit stack access.
// Donor guides: ZH scalar NameKey parser and BFME1 INIPreprocessMacro at
// committed 575ba2b04; the list extension is established by target evidence.
// ZH NameKeyGenerator scalar parser supplies name-key semantics; target and
// WB supply list/macro preprocessing and optional uniqueness behavior.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class INI { public: const char *getNextTokenOrNull(const char *); };
class NameKeyGenerator {public: NameKeyType nameToKey(const AsciiString&);NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
// The existing 31-byte search provider compares four-byte values only.
// Its historical pointer spelling does not claim that NameKeys are pointers.
struct Rva00148AC4Range;
class CreateAHeroData;
unsigned char Rva00148AC4Contains(Rva00148AC4Range *, CreateAHeroData *);
const char *rva0002D145(const char*);
void Rva00149002Parse(INI *ini,void *,void *keyStorage,const void *userData) {
 _STL::vector<NameKeyType> *keys=(_STL::vector<NameKeyType>*)keyStorage;
 bool unique=userData ? *(const bool*)userData : false;
 const char *token=ini->getNextTokenOrNull(0);
 if(token) {
  do {
   const char *expanded=rva0002D145(token);
   if(expanded!=token) {
    AsciiString text(expanded);AsciiString item;
    while(text.nextToken(&item,0)) {
     NameKeyType key=TheNameKeyGenerator->nameToKey(item);
     if(!unique || !Rva00148AC4Contains(reinterpret_cast<Rva00148AC4Range *>(keys), reinterpret_cast<CreateAHeroData *>(key)))keys->push_back(key);
    }
   } else {
    NameKeyType key=TheNameKeyGenerator->nameToKey(token);
    if(!unique || !Rva00148AC4Contains(reinterpret_cast<Rva00148AC4Range *>(keys), reinterpret_cast<CreateAHeroData *>(key)))keys->push_back(key);
   }
   token=ini->getNextTokenOrNull(0);
  } while(token);
 }
}

