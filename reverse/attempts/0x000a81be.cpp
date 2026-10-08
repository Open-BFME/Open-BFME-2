// ?freeUnusedSamples@AudioFileCache@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <set>
#include "ascii_string.h"
struct TreeKey00242F5E { unsigned int id; AsciiString name; };
typedef _STL::_Rb_tree<TreeKey00242F5E,TreeKey00242F5E,_STL::_Identity<TreeKey00242F5E>,_STL::less<TreeKey00242F5E>,_STL::allocator<TreeKey00242F5E> > UnusedTree;
class Rva00056F61 { public: void *rva00056F61(const AsciiString*); };
struct Rva000A80A8Item { char prefix[0x30]; unsigned int amount; };
struct CacheLookupNode { void *next; AsciiString name; Rva000A80A8Item *file; };
class Rva000A7E9E { public: void rva000A80A8(Rva000A80A8Item*,int); };
class AudioFileCache {
public: void freeUnusedSamples();
 char prefix[0x20]; UnusedTree unused; char gap[0xC]; unsigned int usedBytes,unusedBytes,limit;
};
void AudioFileCache::freeUnusedSamples() {
 while(usedBytes>limit) {
  if(unused.empty()) break;
  UnusedTree::iterator first=unused.begin();
  AsciiString name=first->name;
  unused.erase(first);
  CacheLookupNode *found=(CacheLookupNode*)((Rva00056F61*)this)->rva00056F61(&name);
  if(found) {
   unusedBytes-=found->file->amount;
   ((Rva000A7E9E*)this)->rva000A80A8(found->file,1);
  }
 }
}
