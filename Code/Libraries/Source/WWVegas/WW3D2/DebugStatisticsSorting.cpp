// cl: /O2 /G7 /DNDEBUG /MD
//
// Debug_Statistics::Record_Sorting_Polys_And_Vertices, retail 0x001295F0,
// 28 bytes. Adds sorting polys/verts then increments the shared draw counter.

extern int g_stat6;
extern int g_stat7;
extern int g_stat8;

namespace Debug_Statistics
{
	void Record_Sorting_Polys_And_Vertices(int pcount, int vcount);
}

void Debug_Statistics::Record_Sorting_Polys_And_Vertices(int pcount, int vcount)
{
	g_stat6 += pcount;
	g_stat7 += vcount;
	g_stat8 += 1;
}
