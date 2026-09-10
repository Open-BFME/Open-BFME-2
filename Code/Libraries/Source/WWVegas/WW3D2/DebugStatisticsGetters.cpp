// cl: /O2 /DNDEBUG /MD
//
// Debug_Statistics last-frame getters. Each is `mov eax, [last]; ret` (6 bytes).

extern int g_last0;
extern int g_last1;
extern int g_last2;
extern int g_last3;
extern int g_last5;
extern int g_last6;
extern int g_last7;
extern int g_last8;

namespace Debug_Statistics
{
	int Get_DX8_Polygons();
	int Get_DX8_Vertices();
	int Get_DX8_Skin_Renders();
	int Get_DX8_Skin_Polygons();
	int Get_DX8_Skin_Vertices();
	int Get_Sorting_Polygons();
	int Get_Sorting_Vertices();
	int Get_Draw_Calls();
}

int Debug_Statistics::Get_DX8_Polygons()
{
	return g_last0;
}

int Debug_Statistics::Get_DX8_Vertices()
{
	return g_last1;
}

int Debug_Statistics::Get_DX8_Skin_Polygons()
{
	return g_last2;
}

int Debug_Statistics::Get_DX8_Skin_Vertices()
{
	return g_last3;
}

int Debug_Statistics::Get_DX8_Skin_Renders()
{
	return g_last5;
}

int Debug_Statistics::Get_Sorting_Polygons()
{
	return g_last6;
}

int Debug_Statistics::Get_Sorting_Vertices()
{
	return g_last7;
}

int Debug_Statistics::Get_Draw_Calls()
{
	return g_last8;
}
