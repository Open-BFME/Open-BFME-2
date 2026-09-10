// ?Check_Texture_Compression_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
// partial score=0.75 date=2026-09-10
// cl: /G7 /arch:SSE /DNDEBUG /MD
//
// DX8Caps::Check_Texture_Compression_Support, retail 0x0012B4E0, 98 bytes.
// Dedicated TU so dx8caps.cpp cannot see this definition. The five DXT flags
// sit at 0x1B4..0x1B8 and SupportDXTC at 0x139; capsLog is at 0x2DC.

class StringClass
{
public:
	int Format(char const *format, ...);
	const StringClass &operator+=(StringClass const &that);
};

StringClass CapsWorkString;

struct _D3DCAPS8
{
	int unused;
};

class DX8Caps
{
	void Check_Texture_Compression_Support(const _D3DCAPS8 &caps);
};

struct BFME_DX8Caps_CompressionFields
{
	char pad[0x139];
	bool supportDXTC;
	char padToDXT[0x1b4 - 0x13a];
	bool supportDXT1;
	bool supportDXT2;
	bool supportDXT3;
	bool supportDXT4;
	bool supportDXT5;
	char padToLog[0x2dc - 0x1b9];
	StringClass capsLog;
};

void DX8Caps::Check_Texture_Compression_Support(const _D3DCAPS8 &caps)
{
	BFME_DX8Caps_CompressionFields *retail = (BFME_DX8Caps_CompressionFields *)this;
	bool dxt5 = retail->supportDXT5;
	bool dxt4 = retail->supportDXT4;
	bool dxt2 = retail->supportDXT2;
	bool dxt1 = retail->supportDXT1;
	bool ok = dxt5 | dxt4 | retail->supportDXT3 | dxt2 | dxt1;
	retail->supportDXTC = ok;
	CapsWorkString.Format("Texture compression support: %s\r\n", ok ? "Yes" : "No");
	retail->capsLog += CapsWorkString;
}
