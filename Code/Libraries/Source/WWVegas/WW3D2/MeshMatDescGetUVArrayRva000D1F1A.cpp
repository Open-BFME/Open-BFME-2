// Target boundary 0x000D1F1A/38 is a two-index MeshMatDescClass UV-array
// lookup. Direct callers pass (pass,stage), including (0,0) and (0,1). Retail
// reads a source-index grid at this+0x30, a buffer table at this+0x10, and the
// returned Vector2* at UVBuffer+0x0C.
//
// Donor provenance: the original Generals meshmatdesc.h defines
// Get_UV_Array(pass,stage) as UVSource[pass][stage] -> UV[source] -> Get_Array.
// Its W3DMPO base accounts for the +0x10/+0x30 table offsets. The BFME1 Code
// header drops that empty base and instead places those tables at +0x0C/+0x2C;
// this TU uses a target-evidenced partial view rather than claiming any wider
// MeshMatDescClass layout. The Rva prefixes and buffer prefix stay opaque.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2
// stlport
#include <stddef.h>

class Vector2;

class Rva000D1F1AUVBuffer
{
	unsigned char m_prefix[0x0C];
	Vector2 *m_array;
public:
	Vector2 *Get_Array(void) { return m_array; }
};

class MeshMatDescClass
{
	unsigned char Rva000D1F1AHeader[0x10];
	Rva000D1F1AUVBuffer *UV[8];
	int UVSource[4][2];
public:
	Vector2 *Get_UV_Array(int pass, int stage);
};

Vector2 *MeshMatDescClass::Get_UV_Array(int pass, int stage)
{
	if (UVSource[pass][stage] == -1) {
		return NULL;
	}
	if (UV[UVSource[pass][stage]] != NULL) {
		return UV[UVSource[pass][stage]]->Get_Array();
	}
	return NULL;
}
