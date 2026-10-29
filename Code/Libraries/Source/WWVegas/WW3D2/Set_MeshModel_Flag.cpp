// cl: /DNDEBUG /MD
//
// Retail 0x00149FD0, 153 bytes, cdecl (robj, flags, onoff). Name unknown;
// placed among the mesh.cpp bodies (after MeshClass::Generate_Culling_Tree
// 0x00149FC0). Recursively sets or clears bits in the model flag word:
// when the render object's slot 3 (+0x0C) answers 0 (the mesh class id), its
// slot 5 (+0x14) object's +0xC4 model -- fetched with the add-ref/re-read
// shape of the rowed MeshClass::Get_Model 0x001499B0 -- gets `flags` or-ed
// into or cleared from its +0x18 word (MeshGeometryClass::Flags) and is
// released; otherwise every sub-object (slot 28 count, slot 30 getter) is
// visited and released. The only call is its own recursion (0x0014A049).
// Types are views of only what the body touches; names address-derived.

class Rva00149FD0Model
{
public:
	virtual void Delete_This();

	void Add_Ref() { NumRefs++; }
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
	char m_pad08[0x18 - 0x08];
	unsigned int Flags;
};

class Rva00149FD0Mesh
{
public:
	Rva00149FD0Model *Get_Model()
	{
		if (Model)
			Model->Add_Ref();
		return Model;
	}

	char m_pad00[0xC4];
	Rva00149FD0Model *Model;
};

class Rva00149FD0RenderObj
{
public:
	virtual void Delete_This();
	virtual void v01();
	virtual void v02();
	virtual int Class_ID();
	virtual void v04();
	virtual Rva00149FD0Mesh *v05();
	virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
	virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
	virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
	virtual void v26(); virtual void v27();
	virtual int Get_Num_Sub_Objects();
	virtual void v29();
	virtual Rva00149FD0RenderObj *Get_Sub_Object(int index);

	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

void __cdecl Set_MeshModel_Flag(Rva00149FD0RenderObj *robj, unsigned int flags, int onoff)
{
	if (robj->Class_ID() == 0) {
		Rva00149FD0Model *model = robj->v05()->Get_Model();
		if (onoff)
			model->Flags |= flags;
		else
			model->Flags &= ~flags;
		model->Release_Ref();
	} else {
		int count = robj->Get_Num_Sub_Objects();
		for (int i = 0; i < count; i++) {
			Rva00149FD0RenderObj *sub = robj->Get_Sub_Object(i);
			if (sub) {
				Set_MeshModel_Flag(sub, flags, onoff);
				sub->Release_Ref();
			}
		}
	}
}
