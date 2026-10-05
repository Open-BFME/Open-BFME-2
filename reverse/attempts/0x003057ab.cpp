// ?isValidMap@@YA_NVAsciiString@@_N@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ZH MapUtil isValidMap; native3057AB..30582D; record size100 proved
// by metadata copy3039E8. Native flag node38 minus record node14 is24.
#include <map>
#include "ascii_string.h"
class MapMetaData {
public: char unknown00[0x24]; bool m_isMultiplayer;char unknown25[0x100-0x25];
};
class MapCache:public _STL::map<AsciiString,MapMetaData> {
public:void updateCache();
};
extern MapCache *TheMapCache;
bool isValidMap(AsciiString mapName,bool isMultiplayer) {
 if(!TheMapCache||mapName.isEmpty())return false;
 TheMapCache->updateCache();
 mapName.toLower();
 MapCache::iterator it=TheMapCache->find(mapName);
 if(it!=TheMapCache->end()) {
  if(isMultiplayer==it->second.m_isMultiplayer)return true;
 }
 return false;
}
