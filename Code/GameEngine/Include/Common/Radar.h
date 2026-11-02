// Target facts: Radar ctor 0x002D87B9 and dtor 0x002D7CED install primary
// table 0x00C0363C at +0 and secondary table 0x00C03604 at +4. Snapshot's
// table 0x00BBB554 is the ctor's initial and dtor's final primary store.
// The ctor calls SubsystemInterface 0x001B4E63 at +4; the dtor calls
// 0x001B4E74 there. Secondary slot 0 (0x002D7D4F) subtracts 4 before
// 0x002D8888. Secondary slots 9/10 are reset 0x002D7DB9/update 0x002D7DD5;
// those bodies receive the +4 subobject (reset subtracts 4 itself).
// Primary slots 0-6: 0x002D8888, 0x002D7ABF, 0x0004FA11, 0x002D85D7,
// 0x002D7AA6, 0x002D7AB0, 0x002D7E68. Slots 7-12 are purecall. Derived
// W3DRadar table 0x00BC4E34 proves draw's five ints at 7, no args at 8,
// setShroudLevel at 9, clearShroud at 10, two ints and a byte at 11,
// and the reference-returning factory 0x0004F84E at 12. Slot 2 returns
// "Radar" (0x00BC4E68); slots 6, 8, 11 and 12 have no proven original name.
// Ctor stores: bools +0x10/+0x11, lists +0x14/+0x18, floats +0x1C..+0x28,
// window +0x1430, six extent floats +0x1434..+0x1448, frame +0x1460.
// Ctor/dtor array helpers prove 64 events of 0x50 bytes at +0x2C; their
// internal type is opaque here. clearAllEvents 0x002D7D57 stores +0x142C.
// 0x002D7BD3 stores four ints +0x144C..+0x1458 and byte +0x145C;
// 0x002D7BB7 copies that 16-byte rectangle. Extent is at least 0x1464;
// W3DRadar slot 6 at 0x0004E3A6 writes its first added byte at +0x1464.
// The derived ctor 0x0004F8EA calls Radar at 0x0004F8FD before initializing
// +0x1464 at 0x0004F911. The primary table has thirteen entries; the next
// word at 0x00C03670 is not a code pointer. W3DLeftHUDDraw 0x0009DCEE
// pushes -1 for draw's fifth argument when its caller omits the colour.
// Out-of-line members: radarToWorld 0x002D7744, worldToRadar 0x002D77C9,
// localPixelToRadar 0x002D81EC, screenPixelToWorld 0x002D82E4,
// objectUnderRadarPixel 0x002D834E, searchListForRadarLocationMatch
// 0x002D78A4, findDrawPositions 0x002D799C, isPriorityVisible 0x002D7ACB,
// addObject 0x002D7FEC, removeObject 0x002D7714, createEvent 0x002D88A4,
// createPlayerEvent 0x002D893B, tryEvent 0x002D8AF7, tryUnderAttackEvent
// 0x002D8B9D, tryInfiltrationEvent 0x002D8A1B, deleteListResources
// 0x002D75E5 and internalCreateEvent 0x002D8395. Opaque method names name
// their ledger RVAs. The no-argument newMap
// is 0x002D7B6B, distinct from primary slot 6. isRadarWindow 0x0029A224
// returns int. ZH Radar.h supplies the field and inline accessor names;
// the flag, list and float offsets above are target facts.

#pragma once
#ifndef __BFME2_RADAR_H_
#define __BFME2_RADAR_H_

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#ifndef CANONICAL_SUBSYSTEMINTERFACE_H
#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Coord2D;
struct Coord3D;
struct ICoord2D;
class GameWindow;
class Object;
class RadarObject;
class TerrainLogic;
class Xfer;
class Rva0004E4C9;
struct Rva002D76C6Owner;
struct Rva002D893BColorSource;
struct RGBAColorInt;
enum RadarEventType;
enum RadarPriorityType;
enum CellShroudStatus;

class Radar : public Snapshot, public SubsystemInterface
{
public:
    Radar();
    virtual ~Radar();

    virtual void init();
    virtual void reset();
    virtual void update();
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
    virtual void crc(Xfer *);
#endif
    virtual void refreshTerrain(TerrainLogic *);
    virtual void queueTerrainRefresh();
    virtual void vslot06(void *);
    virtual void draw(int, int, int, int, int = -1) = 0;
    virtual void slot08() = 0;
    virtual void setShroudLevel(int, int, CellShroudStatus) = 0;
    virtual void clearShroud() = 0;
    virtual void vslot11(int, int, unsigned char) = 0;
    virtual Rva0004E4C9 &vslot12(Rva0004E4C9 &, const char *) = 0;

    void newMap();
    int isRadarWindow(GameWindow *);
    bool radarToWorld(const ICoord2D *, Coord3D *);
    bool worldToRadar(const Coord3D *, ICoord2D *);
    bool localPixelToRadar(const ICoord2D *, ICoord2D *);
    bool screenPixelToWorld(const ICoord2D *, Coord3D *);
    Object *objectUnderRadarPixel(const ICoord2D *);
    Object *searchListForRadarLocationMatch(RadarObject *, ICoord2D *);
    void findDrawPositions(int, int, int, int, ICoord2D *, ICoord2D *);
    bool isPriorityVisible(RadarPriorityType) const;
    void addObject(Object *);
    void removeObject(Rva002D76C6Owner *);
    void createEvent(const Coord3D *, RadarEventType, float = 4.0f);
    void createPlayerEvent(const Rva002D893BColorSource *, const Coord3D *, RadarEventType, float);
    bool tryEvent(RadarEventType, const Coord3D *);
    void tryUnderAttackEvent(const Object *);
    void tryInfiltrationEvent(const Object *);
    void rva002D790A(float *, float *);
    bool rva002D782C(const Coord3D *, Coord2D *);
    void rva002D7BB7(const void *);
    void rva002D7BD3();
    void rva002D7E68(void *);
    void rva0004DB76(const Coord2D *, Coord2D *, int, int, int, int);
    void rva0004F515(int, int, int, int);

    void hide(bool hidden) { m_radarHidden = hidden; }
    bool isRadarHidden() { return m_radarHidden; }
    void forceOn(bool forced) { m_radarForceOn = forced; }
    bool isRadarForced() { return m_radarForceOn; }
    float getTerrainAverageZ() const { return m_terrainAverageZ; }
    float getWaterAverageZ() const { return m_waterAverageZ; }
    const RadarObject *getObjectList() const { return m_objectList; }
    const RadarObject *getLocalObjectList() const { return m_localObjectList; }

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *);
#endif
    void deleteListResources();
    void clearAllEvents();
    void internalCreateEvent(const Coord3D *, RadarEventType, float,
        const RGBAColorInt *, const RGBAColorInt *);

public:
    bool m_radarHidden;                       // +0x10
    bool m_radarForceOn;                      // +0x11
    unsigned char pad12[2];
    RadarObject *m_objectList;                // +0x14
    RadarObject *m_localObjectList;           // +0x18
    float m_terrainAverageZ;                  // +0x1C
    float m_waterAverageZ;                    // +0x20
    float m_xSample;                          // +0x24
    float m_ySample;                          // +0x28
    unsigned char padEvents[0x1400];          // +0x2C
    int m_nextFreeRadarEvent;                 // +0x142C
    GameWindow *m_radarWindow;                // +0x1430
    float m_mapExtent[6];                     // +0x1434
    int field144C;
    int field1450;
    int field1454;
    int field1458;
    unsigned char field145C;
    unsigned char pad145D[3];
    unsigned int m_queueTerrainRefreshFrame;  // +0x1460
};

extern Radar *TheRadar;

#endif
