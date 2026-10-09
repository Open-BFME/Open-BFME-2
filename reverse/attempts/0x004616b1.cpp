// ?parseLink@DynamicPortalBehaviourData@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9960317 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "ascii_string.h"
#include <cstdlib>
void Rva00030830GameFree(void*);
#define free Rva00030830GameFree
#include <vector>
#undef free
class INI {public: const char *getNextToken(const char *delimiters=0); const char *getNextSubToken(const char*); int scanInt(const char*);};
// Native Link owns a vector of signed32 indices. The target parser scans
// From, any Via entries, then To and copies the 12B owning record.
// long is the existing four-byte STL provider view; no original type name claim.
class DynamicPortalLink : public _STL::vector<long> {public: DynamicPortalLink(const _STL::allocator<long>&a) :_STL::vector<long>(a){} };
template<>void _STL::vector<long>::push_back(const long&);
template<>void _STL::vector<DynamicPortalLink>::push_back(const DynamicPortalLink&);
class DynamicPortalBehaviourData {public:static void parseLink(INI*,void*,void*,const void*);};
void DynamicPortalBehaviourData::parseLink(INI *ini,void*,void *store,const void*) {
 _STL::allocator<long> allocator;
 DynamicPortalLink link(allocator);
 link.push_back(ini->scanInt(ini->getNextSubToken("From")));
 AsciiString token(ini->getNextToken(":"));
 while(token.compare("Via")==0){
  link.push_back(ini->scanInt(ini->getNextToken()));
  token=ini->getNextToken(":");
 }
 link.push_back(ini->scanInt(ini->getNextToken(":")));
 static_cast<_STL::vector<DynamicPortalLink>*>(store)->push_back(link);
}
