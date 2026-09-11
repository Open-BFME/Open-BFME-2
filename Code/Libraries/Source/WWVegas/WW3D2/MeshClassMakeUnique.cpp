// cl: /G7 /DNDEBUG /MD /EHsc
//
// MeshClass::Make_Unique at 0x00149C10.
//
// Zero Hour's body: clone the shared MeshModelClass unless this mesh is its
// only user, then swap the clone in with the usual reference counting.  It
// lives in its own unit because retail allocates the clone with the plain
// global operator new, where mesh.cpp's MeshModelClass carries the W3D memory
// pool allocator and would call into the pool instead.  The classes below are
// reduced to the offsets the body touches: in BFME 2 the model pointer sits at
// +0xC4 and a MeshModelClass is 0xC4 bytes, four less than in BFME 1.  /G7 is the unit's tell (add reg,1
// and sub reg,1 where the default build writes inc and dec).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
public:
	MeshModelClass(const MeshModelClass &);
	virtual void Delete_This();

	int RefCount;
	char Data[0xBC];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass
{
public:
	void Make_Unique(bool force_meshmdl_clone);

private:
	char Base[0xC4];
	MeshModelClass *Model;
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
