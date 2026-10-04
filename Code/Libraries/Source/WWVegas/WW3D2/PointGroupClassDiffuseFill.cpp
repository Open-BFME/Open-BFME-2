// cl: /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep /arch:SSE /G7
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WW3D2/PointGroupClassDiffuseFill.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.

// BFME PointGroup diffuse fill, retail RVA 0x00912880 (1124 bytes).
// The matched renderer 0x00917B70+0x279 proves this helper and its ABI.
// pointgr.h omits the split BFME methods; this view uses the existing renderer
// layout through PointMode. See identity_evidence/00912880-pointgroup-color.md.

#include "sharebuf.h"
#include "vector.h"
#include "vector3.h"
#include "vector4.h"
extern VectorClass<Vector4> VertexDiffuse;

class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva00912880(Vector4 *, int);

private:
  virtual void abstract_dtor();
  ShareBufferClass<Vector3> *PointLoc;
  ShareBufferClass<Vector4> *PointDiffuse;
  ShareBufferClass<unsigned int> *APT;
  ShareBufferClass<float> *PointSize;
  ShareBufferClass<unsigned char> *PointOrientation, *PointFrame;
  int PointCount;
  unsigned char FrameRowColumnCountLog2;
  void *dword_24;
  unsigned int dword_28;
  PointModeEnum PointMode;
};
void PointGroupClass::rva00912880(Vector4 *point_diffuse, int active_points) {
  if (point_diffuse) {
    Vector4 *vertex_color = &VertexDiffuse[0];
    if (PointMode != QUADS) {
      for (int i = 0; i < active_points; i++) {
        vertex_color[0] = point_diffuse[0];
        vertex_color[1] = point_diffuse[0];
        vertex_color[2] = point_diffuse[0];
        point_diffuse++;
        vertex_color += 3;
      }
    } else {
      for (int i = 0; i < active_points; i++) {
        vertex_color[0] = point_diffuse[0];
        vertex_color[1] = point_diffuse[0];
        vertex_color[2] = point_diffuse[0];
        vertex_color[3] = point_diffuse[0];
        point_diffuse++;
        vertex_color += 4;
      }
    }
  }
}
