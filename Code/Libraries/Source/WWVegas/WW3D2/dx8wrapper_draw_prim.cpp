// cl: /O2 /DNDEBUG /MD
//
// DX8Wrapper 4-arg draw wrappers. Both tail into landed
// BfmeDrawOps::Draw at 0x001203C0 with a trailing true.
//   Draw_Triangles  0x00120620  33 bytes  type=4 (TRIANGLELIST)
//   Draw_Strip      0x001206D0  33 bytes  type=5 (TRIANGLESTRIP)
// Kept out of dx8wrapper.cpp so its other claimed bodies stay put.

class BfmeDrawOps
{
public:
	static void Draw(unsigned type, unsigned start_index, unsigned polygon_count,
		unsigned min_vertex_index, unsigned vertex_count, bool extra);
};

class DX8Wrapper
{
public:
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count,
		unsigned min_vertex_index, unsigned vertex_count);
	static void Draw_Strip(unsigned start_index, unsigned polygon_count,
		unsigned min_vertex_index, unsigned vertex_count);
	// Two-argument, non-indexed siblings with no Zero Hour counterpart, so
	// their names are address-derived.
	static void bfmeRva00120650(unsigned start_vertex, unsigned polygon_count);
	static void bfmeRva00120700(unsigned start_vertex, unsigned polygon_count);
};

// 0x00120650, 29 bytes: a non-indexed triangle list -- three vertices per
// polygon from start_vertex, Draw's trailing flag false.
void DX8Wrapper::bfmeRva00120650(unsigned start_vertex, unsigned polygon_count)
{
	BfmeDrawOps::Draw(4, 0, polygon_count, start_vertex, polygon_count * 3, false);
}

// 0x00120700, 29 bytes: the strip form -- polygon_count + 2 vertices.
void DX8Wrapper::bfmeRva00120700(unsigned start_vertex, unsigned polygon_count)
{
	BfmeDrawOps::Draw(5, 0, polygon_count, start_vertex, polygon_count + 2, false);
}

void DX8Wrapper::Draw_Triangles(unsigned start_index, unsigned polygon_count,
	unsigned min_vertex_index, unsigned vertex_count)
{
	unsigned v = vertex_count;
	unsigned m = min_vertex_index;
	unsigned p = polygon_count;
	BfmeDrawOps::Draw(4, start_index, p, m, v, true);
}

void DX8Wrapper::Draw_Strip(unsigned start_index, unsigned polygon_count,
	unsigned min_vertex_index, unsigned vertex_count)
{
	unsigned v = vertex_count;
	unsigned m = min_vertex_index;
	unsigned p = polygon_count;
	BfmeDrawOps::Draw(5, start_index, p, m, v, true);
}
