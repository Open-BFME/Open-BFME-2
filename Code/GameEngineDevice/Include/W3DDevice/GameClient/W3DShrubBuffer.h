#pragma once
// BFME2 consumed shrub storage; no constructor, lifetime, base or vtable-provider recovery claimed.
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/vector3.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Match the existing loader's VC7.1/WWLib placement-array-new include contract.
#ifndef __PLACEMENT_VEC_NEW_INLINE
#define __PLACEMENT_VEC_NEW_INLINE
#endif
#include <vector>
class VertexBufferClass;
class IndexBufferClass;
class MeshClass;
class GeometryInfo;
struct W3DShrubTypeData {
 unsigned char opaque00[0x18];
 float m_maxOutwardMovement;
 unsigned char opaque1c[0x54-0x1c];
 bool m_noSway; //consumed data prefix only
};
struct W3DShrubType {
 MeshClass *m_mesh;
 Vector3 m_offset;
 unsigned char opaque10[0x10];
 const W3DShrubTypeData *m_data;
 Vector2 m_scale;
 unsigned char opaque2c[8];
 Vector2 m_origin;
 unsigned char opaque3c[0x20];
};
struct ShrubInstance {
 Vector3 location;
 float scale;
 Matrix3D transform;
 int treeType;
 bool visible;
 unsigned char opaque45[0x5c-0x45];
 float pushAside,pushAsideDelta,pushAsideSin,pushAsideCos;
 unsigned char opaque6c[0x78-0x6c];
 int swayType,firstIndex,bufferNdx,m_toppleState;
 unsigned char opaque88[0x9c-0x88];
 int m_field9c;
};
class W3DShrubBuffer {
public:
 void rva000E9D18(const Coord3D *,const GeometryInfo &,float);
 void rva000E8365();
 void loadShrubsInVertexAndIndexBuffers();
private:
 void *m_vtable; //storage projection of native primary pointer, not a new provider
 std::vector<VertexBufferClass *> m_vertexTree; //4
 std::vector<int> m_curNumTreeVertices; //10
 std::vector<IndexBufferClass *> m_indexTree; //1C
 std::vector<int> m_curNumTreeIndices; //28
 unsigned char opaque34[0x1958-0x34];
 ShrubInstance m_trees[2000];
 int m_numTrees; //4FB58
 bool m_anythingChanged,m_anyPushChanged; //4FB5C/5D
 unsigned char opaque4fb5e[0x4fb6c-0x4fb5e];
 bool m_initialized;
 unsigned char opaque4fb6d[3];
 W3DShrubType m_treeTypes[64]; //4FB70
 int m_numTypes,m_unknown51274,m_treeIndexStep,m_unknown5127c;
};
