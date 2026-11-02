// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/NameKeyGenerator.h"
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

class Rva0014921EVector;
// ICF-folded twin of Rva00149002Parse above (same 255 bytes at 0x00149002):
// the (int, int, vector *, int) spelling passes the same four words, so the
// body reuses every callee and home with identical codegen.
void rva00149002(int ini,int,Rva0014921EVector *keyStorage,int userData) {
 _STL::vector<NameKeyType> *keys=(_STL::vector<NameKeyType>*)keyStorage;
 bool unique=userData ? *(const bool*)userData : false;
 const char *token=((INI*)ini)->getNextTokenOrNull(0);
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
   token=((INI*)ini)->getNextTokenOrNull(0);
  } while(token);
 }
}

