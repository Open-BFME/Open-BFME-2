// cl: /O2 /G7 /DNDEBUG /MD
//
// Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices, retail 0x00129520,
// 28 bytes. Adds polys/verts then increments the skin-render counter.

extern int g_stat2;
extern int g_stat3;
extern int g_stat5;

namespace Debug_Statistics
{
	void Record_DX8_Skin_Polys_And_Vertices(int pcount, int vcount);
}

void Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(int pcount, int vcount)
{
	g_stat2 += pcount;
	g_stat3 += vcount;
	g_stat5 += 1;
}
