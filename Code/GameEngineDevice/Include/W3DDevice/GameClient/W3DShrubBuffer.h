#pragma once
// BFME2 consumed shrub storage; no constructor, lifetime, base or vtable-provider recovery claimed.
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/vector3.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class VertexBufferClass;
class IndexBufferClass;
class MeshClass;
class GeometryInfo;
class Thing;
class Xfer;
struct FloatPair;
// Draw-module data; the rowed addShrub E91CE signature names it Rva000E91CEData.
struct Rva000E91CEData {
 unsigned char opaque00[8];
 AsciiString m_modelName,m_textureName; //08/0C: addShrub E91CE matches types by both
 unsigned int m_framesToMoveOutward; //10: addShrub E91CE tests it with +0x3D
 unsigned char opaque14[4];
 float m_maxOutwardMovement;
 unsigned char opaque1c[0x3d-0x1c];
 bool m_doTopple; //3D
 unsigned char opaque3e[0x48-0x3e];
 AsciiString m_name48; //48: addShrub E91CE passes it to rva000E8F9D
 unsigned char opaque4c[8];
 bool m_noSway; //54: addShrub E91CE skips the random sway type when set
};
// SphereClass members are typed where the unit included WWMath's sphere.h first.
struct W3DShrubType {
 MeshClass *m_mesh;
 Vector3 m_offset;
#ifdef SPHERE_H
 SphereClass m_bounds; //10: addShrub E91CE copies it into the instance
#else
 unsigned char opaque10[0x10];
#endif
 const Rva000E91CEData *m_data;
 Vector2 m_scale;
 unsigned char opaque2c[8];
 Vector2 m_origin;
 unsigned char opaque3c[0x58-0x3c];
 int m_field58; //58: addShrub E91CE stores rva000E8F9D's result
};
struct ShrubInstance {
 Vector3 location;
 float scale;
 Matrix3D transform;
 int treeType;
 bool visible;
 bool m_flag45,m_flag46; //45/46: addShrub E91CE clears both
 unsigned char opaque47[1];
#ifdef SPHERE_H
 SphereClass bounds; //48: addShrub E91CE scales and translates the type's bounds
#else
 unsigned char opaque48[0x10];
#endif
 unsigned int drawableID; //58: addShrub E91CE stores the id, rva000E90DB compares it
 float pushAside,pushAsideDelta,pushAsideSin,pushAsideCos;
 unsigned int pushAsideSource,lastFrameUpdated; //6C/70: addShrub E91CE zeroes both
 int nextInPartition; //74: addShrub E91CE links it into m_areaPartition
 int swayType,firstIndex,bufferNdx,m_toppleState;
 int m_field88,m_field8c; //88/8C: addShrub E91CE stores the type and the type's m_field58
 unsigned int m_field90; //90: addShrub E91CE zeroes it, rva000E90DB requires it zero
 void *m_field94,*m_field98; //94/98: addShrub E91CE zeroes both
 int m_field9c;
};
class W3DShrubBuffer {
public:
 void rva000E9D18(const Coord3D *,const GeometryInfo &,float);
 void rva000E912A(const Coord3D *,float,int); // 0x000E912A
 void rva000E7734(Thing *);                   // 0x000E7734
 void rva000E8365();
 void loadShrubsInVertexAndIndexBuffers();
 int getPartitionBucket(const FloatPair *); // 0x000E6EF0
 void rva000E7016();                        // 0x000E7016
 void rva000E76B8();                        // 0x000E76B8
 void startMorph(int,int);                  // 0x000E8C2D
 bool rva000E90DB(unsigned int,int);        // 0x000E90DB
 void DoXfer(Xfer *);                       // 0x000E96B4
 int addTreeType(const AsciiString &,const AsciiString &,const void *,int,const AsciiString &,const AsciiString &); // 0x000E8734
 int rva000E8F9D(const AsciiString &,int,const AsciiString &); // 0x000E8F9D
 void addShrub(unsigned int,Coord3D,float,const Matrix3D *,float,const Rva000E91CEData *,int,const AsciiString &,const AsciiString &); // 0x000E91CE
private:
 void *m_vtable; //storage projection of native primary pointer, not a new provider
 // Typed where the unit included STLport's <vector> first; this header includes no STL header.
#ifdef _STLP_INTERNAL_VECTOR_H
 std::vector<VertexBufferClass *> m_vertexTree; //4
 std::vector<int> m_curNumTreeVertices; //10
 std::vector<IndexBufferClass *> m_indexTree; //1C
 std::vector<int> m_curNumTreeIndices; //28
#else
 unsigned char opaque04[0x34-0x04];
#endif
 unsigned char opaque34[0x5c0-0x34];
 short m_areaPartition[2500]; //5C0: DoXfer E96B4 stores -1 into 2500 shorts
 Region2D m_bounds; //1948: getPartitionBucket E6EF0 clamps to lo/hi, DoXfer xfers it as Region2D
 ShrubInstance m_trees[2000];
 int m_numTrees; //4FB58
 bool m_anythingChanged,m_anyPushChanged; //4FB5C/5D
 bool m_flag4fb5e; //addShrub E91CE sets it, rva000E76B8 clears it
 unsigned char opaque4fb5f[0x4fb6c-0x4fb5f];
 bool m_initialized; //4FB6C
 unsigned char opaque4fb6d[1];
 bool m_flag4fb6e; //addShrub E91CE sets it after adding a type
 unsigned char opaque4fb6f[1];
 W3DShrubType m_treeTypes[64]; //4FB70
 int m_numTypes,m_unknown51274,m_treeIndexStep,m_unknown5127c;
};
typedef char ShrubInstanceRetailStride[sizeof(ShrubInstance)==0xa0 ? 1 : -1];
typedef char W3DShrubTypeRetailStride[sizeof(W3DShrubType)==0x5c ? 1 : -1];
typedef char W3DShrubBufferRetailSize[sizeof(W3DShrubBuffer)==0x51280 ? 1 : -1]; // new 0x51280 at 0x0006CB54 before ctor E9C1D
