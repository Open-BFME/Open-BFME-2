// cl: /O2 /G7 /DNDEBUG /MD
//
// Debug_Statistics::Record_DX8_Polys_And_Vertices, retail 0x00129540, 68 bytes.
// Dedicated TU so Begin_Statistics can keep /O2 without this body's /G7.

extern int g_stat0;
extern int g_stat1;
extern int g_stat8;

class ShaderClass
{
public:
	unsigned char pad[2];
	unsigned char flags;
};

class DX8Caps
{
public:
	char pad[0x13B];
	bool SupportNPatches;
};

class DX8Wrapper
{
public:
	static DX8Caps *CurrentCaps;
};

class WW3D
{
public:
	static unsigned NPatchesLevel;
};

namespace Debug_Statistics
{
	void Record_DX8_Polys_And_Vertices(int polys, int verts, const ShaderClass &shader);
}

void Debug_Statistics::Record_DX8_Polys_And_Vertices(int polys, int verts, const ShaderClass &shader)
{
	int n;
	if (shader.flags & 2)
	{
		DX8Caps *caps = DX8Wrapper::CurrentCaps;
		if (caps->SupportNPatches)
		{
			unsigned level = WW3D::NPatchesLevel;
			n = (int)(level * level * (unsigned)polys);
		}
		else
		{
			n = polys;
		}
	}
	else
	{
		n = polys;
	}
	g_stat0 += n;
	g_stat1 += verts;
	g_stat8 += 1;
}
