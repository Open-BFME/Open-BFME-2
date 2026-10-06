// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
//
// ?Get_Bits_Per_Pixel@@YIIW4WW3DFormat@@@Z -- retail 0x00131A9D, 88 bytes of
// code plus its two jump tables. Ported from the BFME1 ww3dformat_bits donor,
// which proves the __fastcall ABI (the format arrives in ecx with nothing
// pushed) and the D3DFORMAT numbering (20-30 contiguous, 40/41, 50-52, and
// the 'DXT1'-0x31545844 FOURCCs -- retail's sub-0x31545810 check reads low
// only because the sub-0x33/dec pair ahead of it has already taken 0x34 off).
//
// BFME2 codegen note: /O1 builds retail's decision tree (50-cluster range
// check first, then the 20-41 jump table, then the 51/52/DXT chain) with the
// push-imm/pop-eax case returns; /O2 checks the 40-cluster first instead.

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN		= 0,

	// D3DFMT_R8G8B8 through D3DFMT_X4R4G4B4, contiguous, which is what lets
	// MSVC reach them through one index table.
	WW3D_FORMAT_R8G8B8		= 20,
	WW3D_FORMAT_A8R8G8B8	= 21,
	WW3D_FORMAT_X8R8G8B8	= 22,
	WW3D_FORMAT_R5G6B5		= 23,
	WW3D_FORMAT_X1R5G5B5	= 24,
	WW3D_FORMAT_A1R5G5B5	= 25,
	WW3D_FORMAT_A4R4G4B4	= 26,
	WW3D_FORMAT_R3G3B2		= 27,
	WW3D_FORMAT_A8			= 28,
	WW3D_FORMAT_A8R3G3B2	= 29,
	WW3D_FORMAT_X4R4G4B4	= 30,

	WW3D_FORMAT_A8P8		= 40,
	WW3D_FORMAT_P8			= 41,
	WW3D_FORMAT_L8			= 50,
	WW3D_FORMAT_A8L8		= 51,
	WW3D_FORMAT_A4L4		= 52,

	WW3D_FORMAT_DXT1		= 0x31545844,	// 'DXT1'
	WW3D_FORMAT_DXT2		= 0x32545844,
	WW3D_FORMAT_DXT3		= 0x33545844,
	WW3D_FORMAT_DXT4		= 0x34545844,
	WW3D_FORMAT_DXT5		= 0x35545844,
};

// ?Get_Bits_Per_Pixel@@YIIW4WW3DFormat@@@Z
unsigned __fastcall Get_Bits_Per_Pixel( WW3DFormat format )
{
	// Zeroed up front rather than returned from a default arm: that is what puts
	// retail's xor eax,eax ahead of the range checks and lets the unmatched
	// formats fall straight through to the shared ret.
	unsigned bits = 0;

	switch( format )
	{
		case WW3D_FORMAT_A8R8G8B8:
		case WW3D_FORMAT_X8R8G8B8:
			bits = 32;
			break;

		case WW3D_FORMAT_R8G8B8:
			bits = 24;
			break;

		case WW3D_FORMAT_R5G6B5:
		case WW3D_FORMAT_X1R5G5B5:
		case WW3D_FORMAT_A1R5G5B5:
		case WW3D_FORMAT_A4R4G4B4:
		case WW3D_FORMAT_A8R3G3B2:
		case WW3D_FORMAT_X4R4G4B4:
		case WW3D_FORMAT_A8P8:
		case WW3D_FORMAT_A8L8:
			bits = 16;
			break;

		case WW3D_FORMAT_R3G3B2:
		case WW3D_FORMAT_A8:
		case WW3D_FORMAT_P8:
		case WW3D_FORMAT_L8:
		case WW3D_FORMAT_A4L4:
		case WW3D_FORMAT_DXT2:
		case WW3D_FORMAT_DXT3:
		case WW3D_FORMAT_DXT4:
		case WW3D_FORMAT_DXT5:
			bits = 8;
			break;

		// The one format that is not a whole number of bytes, and the reason
		// this returns bits where Zero Hour returned bytes.
		case WW3D_FORMAT_DXT1:
			bits = 4;
			break;

		default:
			break;
	}

	return bits;
}
