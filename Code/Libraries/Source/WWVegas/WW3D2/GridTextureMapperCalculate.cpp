// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// Reference: GeneralsMD WW3D2/mapper.cpp Calculate_Texture_Matrix;
// BFME2 already matched update_temporal_state (0x182590) and
// calculate_uv_offset (0x1825E0) are visible inline, as in the retail body.
// Identity: matched GridTextureMapper constructors install table 0x7D57B4;
// its slot +0x24 points to retail RVA 0x1849A0, 267 bytes (boundary batch12).
// Constructor identity comes from existing donor matches. Retail separately
// establishes the frame timing arithmetic, UV offsets and identity matrix.
// GridClassicEnvironmentMapperClass matrix: RVA 0x183740, 260 bytes.
// Matched constructor 0x13D2F0 installs table 0x7D32A8; slot+0x24 reaches
// this body. The Environment variant shares it and is not counted twice.
// The local initMatrix preserves the donor scalar-argument evaluation order;
// expanding its call into direct assignments prematurely rounds UV products.
// The bfmemapper shim supplies the constructor-verified +4 grid layout shift.

#include "../../../../../reference/shims/bfme_matrix3d_link/vector4.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "../../../../../reference/shims/bfme_grid_mapper_link/mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>


inline void GridTextureMapperClass::update_temporal_state()
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta = now - LastUsedSyncTime;
	Remainder += delta;
	LastUsedSyncTime = now;

	int new_frame = (int)CurrentFrame + ((int)(Remainder / MSPerFrame) * Sign);
	new_frame = (int)((unsigned)new_frame % LastFrame);

	if (new_frame < 0)
		CurrentFrame = LastFrame + new_frame;
	else
		CurrentFrame = (unsigned int)new_frame;
	Remainder = Remainder % MSPerFrame;
}

__declspec(dllimport) __forceinline void GridTextureMapperClass::calculate_uv_offset(float * u_offset, float * v_offset)
{
	unsigned int row_mask = ~(0xFFFFFFFF << GridWidthLog2);
	unsigned int col_mask = row_mask << GridWidthLog2;
	unsigned int x = CurrentFrame & row_mask;
	unsigned int y = (CurrentFrame & col_mask) >> GridWidthLog2;
	*u_offset = x * OOGridWidth;
	*v_offset = y * OOGridWidth;
}
void GridTextureMapperClass::Calculate_Texture_Matrix(Matrix4x4 &tex_matrix)
{
	update_temporal_state();

	float u_offset, v_offset;
	calculate_uv_offset(&u_offset, &v_offset);

	// Set up the offset matrix
	tex_matrix.Make_Identity();
	
	// According to the docs this should work since its 2D
	// otherwise change to translate
	tex_matrix[0].Z = u_offset;
	tex_matrix[1].Z = v_offset;
}
static __forceinline void initMatrix(Matrix4 &m, float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15) {
    m[0].Set(m0, m1, m2, m3);
    m[1].Set(m4, m5, m6, m7);
    m[2].Set(m8, m9, m10, m11);
    m[3].Set(m12, m13, m14, m15);
}

void GridClassicEnvironmentMapperClass::Calculate_Texture_Matrix(Matrix4x4 &tex_matrix)
{
	update_temporal_state();

	float u_offset, v_offset;
	calculate_uv_offset(&u_offset, &v_offset);

	float del = 0.5f * OOGridWidth;	
	// Set up the offset matrix		
	initMatrix(tex_matrix, 	del,	0.0f,	0.0f,	u_offset + del,
							0.0f,	del,	0.0f,	v_offset + del,
							0.0f,	0.0f,	1.0f,	0.0f,
							0.0f, 0.0f, 0.0f, 1.0f );		
}
