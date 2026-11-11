// DX8MeshRendererClass: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_DX8MESHRENDERERCLASS_H
#define CANONICAL_DX8MESHRENDERERCLASS_H

class MeshModelClass;

class DX8MeshRendererClass
{
public:
	~DX8MeshRendererClass();
	void Clear_Pending_Delete_Lists();
	void Flush();
	void Invalidate(bool);
	void Register_Mesh_Type(MeshModelClass *mesh);
	void Unregister_Mesh_Type(MeshModelClass *mmc);
};

#endif // CANONICAL_DX8MESHRENDERERCLASS_H
