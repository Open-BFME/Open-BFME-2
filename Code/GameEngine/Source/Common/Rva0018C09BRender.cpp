// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Begin_Rendering@FXShaderGeometry@@QAEXG@Z @0x0018C09B 76B
// Render setup: unless byte at +0 set vb at +0xC via Set_Vertex 0, then ib at
// +0x10 via Set_Index with WORD arg, then Draw via D3DDevice slot 87 with
// count at +8 unless zero, inc number_of_DX8_calls. Evidence: unlock lane,
// rowed Set_Vertex 0x0011D4A0 plus Set_Index 0x0011D530, extern D3DDevice plus
// number_of_DX8_calls, ret-4 WORD arg, 1 caller, honest rva name.
class VertexBufferClass;
class IndexBufferClass;
struct IDirect3DDevice8;

class FXShaderGeometry;

class DX8Wrapper
{
public:
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned int stream);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index);
protected:
	static struct IDirect3DDevice8 *D3DDevice;
	friend class FXShaderGeometry;
};

extern unsigned int number_of_DX8_calls;

typedef void (__stdcall *Rva0018C09BDrawFunc)(struct IDirect3DDevice8 *, int);

class FXShaderGeometry
{
public:
	void Begin_Rendering(unsigned short idx);
private:
	unsigned char m_flag0;
	char m_pad01[7];
	int m_count08;
	VertexBufferClass *m_vb0C;
	IndexBufferClass *m_ib10;
};

void FXShaderGeometry::Begin_Rendering(unsigned short idx)
{
	if (m_flag0 == 0) {
		VertexBufferClass *vb = m_vb0C;
		if (vb == 0)
			return;
		DX8Wrapper::Set_Vertex_Buffer(vb, 0);
	}
	IndexBufferClass *ib = m_ib10;
	if (ib == 0)
		return;
	DX8Wrapper::Set_Index_Buffer(ib, idx);
	int cnt = m_count08;
	if (cnt == 0)
		return;
	struct IDirect3DDevice8 *dev = DX8Wrapper::D3DDevice;
	(*(Rva0018C09BDrawFunc **)dev)[87](dev, cnt);
	++number_of_DX8_calls;
}
