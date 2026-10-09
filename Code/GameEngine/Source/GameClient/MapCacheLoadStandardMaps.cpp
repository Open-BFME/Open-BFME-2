// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Ob2 /EHs /MD /D_CRTIMP=
// BF1/ZH MapCache::loadStandardMaps semantic lead; native3006E1..3007A2
// constructs INI87CB, formats Maps\\MapCache.ini and loads parser5350BA.
#include "ascii_string.h"
class Xfer;
enum INILoadType {INI_LOAD_INVALID,INI_LOAD_OVERWRITE,INI_LOAD_CREATE_OVERRIDES,INI_LOAD_MULTIFILE};
class INI {public:INI();~INI();void load(AsciiString,INILoadType,Xfer*,void(*)(INI*));static void parseMapCacheDefinition(INI*);private:char bytes[0x87C];};
class Rva00300489 {public:virtual AsciiString rva00300489()const;};
class MapCache {public:void loadStandardMaps();};
void MapCache::loadStandardMaps()
{
 INI ini;AsciiString fname;
 fname.format("%s\\%s",reinterpret_cast<const Rva00300489*>(this)->Rva00300489::rva00300489().str(),"MapCache.ini");
 try {ini.load(fname,INI_LOAD_OVERWRITE,0,INI::parseMapCacheDefinition);}
 catch(...) {}
}
