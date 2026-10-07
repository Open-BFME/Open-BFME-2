// cl: /DNDEBUG /MD /EHsc
//
// MeshClass::Make_Unique at 0x00149C10 and MeshClass::Load_W3D at 0x00149CC0.
//
// Zero Hour's bodies: Make_Unique clones the shared MeshModelClass unless this
// mesh is its only user, then swaps the clone in with the usual reference
// counting; Load_W3D creates and loads a fresh model and derives the
// collision, hidden and translucency bits from it. They live in their own unit
// because retail allocates models with the plain global operator new, where
// mesh.cpp's MeshModelClass carries the W3D memory pool allocator and would
// call into the pool instead. The classes below are reduced to the offsets the
// bodies touch: in BFME 2 the model pointer sits at +0xC4 and a MeshModelClass
// is 0xC4 bytes, four less than in BFME 1. /G7 is the unit's tell (add reg,1
// and sub reg,1 where the default build writes inc and dec).
//
// Load_W3D target evidence: the only caller (the mesh prototype loader at
// 0x00180274) news a 0x324-byte MeshClass, calls this with its ChunkLoadClass
// and tests the bool result. BFME 2 deltas from Zero Hour: the model's
// Load_W3D is its virtual slot 2 returning bool, Set_Collision_Type takes a
// second bool (RenderObjClass's rowed 0x0013BAF0), and a mesh without a
// per-polygon shader array but with either per-pass slot at material +0xB8 or
// +0x108 (the FX shader buffers MeshMatDescClass gained) clears all three
// translucency flags instead of reading its single shader.

class ChunkLoadClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	enum AlphaTestType { ALPHATEST_DISABLE = 0, ALPHATEST_ENABLE };
	enum DstBlendFuncType { DSTBLEND_ZERO = 0, DSTBLEND_ONE };
	enum SrcBlendFuncType { SRCBLEND_ZERO = 0, SRCBLEND_ONE };

	ShaderClass(const ShaderClass &s) : ShaderBits(s.ShaderBits) {}

	AlphaTestType Get_Alpha_Test() const { return (AlphaTestType)((ShaderBits >> 18) & 3); }
	DstBlendFuncType Get_Dst_Blend_Func() const { return (DstBlendFuncType)((ShaderBits >> 5) & 7); }
	SrcBlendFuncType Get_Src_Blend_Func() const { return (SrcBlendFuncType)((ShaderBits >> 14) & 3); }

	unsigned long ShaderBits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.h
class MeshMatDescClass
{
public:
	ShaderClass Get_Shader(int pidx, int pass) const;
	ShaderClass Get_Single_Shader(int pass) const { return Shader[pass]; }
	bool Has_Shader_Array(int pass) const { return ShaderArray[pass] != 0; }
	bool Has_Pass_Buffer(int pass) const { return PassBufferB8[pass] != 0 || PassBuffer108[pass] != 0; }

	char Pad[0x98];
	ShaderClass Shader[4];			// +0x98
	void *Material[4];			// +0xA8
	void *PassBufferB8[4];			// +0xB8, BFME 2 per-pass slot
	void *TextureArray[4][2];		// +0xC8
	void *MaterialArray[4];			// +0xE8
	void *ShaderArray[4];			// +0xF8
	void *PassBuffer108[4];			// +0x108, BFME 2 per-pass slot
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
public:
	enum { SORT = 0x10 };

	MeshModelClass();
	MeshModelClass(const MeshModelClass &);
	virtual void Delete_This();
	virtual void Slot1();
	virtual bool Load_W3D(ChunkLoadClass &cload);

	void Release_Ref() { if (--RefCount == 0) Delete_This(); }
	int Get_Flag(int flag) { return Flags & flag; }
	int Get_Polygon_Count() { return PolyCount; }
	bool Has_Shader_Array(int pass) const { return CurMatDesc->Has_Shader_Array(pass); }
	bool Has_Pass_Buffer(int pass) const { return CurMatDesc->Has_Pass_Buffer(pass); }
	ShaderClass Get_Shader(int pidx, int pass) const { return CurMatDesc->Get_Shader(pidx, pass); }
	ShaderClass Get_Single_Shader(int pass) const { return CurMatDesc->Get_Single_Shader(pass); }

	int RefCount;				// +0x04
	char Pad08[0x10];
	unsigned int Flags;			// +0x18
	char Pad1C[4];
	unsigned int W3dAttributes;		// +0x20
	int PolyCount;				// +0x24
	char Pad28[0x94 - 0x28];
	MeshMatDescClass *CurMatDesc;		// +0x94
	char Pad98[0xC4 - 0x98];
};

#define MESH_SLOT(n) virtual void Slot##n()
#define MESH_SLOTS10(t) MESH_SLOT(t##0); MESH_SLOT(t##1); MESH_SLOT(t##2); MESH_SLOT(t##3); MESH_SLOT(t##4); \
	MESH_SLOT(t##5); MESH_SLOT(t##6); MESH_SLOT(t##7); MESH_SLOT(t##8); MESH_SLOT(t##9)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
// The virtual slots are RenderObjClass's as BFME 2 lays them out; only the
// five setters Load_W3D calls are named.
class MeshClass
{
public:
	MESH_SLOTS10(0); MESH_SLOTS10(1); MESH_SLOTS10(2); MESH_SLOTS10(3); MESH_SLOTS10(4);
	MESH_SLOTS10(5); MESH_SLOTS10(6); MESH_SLOTS10(7); MESH_SLOTS10(8); MESH_SLOTS10(9);
	MESH_SLOT(100);
	virtual void Set_Hidden(int onoff);				// slot 101
	MESH_SLOT(102); MESH_SLOT(103); MESH_SLOT(104); MESH_SLOT(105);
	MESH_SLOT(106); MESH_SLOT(107); MESH_SLOT(108);
	virtual void Set_Translucent(int onoff);			// slot 109
	MESH_SLOT(110);
	virtual void Set_Alpha(int onoff);				// slot 111
	MESH_SLOT(112); MESH_SLOT(113); MESH_SLOT(114); MESH_SLOT(115);
	MESH_SLOT(116); MESH_SLOT(117); MESH_SLOT(118);
	virtual void Set_Additive(int onoff);				// slot 119
	MESH_SLOT(120);
	virtual void Set_Collision_Type(int type, bool recurse);	// slot 121

	void Make_Unique(bool force_meshmdl_clone);
	bool Load_W3D(ChunkLoadClass &cload);

private:
	char Base[0xC0];
	MeshModelClass *Model;			// +0xC4
};

void MeshClass::Make_Unique(bool force_meshmdl_clone)
{
	// Usually we will not clone the mesh model if it is already unique -
	// force_meshmdl_clone forces a clone in any case.
	int refs = Model->RefCount;
	if (refs == 1 && !force_meshmdl_clone) {
		return;
	}

	// NEW_REF: the new model starts with one reference, which REF_PTR_SET adds to.
	MeshModelClass *newmesh = new MeshModelClass(*Model);
	if (newmesh != 0) {
		++newmesh->RefCount;
	}

	// REF_PTR_SET(Model, newmesh)
	MeshModelClass *oldmesh = Model;
	if (oldmesh != 0) {
		if (--oldmesh->RefCount == 0) {
			oldmesh->Delete_This();
		}
	}
	Model = newmesh;

	// REF_PTR_RELEASE(newmesh)
	if (newmesh != 0) {
		if (--newmesh->RefCount == 0) {
			newmesh->Delete_This();
		}
	}
}

bool MeshClass::Load_W3D(ChunkLoadClass &cload)
{
	// Make sure this mesh is "empty"
	if (Model != 0) {
		Model->Release_Ref();
		Model = 0;
	}

	// Create an empty model (NEW_REF) and read it in.
	Model = new MeshModelClass();
	if (Model == 0) {
		return false;
	}
	if (!Model->Load_W3D(cload)) {
		if (Model != 0) {
			Model->Release_Ref();
			Model = 0;
		}
		return false;
	}

	// Pull interesting stuff out of the w3d attributes bits
	int col_bits = (Model->W3dAttributes & 0x00000FF0) >> 4;
	Set_Collision_Type(col_bits << 1, false);
	Set_Hidden(Model->W3dAttributes & 0x00001000);

	// The mesh is translucent if sorting is enabled or pass 0 alpha-tests.
	int is_translucent = Model->Get_Flag(MeshModelClass::SORT);
	int is_alpha = 0;
	int is_additive = 0;
	if (Model->Has_Shader_Array(0)) {
		for (int i = 0; i < Model->Get_Polygon_Count(); i++) {
			ShaderClass shader = Model->Get_Shader(i, 0);
			is_translucent |= (shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE);
			is_alpha |= (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO ||
					shader.Get_Src_Blend_Func() != ShaderClass::SRCBLEND_ONE) && (shader.Get_Alpha_Test() != ShaderClass::ALPHATEST_ENABLE);
			is_additive |= (shader.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE &&
					shader.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE);
		}
	} else if (Model->Has_Pass_Buffer(0)) {
		is_translucent = 0;
		is_alpha = 0;
		is_additive = 0;
	} else {
		ShaderClass shader = Model->Get_Single_Shader(0);
		is_translucent |= (shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE);
		is_alpha |= (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO ||
				shader.Get_Src_Blend_Func() != ShaderClass::SRCBLEND_ONE) && (shader.Get_Alpha_Test() != ShaderClass::ALPHATEST_ENABLE);
		is_additive |= (shader.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE &&
				shader.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE);
	}
	Set_Translucent(is_translucent);
	Set_Alpha(is_alpha);
	Set_Additive(is_additive);

	return true;
}
