// cl: /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// DX8Wrapper 4-arg draw wrappers. Both tail into landed
// DX8Wrapper::Draw at 0x001203C0 with a trailing true.
//   Draw_Triangles  0x00120620  33 bytes  type=4 (TRIANGLELIST)
//   Draw_Strip      0x001206D0  33 bytes  type=5 (TRIANGLESTRIP)
// Kept out of dx8wrapper.cpp so its other claimed bodies stay put.

#include "DX8WrapperClass.h"

// 0x00120650, 29 bytes: a non-indexed triangle list -- three vertices per
// polygon from start_vertex, Draw's trailing flag false.
void DX8Wrapper::bfmeRva00120650(unsigned start_vertex, unsigned polygon_count)
{
	Draw(4, 0, polygon_count, start_vertex, polygon_count * 3, false);
}

// 0x00120700, 29 bytes: the strip form -- polygon_count + 2 vertices.
void DX8Wrapper::bfmeRva00120700(unsigned start_vertex, unsigned polygon_count)
{
	Draw(5, 0, polygon_count, start_vertex, polygon_count + 2, false);
}

void DX8Wrapper::Draw_Triangles(unsigned start_index, unsigned polygon_count,
	unsigned min_vertex_index, unsigned vertex_count)
{
	unsigned vertexCount = vertex_count;
	unsigned m = min_vertex_index;
	unsigned p = polygon_count;
	Draw(4, start_index, p, m, vertexCount, true);
}

void DX8Wrapper::Draw_Strip(unsigned start_index, unsigned polygon_count,
	unsigned min_vertex_index, unsigned vertex_count)
{
	unsigned v = vertex_count;
	unsigned m = min_vertex_index;
	unsigned p = polygon_count;
	Draw(5, start_index, p, m, v, true);
}
