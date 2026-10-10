// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "ascii_string.h"
#include <cstdlib>
void Rva00030830GameFree(void*);
#define free Rva00030830GameFree
#include <vector>
#undef free
class INI {public: const char *getNextToken(const char *delimiters=0); const char *getNextSubToken(const char*); int scanInt(const char*);};
// Retail 0x004616B1 (252 B, cdecl): the Link line parser of DynamicPortalBehaviour's
// module data. The target vector is read from the argument before the link is built
// (the empty allocator temporary then takes a byte of the dead argument slot).
// Native Link owns a vector of signed32 indices. The target parser scans
// From, any Via entries, then To and copies the 12B owning record.
// long is the existing four-byte STL provider view; no original type name claim.
class DynamicPortalLink : public _STL::vector<long> {public: DynamicPortalLink(const _STL::allocator<long>&a) :_STL::vector<long>(a){} };
template<>void _STL::vector<long>::push_back(const long&);
template<>void _STL::vector<DynamicPortalLink>::push_back(const DynamicPortalLink&);
class DynamicPortalBehaviourData {public:static void parseLink(INI*,void*,void*,const void*);};
void DynamicPortalBehaviourData::parseLink(INI *ini,void*,void *store,const void*) {
 _STL::vector<DynamicPortalLink> *links = static_cast<_STL::vector<DynamicPortalLink>*>(store);
 DynamicPortalLink link((_STL::allocator<long>()));
 link.push_back(ini->scanInt(ini->getNextSubToken("From")));
 AsciiString token(ini->getNextToken(":"));
 while(token.compare("Via")==0){
  link.push_back(ini->scanInt(ini->getNextToken()));
  token=ini->getNextToken(":");
 }
 link.push_back(ini->scanInt(ini->getNextToken(":")));
 links->push_back(link);
}
