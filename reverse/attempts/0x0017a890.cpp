// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// partial score=0.423396552 date=2026-10-09
// PointGroup geometry helper, target0x0017A890, full12000B including its12-entry table.
// Identity/ABI: caller PointGroupClass::Render and existing neutral pin; twelve dispatch
// entries and target calls align with ZH pointgr.cpp Update_Arrays geometry subsection.
// Donor revision9cbfb551fe20dae985f91f2319d8997287b6a705. BFME1 still forwards this helper
// to a dump, so ZH is the clean semantic lead. Target proof: view-cache loads transpose
// three rows into a48B Matrix3D, billboard flagbit1, immediate scalar writes/reloads,
// four-point main loops for the variable triangle paths; full RET16+table boundaries.
// The RenderState view offset22C follows target DEE804 minus named render_state DEE5D8.
// MatrixRotationZ has a proven import thunk at62AF5C but is unresolved by normal tools;
// trial score uses only a read-only symbol-map entry, no ledger pin. Remaining shape:
// emitted12280B/frameDC vs native12000B/frameB8, main-loop pointer/register allocation,
// angle grouping and matrix-transform scheduling. Banked source is NOT verified recovery.
// cl: /O2 /Ireference/shims/bfmestages /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "matrix3d.h"
struct RenderStateStruct { unsigned char opaque[0x22C]; Matrix4 view; };
class DX8Wrapper { public:
 static __forceinline void Get_Transform(int,Matrix3D& v) {
  if(render_state_changed&(1<<19)) v.Make_Identity();
  else { for(int r=0;r<3;++r)for(int c=0;c<4;++c)v[r][c]=render_state.view[c][r]; }
 }
private: static RenderStateStruct render_state; static unsigned render_state_changed;
};
#include "ww3d.h"
#include <d3dx8.h>
static Vector3 GroundMultiplierX(1,0,0),GroundMultiplierY(0,1,0);
extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;

class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva009148C0(Vector3*,float*,unsigned char*,int);
  enum FlagsType{TRANSFORM,BILLBOARD};
  int Get_Flag(FlagsType f){return (Flags>>f)&1;}

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
  unsigned int Flags;
  float DefaultPointSize;
  Vector3 DefaultPointColor;
  float DefaultPointAlpha;
  unsigned char DefaultPointOrientation, DefaultPointFrame;
  float VPXMin, VPYMin, VPXMax, VPYMax;
  static Vector3 _TriVertexLocationOrientationTable[256][3];
  static Vector3 _QuadVertexLocationOrientationTable[256][4];
  static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
  static Vector2 *_TriVertexUVFrameTable[5];
  static Vector2 *_QuadVertexUVFrameTable[5];
};

void PointGroupClass::rva009148C0(Vector3*point_loc,float*point_size,unsigned char*point_orientation,int active_points) {
	int vert, i, j;

	/*
	** Generate the vertex locations from the point locations (note that both are in camera space).
	** Vertex locations depend on the point mode and the points' orientation and size
	*/

	// This defines the loop we run: the LSB indicates whether there is a size override array, the
	// next bit indicates whether there is an orientation override array, and the higher bits
	// indicate the point mode.
	enum LoopSelectionEnum {
		TRIS_NOSIZE_NOORIENT		= ((int)TRIS << 2) + 0,
		TRIS_SIZE_NOORIENT		= ((int)TRIS << 2) + 1,
		TRIS_NOSIZE_ORIENT		= ((int)TRIS << 2) + 2,
		TRIS_SIZE_ORIENT			= ((int)TRIS << 2) + 3,
		QUADS_NOSIZE_NOORIENT	= ((int)QUADS << 2) + 0,
		QUADS_SIZE_NOORIENT		= ((int)QUADS << 2) + 1,
		QUADS_NOSIZE_ORIENT		= ((int)QUADS << 2) + 2,
		QUADS_SIZE_ORIENT			= ((int)QUADS << 2) + 3,
		SCREEN_NOSIZE_NOORIENT	= ((int)SCREENSPACE << 2) + 0,
		SCREEN_SIZE_NOORIENT		= ((int)SCREENSPACE << 2) + 1,
		SCREEN_NOSIZE_ORIENT		= ((int)SCREENSPACE << 2) + 2,
		SCREEN_SIZE_ORIENT		= ((int)SCREENSPACE << 2) + 3,
	};
	LoopSelectionEnum loop_sel = (LoopSelectionEnum)(((int)PointMode << 2) +
		(point_orientation ? 2 : 0) + (point_size ? 1 : 0));

	vert = 0;
	Vector3 *vertex_loc = &VertexLoc[0];


	/// @todo lorenzen sez: this switch statement may be done more compactly another way... look into it

	switch (loop_sel) {

		case TRIS_NOSIZE_NOORIENT:
			{
				// Setup constant vertex offsets (since size and orientation are invariants)
				Vector3 scaled_offset[3];
				scaled_offset[0] = _TriVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _TriVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _TriVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;

				// Add vertex offsets to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 3) {
					vertex_loc[ 0].X = point_loc[0].X + scaled_offset[0].X;
vertex_loc[ 0].Y = point_loc[0].Y + scaled_offset[0].Y;
vertex_loc[ 0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[ 1].X = point_loc[0].X + scaled_offset[1].X;
vertex_loc[ 1].Y = point_loc[0].Y + scaled_offset[1].Y;
vertex_loc[ 1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[ 2].X = point_loc[0].X + scaled_offset[2].X;
vertex_loc[ 2].Y = point_loc[0].Y + scaled_offset[2].Y;
vertex_loc[ 2].Z = point_loc[0].Z + scaled_offset[2].Z;
					
				}
			}
			break;

		case TRIS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 0];
vertex_loc[0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 0];
vertex_loc[0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 0];
					vertex_loc[1].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 0];
vertex_loc[1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 0];
vertex_loc[1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 0];
					vertex_loc[2].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 0];
vertex_loc[2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 0];
vertex_loc[2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 0];

					vertex_loc[3].X = point_loc[1].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 1];
vertex_loc[3].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 1];
vertex_loc[3].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 1];
					vertex_loc[4].X = point_loc[1].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 1];
vertex_loc[4].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 1];
vertex_loc[4].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 1];
					vertex_loc[5].X = point_loc[1].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 1];
vertex_loc[5].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 1];
vertex_loc[5].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 1];

					vertex_loc[6].X = point_loc[2].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 2];
vertex_loc[6].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 2];
vertex_loc[6].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 2];
					vertex_loc[7].X = point_loc[2].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 2];
vertex_loc[7].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 2];
vertex_loc[7].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 2];
					vertex_loc[8].X = point_loc[2].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 2];
vertex_loc[8].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 2];
vertex_loc[8].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 2];

					vertex_loc[9].X = point_loc[3].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i + 3];
vertex_loc[9].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i + 3];
vertex_loc[9].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i + 3];
					vertex_loc[10].X = point_loc[3].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i + 3];
vertex_loc[10].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i + 3];
vertex_loc[10].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i + 3];
					vertex_loc[11].X = point_loc[3].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i + 3];
vertex_loc[11].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i + 3];
vertex_loc[11].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i + 3];
i+=4;point_loc+=4;vertex_loc+=12;
} while(--groups); }
for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i];
vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i];
vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i];
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i];
vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i];
vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i];
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i];
vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i];
vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i];
}
			}
			break;

		case TRIS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].X * DefaultPointSize;
vertex_loc[0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Y * DefaultPointSize;
vertex_loc[0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Z * DefaultPointSize;
					vertex_loc[1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].X * DefaultPointSize;
vertex_loc[1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Y * DefaultPointSize;
vertex_loc[1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Z * DefaultPointSize;
					vertex_loc[2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].X * DefaultPointSize;
vertex_loc[2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Y * DefaultPointSize;
vertex_loc[2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Z * DefaultPointSize;

					vertex_loc[3].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].X * DefaultPointSize;
vertex_loc[3].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Y * DefaultPointSize;
vertex_loc[3].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Z * DefaultPointSize;
					vertex_loc[4].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].X * DefaultPointSize;
vertex_loc[4].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Y * DefaultPointSize;
vertex_loc[4].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Z * DefaultPointSize;
					vertex_loc[5].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].X * DefaultPointSize;
vertex_loc[5].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Y * DefaultPointSize;
vertex_loc[5].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Z * DefaultPointSize;

					vertex_loc[6].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].X * DefaultPointSize;
vertex_loc[6].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Y * DefaultPointSize;
vertex_loc[6].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Z * DefaultPointSize;
					vertex_loc[7].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].X * DefaultPointSize;
vertex_loc[7].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Y * DefaultPointSize;
vertex_loc[7].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Z * DefaultPointSize;
					vertex_loc[8].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].X * DefaultPointSize;
vertex_loc[8].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Y * DefaultPointSize;
vertex_loc[8].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Z * DefaultPointSize;

					vertex_loc[9].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].X * DefaultPointSize;
vertex_loc[9].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Y * DefaultPointSize;
vertex_loc[9].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Z * DefaultPointSize;
					vertex_loc[10].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].X * DefaultPointSize;
vertex_loc[10].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Y * DefaultPointSize;
vertex_loc[10].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Z * DefaultPointSize;
					vertex_loc[11].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].X * DefaultPointSize;
vertex_loc[11].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Y * DefaultPointSize;
vertex_loc[11].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Z * DefaultPointSize;
i+=4;point_loc+=4;vertex_loc+=12;
} while(--groups); }
for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][0].X * DefaultPointSize;
vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][0].Y * DefaultPointSize;
vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][0].Z * DefaultPointSize;
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][1].X * DefaultPointSize;
vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][1].Y * DefaultPointSize;
vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][1].Z * DefaultPointSize;
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][2].X * DefaultPointSize;
vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][2].Y * DefaultPointSize;
vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][2].Z * DefaultPointSize;
}
			}
			break;

		case TRIS_SIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				i=0; if(active_points>=4) { int groups=(active_points-4)/4+1; do {
					vertex_loc[0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].X * point_size[i + 0];
vertex_loc[0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Y * point_size[i + 0];
vertex_loc[0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][0].Z * point_size[i + 0];
					vertex_loc[1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].X * point_size[i + 0];
vertex_loc[1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Y * point_size[i + 0];
vertex_loc[1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][1].Z * point_size[i + 0];
					vertex_loc[2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].X * point_size[i + 0];
vertex_loc[2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Y * point_size[i + 0];
vertex_loc[2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i + 0]][2].Z * point_size[i + 0];

					vertex_loc[3].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].X * point_size[i + 1];
vertex_loc[3].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Y * point_size[i + 1];
vertex_loc[3].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][0].Z * point_size[i + 1];
					vertex_loc[4].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].X * point_size[i + 1];
vertex_loc[4].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Y * point_size[i + 1];
vertex_loc[4].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][1].Z * point_size[i + 1];
					vertex_loc[5].X = point_loc[1].X + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].X * point_size[i + 1];
vertex_loc[5].Y = point_loc[1].Y + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Y * point_size[i + 1];
vertex_loc[5].Z = point_loc[1].Z + _TriVertexLocationOrientationTable[point_orientation[i + 1]][2].Z * point_size[i + 1];

					vertex_loc[6].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].X * point_size[i + 2];
vertex_loc[6].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Y * point_size[i + 2];
vertex_loc[6].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][0].Z * point_size[i + 2];
					vertex_loc[7].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].X * point_size[i + 2];
vertex_loc[7].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Y * point_size[i + 2];
vertex_loc[7].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][1].Z * point_size[i + 2];
					vertex_loc[8].X = point_loc[2].X + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].X * point_size[i + 2];
vertex_loc[8].Y = point_loc[2].Y + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Y * point_size[i + 2];
vertex_loc[8].Z = point_loc[2].Z + _TriVertexLocationOrientationTable[point_orientation[i + 2]][2].Z * point_size[i + 2];

					vertex_loc[9].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].X * point_size[i + 3];
vertex_loc[9].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Y * point_size[i + 3];
vertex_loc[9].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][0].Z * point_size[i + 3];
					vertex_loc[10].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].X * point_size[i + 3];
vertex_loc[10].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Y * point_size[i + 3];
vertex_loc[10].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][1].Z * point_size[i + 3];
					vertex_loc[11].X = point_loc[3].X + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].X * point_size[i + 3];
vertex_loc[11].Y = point_loc[3].Y + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Y * point_size[i + 3];
vertex_loc[11].Z = point_loc[3].Z + _TriVertexLocationOrientationTable[point_orientation[i + 3]][2].Z * point_size[i + 3];
i+=4;point_loc+=4;vertex_loc+=12;
} while(--groups); }
for (;i < active_points;++i,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][0].X * point_size[i];
vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][0].Y * point_size[i];
vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][0].Z * point_size[i];
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][1].X * point_size[i];
vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][1].Y * point_size[i];
vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][1].Z * point_size[i];
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[i]][2].X * point_size[i];
vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[i]][2].Y * point_size[i];
vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[i]][2].Z * point_size[i];
}
			}
			break;

		case QUADS_NOSIZE_NOORIENT:
			{
				// Setup constant vertex offsets (since size and orientation are invariants)
				Vector3 scaled_offset[4];
				scaled_offset[0] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				scaled_offset[3] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3] * DefaultPointSize;

				// Add vertex offsets to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + scaled_offset[0].X;
vertex_loc[ 0].Y = point_loc[0].Y + scaled_offset[0].Y;
vertex_loc[ 0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[ 1].X = point_loc[0].X + scaled_offset[1].X;
vertex_loc[ 1].Y = point_loc[0].Y + scaled_offset[1].Y;
vertex_loc[ 1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[ 2].X = point_loc[0].X + scaled_offset[2].X;
vertex_loc[ 2].Y = point_loc[0].Y + scaled_offset[2].Y;
vertex_loc[ 2].Z = point_loc[0].Z + scaled_offset[2].Z;
					vertex_loc[ 3].X = point_loc[0].X + scaled_offset[3].X;
vertex_loc[ 3].Y = point_loc[0].Y + scaled_offset[3].Y;
vertex_loc[ 3].Z = point_loc[0].Z + scaled_offset[3].Z;
					
				}
			}
			break;

		case QUADS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[i];
vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[i];
vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[i];
					vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[i];
vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[i];
vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[i];
					vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[i];
vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[i];
vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[i];
					vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].X * point_size[i];
vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Y * point_size[i];
vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Z * point_size[i];
					
				}
			}
			break;

		case QUADS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][0].X * DefaultPointSize;
vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][0].Y * DefaultPointSize;
vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][0].Z * DefaultPointSize;
					vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][1].X * DefaultPointSize;
vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][1].Y * DefaultPointSize;
vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][1].Z * DefaultPointSize;
					vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][2].X * DefaultPointSize;
vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][2].Y * DefaultPointSize;
vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][2].Z * DefaultPointSize;
					vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][3].X * DefaultPointSize;
vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][3].Y * DefaultPointSize;
vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][3].Z * DefaultPointSize;
					
				}
			}
			break;

		case QUADS_SIZE_ORIENT:
			{
				Matrix3D view;
				Vector3 result;
				if (!Get_Flag(BILLBOARD)) {
					DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
				}

				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					if (!Get_Flag(BILLBOARD)) {
						// If we're not billboarding, then the coordinate we have is in screen space.
						Matrix4 rotMat;
						D3DXMatrixRotationZ(&(D3DXMATRIX&) rotMat, ((float)point_orientation[i] / 255.0f * 2 * D3DX_PI));
						
						Vector4 orientedVecX = rotMat * GroundMultiplierX;
						Vector4 orientedVecY = rotMat * GroundMultiplierY;

						vertex_loc[ 0].X = point_loc[0].X +	(orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[ 0].Y = point_loc[0].Y +	(orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[ 0].Z = point_loc[0].Z;

						vertex_loc[ 1].X = point_loc[0].X +	(orientedVecX.X - orientedVecY.X) * point_size[i];
						vertex_loc[ 1].Y = point_loc[0].Y +	(orientedVecX.Y - orientedVecY.Y) * point_size[i];
						vertex_loc[ 1].Z = point_loc[0].Z;

						vertex_loc[ 2].X = point_loc[0].X +	-(orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[ 2].Y = point_loc[0].Y +	-(orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[ 2].Z = point_loc[0].Z;

						vertex_loc[ 3].X = point_loc[0].X +	(-orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[ 3].Y = point_loc[0].Y +	(-orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[ 3].Z = point_loc[0].Z;

						// now apply the view transform so that this data is in the format expected
						// upon the functions return.
						Matrix3D::Transform_Vector(view,vertex_loc[ 0],&result);
						vertex_loc[ 0].X = result.X;
						vertex_loc[ 0].Y = result.Y;
						vertex_loc[ 0].Z = result.Z;

						Matrix3D::Transform_Vector(view,vertex_loc[ 1],&result);
						vertex_loc[ 1].X = result.X;
						vertex_loc[ 1].Y = result.Y;
						vertex_loc[ 1].Z = result.Z;

						Matrix3D::Transform_Vector(view,vertex_loc[ 2],&result);
						vertex_loc[ 2].X = result.X;
						vertex_loc[ 2].Y = result.Y;
						vertex_loc[ 2].Z = result.Z;

						Matrix3D::Transform_Vector(view,vertex_loc[ 3],&result);
						vertex_loc[ 3].X = result.X;
						vertex_loc[ 3].Y = result.Y;
						vertex_loc[ 3].Z = result.Z;
					} else {

						vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][0].X * point_size[i];
vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][0].Y * point_size[i];
vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][0].Z * point_size[i];
						vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][1].X * point_size[i];
vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][1].Y * point_size[i];
vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][1].Z * point_size[i];
						vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][2].X * point_size[i];
vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][2].Y * point_size[i];
vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][2].Z * point_size[i];
						vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[i]][3].X * point_size[i];
vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[i]][3].Y * point_size[i];
vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[i]][3].Z * point_size[i];
					}
					
				}
			}
			break;

		// Orientations are ignored for screensize pointgroups
		case SCREEN_NOSIZE_NOORIENT:
		case SCREEN_NOSIZE_ORIENT:
			{
				// Offsets need to be scaled to the current screen resolution

   			// First find x and y scale factors (sizes in pixels need to be
   			// normalized to 2D cam viewplane of -1,-1 to 1,1)
   			int xres, yres, bitdepth;
   			bool windowed;
   			WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
   
   			float x_scale = (VPXMax - VPXMin) / xres;
   			float y_scale = (VPYMax - VPYMin) / yres;
   
				Vector3 scaled_locs[2][3];
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 3; j++) {
						scaled_locs[i][j].X = _ScreenspaceVertexLocationSizeTable[i][j].X * x_scale;
						scaled_locs[i][j].Y = _ScreenspaceVertexLocationSizeTable[i][j].Y * y_scale;
						scaled_locs[i][j].Z = _ScreenspaceVertexLocationSizeTable[i][j].Z;
					}
				}

				// Add vertex offsets to point locations to get vertex locations
				int size_idx = (DefaultPointSize <= 1.0f) ? 0 : 1;
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] + scaled_locs[size_idx][0];
					vertex_loc[vert + 1] = point_loc[i] + scaled_locs[size_idx][1];
					vertex_loc[vert + 2] = point_loc[i] + scaled_locs[size_idx][2];
					vert += 3;
				}
			}
			break;
			
		case SCREEN_SIZE_NOORIENT:
		case SCREEN_SIZE_ORIENT:
			{
				// Offsets need to be scaled to the current screen resolution

   			// First find x and y scale factors (sizes in pixels need to be
   			// normalized to 2D cam viewplane of -1,-1 to 1,1)
   			int xres, yres, bitdepth;
   			bool windowed;
   			WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
   
   			float x_scale = (VPXMax - VPXMin) / xres;
   			float y_scale = (VPYMax - VPYMin) / yres;
   
				Vector3 scaled_locs[2][3];
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 3; j++) {
						scaled_locs[i][j].X = _ScreenspaceVertexLocationSizeTable[i][j].X * x_scale;
						scaled_locs[i][j].Y = _ScreenspaceVertexLocationSizeTable[i][j].Y * y_scale;
						scaled_locs[i][j].Z = _ScreenspaceVertexLocationSizeTable[i][j].Z;
					}
				}

				// Add vertex offsets to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					int size_idx = (point_size[i] <= 1.0f) ? 0 : 1;
					vertex_loc[vert + 0] = point_loc[i] + scaled_locs[size_idx][0];
					vertex_loc[vert + 1] = point_loc[i] + scaled_locs[size_idx][1];
					vertex_loc[vert + 2] = point_loc[i] + scaled_locs[size_idx][2];
					vert += 3;
				}
			}
			break;

		default:
			WWASSERT(0);
			break;

	}

}
