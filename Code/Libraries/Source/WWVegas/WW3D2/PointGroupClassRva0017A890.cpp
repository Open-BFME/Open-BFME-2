// cl: /O2 /arch:SSE /G7 /DBFME_WWSTRING_CTOR_BUFFER_RELOAD /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /DNDEBUG /MD /I. /Ireference/shims/banked_segline /Ireference/shims/bfmestages /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// PointGroupClass vertex-location fill, retail RVA 0x0017A890 (VA 0x009148C0),
// 12000 bytes including its 12-entry dispatch table. Called by the matched
// array-update helper 0x0017F3A0, which proves the receiver and the
// (point_loc, point_size, point_orientation, active_points) ABI.
// Semantic lead (donor source, not a target fact): the location subsection of
// ZH/BFME1 pointgr.cpp PointGroupClass::Update_Arrays (the WorldBuilder twin
// names it Update_Location_Array), split out of Update_Arrays in BFME 2.
// Retail approves this row for pointgr.cpp, whose header world this file now
// shares: BFME 1's matrix4.h, the banked DX8Wrapper with BFME 2's transform
// accessors (BFME2_DX8WRAPPER_TRANSFORMS; Get_Transform 0x000768FE) and
// canonical PointGroupClass.h. Retail codegen only reproduces with VertexLoc
// at internal linkage (an extern changes the prologue load and the induction
// variables), so this file keeps its own static copy until the merge into
// pointgr.cpp leaves one. History: reverse/attempt_support/rva17a890-2026-10-20.md
// and reverse/attempt_support/pointgr-vertexloc-merge-probe-20261112.md.
#define Matrix4x4 Matrix4
#define BFME_POINT_MATRIX4_TRANSFORM_INLINE
#include "reference/shims/bfme_vector3_len_link/vector3_len_link.h"
#include "reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/matrix4.h"
#include "refcount.h"
#include "rendobj.h"
#include "wwstring.h"
#include "shader.h"
#define BFME2_DX8WRAPPER_TRANSFORMS
#include "reference/shims/banked_segline/dx8wrapper.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "vector.h"
#include "vector2.h"
template <> bool VectorClass<Vector3>::Resize(int, Vector3 const *);
#include "sharebuf.h"
#include "shader.h"
#include "vector4.h"
#include "vector3.h"
#include "vector2.h"
#include "vector.h"
#include "PointGroupClass.h"
#include "ww3d.h"
#include "D3dx8math.h"
// The static VertexLoc instantiates VectorClass<Vector3>; its /O2 copies of
// the constructor and Resize are not retail's, so bind both to the rowed
// 0x000F0D2F and 0x000F0BF1 bodies (vector_class_vector3_ctor/_resize.cpp).
// Declaring the dtor too stops cl synthesizing a /O2 scalar deleting destructor
// copy here; retail's is 0x000F1CF7.
template <> VectorClass<Vector3>::VectorClass(int, Vector3 const *);
template <> VectorClass<Vector3>::~VectorClass();
static Vector3 GroundMultiplierX(1.0f, 0.0f, 0.0f);
static Vector3 GroundMultiplierY(0.0f, 1.0f, 0.0f);
static VectorClass<Vector3>			VertexLoc;

// Get_Flag is owned here with the consolidated render helpers.
inline int PointGroupClass::Get_Flag(FlagsType flag)
{
	return (Flags>>flag) & 0x1;
}

void PointGroupClass::rva009148C0(Vector3 *point_loc, float *point_size, unsigned char *point_orientation, int active_points)
{
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
	Vector3 *vertex_loc = &VertexLoc[0];

	/// @todo lorenzen sez: this switch statement may be done more compactly another way... look into it

	switch (loop_sel) {

		case TRIS_NOSIZE_NOORIENT:
			{
				Vector3 scaled_offset[3];
				scaled_offset[0] = _TriVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _TriVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _TriVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = scaled_offset[0].X + point_loc->X;
					vertex_loc[0].Y = scaled_offset[0].Y + point_loc->Y;
					vertex_loc[0].Z = scaled_offset[0].Z + point_loc->Z;
					vertex_loc[1].X = scaled_offset[1].X + point_loc->X;
					vertex_loc[1].Y = scaled_offset[1].Y + point_loc->Y;
					vertex_loc[1].Z = scaled_offset[1].Z + point_loc->Z;
					vertex_loc[2].X = scaled_offset[2].X + point_loc->X;
					vertex_loc[2].Y = scaled_offset[2].Y + point_loc->Y;
					vertex_loc[2].Z = scaled_offset[2].Z + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
				}
			}
			break;

		case TRIS_SIZE_NOORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[0] + point_loc->X;
					vertex_loc[0].Y = _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[0] + point_loc->Y;
					vertex_loc[0].Z = _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[0] + point_loc->Z;
					vertex_loc[1].X = _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[0] + point_loc->X;
					vertex_loc[1].Y = _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[0] + point_loc->Y;
					vertex_loc[1].Z = _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[0] + point_loc->Z;
					vertex_loc[2].X = _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[0] + point_loc->X;
					vertex_loc[2].Y = _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[0] + point_loc->Y;
					vertex_loc[2].Z = _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[0] + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
					point_size++;
				}
			}
			break;

		case TRIS_NOSIZE_ORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _TriVertexLocationOrientationTable[point_orientation[0]][0].X * DefaultPointSize + point_loc->X;
					vertex_loc[0].Y = _TriVertexLocationOrientationTable[point_orientation[0]][0].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[0].Z = _TriVertexLocationOrientationTable[point_orientation[0]][0].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[1].X = _TriVertexLocationOrientationTable[point_orientation[0]][1].X * DefaultPointSize + point_loc->X;
					vertex_loc[1].Y = _TriVertexLocationOrientationTable[point_orientation[0]][1].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[1].Z = _TriVertexLocationOrientationTable[point_orientation[0]][1].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[2].X = _TriVertexLocationOrientationTable[point_orientation[0]][2].X * DefaultPointSize + point_loc->X;
					vertex_loc[2].Y = _TriVertexLocationOrientationTable[point_orientation[0]][2].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[2].Z = _TriVertexLocationOrientationTable[point_orientation[0]][2].Z * DefaultPointSize + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
					point_orientation++;
				}
			}
			break;

		case TRIS_SIZE_ORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _TriVertexLocationOrientationTable[point_orientation[0]][0].X * point_size[0] + point_loc->X;
					vertex_loc[0].Y = _TriVertexLocationOrientationTable[point_orientation[0]][0].Y * point_size[0] + point_loc->Y;
					vertex_loc[0].Z = _TriVertexLocationOrientationTable[point_orientation[0]][0].Z * point_size[0] + point_loc->Z;
					vertex_loc[1].X = _TriVertexLocationOrientationTable[point_orientation[0]][1].X * point_size[0] + point_loc->X;
					vertex_loc[1].Y = _TriVertexLocationOrientationTable[point_orientation[0]][1].Y * point_size[0] + point_loc->Y;
					vertex_loc[1].Z = _TriVertexLocationOrientationTable[point_orientation[0]][1].Z * point_size[0] + point_loc->Z;
					vertex_loc[2].X = _TriVertexLocationOrientationTable[point_orientation[0]][2].X * point_size[0] + point_loc->X;
					vertex_loc[2].Y = _TriVertexLocationOrientationTable[point_orientation[0]][2].Y * point_size[0] + point_loc->Y;
					vertex_loc[2].Z = _TriVertexLocationOrientationTable[point_orientation[0]][2].Z * point_size[0] + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
					point_orientation++;
					point_size++;
				}
			}
			break;

		case QUADS_NOSIZE_NOORIENT:
			{
				Vector3 scaled_offset[4];
				scaled_offset[0] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				scaled_offset[3] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3] * DefaultPointSize;
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = scaled_offset[0].X + point_loc->X;
					vertex_loc[0].Y = scaled_offset[0].Y + point_loc->Y;
					vertex_loc[0].Z = scaled_offset[0].Z + point_loc->Z;
					vertex_loc[1].X = scaled_offset[1].X + point_loc->X;
					vertex_loc[1].Y = scaled_offset[1].Y + point_loc->Y;
					vertex_loc[1].Z = scaled_offset[1].Z + point_loc->Z;
					vertex_loc[2].X = scaled_offset[2].X + point_loc->X;
					vertex_loc[2].Y = scaled_offset[2].Y + point_loc->Y;
					vertex_loc[2].Z = scaled_offset[2].Z + point_loc->Z;
					vertex_loc[3].X = scaled_offset[3].X + point_loc->X;
					vertex_loc[3].Y = scaled_offset[3].Y + point_loc->Y;
					vertex_loc[3].Z = scaled_offset[3].Z + point_loc->Z;
					vertex_loc += 4;
					point_loc++;
				}
			}
			break;

		case QUADS_SIZE_NOORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[0] + point_loc->X;
					vertex_loc[0].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[0] + point_loc->Y;
					vertex_loc[0].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[0] + point_loc->Z;
					vertex_loc[1].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[0] + point_loc->X;
					vertex_loc[1].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[0] + point_loc->Y;
					vertex_loc[1].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[0] + point_loc->Z;
					vertex_loc[2].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[0] + point_loc->X;
					vertex_loc[2].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[0] + point_loc->Y;
					vertex_loc[2].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[0] + point_loc->Z;
					vertex_loc[3].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].X * point_size[0] + point_loc->X;
					vertex_loc[3].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Y * point_size[0] + point_loc->Y;
					vertex_loc[3].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Z * point_size[0] + point_loc->Z;
					vertex_loc += 4;
					point_loc++;
					point_size++;
				}
			}
			break;

		case QUADS_NOSIZE_ORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _QuadVertexLocationOrientationTable[point_orientation[0]][0].X * DefaultPointSize + point_loc->X;
					vertex_loc[0].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[0].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[1].X = _QuadVertexLocationOrientationTable[point_orientation[0]][1].X * DefaultPointSize + point_loc->X;
					vertex_loc[1].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[1].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[2].X = _QuadVertexLocationOrientationTable[point_orientation[0]][2].X * DefaultPointSize + point_loc->X;
					vertex_loc[2].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[2].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[3].X = _QuadVertexLocationOrientationTable[point_orientation[0]][3].X * DefaultPointSize + point_loc->X;
					vertex_loc[3].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[3].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Z * DefaultPointSize + point_loc->Z;
					vertex_loc += 4;
					point_loc++;
					point_orientation++;
				}
			}
			break;

		case QUADS_SIZE_ORIENT:
			{
				if (!Get_Flag(flag01)) {
					Matrix4 rotMat;
					Matrix4 view;
					Vector4 result;
					DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
					for (int i = 0; i < active_points; i++) {
						D3DXMatrixRotationZ(&(D3DXMATRIX&) rotMat, ((float)point_orientation[0] / 255.0f * 2 * D3DX_PI));
						Vector4 orientedVecX = rotMat * GroundMultiplierX;
						Vector4 orientedVecY = rotMat * GroundMultiplierY;
						float dx0 = (orientedVecX.X + orientedVecY.X) * point_size[0];
						float dy0 = (orientedVecX.Y + orientedVecY.Y) * point_size[0];
						float dx1 = (orientedVecX.X - orientedVecY.X) * point_size[0];
						float dy1 = (orientedVecX.Y - orientedVecY.Y) * point_size[0];
						vertex_loc[0].X = dx0 + point_loc->X;
						vertex_loc[0].Y = dy0 + point_loc->Y;
						vertex_loc[0].Z = point_loc->Z;
						vertex_loc[1].X = dx1 + point_loc->X;
						vertex_loc[1].Y = dy1 + point_loc->Y;
						vertex_loc[1].Z = point_loc->Z;
						vertex_loc[2].X = point_loc->X - dx0;
						vertex_loc[2].Y = point_loc->Y - dy0;
						vertex_loc[2].Z = point_loc->Z;
						vertex_loc[3].X = point_loc->X - dx1;
						vertex_loc[3].Y = point_loc->Y - dy1;
						vertex_loc[3].Z = point_loc->Z;
						result = view * vertex_loc[0];
						vertex_loc[0].X = result.X;
						vertex_loc[0].Y = result.Y;
						vertex_loc[0].Z = result.Z;
						result = view * vertex_loc[1];
						vertex_loc[1].X = result.X;
						vertex_loc[1].Y = result.Y;
						vertex_loc[1].Z = result.Z;
						result = view * vertex_loc[2];
						vertex_loc[2].X = result.X;
						vertex_loc[2].Y = result.Y;
						vertex_loc[2].Z = result.Z;
						result = view * vertex_loc[3];
						vertex_loc[3].X = result.X;
						vertex_loc[3].Y = result.Y;
						vertex_loc[3].Z = result.Z;
						vertex_loc += 4;
						point_loc++;
						point_orientation++;
						point_size++;
					}
				} else {
					for (int i = 0; i < active_points; i++) {
						vertex_loc[0].X = _QuadVertexLocationOrientationTable[point_orientation[0]][0].X * point_size[0] + point_loc->X;
						vertex_loc[0].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Y * point_size[0] + point_loc->Y;
						vertex_loc[0].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Z * point_size[0] + point_loc->Z;
						vertex_loc[1].X = _QuadVertexLocationOrientationTable[point_orientation[0]][1].X * point_size[0] + point_loc->X;
						vertex_loc[1].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Y * point_size[0] + point_loc->Y;
						vertex_loc[1].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Z * point_size[0] + point_loc->Z;
						vertex_loc[2].X = _QuadVertexLocationOrientationTable[point_orientation[0]][2].X * point_size[0] + point_loc->X;
						vertex_loc[2].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Y * point_size[0] + point_loc->Y;
						vertex_loc[2].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Z * point_size[0] + point_loc->Z;
						vertex_loc[3].X = _QuadVertexLocationOrientationTable[point_orientation[0]][3].X * point_size[0] + point_loc->X;
						vertex_loc[3].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Y * point_size[0] + point_loc->Y;
						vertex_loc[3].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Z * point_size[0] + point_loc->Z;
						vertex_loc += 4;
						point_loc++;
						point_orientation++;
						point_size++;
					}
					}
			}
			break;

		// Orientations are ignored for screensize pointgroups
		case SCREEN_NOSIZE_NOORIENT:
		case SCREEN_NOSIZE_ORIENT:
			{
				int xres, yres, bitdepth;
				bool windowed;
				WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
				float x_scale = (VPXMax - VPXMin) / xres;
				float y_scale = (VPYMax - VPYMin) / yres;
				int size_idx = (DefaultPointSize <= 1.0f) ? 0 : 1;
				Vector3 scaled_locs[3];
				scaled_locs[0].X = x_scale * _ScreenspaceVertexLocationSizeTable[size_idx][0].X;
				scaled_locs[0].Y = y_scale * _ScreenspaceVertexLocationSizeTable[size_idx][0].Y;
				scaled_locs[0].Z = _ScreenspaceVertexLocationSizeTable[size_idx][0].Z;
				scaled_locs[1].X = x_scale * _ScreenspaceVertexLocationSizeTable[size_idx][1].X;
				scaled_locs[1].Y = y_scale * _ScreenspaceVertexLocationSizeTable[size_idx][1].Y;
				scaled_locs[1].Z = _ScreenspaceVertexLocationSizeTable[size_idx][1].Z;
				scaled_locs[2].X = x_scale * _ScreenspaceVertexLocationSizeTable[size_idx][2].X;
				scaled_locs[2].Y = y_scale * _ScreenspaceVertexLocationSizeTable[size_idx][2].Y;
				scaled_locs[2].Z = _ScreenspaceVertexLocationSizeTable[size_idx][2].Z;
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = scaled_locs[0].X + point_loc->X;
					vertex_loc[0].Y = scaled_locs[0].Y + point_loc->Y;
					vertex_loc[0].Z = scaled_locs[0].Z + point_loc->Z;
					vertex_loc[1].X = scaled_locs[1].X + point_loc->X;
					vertex_loc[1].Y = scaled_locs[1].Y + point_loc->Y;
					vertex_loc[1].Z = scaled_locs[1].Z + point_loc->Z;
					vertex_loc[2].X = scaled_locs[2].X + point_loc->X;
					vertex_loc[2].Y = scaled_locs[2].Y + point_loc->Y;
					vertex_loc[2].Z = scaled_locs[2].Z + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
				}
			}
			break;

		case SCREEN_SIZE_NOORIENT:
		case SCREEN_SIZE_ORIENT:
			{
				int xres, yres, bitdepth;
				bool windowed;
				WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
				float x_scale = (VPXMax - VPXMin) / xres;
				float y_scale = (VPYMax - VPYMin) / yres;
				Vector3 scaled_locs[2][3];
				for (int i = 0; i < 2; i++) {
					scaled_locs[i][0].X = x_scale * _ScreenspaceVertexLocationSizeTable[i][0].X;
					scaled_locs[i][0].Y = y_scale * _ScreenspaceVertexLocationSizeTable[i][0].Y;
					scaled_locs[i][0].Z = _ScreenspaceVertexLocationSizeTable[i][0].Z;
					scaled_locs[i][1].X = x_scale * _ScreenspaceVertexLocationSizeTable[i][1].X;
					scaled_locs[i][1].Y = y_scale * _ScreenspaceVertexLocationSizeTable[i][1].Y;
					scaled_locs[i][1].Z = _ScreenspaceVertexLocationSizeTable[i][1].Z;
					scaled_locs[i][2].X = x_scale * _ScreenspaceVertexLocationSizeTable[i][2].X;
					scaled_locs[i][2].Y = y_scale * _ScreenspaceVertexLocationSizeTable[i][2].Y;
					scaled_locs[i][2].Z = _ScreenspaceVertexLocationSizeTable[i][2].Z;
				}
				for (i = 0; i < active_points; i++) {
					int size_idx = (point_size[0] <= 1.0f) ? 0 : 1;
					vertex_loc[0].X = point_loc->X + scaled_locs[size_idx][0].X;
					vertex_loc[0].Y = point_loc->Y + scaled_locs[size_idx][0].Y;
					vertex_loc[0].Z = point_loc->Z + scaled_locs[size_idx][0].Z;
					vertex_loc[1].X = point_loc->X + scaled_locs[size_idx][1].X;
					vertex_loc[1].Y = point_loc->Y + scaled_locs[size_idx][1].Y;
					vertex_loc[1].Z = point_loc->Z + scaled_locs[size_idx][1].Z;
					vertex_loc[2].X = point_loc->X + scaled_locs[size_idx][2].X;
					vertex_loc[2].Y = point_loc->Y + scaled_locs[size_idx][2].Y;
					vertex_loc[2].Z = point_loc->Z + scaled_locs[size_idx][2].Z;
					vertex_loc += 3;
					point_loc++;
					point_size++;
				}
			}
			break;

		default:
			WWASSERT(0);
			break;
	}
}
