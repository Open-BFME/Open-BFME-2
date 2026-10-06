// cl: /MD /EHsc
//
// ?Add_Mesh@DX8SkinFVFCategoryContainer@@UAEXPAVMeshModelClass@@@Z retail
// 0x00146EE0, 101 bytes.
//
// ZH dx8renderer.cpp body: build the out-of-line Vertex_Split_Table from the
// mesh (rowed ctor 0x001454D0; layout mmc@0x00, npatch_enable@0x04,
// polygon_count@0x08, polygon_array@0x0C, allocated_polygon_array@0x10), pass
// it to the base DX8FVFCategoryContainer::Generate_Texture_Categories(table,0)
// (unrowed 0x00146BA0, ret 8), then run the inlined ~Vertex_Split_Table, which
// frees polygon_array through operator delete[] 0x0002FD80. /EHsc plus a
// nothrow declaration of operator delete[] reproduces retail's EH shape
// (state reset is absent only when the deallocator cannot throw). Callee
// identities are the ZH member names; only the 101 retail bytes are proven.

class MeshModelClass;

typedef unsigned short TriIndex[3];

// Retail's destructor runs with the try level already reset, which MSVC only
// emits when it knows the deallocator cannot throw; declare the standard
// operator delete[] that way before the inlined destructor uses it.
void __cdecl operator delete[](void *p) throw();

class Vertex_Split_Table
{
public:
	__declspec(noinline) Vertex_Split_Table(MeshModelClass *mmc);
	~Vertex_Split_Table()
	{
		if (allocated_polygon_array)
			delete[] polygon_array;
	}

private:
	MeshModelClass *mmc;          // +0x00
	bool npatch_enable;           // +0x04
	unsigned polygon_count;       // +0x08
	TriIndex *polygon_array;      // +0x0C
	bool allocated_polygon_array; // +0x10
};

class DX8FVFCategoryContainer
{
public:
	virtual void Add_Mesh(MeshModelClass *mmc) = 0;
	void Generate_Texture_Categories(Vertex_Split_Table &split_table, unsigned vertex_offset);
};

class DX8SkinFVFCategoryContainer : public DX8FVFCategoryContainer
{
public:
	virtual void Add_Mesh(MeshModelClass *mmc);
};

void DX8SkinFVFCategoryContainer::Add_Mesh(MeshModelClass *mmc)
{
	Vertex_Split_Table split_table(mmc);
	Generate_Texture_Categories(split_table, 0);
}
