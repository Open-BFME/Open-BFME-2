// Target facts: constructors RVA 0x00282212/0x002823D1 store VA 0x00BFB21C at +0 (sites 0x00282239/0x002823E2); destructor 0x00282500 restores it at 0x00282511. The table has only slot 0, deleting destructor 0x00282B9F; VA 0x00BFB220 starts the string "WaypointsList". xfer 0x0027F5F7 is nonvirtual. Zero Hour TerrainLogic.h supplies MemoryPoolObject inheritance and the named common fields/accessors; its four-byte destructor-only parent agrees with retail.
// Target facts: allocation 0x00461086 pushes 0xC0, calls operator new at 0x00461090 and constructs Waypoint at 0x00461109; 0x002839BC independently allocates 0xC0. Constructor 0x00282212 stores id +4, copies string +8 and position +0xC/+0x10/+0x14, links prev/next +0x18/+0x1C, zeroes eight pointers +0x20..+0x3F and source +0x40, stores pointer +0x44, byte +0x48, count +0x4C, strings +0x50/+0x54/+0x58/+0x64, byte +0x5C and integer +0x60. Stores 0x00282268/0x0028243D prove +0x48 is one byte. The string members require AsciiString to be complete before this header.
// Target facts: constructors call 0x0024C7B3 for 0x1C-byte members +0x6C/+0x8C and 0x003623E5 for four-byte member +0xBC; destructor calls 0x00360D26 for +0xBC and 0x00036410 for the five strings. Constructor/xfer 0x0027F5F7 prove bytes +0x68/+0x88/+0xA8/+0xA9/+0xB8, dwords +0xAC/+0xB0/+0xB4. getLink 0x00085404 bounds eight entries at +0x20; addLink 0x00272306 updates +0x4C and other->+0x40. Ledger rows also prove isValidUnitType 0x00281AED, rva0027C313/0x0027C330 and the two constructors/destructor. Retail calls to getPathLabel1 0x0027F5A6 use a by-value string at +0x50. Lookup 0x00281D6A passes the name at +8 directly to compare without a string copy, supporting the reference-returning name accessor; 0x00281D76 advances the list pointer at +0x1C. Unknown fields retain offset names.
#pragma once
#ifndef BFME2_WAYPOINT_H
#define BFME2_WAYPOINT_H

#include "../Common/MemoryPoolObject.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class MemoryPoolObject;
class AsciiString;
struct Coord3D;
class Object;
class Xfer;
class Waypoint;

class Waypoint : public MemoryPoolObject
{
public:
    Waypoint();
    Waypoint(unsigned int id, AsciiString name, const Coord3D *location,
        AsciiString label1, AsciiString label2, AsciiString label3,
        bool biDirectional, int field60, AsciiString field64);
    virtual ~Waypoint();

    enum { MAX_LINKS = 8 };
    Waypoint *getLink(int index) const;
    void addLink(Waypoint *other);
    bool isValidUnitType(Object *object);
    void xfer(Xfer *xfer);
    Waypoint *rva0027C313(int id);
    void rva0027C330();
    AsciiString getPathLabel1() const;

    unsigned int getID() const { return m_id; }
    const AsciiString &getName() const { return m_name; }
    const Coord3D *getLocation() const { return &m_location; }
    Coord3D *getLocation() { return &m_location; }
    Waypoint *getNext() const { return m_pNext; }
    int getNumLinks() const { return m_numLinks; }
    bool getBiDirectional() const { return m_biDirectional; }
    void setLocationZ(float z) { m_location.z = z; }

    unsigned int m_id;
    AsciiString m_name;
    Coord3D m_location;
    Waypoint *m_field18;
    Waypoint *m_pNext;
    Waypoint *m_links[MAX_LINKS];
    Waypoint *m_field40;
    Waypoint *m_field44;
    bool m_field48;
    int m_numLinks;
    AsciiString m_pathLabel1;
    AsciiString m_pathLabel2;
    AsciiString m_pathLabel3;
    bool m_biDirectional;
    int m_field60;
    AsciiString m_field64;
    bool m_field68;
    unsigned int m_field6C[7];
    bool m_field88;
    unsigned int m_field8C[7];
    bool m_fieldA8;
    bool m_fieldA9;
    int m_fieldAC;
    unsigned int m_fieldB0;
    unsigned int m_fieldB4;
    bool m_fieldB8;
    unsigned int m_fieldBC;
};

#endif
