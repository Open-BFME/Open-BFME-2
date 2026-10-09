// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// Native 412AF3..412B94 cdecl161B; called by rowed image draw412B94.
// Six (mode,name) pairs are read directly from retail C39814..C39844.
// GetParam4128F0 writes the canonical counted AsciiString; key is "_mode".
// The application mode names come from target data, not a donor inference.
#include "ascii_string.h"
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
struct AptImageMode {int mode;const char *name;};
static const AptImageMode imageModes[]={{0,"SOLID"},{1,"GRAYSCALE"},{2,"ALPHA"},{3,"ADDITIVE"},{4,"SOLID_GRAYSCALE"},{5,"SOLID_TEXTURE"}};
int Rva00412AF3(const char *parameters)
{
 AsciiString mode;
 if(Rva004128F0GetParam(parameters,"_mode",mode) && !mode.isEmpty()) {
  for(unsigned int i=0;i<6;++i)
   if(!_strcmpi(imageModes[i].name,mode.str()))return imageModes[i].mode;
  return 2;
 }
 return 2;
}
