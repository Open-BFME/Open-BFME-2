// Target facts: MapMetaData has no bases, virtual functions or vftable. Its
// constructors (RVA 0x003031D3, 0x003039E8) and destructor (0x0022DBC6) store
// no vptr; 0x003031E9 zeroes the string handle at +0. The copy calls wide-string
// construction at +0, +4, +0xF8 and +0xFC, Region3D at +8, WaypointMap at
// +0x38, coordinate lists at +0x48/+0x4C, AsciiString at +0x50 and MapPlayers
// at +0x54. Assignment 0x0030328D copies six dwords at +8, an int at +0x20,
// three bytes at +0x24/+0x25/+0x26 and dwords at +0x28/+0x2C/+0x30/+0x34/+0xF4.
// MapPlayers copy 0x00303374 and destruction 0x0022DBF8 use eight 0x14-byte
// PlayerPosition records; copy 0x00302CE2 proves bytes +0/+1/+2, int +4 and a
// string set at +8. WaypointMap copy 0x00303359 and assignment 0x00302C9C
// prove its 0x0C-byte coordinate map and count at +0x0C. The final wide string
// occupies +0xFC..+0xFF. Allocation at 0x0057CFC0 pushes 0x100 and calls new
// at 0x0057CFC5 before constructing MapMetaData at 0x0057CFDA: sizeof 0x100.
// getDescription (0x003009CD) uses description +4, filename +0x50 and cache
// +0xFC; bfme_getBaseDisplayName (0x00300AEA) uses label +0 and cache +0xF8.
// bfme_getDisplayName (0x00300C7E), rva00300D0E (0x00300D0E) and
// bfme_getDescriptionFirstLine (0x00301534) are separate out-of-line bodies.
// Zero Hour MapUtil.h proves the shared field and WaypointMap count names;
// BFME2 INI reader 0x005350BA proves the added description and scenario flag.
// PlayerPosition default/copy/destructor/assignment are 0x00302805,
// 0x00302CE2, 0x0022D920 and 0x0030242A. MapPlayers default/copy/destructor/
// assignment are 0x00302C81, 0x00303374, 0x0022D9F3 and 0x00302CB7.
// The waypoint map, coordinate lists and player array occupy opaque storage
// of their proven extents; their constructors, copies and teardown stay in
// MapMetaData's out-of-line bodies.
// String class definitions must precede this header; their registered headers
// are supplied by consumers. No scoped string shim is included here.

#pragma once
#ifndef BFME2_MAPMETADATA_H
#define BFME2_MAPMETADATA_H

#include "../../../Libraries/Include/Lib/Region3D.h"

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class UnicodeString;
struct Coord3D;
struct Region3D;
class MapMetaData;

class MapMetaData
{
public:
    MapMetaData();
    MapMetaData(const MapMetaData &);
    ~MapMetaData();
    MapMetaData &operator=(const MapMetaData &);

    UnicodeString getDescription();
    UnicodeString bfme_getBaseDisplayName();
    UnicodeString bfme_getDisplayName(bool includePlayerCount);
    UnicodeString rva00300D0E();
    UnicodeString bfme_getDescriptionFirstLine();

    UnicodeString m_displayName;
    UnicodeString m_description;
    Region3D m_extent;
    int m_numPlayers;
    bool m_isMultiplayer;
    unsigned char m_isScenarioMP;
    bool m_isOfficial;
    unsigned int m_filesize;
    unsigned int m_CRC;
    unsigned int field30;
    unsigned int field34;
    unsigned char field38[0x10];
    unsigned char field48[4];
    unsigned char field4C[4];
    AsciiString m_fileName;
    unsigned char field54[0xA0];
    unsigned int fieldF4;
    UnicodeString m_cachedDisplayName;
    UnicodeString m_cachedDescription;
};

typedef char MapMetaDataRetailSize[(sizeof(MapMetaData) == 0x100) ? 1 : -1];

#endif
