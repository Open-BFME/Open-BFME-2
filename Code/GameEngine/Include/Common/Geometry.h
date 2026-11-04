// Target facts (addresses are retail RVAs unless marked VA): GeometryInfo is polymorphic, with a Snapshot base at +0 and sizeof 0x5C.
// Constructors 0x00050B74, 0x000929E8 and 0x0029840D install VA 0x00BC4E94; destructor 0x00050B2A destroys members +0x38/+0x2C then restores Snapshot's VA 0x00BBB554 at 0x00050B59.
// VA 0x00BC4E94 has four slots: deleting destructor 0x00050C31, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x00050C2B and DoXfer(Xfer&) 0x006C0030. The following word begins the class-name string.
// parseGeometryOther copies through 0x000929E8 at 0x006C0360 and advances its GeometryInfo vector by 0x5C at 0x006C0368; constructor stores at 0x00050C08 reach +0x58.
// parseGeometryIsSmall 0x006BE9EA writes the byte +4; constructor 0x00050BC4/0x00050BCC clears four-byte fields +8/+0x0C. calcBoundingStuff 0x006BE700 computes radii +0x10/+0x14, centre +0x18/+0x1C/+0x20 and extents +0x24/+0x28.
// Copy constructor 0x000929E8 copies +4, four-byte fields +8..+0x28 and +0x44..+0x58, and calls vector copy providers 0x0009292B/0x0009298B for +0x2C/+0x38. Vector storage stays opaque here; the rowed lifetime methods own it.
// DoXfer 0x006C0030 transfers the +4 flag, shape vector +0x2C (stride 0x24), radii/extents and triples +0x18/+0x44/+0x50. Constructor 0x00050BEF..0x00050C08 initializes the six tail floats.
// The method declarations below use the ledger's signatures; Zero Hour Common/Geometry.h supplies the GeometryType enumerators and the getIsSmall/getBoundingCircleRadius/getBoundingSphereRadius accessor names. Retail 0x006BFF50 tests BOX=2; parseGeometryType 0x006BFEE0 uses the SPHERE/CYLINDER/BOX name table.
// Nonvirtual rows: set 0x006BFF50, height above/below 0x006BD7C0/0x006BD8A0, calcPitches 0x006BE4C0, line-segment test 0x006BD780, expandFootprint 0x006BEB40, CollidesWith 0x006BEB80, getBestContactPoint 0x006BEF80, rva006BD830 0x006BD830, rva006BD9C0 0x006BD9C0, rva0087E650 0x006BDEE0, radius setters 0x004BBA15/0x004BBA3D and private calcBoundingStuff 0x006BE700.
// Parser rows: type 0x006BFEE0, isSmall 0x006BE9D0, height 0x006BEA00, major/minor 0x006BEA60/0x006BEAB0, active 0x006BD590, offset 0x006BD610, health-box flag 0x006BD5D0 and other 0x006C01B0. The type-name table is VA 0x00DDBFE0 (pushed at 0x006BFEE7).

#pragma once
#ifndef __BFME2_GEOMETRY_H_
#define __BFME2_GEOMETRY_H_

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

struct Coord3D;
struct GeometryShape;
struct Rva0087E650Bounds;
class INI;

enum GeometryType
{
    GEOMETRY_SPHERE = 0,
    GEOMETRY_CYLINDER = 1,
    GEOMETRY_BOX = 2,
    GEOMETRY_NUM_TYPES = 3,
    GEOMETRY_FIRST = GEOMETRY_SPHERE
};

class GeometryInfo : public Snapshot
{
public:
    GeometryInfo();
    GeometryInfo(GeometryType type, bool isSmall, float height, float majorRadius, float minorRadius);
    GeometryInfo(const GeometryInfo &other);
    virtual ~GeometryInfo();
    // Slots 1 to 3 take the spelling of the unit's Snapshot selection, as Snapshot.h does; the default is the ledger's.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#if defined(BFME_SNAPSHOT_NAME_SLOT) && defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT)
    virtual const char *GetSnapshotName();
#elif defined(BFME_SNAPSHOT_NAME_SLOT)
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) && defined(BFME_SNAPSHOT_REFERENCE_XFER)
    virtual void DoXfer(Xfer &xfer);
#elif defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS)
    virtual void DoXfer(Xfer *xfer);
#else
    virtual void xfer(Xfer *xfer);
#endif

    void set(GeometryType type, bool isSmall, float height, float majorRadius, float minorRadius);
    float getMaxHeightAbovePosition() const;
    float getMaxHeightBelowPosition() const;
    float rva006BD830() const;
    void calcPitches(const Coord3D &thisPos, const GeometryInfo &that, const Coord3D &thatPos, float &minPitch, float &maxPitch) const;
    bool isIntersectedByLineSegment(const Coord3D &loc, const Coord3D &from, const Coord3D &to) const;
    void expandFootprint(float radius);
    bool CollidesWith(const Coord3D &pos, float angle, const GeometryInfo &other, const Coord3D &otherPos, float otherAngle) const;
    bool getBestContactPoint(Coord3D *out, const Coord3D *pos, const char *label, int first, int second, bool flag) const;
    void rva006BD9C0(GeometryShape &out) const;
    void rva0087E650(Rva0087E650Bounds *bounds);
    void rva004BBA15(float value);
    void rva004BBA3D(float value);

    bool getIsSmall() const { return m_isSmall; }
    float getBoundingCircleRadius() const { return m_boundingCircleRadius; }
    float getBoundingSphereRadius() const { return m_boundingSphereRadius; }

    static void parseGeometryType(INI *, void *, void *, const void *);
    static void parseGeometryIsSmall(INI *, void *, void *, const void *);
    static void parseGeometryHeight(INI *, void *, void *, const void *);
    static void parseGeometryMajorRadius(INI *, void *, void *, const void *);
    static void parseGeometryMinorRadius(INI *, void *, void *, const void *);
    static void parseGeometryActive(INI *, void *, void *, const void *);
    static void parseGeometryOffset(INI *, void *, void *, const void *);
    static void parseGeometryUsedForHealthBox(INI *, void *, void *, const void *);
    static void parseGeometryOther(INI *, void *, void *, const void *);

    bool m_isSmall;
    float field08;
    float field0c;
    float m_boundingCircleRadius;
    float m_boundingSphereRadius;
    float field18;
    float field1c;
    float field20;
    float field24;
    float field28;
    void *field2c[3];
    void *field38[3];
    float field44;
    float field48;
    float field4c;
    float field50;
    float field54;
    float field58;

private:
    void calcBoundingStuff();
};

typedef char GeometryInfo_size_check[sizeof(GeometryInfo) == 0x5C ? 1 : -1];

#endif
