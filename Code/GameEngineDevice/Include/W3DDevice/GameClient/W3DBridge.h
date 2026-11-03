// Target facts (BFME 2 1.06, RVAs): W3DBridge has no virtual functions, vtable or base subobject. Constructor 0x000DD97F and nonvirtual destructor 0x000DDA6E install no tables; init 0x000DDB17 and getBridgeInfo 0x000DDB94 treat +0 and +0xC as three-float data. W3DBridgeBuffer constructor 0x000DE52E passes this+0x10, stride 0x114, count 200 and callbacks 0x000DD97F/0x000DDA6E to the array constructor at 0x000DE53A..0x000DE557; destructor 0x000DE4EB repeats that stride at 0x000DE509..0x000DE51C. sizeof is 0x114.
// Layout facts: constructor 0x000DD97F stores scale/length +0x18/+0x1C, type +0x20, texture handle +0x34, meshes +0x38/+0x7C/+0xB8, scalar bounds +0x6C/+0x70/+0x74/+0x78/+0xB0/+0xB4/+0xEC/+0xF0, counts +0xF4/+0xF8/+0xFC/+0x100, visible byte +0x104, AsciiString +0x108, damage state +0x10C and enabled byte +0x110. Its three calls to 0x00001423 construct three 16-byte rows at +0x3C/+0x80/+0xBC using callback 0x0047A6A9; these matrices are stored here as those Vector4 row arrays. Destructor 0x000DDA6E destroys the string at +0x108 and releases the handle at +0x34; renderBridge 0x000DDAB7 copies that handle through AssetReference's rowed copy constructor 0x000424BB. Setter 0x0039B780 writes byte +0x110.
// Method RVAs: clearBridge 0x000DD816, cullBridge 0x000DD862, renderBridge 0x000DDAB7, init 0x000DDB17, getBridgeInfo 0x000DDB94, getModelVertices 0x000DDE13, getModelVerticesFixed 0x000DE2AE, getModelIndices 0x000DE5D2, load 0x000DE648 and getIndicesNVertices 0x000DF11E remain out of line. Donor facts: Zero Hour GeneralsMD W3DBridgeBuffer.h names the fields, matrix aggregates and simple accessors; retail's matrix row construction establishes those aggregates rather than separate Row members. BFME 2's renderBridge parameter is FXShader::RenderingMethod*, and its getBridgeInfo parameter retains the ledger's Rva0027C36A spelling.

#pragma once

#ifndef BFME2_W3DBRIDGE_H
#define BFME2_W3DBRIDGE_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/SphereClass.h"
#include "../../../../GameEngine/Include/Common/AssetReference.h"

class CameraClass;
class MeshClass;
class Matrix3D;
class RenderObjClass;
class Rva0027C36A;
struct VertexFormatXYZNDUV1;
template <class T> class RefMultiListIterator;
enum BodyDamageType;
enum TBridgeType;
namespace FXShader { class RenderingMethod; }

class W3DBridge
{
public:
    W3DBridge();
    ~W3DBridge();

    void init(Vector3 fromLoc, Vector3 toLoc, AsciiString name);
    bool load(BodyDamageType curDamageState);
    void clearBridge();
    bool cullBridge(CameraClass *camera);
    void renderBridge(FXShader::RenderingMethod *method);
    void getBridgeInfo(Rva0027C36A *info);
    void getIndicesNVertices(unsigned short *indices, VertexFormatXYZNDUV1 *vertices, int *curIndex, int *curVertex, RefMultiListIterator<RenderObjClass> *lights);
    void setEnabled(bool enable);

    AsciiString getTemplateName() { return m_templateName; }
    const Vector3 *getStart() const { return &m_start; }
    const Vector3 *getEnd() const { return &m_end; }
    BodyDamageType getDamageState() { return m_curDamageState; }
    void setDamageState(BodyDamageType state) { m_curDamageState = state; }
    bool isVisible() { return m_visible; }
    bool isEnabled() const { return m_enabled; }

    Vector3 m_start;
    Vector3 m_end;
    float m_scale;
    float m_length;
    TBridgeType m_bridgeType;
    SphereClass m_bounds;
    AssetReference m_bridgeTexture;
    MeshClass *m_leftMesh;
    Vector4 m_leftMtx[3];
    float m_minY;
    float m_maxY;
    float m_leftMinX;
    float m_leftMaxX;
    MeshClass *m_sectionMesh;
    Vector4 m_sectionMtx[3];
    float m_sectionMinX;
    float m_sectionMaxX;
    MeshClass *m_rightMesh;
    Vector4 m_rightMtx[3];
    float m_rightMinX;
    float m_rightMaxX;
    int m_firstIndex;
    int m_numVertex;
    int m_firstVertex;
    int m_numPolygons;
    bool m_visible;
    AsciiString m_templateName;
    BodyDamageType m_curDamageState;
    bool m_enabled;

protected:
    int getModelVerticesFixed(VertexFormatXYZNDUV1 *vertices, int curVertex, const Matrix3D &matrix, MeshClass *mesh, RefMultiListIterator<RenderObjClass> *lights);
    int getModelIndices(unsigned short *indices, int curIndex, int vertexOffset, MeshClass *mesh);
    int getModelVertices(VertexFormatXYZNDUV1 *vertices, int curVertex, float xOffset, Vector3 &vec, Vector3 &normal, Vector3 &vecZ, Vector3 &offset, const Matrix3D &matrix, MeshClass *mesh, RefMultiListIterator<RenderObjClass> *lights);
};

typedef char W3DBridgeSizeIs0x114[(sizeof(W3DBridge) == 0x114) ? 1 : -1];

#endif
