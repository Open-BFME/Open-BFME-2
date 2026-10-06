// ?Calculate_Texture_Matrix@WSEnvMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.9269 date=2026-10-05
// cl: /Ireference/shims/bfmestages /G7 /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Banked partial: WSEnvMapperClass::Calculate_Texture_Matrix, RVA 0x1854E0.
// Boundary discovery batch 6 proves 1174 bytes. Existing WSEnv constructors
// install table 0x7D3210, whose slot +0x24 identifies this candidate.
// Reference: EA GeneralsMD WW3D2/mapper.cpp. The 16-scalar Init operations
// are expanded into element assignments to use the BFME1 Matrix4 interface.
// No exact recovery: emits 1172 bytes; first mismatch +0x7F is row-2 store
// ordering, followed by SSE register allocation differences. No unresolved calls.
// /G7 and /arch:SSE are supported by the nearby verified Apply bodies.


#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>


void WSEnvMapperClass::Calculate_Texture_Matrix(Matrix4x4 &tex_matrix)
{
	// The canonical environment map
	// scale the normal by (.5,.5) and add (.5,.5) to move it to (0,1) range
	switch (Axis) {
		case AXISTYPE_X:
				tex_matrix[0].X = 0.0f;
	tex_matrix[0].Y = 0.5f;
	tex_matrix[0].Z = 0.0f;
	tex_matrix[0].W = 0.5f;
	tex_matrix[1].Y = 0.0f;
	tex_matrix[1].Z = 0.5f;
	tex_matrix[1].X = 0.0f;
	tex_matrix[1].W = 0.5f;
	tex_matrix[2].W = 0.0f;
	tex_matrix[2].Z = 1.0f;
	tex_matrix[2].Y = 0.0f;
	tex_matrix[2].X = 0.0f;
	tex_matrix[3].X = 0.0f;
	tex_matrix[3].Y = 0.0f;
	tex_matrix[3].Z = 0.0f;
	tex_matrix[3].W = 1.0f;
			break;
		case AXISTYPE_Y:
				tex_matrix[0].X = 0.5f;
	tex_matrix[0].Y = 0.0f;
	tex_matrix[0].Z = 0.0f;
	tex_matrix[0].W = 0.5f;
	tex_matrix[1].Y = 0.0f;
	tex_matrix[1].X = 0.0f;
	tex_matrix[1].W = 0.5f;
	tex_matrix[1].Z = 0.5f;
	tex_matrix[2].W = 0.0f;
	tex_matrix[2].Z = 1.0f;
	tex_matrix[2].X = 0.0f;
	tex_matrix[2].Y = 0.0f;
	tex_matrix[3].Y = 0.0f;
	tex_matrix[3].W = 1.0f;
	tex_matrix[3].Z = 0.0f;
	tex_matrix[3].X = 0.0f;
			break;
		case AXISTYPE_Z:
		default:
				tex_matrix[0].X = 0.5f;
	tex_matrix[0].Y = 0.0f;
	tex_matrix[0].Z = 0.0f;
	tex_matrix[0].W = 0.5f;
	tex_matrix[1].X = 0.0f;
	tex_matrix[1].Y = 0.5f;
	tex_matrix[1].Z = 0.0f;
	tex_matrix[1].W = 0.5f;
	tex_matrix[2].X = 0.0f;
	tex_matrix[2].Y = 0.0f;
	tex_matrix[2].Z = 1.0f;
	tex_matrix[2].W = 0.0f;
	tex_matrix[3].W = 1.0f;
	tex_matrix[3].Y = 0.0f;
	tex_matrix[3].X = 0.0f;
	tex_matrix[3].Z = 0.0f;
			break;
	}
	// multiply by inverse of view transform	
	Matrix4x4 mat;	
	Matrix4x4 mat2;
	DX8Wrapper::Get_Transform(D3DTS_VIEW,mat);		
	mat2[0].X = mat[0].X;
	mat2[1].W = 0.0f;
	mat2[1].X = mat[0].Y;
	mat2[0].Y = mat[1].X;
	mat2[0].Z = mat[2].X;
	mat2[2].X = mat[0].Z;
	mat2[1].Y = mat[1].Y;
	mat2[1].Z = mat[2].Y;
	mat2[2].W = 0.0f;
	mat2[0].W = 0.0f;
	mat2[2].Z = mat[2].Z;
	mat2[2].Y = mat[1].Z;
	mat2[3].X = 0.0f;
	mat2[3].Y = 0.0f;
	mat2[3].Z = 0.0f;
	mat2[3].W = 1.0f;						  	
	tex_matrix = tex_matrix * mat2;	
}


// Resume: scalar-Init and product-temporary variants did not match. Use
// bfmestages first: verified render-state has 16 textures and view at +22C.
