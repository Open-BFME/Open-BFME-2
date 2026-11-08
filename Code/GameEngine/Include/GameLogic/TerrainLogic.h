/* Target facts (code addresses are RVAs, tables are VAs): constructor 0x00283FAA stores Snapshot's 0x00BBB554 at +0, calls SubsystemInterface's 0x001B4E63 on +4 at 0x00283FCE, and stores listener root 0x00BC6F34 at +0x10/+0x14. Its final stores 0x00283FE8..0x00283FFB select 0x00BFB2C8/+0, 0x00BFB28C/+4, 0x00BC5848/+0x10 and 0x00BC5838/+0x14. Destructor 0x0028418A installs those same four tables at 0x002841A0..0x002841B3, then restores the listener roots at 0x00284261/0x0028426B, calls parent destructor 0x001B4E74 at 0x00284276, and restores Snapshot at 0x0028427F. These are successive base lifetimes, not competing TerrainLogic layouts. Deleting destructor 0x00285177 calls 0x0028418A; secondary thunk 0x00284182 subtracts four. TerrainLogic is polymorphic. Its constructor writes through +0x1918; W3DTerrainLogic constructor 0x00062A7E calls it and adds floats at +0x191C/+0x1920, establishing the 0x191C base extent. The derived allocation pushes 0x1924 at 0x00041FDA, calls operator new at 0x00041FDF and calls 0x00062A7E at 0x00041FF3.
   Primary table 0x00BFB2C8 has 51 slots, ending before the TerrainLogic string at 0x00BFB394: 0=285177, 1=2820A0, 2=28417C, 3=283845, 4=282BBB, 5=284290, 6=27CE9A, 7=27CEBC, 8-12/15/16/50=03B810 purecall, 13=27D5E0, 14=27D6DF, 17=062E72, 18=2811DD, 19=27D77D, 20-24=50B5F1, 25=27D815, 26/27=062ACA, 28/29=062AEC, 30=27D85B, 31=282E20, 32=27D88E, 33=062AC4, 34=281D4C, 35=28333F, 36=2812BF, 37=2813EA, 38=281D92, 39=281E47, 40=5C4AF5, 41=27F30A, 42=27F337, 43=2804B2, 44=2805C1, 45=281ECA, 46=280294, 47=28125C, 48=281F7F, 49=281EA5. Secondary 0x00BFB28C has the parent's fourteen slots: overrides 0=284182, 1=0B3FD0, 9=283567, 10=27CD63; slots 2-8/11-13 equal parent table 0x00BD77A0. Listener tables have four slots and no virtual destructor: 0=47A69C, 1=283C0F/283C40, 2=50B238, 3=2833A3/2833C5. Equal folded root tables do not prove identity with another registered observer class.
   Fields: constructor 0x00284002..0x00284126 proves +18/+1C/+20 and +24/+28/+2C words, +30 three-word vector, +3C/+40 words, +44 byte, +48 word, +4C string, +50/+54/+58/+5C pointers, +60 byte, +64 list pointer, +68 sixty-four 20-byte water records, +568 count, +56C map, +578 three-word vector, +584 pointer, +588 1250 dwords filled with -1, +1910 word, +1914 byte and +1918 float. Destructor 0x002841C6..0x00284260 proves pointer ownership and container/string teardown. getSourceFilename 0x00062E72 copies +4C; getPartitionBucket 0x0027D0D6 and xfer 0x00283845 access +588 as 2500 shorts. Zero Hour's TerrainLogic.h supplies established terrain/waypoint/bridge method names and water-record field names; unknown methods and storage retain ordinal/offset names. Named out-of-line declarations follow reverse/functions.csv: 27D1A4, 27D40B, 27D447, 27F009, 27D0D6, 27F28E, 2803F9, 2825AE, 283E9C, 27D5AD, 27D483, 2802FE, 27D3D9, 280176, 28077A, 2817F2, 282CFB, 283262, 283642, 283CE7, 28449F, 285193, 28458F, 283D70, 2814EF, 284DD2, 27FFF3 and static 2811CA. Lifetimes and all rowed members are declared out of line. */
#ifndef BFME2_TERRAINLOGIC_H
#define BFME2_TERRAINLOGIC_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Region3D;
struct DataChunkInfo;
struct TBridgeAttackInfo;
class Bridge;
class ChunkInputStream;
class DataChunkInput;
class Dict;
class GeometryInfo;
class MapObject;
class Matrix3D;
class Object;
class PolygonTrigger;
class Rva0027C36A;
#ifdef _STLP_INTERNAL_VECTOR_H
class Rva0027D098;
struct ICoord2D;
#endif
class BfmeT1035;
class ThingTemplate;
class Vector3;
class WaterHandle;
class Waypoint;
enum PathfindLayerEnum;

class TerrainLogicListenerRootA {
public:
    virtual void vslot0(int);
    virtual void vslot1(int, WaterHandle *);
    virtual void vslot2(void *, void *);
    virtual void vslot3(void *, void *);
};

class TerrainLogicListenerA : public TerrainLogicListenerRootA {
public:
    virtual void vslot1(int, WaterHandle *);
    virtual void vslot3(void *, void *);
    ~TerrainLogicListenerA();
};

class TerrainLogicListenerRootB {
public:
    virtual void vslot0(int);
    virtual void vslot1(int, WaterHandle *);
    virtual void vslot2(void *, void *);
    virtual void vslot3(void *, void *);
};

class TerrainLogicListenerB : public TerrainLogicListenerRootB {
public:
    virtual void vslot1(int, WaterHandle *);
    virtual void vslot3(void *, void *);
    ~TerrainLogicListenerB();
};

class TerrainLogic : public Snapshot, public SubsystemInterface,
                     public TerrainLogicListenerA, public TerrainLogicListenerB {
public:
    TerrainLogic();
    virtual ~TerrainLogic();
    virtual void init();
    virtual void reset();
    virtual void update();

protected:
    // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *);
#endif

public:
    virtual bool loadMap(const AsciiString &, ChunkInputStream *, bool, bool);
    virtual void newMap(bool);
    virtual float getGroundHeight(float, float, Coord3D * = 0) const;
    virtual float getLayerHeight(float, float, PathfindLayerEnum, Coord3D * = 0, bool = true) const;
    virtual void getExtent(Region3D *) const = 0;
    virtual void slot09(Region3D *) const = 0;
    virtual void getExtentIncludingBorder(Region3D *) const = 0;
    virtual float slot11() = 0;
    virtual void getMaximumPathfindExtent(Region3D *) const = 0;
    virtual Coord3D findClosestEdgePoint(const Coord3D *) const;
    virtual Coord3D findFarthestEdgePoint(const Coord3D *) const;
    virtual bool isClearLineOfSight(const Coord3D &, const Coord3D &) const = 0;
    virtual float slot16(const Coord3D &, const Coord3D &) const = 0;
    virtual AsciiString getSourceFilename();
    virtual PathfindLayerEnum alignOnTerrain(float, const Coord3D &, bool, Matrix3D &);
    virtual bool isUnderwater(float, float, float * = 0, float * = 0, bool * = 0);
    virtual bool isCliffCell(float, float) const;
    virtual unsigned char slot21(float, float) const;
    virtual unsigned char slot22(float, float) const;
    virtual bool slot23(float, float) const;
    virtual unsigned char slot24(float, float) const;
    virtual float slot25(float, float);
    virtual void *slot26(float, float, float);
    virtual void *slot27(float, float, float);
    virtual void *slot28(const StringBase<char> &);
    virtual void *slot29(const StringBase<char> &);
    virtual float getWaterHeight(const WaterHandle *);
    virtual void setWaterHeight(const WaterHandle *, float, float, bool);
    virtual void changeWaterHeightOverTime(const WaterHandle *, float, float, float);
    virtual Waypoint *getFirstWaypoint();
    virtual Waypoint *getWaypointByName(const AsciiString &);
    virtual Waypoint *getWaypointByID(unsigned int);
    virtual Waypoint *getClosestWaypointOnPath(const Coord3D *, const AsciiString &);
    virtual Waypoint *getWaypointByPath(const AsciiString &);
    virtual bool isPurposeOfPath(Waypoint *, const AsciiString &);
    virtual PolygonTrigger *getTriggerAreaByName(const AsciiString &);
    virtual Bridge *getFirstBridge() const;
    virtual Bridge *findBridgeAt(const Coord3D *) const;
    virtual Bridge *findBridgeLayerAt(const Coord3D *, PathfindLayerEnum, bool = true) const;
    virtual bool objectInteractsWithBridgeLayer(Object *, int, bool = true) const;
    virtual bool objectInteractsWithBridgeEnd(Object *, int) const;
    virtual bool pickBridge(const Vector3 &, const Vector3 &, Vector3 *);
    virtual void addBridgeToLogic(Rva0027C36A *, Dict *, const AsciiString &);
    virtual void addLandmarkBridgeToLogic(Object *);
    virtual void deleteBridge(Bridge *);
    virtual void updateBridgeDamageStates();
    virtual bool slot50(const Coord3D *) const = 0;

    void setActiveBoundary(int);
    void rva0027D1A4(const Coord3D *, float, int);
    // Inline in retail: evaluateBridgeBroken 0x003E3D95 and evaluateBridgeRepaired 0x003E3DC6 test byte +0x44.
    bool anyBridgesDamageStatesChanged() { return field44; }
    bool isBridgeRepaired(const Object *);
    bool isBridgeBroken(const Object *);
    int getPartitionBucket(float *);
    void rva0027F28E(const Coord3D *, float, int);
    PathfindLayerEnum getHighestLayerForDestination(const Coord3D *, bool = false);
    PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
    void getBridgeAttackPoints(const Object *, TBridgeAttackInfo *);
    void rva0027D3D9(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
    void rva00280176(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
    bool FindClosestBeacon(Coord3D *, const Coord3D *, const Coord3D *, float, bool);
    void LoadAmbientLightmap(const AsciiString &);
    void rva00282CFB(const Coord3D *, float, unsigned int);
    void rva00283262(const Coord3D *, float);
    void addTree(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
    void rva00283CE7(unsigned int);
    void rva0028449F(const Coord3D *, const GeometryInfo &, float);
    void rva00285193(Object *);
    void flattenTerrain(Object *);
    Object *rva00283D70(const Coord3D *);
    bool rva002814EF(const Coord3D *, const Coord3D *, Coord3D *);
    void iterateTreesNearAPoint(const Coord3D *, float, GeometryInfo *, BfmeT1035 *, bool, int);

protected:
    static bool parseWaypointDataChunk(DataChunkInput &, DataChunkInfo *, void *);
    bool parseWaypointData(DataChunkInput &, DataChunkInfo *, void *);
    void addWaypoint(MapObject *);
    void addWaypointLink(int, int);
    void buildBeacons();
    void deleteBridges();

public:
    unsigned int field18;
    // Retail compares both signed: jl at 0x0027DA81/0x0027DA8B, cvtsi2ss at 0x0027DACA/0x000630C3.
    int field1C;
    int field20;
    unsigned char *field24;
    unsigned int field28;
    unsigned int field2C;
    // STLport containers are typed where the unit included their STLport header first;
    // elsewhere the same bytes stay opaque, so other includers compile unchanged.
#ifdef _STLP_INTERNAL_VECTOR_H
    _STL::vector<ICoord2D> field30; // setActiveBoundary 0x0028069E selects a boundary from it
#else
    unsigned int field30[3];
#endif
    int field3C;
    Bridge *field40;
    bool field44;
    unsigned int field48;
    AsciiString field4C;
    void *field50;
    void *field54;
    void *field58;
    void *field5C;
    bool field60;
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<_STL::list<Coord3D> > field64; // buildBeacons 0x00283E9C appends beacon paths
#else
    void *field64;
#endif
    struct DynamicWaterEntry {
        const WaterHandle *waterTable;
        float changePerFrame;
        float targetHeight;
        float damageAmount;
        float currentHeight;
    } field68[64];
    int field568;
#ifdef _STLP_INTERNAL_MAP_H
    _STL::map<unsigned int, Waypoint *> field56C; // getWaypointByID 0x0028333F looks ids up in it
#else
    unsigned int field56C[3];
#endif
#ifdef _STLP_INTERNAL_VECTOR_H
    _STL::vector<Rva0027D098 *> field578; // rva00283CE7 walks it; destructor 0x0028418A frees +0x578
#else
    void **field578;
    void **field57C;
    void **field580;
#endif
    void *field584;
    short field588[2500];
    unsigned int field1910;
    bool field1914;
    float field1918;
};

extern TerrainLogic *TheTerrainLogic;

#endif
