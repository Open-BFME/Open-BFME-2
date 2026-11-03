/* Target facts (code addresses are RVAs; tables and strings are VAs): constructor 0x00091A80, rowed as Rva00091A80, calls TerrainVisual's constructor 0x002DAB18 at 0x00091A83, clears pointers +0x14/+0x18/+0x1C at 0x00091A8A..0x00091A90 and byte +0x20 at 0x00091A93, then installs 0x00BC80A0/+0 and 0x00BC8068/+4 at 0x00091A96/0x00091A9C. Factory 0x0004C5C6 pushes 0x24 at 0x0004C5D1 and calls this constructor at 0x0004C5E7, proving sizeof 0x24. Destructor 0x0009203A installs the same tables at 0x0009204C/0x00092052 and calls the parent destructor 0x002DAB6C at 0x00092110; deleting destructor 0x00092123 calls it at 0x00092126. The parent's constructor installs Snapshot at +0 and constructs SubsystemInterface at +4 (0x002DAB2A..0x002DAB39), then installs 0x00C03910/+0 and 0x00C039A0/+4. Those different tables belong to TerrainVisual's construction and teardown, not a different W3DTerrainVisual layout. Its filename string is at +0x10, so the registered parent's sizeof is 0x14. W3D's slot-2 getter 0x00091AAC returns "W3DTerrainVisual" at 0x00BC8130; TerrainVisual's getter 0x002DAB5E returns "TerrainVisual" at 0x00C039D8.
Primary table 0x00BC80A0 has 36 entries ending at that name string: slots 0..4 are 0x00092123/0x000B3FD0/0x00091AAC/0x000926EC/0x0009213F; slots 5..15 are 0x00091D32/0x00091D3D/0x00092512/0x00092832/0x00092014/0x00092DD8/0x00091DE3/0x00092A95/0x00091DC4/0x00091DFB/0x00091E0A; slots 16..25 are 0x00091E19/0x00091E38/0x00091E45/0x00091E64/0x0009257A/0x00091E83/0x00091EDD/0x00091EEC/0x00091F2A/0x00091F3B; slots 26..35 are 0x00091FBA/0x00091FAB/0x00091F51/0x00091F62/0x00091F73/0x00091F84/0x00091F95/0x00091DB2/0x00091D61/0x000926AC. Overrides retain the registered parent's names and signatures. Secondary table 0x00BC8068 has fourteen entries before the primary table; slot 0 is the this-4 deleting-destructor thunk 0x00092032, and slots 1/9/10 are init/reset/update at 0x00091AEA/0x00091CA7/0x00091D0D. Their incoming this is the +4 subobject: init stores at receiver+0x10/+0x14 and update reads receiver+0x10, corresponding to complete-object +0x14/+0x18 and +0x14. Destructor accesses complete-object +0x14/+0x18/+0x1C at 0x00092060/0x000920C8/0x000920F7; xfer 0x000926EC transfers byte +0x20 and these pointer members. These are two polymorphic subobjects, with no virtual-base pointer.
Donor facts: Zero Hour GeneralsMD W3DTerrainVisual.h supplies the four member names and the named overrides whose BFME2 ledger entries and table positions prove them. BFME2's allocation and constructor exclude the donor's skybox arrays. Lifecycle and transfer methods are declared out of line. Neutral slots use TerrainVisualClass.h's registered declarations. */
#pragma once
#ifndef BFME2_W3DTERRAINVISUALCLASS_H
#define BFME2_W3DTERRAINVISUALCLASS_H

#include "../../../../GameEngine/Include/GameClient/TerrainVisualClass.h"

class BaseHeightMapRenderObjClass;
class WaterRenderObjClass;
class WorldHeightMap;

class W3DTerrainVisual : public TerrainVisual
{
public:
    W3DTerrainVisual();
    virtual ~W3DTerrainVisual();

    virtual bool load(const AsciiString &filename, ChunkInputStream *stream,
        AreaSet<StandingWaveArea> *standingWaves, AreaSet<RiverArea> *rivers,
        AreaSet<WaterWaveArea> *waterWaves);
    virtual void slot05();
    virtual void getTerrainColorAt(float x, float y, RGBColor *color);
    virtual TerrainType *getTerrainTile(float x, float y);
    virtual bool intersectTerrain(Coord3D *start, Coord3D *end, Coord3D *result);
    virtual void slot09();
    virtual void addFactionBib(Object *object, bool highlight, float extra = 0);
    virtual void slot11(Rva00091DE3Arg *object);
    virtual void addFactionBibDrawable(Drawable *drawable, bool highlight, float extra = 0);
    virtual void slot13(Rva0055A88BDwordField *drawable);
    virtual void removeAllBibs();
    virtual void slot15();
    virtual void slot16(int value, float amount, int flags);
    virtual void slot17();
    virtual void removeTreesAndPropsForConstruction(const Coord3D *position,
        const GeometryInfo &geometry, float angle);
    virtual void slot19(const Coord3D *position, const GeometryInfo *geometry, float angle);
    virtual void addProp(const ThingTemplate *thing, const Coord3D *position,
        float angle, float scale);
    virtual void slot21(unsigned int value, Rva000ECF79Coord position, float angle,
        const Matrix3D *transform, float scale, const Rva000ECF79Data *data,
        int flags, const AsciiString &name, const AsciiString &variant);
    virtual void slot22(int value);
    virtual void slot23(Vector3 position, float amount);
    virtual int slot24(int x, int y);
    virtual void slot25(void *value);
    virtual void slot26(unsigned int value, Coord3D position, float angle,
        const Matrix3D *transform, float scale, const Rva000E91CEData *data,
        int flags, const AsciiString &name, const AsciiString &variant);
    virtual void slot27(int value);
    virtual bool slot28(int value, const Coord3D *direction);
    virtual bool slot29(int value, int argument);
    virtual bool slot30(int value, bool flag);
    virtual bool slot31(int value);
    virtual bool slot32(int value);
    virtual void slot33();
    virtual void slot34(int *values, int count);
    virtual void slot35(const AsciiString &name, bool flag, const AsciiString &variant);

    virtual void init();
    virtual void reset();
    virtual void update();

protected:
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

    BaseHeightMapRenderObjClass *m_terrainRenderObject;
    WaterRenderObjClass *m_waterRenderObject;
    WorldHeightMap *m_logicHeightMap;
    bool m_isWaterGridRenderingEnabled;
};

#endif
