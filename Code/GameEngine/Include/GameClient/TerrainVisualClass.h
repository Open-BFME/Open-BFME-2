/* Target facts (code addresses are RVAs; tables and strings are VAs):
Constructor 0x002DAB18 (rowed as Rva002DAB18) stores Snapshot's 0x00BBB554 at +0 (0x002DAB2A), calls SubsystemInterface's constructor 0x001B4E63 with this+4 (0x002DAB34..0x002DAB39), then installs 0x00C039A0 at +4 and 0x00C03910 at +0 (0x002DAB41/0x002DAB47). Destructor 0x002DAB6C restores that same pair at 0x002DAB81/0x002DAB87, destroys the AsciiString at +0x10 through 0x00036410 (0x002DAB8D..0x002DAB97), calls the secondary parent destructor 0x001B4E74 at 0x002DABA2, then restores Snapshot at 0x002DABAA. The final Snapshot store belongs to base teardown. The class is polymorphic, with Snapshot at +0 and the twelve-byte SubsystemInterface at +4.
Primary table 0x00C03910 has 36 slots before the secondary table at 0x00C039A0. Slots 0..4 are deleting destructor 0x002DABBB, empty loadPostProcess 0x000B3FD0, name getter 0x002DAB5E (returns "TerrainVisual" at 0x00C039D8), xfer 0x00306A9B and load 0x002DAAF2. Slot 8 is false-returning 0x0041BA5C; the other slots 5..35 are purecall 0x0003B810. Secondary table 0x00C039A0 has fourteen slots before that string: slot 0 is the this-4 deleting-destructor thunk 0x002DAB64; slots 1/9/10 are init/reset/update, and slots 2..8/11..13 agree with SubsystemInterface's table 0x00BD77A0. The registered parent's BFME_SUBSYSTEM_SLOTS surface supplies their order.
The constructor clears dword +0x10 at 0x002DAB4D. Load 0x002DAAF2 assigns a string at +0x10 through 0x000366F0 (0x002DAB0A..0x002DAB0D). W3D constructor 0x00091A80 calls this constructor at 0x00091A83 and starts its own pointers at +0x14/+0x18/+0x1C, then its byte at +0x20. Factory 0x0004C5C6 allocates 0x24 bytes at 0x0004C5D1 before calling 0x00091A80 at 0x0004C5E7. Together these accesses bound TerrainVisual to sizeof 0x14 with four-byte alignment.
W3D tables 0x00BC80A0 (primary, 36 slots) and 0x00BC8068 (secondary, fourteen slots) preserve this layout. Named primary slots follow ledger entries: 4 load 0x0009213F, 6 getTerrainColorAt 0x00091D3D, 7 getTerrainTile 0x00092512, 8 intersectTerrain 0x00092832, 10 addFactionBib 0x00092DD8, 12 addFactionBibDrawable 0x00092A95, 18 removeTreesAndPropsForConstruction 0x00091E45 and 20 addProp 0x0009257A. Slot 14's 0x00091DFB is the no-argument terrain-render-object forwarder matching Zero Hour's removeAllBibs. Caller 0x002842CD dispatches slot 19 with position/geometry/float and slot 28 with an integer and a Coord3D pointer. These two names remain neutral. Slot 17 (0x00091E38) is distinct from secondary update (0x00091D0D).
Other neutral slots retain the W3D ledger's entry signatures: 11/13/16 at 0x00091DE3/0x00091DC4/0x00091E19, 21..27 at 0x00091E83/0x00091EDD/0x00091EEC/0x00091F2A/0x00091F3B/0x00091FBA/0x00091FAB, and 29..35 at 0x00091F62/0x00091F73/0x00091F84/0x00091F95/0x00091DB2/0x00091D61/0x000926AC. Their opaque argument spellings preserve those ABI views without asserting original type identities.
Donor facts: Zero Hour GeneralsMD TerrainVisual.h supplies the class name, m_filenameString, removeAllBibs and the named virtual declarations. Its load signature differs; BFME2's slot-4 row proves a const AsciiString reference and four further pointer-sized arguments. Snapshot slots follow the registered parent's selected spelling. All lifecycle and transfer bodies are declared out of line. */
#pragma once
#ifndef BFME2_TERRAINVISUALCLASS_H
#define BFME2_TERRAINVISUALCLASS_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ChunkInputStream;
class StandingWaveArea;
class RiverArea;
class WaterWaveArea;
template<class T> class AreaSet;
struct Coord3D;
struct RGBColor;
class GeometryInfo;
class TerrainType;
class Object;
class Drawable;
class ThingTemplate;
class Rva00091DE3Arg;
class Rva0055A88BDwordField;
class Matrix3D;
class Vector3;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;
struct Rva000E91CEData;

class TerrainVisual : public Snapshot, public SubsystemInterface
{
public:
    TerrainVisual();
    virtual ~TerrainVisual();

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
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

    virtual bool load(const AsciiString &filename, ChunkInputStream *stream,
        AreaSet<StandingWaveArea> *standingWaves, AreaSet<RiverArea> *rivers,
        AreaSet<WaterWaveArea> *waterWaves);
    virtual void slot05() = 0;
    virtual void getTerrainColorAt(float x, float y, RGBColor *color) = 0;
    virtual TerrainType *getTerrainTile(float x, float y) = 0;
    virtual bool intersectTerrain(Coord3D *start, Coord3D *end, Coord3D *result);
    virtual void slot09() = 0;
    virtual void addFactionBib(Object *object, bool highlight, float extra = 0) = 0;
    virtual void slot11(Rva00091DE3Arg *object) = 0;
    virtual void addFactionBibDrawable(Drawable *drawable, bool highlight, float extra = 0) = 0;
    virtual void slot13(Rva0055A88BDwordField *drawable) = 0;
    virtual void removeAllBibs() = 0;
    virtual void slot15() = 0;
    virtual void slot16(int value, float amount, int flags) = 0;
    virtual void slot17() = 0;
    virtual void removeTreesAndPropsForConstruction(const Coord3D *position,
        const GeometryInfo &geometry, float angle) = 0;
    virtual void slot19(const Coord3D *position, const GeometryInfo *geometry, float angle) = 0;
    virtual void addProp(const ThingTemplate *thing, const Coord3D *position,
        float angle, float scale) = 0;
    virtual void slot21(unsigned int value, Rva000ECF79Coord position, float angle,
        const Matrix3D *transform, float scale, const Rva000ECF79Data *data,
        int flags, const AsciiString &name, const AsciiString &variant) = 0;
    virtual void slot22(int value) = 0;
    virtual void slot23(Vector3 position, float amount) = 0;
    virtual int slot24(int x, int y) = 0;
    virtual void slot25(void *value) = 0;
    virtual void slot26(unsigned int value, Coord3D position, float angle,
        const Matrix3D *transform, float scale, const Rva000E91CEData *data,
        int flags, const AsciiString &name, const AsciiString &variant) = 0;
    virtual void slot27(int value) = 0;
    virtual bool slot28(int value, const Coord3D *direction) = 0;
    virtual bool slot29(int value, int argument) = 0;
    virtual bool slot30(int value, bool flag) = 0;
    virtual bool slot31(int value) = 0;
    virtual bool slot32(int value) = 0;
    virtual void slot33() = 0;
    virtual void slot34(int *values, int count) = 0;
    virtual void slot35(const AsciiString &name, bool flag, const AsciiString &variant) = 0;

    virtual void init();
    virtual void reset();
    virtual void update();

protected:
    AsciiString m_filenameString;
};

#endif
