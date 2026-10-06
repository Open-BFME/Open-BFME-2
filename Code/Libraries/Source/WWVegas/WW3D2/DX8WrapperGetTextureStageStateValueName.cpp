// flags: region default (reverse/retail_inventory/flag_regions.csv)
// DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name (retail 0x00120B90,
// 266 bytes): switch over the D3D texture-stage state formatting the value
// into a StringClass. BFME1 dx8wrapper.cpp with one evidence-backed repair:
// retail's switch map sends MIPMAPLODBIAS (19) to the UNKNOWN default, so it
// is not among the float cases, and the ADDRESS/FILTER/MAX/BORDER arms this
// tree's dx8wrapper.cpp carries are absent (their states all map default).
// Static member; every callee (the three used Get_DX8_*_Name helpers,
// StringClass::operator=(const char*), StringClass::Format) stays out-of-line
// via declared-only decls and resolves to its matched row.
// /G7 for the add-of--1 switch bounds check (dx8wrapper_names.cpp rule).

class StringClass
{
public:
	const StringClass &operator=(const char *string);
	int _cdecl Format(const char *format, ...);
};

enum D3DTEXTURESTAGESTATETYPE
{
	D3DTSS_COLOROP = 1,
	D3DTSS_COLORARG1 = 2,
	D3DTSS_COLORARG2 = 3,
	D3DTSS_ALPHAOP = 4,
	D3DTSS_ALPHAARG1 = 5,
	D3DTSS_ALPHAARG2 = 6,
	D3DTSS_BUMPENVMAT00 = 7,
	D3DTSS_BUMPENVMAT01 = 8,
	D3DTSS_BUMPENVMAT10 = 9,
	D3DTSS_BUMPENVMAT11 = 10,
	D3DTSS_TEXCOORDINDEX = 11,
	D3DTSS_ADDRESSU = 13,
	D3DTSS_ADDRESSV = 14,
	D3DTSS_BORDERCOLOR = 15,
	D3DTSS_MAGFILTER = 16,
	D3DTSS_MINFILTER = 17,
	D3DTSS_MIPFILTER = 18,
	D3DTSS_MIPMAPLODBIAS = 19,
	D3DTSS_MAXMIPLEVEL = 20,
	D3DTSS_MAXANISOTROPY = 21,
	D3DTSS_BUMPENVLSCALE = 22,
	D3DTSS_BUMPENVLOFFSET = 23,
	D3DTSS_TEXTURETRANSFORMFLAGS = 24,
	D3DTSS_ADDRESSW = 25,
	D3DTSS_COLORARG0 = 26,
	D3DTSS_ALPHAARG0 = 27,
	D3DTSS_RESULTARG = 28
};

#define D3DTSS_TCI_CAMERASPACENORMAL 0x00010000
#define D3DTSS_TCI_CAMERASPACEPOSITION 0x00020000
#define D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR 0x00030000

class DX8Wrapper
{
public:
	static const char *Get_DX8_Texture_Op_Name(unsigned value);
	static const char *Get_DX8_Texture_Arg_Name(unsigned value);
	static const char *Get_DX8_Texture_Transform_Flag_Name(unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
};

void DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value)
{
	switch (state) {
	case D3DTSS_COLOROP:
	case D3DTSS_ALPHAOP:
		name = Get_DX8_Texture_Op_Name(value);
		break;

	case D3DTSS_COLORARG0:
	case D3DTSS_COLORARG1:
	case D3DTSS_COLORARG2:
	case D3DTSS_ALPHAARG0:
	case D3DTSS_ALPHAARG1:
	case D3DTSS_ALPHAARG2:
	case D3DTSS_RESULTARG:
		name = Get_DX8_Texture_Arg_Name(value);
		break;

	case D3DTSS_TEXTURETRANSFORMFLAGS:
		name = Get_DX8_Texture_Transform_Flag_Name(value);

	// Floating point values
	case D3DTSS_BUMPENVMAT00:
	case D3DTSS_BUMPENVMAT01:
	case D3DTSS_BUMPENVMAT10:
	case D3DTSS_BUMPENVMAT11:
	case D3DTSS_BUMPENVLSCALE:
	case D3DTSS_BUMPENVLOFFSET:
		name.Format("%f", *(float *)&value);
		break;

	case D3DTSS_TEXCOORDINDEX:
		if ((value & 0xffff0000) == D3DTSS_TCI_CAMERASPACENORMAL) {
			name.Format("D3DTSS_TCI_CAMERASPACENORMAL|%d", value & 0xffff);
		}
		else if ((value & 0xffff0000) == D3DTSS_TCI_CAMERASPACEPOSITION) {
			name.Format("D3DTSS_TCI_CAMERASPACEPOSITION|%d", value & 0xffff);
		}
		else if ((value & 0xffff0000) == D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR) {
			name.Format("D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR|%d", value & 0xffff);
		}
		else {
			name.Format("%d", value);
		}
		break;

	// Integer value
	default:
		name.Format("UNKNOWN (%d)", value);
		break;
	}
}
