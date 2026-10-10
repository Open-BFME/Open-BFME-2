// ?updateCache@MapCache@@QAEXXZ
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class FileSystem;
extern FileSystem *TheFileSystem;
class Rva003006C4 {public:bool rva003006C4(const AsciiString&);};
class Rva00300D7A {public:AsciiString rva00300D7A();};
void setFPMode();
class MapCache {public:void updateCache();bool loadUserMaps();void loadStandardMaps();private:void writeCacheINI(bool);};
void MapCache::updateCache(){setFPMode();((Rva003006C4*)TheFileSystem)->rva003006C4(((Rva00300D7A*)this)->rva00300D7A());if(loadUserMaps())writeCacheINI(true);loadStandardMaps();}
