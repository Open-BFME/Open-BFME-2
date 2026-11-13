// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class FileSystem;
extern FileSystem *TheFileSystem;
#include "../../Include/GameClient/Rva003006C4.h"
#include "../../Include/Common/Rva00300D7A.h"
void setFPMode();
#include "../../Include/GameClient/MapCache.h"
// BF1 MapCache.cpp supplies the update sequence; the native caller at
// 0x3057AB names this method. Its 0x305749..0x3057AB body calls the owned
// directory lookup and map loaders with a private writeCacheINI member.
void MapCache::updateCache()
{
    setFPMode();
    ((Rva003006C4 *)TheFileSystem)->rva003006C4(((Rva00300D7A *)this)->rva00300D7A());
    if (loadUserMaps())
        writeCacheINI(true);
    loadStandardMaps();
}
