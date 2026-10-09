// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.88 date=2026-10-09
// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.85 date=2026-10-04
// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ScreenMapperClass::Calculate_Texture_Matrix, retail 0x00186380.
// Evidence: slot 9 (+0x24) of vtable 0x007D32D0, the table the matched
// ScreenMapperClass constructor 0x0013DA40 and Clone 0x0013DA80 install
// (TextureMapperApply.cpp). Zero Hour mapper.cpp body; built in its own unit
// with LinearOffsetTextureMapperCalculate.cpp's flags so mapper.cpp keeps its
// matched bodies.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

// DX8Wrapper's device projection copy at VA 0x00DEDBF0 (bfmecamera shim:
// DX8Wrapper::DeviceProjectionMatrix), defined under this name in
// TextureMapperApply.cpp. BFME2 answers Get_Transform(D3DTS_PROJECTION) from
// it rather than from the device.
extern Matrix4x4 g_mapperProjectionUpload_009EDBF0;

void ScreenMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
	float del = (float)delta;
	float offset_u = CurrentUVOffset.X + UVOffsetDeltaPerMS.X * del;
	float offset_v = CurrentUVOffset.Y + UVOffsetDeltaPerMS.Y * del;

	// We need to clamp these texture coordinates to a reasonable range so the hardware doesn't
	// choke on them. We do this in one of two ways:
	// If ClampFix is not TRUE we use the fractional part of the offset, restricting it between
	// 0 and 1 with wraparound. This works well for tiled textures.
	// If ClampFix is TRUE we clamp the offsets between -Scale and +Scale with no wraparound.
	// This works well for clamped textures.
	if (!ClampFix) {
		offset_u = offset_u - WWMath::Floor(offset_u);
		offset_v = offset_v - WWMath::Floor(offset_v);
	} else {
		offset_u = WWMath::Clamp(offset_u, -Scale.X, Scale.X);
		offset_v = WWMath::Clamp(offset_v, -Scale.Y, Scale.Y);
	}

	// multiply by projection matrix
	// followed by scale and translation
	tex_matrix = g_mapperProjectionUpload_009EDBF0.Transpose();
	tex_matrix[0] *= Scale.X; // entire row since we're pre-multiplying
	float ky=Scale.Y;
 tex_matrix[1].X=ky*tex_matrix[1].X;
 tex_matrix[1].Y=ky*tex_matrix[1].Y;
 tex_matrix[1].Z=ky*tex_matrix[1].Z;
 tex_matrix[1].W=ky*tex_matrix[1].W;
	Vector4 last(tex_matrix[3]); // this gets the w
	last *= offset_u; // multiply by w because the projected flag will divide by w
	tex_matrix[0].X=last.X+tex_matrix[0].X;
tex_matrix[0].Y=last.Y+tex_matrix[0].Y;
tex_matrix[0].Z=last.Z+tex_matrix[0].Z;
tex_matrix[0].W=last.W+tex_matrix[0].W;
	last = tex_matrix[3];
	last *= offset_v;
	tex_matrix[1].X=last.X+tex_matrix[1].X;
tex_matrix[1].Y=last.Y+tex_matrix[1].Y;
tex_matrix[1].Z=last.Z+tex_matrix[1].Z;
tex_matrix[1].W=last.W+tex_matrix[1].W;

	// Update state
	CurrentUVOffset.X = offset_u;
	CurrentUVOffset.Y = offset_v;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}
