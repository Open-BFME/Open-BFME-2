// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// partial score=0.4 date=2026-10-08
// cl: /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep /arch:SSE /G7
// Position-generation switch from ZH pointgr.cpp Update_Arrays.
// Donor reviewed at BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705.
// The landed BFME2 PointGroup renderer calls this split helper at17F6B4.
#define Matrix4x4 Matrix4
#include "sharebuf.h"
#include "vector.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
#include "wwmath.h"
extern VectorClass<Vector3> VertexLoc;
extern Vector3 GroundMultiplierX,GroundMultiplierY;
class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva009148C0(Vector3 *,float *,unsigned char *,int);

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
  bool Billboard;
  static Vector3 _TriVertexLocationOrientationTable[256][3];
  static Vector3 _QuadVertexLocationOrientationTable[256][4];
  static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
  static Vector2 *_TriVertexUVFrameTable[5];
  static Vector2 *_QuadVertexUVFrameTable[5];
};

// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z present-unmatched
void PointGroupClass::rva009148C0(Vector3 *point_loc,float *point_size,unsigned char *point_orientation,int active_points) {
int vert,i,j;
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
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] + scaled_offset[0];
					vertex_loc[vert + 1] = point_loc[i] + scaled_offset[1];
					vertex_loc[vert + 2] = point_loc[i] + scaled_offset[2];
					vert += 3;
				}
			}
			break;

		case TRIS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] +
						_TriVertexLocationOrientationTable[DefaultPointOrientation][0] * point_size[i];
					vertex_loc[vert + 1] = point_loc[i] +
						_TriVertexLocationOrientationTable[DefaultPointOrientation][1] * point_size[i];
					vertex_loc[vert + 2] = point_loc[i] +
						_TriVertexLocationOrientationTable[DefaultPointOrientation][2] * point_size[i];
					vert += 3;
				}
			}
			break;

		case TRIS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] +
						_TriVertexLocationOrientationTable[point_orientation[i]][0] * DefaultPointSize;
					vertex_loc[vert + 1] = point_loc[i] +
						_TriVertexLocationOrientationTable[point_orientation[i]][1] * DefaultPointSize;
					vertex_loc[vert + 2] = point_loc[i] +
						_TriVertexLocationOrientationTable[point_orientation[i]][2] * DefaultPointSize;
					vert += 3;
				}
			}
			break;

		case TRIS_SIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] +
						_TriVertexLocationOrientationTable[point_orientation[i]][0] * point_size[i];
					vertex_loc[vert + 1] = point_loc[i] +
						_TriVertexLocationOrientationTable[point_orientation[i]][1] * point_size[i];
					vertex_loc[vert + 2] = point_loc[i] +
						_TriVertexLocationOrientationTable[point_orientation[i]][2] * point_size[i];
					vert += 3;
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
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] + scaled_offset[0];
					vertex_loc[vert + 1] = point_loc[i] + scaled_offset[1];
					vertex_loc[vert + 2] = point_loc[i] + scaled_offset[2];
					vertex_loc[vert + 3] = point_loc[i] + scaled_offset[3];
					vert += 4;
				}
			}
			break;

		case QUADS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] +
						_QuadVertexLocationOrientationTable[DefaultPointOrientation][0] * point_size[i];
					vertex_loc[vert + 1] = point_loc[i] +
						_QuadVertexLocationOrientationTable[DefaultPointOrientation][1] * point_size[i];
					vertex_loc[vert + 2] = point_loc[i] +
						_QuadVertexLocationOrientationTable[DefaultPointOrientation][2] * point_size[i];
					vertex_loc[vert + 3] = point_loc[i] +
						_QuadVertexLocationOrientationTable[DefaultPointOrientation][3] * point_size[i];
					vert += 4;
				}
			}
			break;

		case QUADS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					vertex_loc[vert + 0] = point_loc[i] +
						_QuadVertexLocationOrientationTable[point_orientation[i]][0] * DefaultPointSize;
					vertex_loc[vert + 1] = point_loc[i] +
						_QuadVertexLocationOrientationTable[point_orientation[i]][1] * DefaultPointSize;
					vertex_loc[vert + 2] = point_loc[i] +
						_QuadVertexLocationOrientationTable[point_orientation[i]][2] * DefaultPointSize;
					vertex_loc[vert + 3] = point_loc[i] +
						_QuadVertexLocationOrientationTable[point_orientation[i]][3] * DefaultPointSize;
					vert += 4;
				}
			}
			break;

		case QUADS_SIZE_ORIENT:
			{
				Matrix4x4 view;
				Vector4 result;
				if (!Billboard) {
					DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
				}

				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++) {
					if (!Billboard) {
						// If we're not billboarding, then the coordinate we have is in screen space.
						Matrix4x4 rotMat;
						D3DXMatrixRotationZ(&(D3DXMATRIX&) rotMat, ((float)point_orientation[i] / 255.0f * 2 * D3DX_PI));
						
						Vector4 orientedVecX = rotMat * GroundMultiplierX;
						Vector4 orientedVecY = rotMat * GroundMultiplierY;

						vertex_loc[vert + 0].X = point_loc[i].X +	(orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[vert + 0].Y = point_loc[i].Y +	(orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[vert + 0].Z = point_loc[i].Z;

						vertex_loc[vert + 1].X = point_loc[i].X +	(orientedVecX.X - orientedVecY.X) * point_size[i];
						vertex_loc[vert + 1].Y = point_loc[i].Y +	(orientedVecX.Y - orientedVecY.Y) * point_size[i];
						vertex_loc[vert + 1].Z = point_loc[i].Z;

						vertex_loc[vert + 2].X = point_loc[i].X +	-(orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[vert + 2].Y = point_loc[i].Y +	-(orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[vert + 2].Z = point_loc[i].Z;

						vertex_loc[vert + 3].X = point_loc[i].X +	(-orientedVecX.X + orientedVecY.X) * point_size[i];
						vertex_loc[vert + 3].Y = point_loc[i].Y +	(-orientedVecX.Y + orientedVecY.Y) * point_size[i];
						vertex_loc[vert + 3].Z = point_loc[i].Z;

						// now apply the view transform so that this data is in the format expected
						// upon the functions return.
						result = view*vertex_loc[vert + 0];
						vertex_loc[vert + 0].X = result.X;
						vertex_loc[vert + 0].Y = result.Y;
						vertex_loc[vert + 0].Z = result.Z;

						result = view*vertex_loc[vert + 1];
						vertex_loc[vert + 1].X = result.X;
						vertex_loc[vert + 1].Y = result.Y;
						vertex_loc[vert + 1].Z = result.Z;

						result = view*vertex_loc[vert + 2];
						vertex_loc[vert + 2].X = result.X;
						vertex_loc[vert + 2].Y = result.Y;
						vertex_loc[vert + 2].Z = result.Z;

						result = view*vertex_loc[vert + 3];
						vertex_loc[vert + 3].X = result.X;
						vertex_loc[vert + 3].Y = result.Y;
						vertex_loc[vert + 3].Z = result.Z;
					} else {

						vertex_loc[vert + 0] = point_loc[i] +
							_QuadVertexLocationOrientationTable[point_orientation[i]][0] * point_size[i];
						vertex_loc[vert + 1] = point_loc[i] +
							_QuadVertexLocationOrientationTable[point_orientation[i]][1] * point_size[i];
						vertex_loc[vert + 2] = point_loc[i] +
							_QuadVertexLocationOrientationTable[point_orientation[i]][2] * point_size[i];
						vertex_loc[vert + 3] = point_loc[i] +
							_QuadVertexLocationOrientationTable[point_orientation[i]][3] * point_size[i];
					}
					vert += 4;
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
