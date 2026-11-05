/* Target facts (BFME2 1.06; code addresses are RVAs, table addresses are VAs): constructor 0x0006C9CF calls RenderObjClass at 0x0013BF00; stores 0x00C6FFFC at +0xC4 and 0x00BBB554 at +0xC8 before installing 0x00BC5DB0 at +0, 0x00BC5DA8 at +8, 0x00BC5DA0 at +0xC4 and 0x00BC5D90 at +0xC8. Destructor 0x0006D0D7 installs the same four final tables and restores Snapshot's 0x00BBB554 during base teardown. The class is polymorphic; the temporary tables belong to bases. The primary table contains 148 slots, including RenderObjClass's 129 slots; the +8 table has one destructor thunk (0x0006D05A), the cleanup table has ReleaseResources (0x00066808) and ReAcquireResources (0x00066962) with no destructor, and the Snapshot table has destructor thunk 0x0006D062, an empty loadPostProcess, name getter 0x0006D054 and xfer 0x00068506. The getter returns "BaseHeightMapRenderObjClass". Zero Hour BaseHeightMap.h names DX8_CleanupHook and its two slots; it is unregistered here.
Target layout: constructor 0x0006C9CF writes the scorch buffer pointers +0xCC/+0xD0 (drawScorches 0x000693AE binds them as index and vertex buffers and reads the scorch vertex/index counts at +0xD8/+0xDC; 0x00067878 releases them), initializes 500 records of stride 0x1C at +0xE0, counters +0x3790/+0x3794/+0x3798, floats +0x379C/+0x37A0, words +0x37A4/+0x37A8/+0x37AC, map +0x37C0, flags +0x37C4/+0x37C5/+0x37D4/+0x37E0, depth floats +0x37C8/+0x37CC/+0x37D0, heights +0x37D8/+0x37DC, settings +0x37E4/+0x37E8, vector bases +0x37EC/+0x3800, shader +0x3814, handles +0x381C/+0x3828/+0x3838/+0x3844, string words +0x3820/+0x3824/+0x382C/+0x3830/+0x383C/+0x3840/+0x3848/+0x384C and buffer pointers +0x3850..+0x387C; it writes byte +0x3880. Derived constructor 0x000E3BFE calls this constructor and starts its own members at +0x3884, bounding sizeof to 0x3884 with four-byte alignment. reset 0x0006D5A7 corroborates the counts, two vectors, buffers and final flag; 0x0006831C proves the prop pointer at +0x3858; 0x000670B8 and 0x0006AD6A read the map at +0x37C0. Unidentified storage has neutral names and no invented ownership operations.
Target interface: named virtual overrides are proved by primary slots 26 (0x00068477), 60 (0x0006BF62), 68 (0x00069BCC), 135 (0x0006669F), 138 (0x0006D5A7), 145 (0x0006AD6A) and 146 (0x000670B8). Slot 137 takes one word: 0x0006846A dispatches [vptr+0x224] with zero. Other unproved slots retain neutral names. Nonvirtual declarations preserve the ledger's spellings, including bodies also reached through table slots; destructor and all rowed methods remain out of line. Donor names for scorch buffers, map, height, depth and buffer fields come from Zero Hour BaseHeightMap.h, with target placement supplied by the cited retail accesses. Additional placement witnesses: 0x00068494 reads the texture flag at +0x3834; 0x000686F2 allocates the buffer fields at +0x37A4/+0x37A8. Ledger declaration witnesses (names do not assert a recovered source path): rva00067878 0x00067878; rva0006B7BF 0x0006B7BF; getMaximumVisibleBox 0x0006B1FA; rva0006B76C 0x0006B76C; xfer 0x00068506; rva0006ACBD 0x0006ACBD; loadRoadsAndBridges 0x00067800; rva0006846A 0x0006846A; addProp 0x0006831C; getMacroTexture 0x000E234E; getLowTexture 0x000E2983; getHighTexture 0x000E2A62; getCloudTexture 0x000E2BCF; Notify_Added 0x00068477; isCliffCell 0x000671B2; rva00067225 0x00067225; rva0006730B 0x0006730B; rva0006B114 0x0006B114; rva0006B187 0x0006B187; getMaxCellHeight 0x000670B8; rva0006B804 0x0006B804; rva00067298 0x00067298; CheckCorners 0x00067494; EstimateMaxHeightAlongLine 0x00066E69; Get_Obj_Space_Bounding_Box 0x00069BCC; ReleaseResources 0x00066808; addScorch 0x00067EA3; addTree 0x0006813B; adjustTerrainLOD 0x0006669F; doTheLight 0x000694A3; drawScorches 0x000693AE; evaluateAsVisibleCliff 0x0006737E; getHeightMapHeight 0x0006AD6A; getStaticDiffuse 0x0006B4CC; initHeightData 0x0006D6D9; isClearLineOfSight 0x00066AD1; reset 0x0006D5A7; rva0006692C 0x0006692C; rva00067FCD 0x00067FCD; rva00068017 0x00068017; rva00068223 0x00068223; rva00068395 0x00068395; rva00069C5F 0x00069C5F; rva00069CE6 0x00069CE6; rva0006B3F3 0x0006B3F3; rva0006B895 0x0006B895; updateViewImpassableAreas 0x0006DBB2; ReAcquireResources 0x00066962; rva0006ABE7 0x0006ABE7; showAsVisibleCliff 0x0006C6A3; showAsVisibleImpassable 0x0006C6E2; rva000683AC 0x000683AC; writeEnvironmentData 0x00068494; rva0006BBD9 0x0006BBD9; updateScorches 0x000678BB; rva000685E2 0x000685E2; Cast_Ray 0x0006BF62; rva000687EF 0x000687EF. */
#pragma once

#ifndef BFME2_BASE_HEIGHTMAP_H
#define BFME2_BASE_HEIGHTMAP_H

#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
template<class T> class StringBase;
template<class T> class RefCountPtr;
template<class T> class RefMultiListIterator;
struct Coord3D;
struct VertexFormatXYZDUV2;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;
struct Rva000E91CEData;
class Rva0055A88BDwordField;
class Rva000E3A8D;
class WorldHeightMap;
class FrustumClass;
class DataChunkOutput;
class W3DTerrainLogic;
class W3DTreeBuffer;
class W3DShrubBuffer;
class W3DPropBuffer;
class W3DBibBuffer;
class W3DWaypointBuffer;
class W3DRoadBuffer;
class W3DBridgeBuffer;
class W3DShroud;
class W3DTaint;
class VertexBufferClass;
class IndexBufferClass;
enum Scorches;

class DX8_CleanupHook
{
public:
    virtual void ReleaseResources() = 0;
    virtual void ReAcquireResources() = 0;
};

class BaseHeightMapRenderObjClass : public RenderObjClass, public DX8_CleanupHook, public Snapshot
{
public:
    BaseHeightMapRenderObjClass();
    virtual ~BaseHeightMapRenderObjClass();
    virtual void ReleaseResources();
    virtual void ReAcquireResources();
    virtual void Notify_Added(SceneClass *scene);
    virtual bool Cast_Ray(RayCollisionTestClass &ray);
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;

    virtual void vslot129();
    virtual void vslot130();
    virtual int vslot131(int, int, WorldHeightMap *, void *);
    virtual void vslot132() = 0;
    virtual int vslot133();
    virtual void vslot134(const Rva000E3A8D &, int);
    virtual void adjustTerrainLOD(int adjustment);
    virtual void vslot136() = 0;
    virtual void vslot137(int);
    virtual void reset();
    virtual void vslot139(int);
    virtual void vslot140() = 0;
    virtual void vslot141() = 0;
    virtual bool vslot142(int);
    virtual void vslot143();
    virtual int vslot144();
    virtual float getHeightMapHeight(float x, float y, Coord3D *normal) const;
    virtual float getMaxCellHeight(float x, float y) const;
    virtual void vslot147() = 0;

    void rva00067878();
    void rva0006B7BF(const Rva0055A88BDwordField *, StringBase<char>, float);
    bool getMaximumVisibleBox(const FrustumClass &, AABoxClass *, bool);
    void rva0006B76C(const Rva0055A88BDwordField *, AsciiString);
    void rva0006ACBD(AsciiString);
    void loadRoadsAndBridges(W3DTerrainLogic *, bool);
    void rva0006846A(int);
    void addProp(int, Coord3D, float, float, const AsciiString &, bool);
    RefCountPtr<TextureClass> getMacroTexture();
    RefCountPtr<TextureClass> getLowTexture();
    RefCountPtr<TextureClass> getHighTexture();
    RefCountPtr<TextureClass> getCloudTexture();
    bool isCliffCell(float, float);
    unsigned char rva00067225(float, float);
    unsigned char rva0006730B(float, float);
    bool rva0006B114(float, float);
    unsigned char rva0006B187(float, float);
    void rva0006B804();
    bool rva00067298(float, float);
    void CheckCorners(int, int, int, int, int, int, bool *, bool *);
    float EstimateMaxHeightAlongLine(const Coord3D &, const Coord3D &) const;
    void addScorch(Vector3, float, Scorches);
    void addTree(unsigned int, Rva000ECF79Coord, float, const Matrix3D *, float, const Rva000ECF79Data *, int, const AsciiString &, const AsciiString &);
    void doTheLight(VertexFormatXYZDUV2 *, Vector3 *, Vector3 *, RefMultiListIterator<RenderObjClass> *, unsigned char, bool);
    void drawScorches();
    bool evaluateAsVisibleCliff(int, int, float);
    int getStaticDiffuse(int, int, bool);
    int initHeightData(int, int, WorldHeightMap *, void *);
    bool isClearLineOfSight(const Coord3D &, const Coord3D &) const;
    void rva0006692C();
    char rva00067FCD(void *, Vector3, const Matrix3D *);
    char rva00068017(void *, Vector3, const Matrix3D *);
    void rva00068223(unsigned int, Coord3D, float, const Matrix3D *, float, const Rva000E91CEData *, int, const AsciiString &, const AsciiString &);
    void rva00068395(int, AsciiString *, AsciiString *, bool, bool);
    void rva00069C5F(Vector3, float);
    void rva00069CE6(const Rva000E3A8D &, int);
    void rva0006B3F3();
    void rva0006B895(RenderInfoClass &);
    void updateViewImpassableAreas(bool, int, int, int, int);
    void rva0006ABE7(AsciiString, bool);
    bool showAsVisibleCliff(int, int) const;
    bool showAsVisibleImpassable(int, int) const;
    bool rva000683AC(int, Coord3D, float, float);
    void writeEnvironmentData(DataChunkOutput *);
    void rva0006BBD9(int, int);
    void updateScorches();
    void rva000685E2();
    void rva000687EF();

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);

public:
    VertexBufferClass *m_vertexScorch;
    IndexBufferClass *m_indexScorch;
    void *field00D4;
    int m_curNumScorchVertices;
    int m_curNumScorchIndices;
    char unknown00E0[0x36B0];
    int m_numScorches;
    int m_scorchesInBuffer;
    int field3798;
    float m_curImpassableSlope;
    float field37A0;
    void *field37A4;
    void *field37A8;
    int field37AC;
    char unknown37B0[0x10];
    WorldHeightMap *m_map;
    bool m_useDepthFade;
    bool m_updating;
    char unknown37C6[2];
    float field37C8;
    float field37CC;
    float field37D0;
    bool m_disableTextures;
    char unknown37D5[3];
    float m_minHeight;
    float m_maxHeight;
    bool m_showImpassableAreas;
    char unknown37E1[3];
    int field37E4;
    int field37E8;
    char unknown37EC[0x14];
    char unknown3800[0x14];
    unsigned int field3814;
    void *field3818;
    void *field381C;
    unsigned int field3820;
    unsigned int field3824;
    void *field3828;
    unsigned int field382C;
    unsigned int field3830;
    bool field3834;
    char unknown3835[3];
    void *field3838;
    unsigned int field383C;
    unsigned int field3840;
    void *field3844;
    unsigned int field3848;
    unsigned int field384C;
    W3DTreeBuffer *m_treeBuffer;
    W3DShrubBuffer *m_shrubBuffer;
    W3DPropBuffer *m_propBuffer;
    W3DBibBuffer *m_bibBuffer;
    void *field3860;
    W3DWaypointBuffer *m_waypointBuffer;
    void *field3868;
    W3DRoadBuffer *m_roadBuffer;
    W3DBridgeBuffer *m_bridgeBuffer;
    void *field3874;
    W3DShroud *m_shroud;
    W3DTaint *field387C;
    bool field3880;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#endif
