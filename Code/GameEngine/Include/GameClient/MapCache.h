// Target facts: MapCache has no virtual functions, vptr or vftable. Constructor
// RVA 0x0022E28B calls the metadata-map constructor 0x0022E272 at +0, the
// seen-map constructor 0x0033C432 at +0x0C and set constructor 0x000D3A71 at
// +0x18 without storing a vptr. Destructor 0x0022E22E calls 0x000589BE at
// +0x18, 0x002076E7 at +0x0C and 0x0022E1F1 at +0, with no vptr stores.
// Both bodies load EH handler VA 0x00B6FA26 into EAX, not into the object.
// GameEngine::init pushes 0x24 at 0x0022FE81, calls new at 0x0022FE89,
// calls MapCache's constructor at 0x0022FE9C and stores TheMapCache at
// 0x0022FEAB: sizeof 0x24. Teardown 0x0023057C calls its destructor directly.
// findMap (0x003024BC) searches the +0 map and returns metadata at node+0x14.
// clearUnseenMaps reads the seen-map header at +0x0C (0x003046BA) and its
// one-byte value at node+0x14 (0x003046D4). Zero Hour MapUtil.h supplies the
// map base, m_seen and m_allowedMaps names and the AsciiString key types.
// Ledger methods are getMapExtension 0x003004A5, loadStandardMaps 0x003006E1,
// writeCacheINI 0x00303409, clearUnseenMaps 0x0030469E, addMap 0x00304E64,
// loadUserMaps 0x0030529C and updateCache 0x00305749. updateCache calls
// loadUserMaps at 0x00305785, writeCacheINI at 0x00305792 and loadStandardMaps
// at 0x00305799.
// Zero Hour MapUtil.h also declares getMapDir, getUserMapDir and the static
// m_mapCacheName; these names do not identify additional BFME2 ledger rows.

#pragma once
#ifndef BFME2_MAPCACHE_H
#define BFME2_MAPCACHE_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <map>
#include <set>

class MapMetaData;
struct FileInfo;

class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
    MapCache();
    ~MapCache();

    void updateCache();
    AsciiString getMapDir() const;
    AsciiString getUserMapDir() const;
    AsciiString getMapExtension() const;
    const MapMetaData *findMap(AsciiString mapName);
    void loadStandardMaps();
    bool loadUserMaps();
    bool addMap(AsciiString dirName, AsciiString fname, FileInfo *fileInfo, bool isOfficial);

private:
    bool clearUnseenMaps(AsciiString dirName);
    void writeCacheINI(bool userDir);

    static const char *m_mapCacheName;
    std::map<AsciiString, bool> m_seen;
    std::set<AsciiString> m_allowedMaps;
};

typedef char MapCacheRetailSize[(sizeof(MapCache) == 0x24) ? 1 : -1];

#endif
