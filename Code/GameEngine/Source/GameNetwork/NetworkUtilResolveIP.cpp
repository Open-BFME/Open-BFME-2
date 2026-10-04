// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME1 donor: game/GameEngine/Source/GameNetwork/NetworkUtilResolveIP.cpp,
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24; unchanged at verified 6583b3c1.
// Target facts: complete 155B entry 0x00581339, four direct caller sites,
// cdecl return/one-pointer AsciiString by-value ABI, EH cleanup via the matched
// StringBase<char>::releaseBuffer 0x36410. Native accesses length at header+4,
// signed first character at header+8, and strings through the canonical view.
// IAT slots BBA544/BBA974/BBA978/BBA9A4 establish isdigit/inet_addr/
// gethostbyname/htonl; therefore the host/address resolver role is independent
// of donor naming. ResolveIP is donor spelling and an existing caller pin,
// rather than a newly proven original target name. Keep an address-qualified
// provider and a weak alias for existing callers. No class/header changes.
struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

struct in_addr
{
	unsigned long s_addr;
};

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) unsigned long __stdcall inet_addr(const char *cp);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long netlong);
extern "C" __declspec(dllimport) struct hostent * __stdcall gethostbyname(const char *name);

typedef unsigned int UnsignedInt;

#include "ascii_string.h"
#pragma intrinsic(memcpy)
// The canonical object contains one pointer. Copy its representation without
// redefining StringBase::getCharAt; that out-of-line copy has different codegen.
// Native returns a signed first character from header+8, or zero for null.
// ?rva00581339FirstChar present-unmatched
static __forceinline char rva00581339FirstChar(const AsciiString &host) {
    const char *header;
    memcpy(&header, &host, sizeof(header));
    return header ? header[8] : 0;
}

// Resolve a numeric address or host name to the native host-order IP value.
UnsignedInt rva00581339ResolveIP(AsciiString host)
{
  struct hostent *hostStruct;
  struct in_addr *hostNode;

  if (host.getLength() == 0)
  {
	  return 0;
  }

  // String such as "127.0.0.1"
  if (isdigit(rva00581339FirstChar(host)))
  {
    return ( htonl(inet_addr(host.str())) );
  }

  // String such as "localhost"
  hostStruct = gethostbyname(host.str());
  if (hostStruct == 0)
  {
	  return 0;
  }
  hostNode = (struct in_addr *) hostStruct->h_addr_list[0];
  return ( htonl(hostNode->s_addr) );
}

#pragma comment(linker,"/alternatename:?ResolveIP@@YAIVAsciiString@@@Z=?rva00581339ResolveIP@@YAIVAsciiString@@@Z")
