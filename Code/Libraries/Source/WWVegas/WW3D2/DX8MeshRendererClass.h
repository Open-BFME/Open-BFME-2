// DX8MeshRendererClass: canonical declarations for the members units call through private views of it;
// each call resolves to the unit's ledger row or pin. The flag and camera are typed, the lists stay opaque.
#ifndef CANONICAL_DX8MESHRENDERERCLASS_H
#define CANONICAL_DX8MESHRENDERERCLASS_H

class CameraClass;
class MeshModelClass;

class DX8MeshRendererClass
{
public:
	DX8MeshRendererClass();
	~DX8MeshRendererClass();
	void Init();
	void Shutdown();
	void Clear_Pending_Delete_Lists();
	void Flush();
	void Invalidate(bool);
	void Register_Mesh_Type(MeshModelClass *mesh);
	void Unregister_Mesh_Type(MeshModelClass *mmc);
	void Set_Camera(CameraClass *cam) { camera = cam; }

protected:
	bool enable_lighting;

public:
	// Public: the projected-shadow pass stores it directly, which an inline Set_Camera call does not reproduce.
	CameraClass *camera;

protected:
	// Rigid list vector +0x08, skin list +0x18 and the two pending-delete lists +0x1C/+0x34; retail allocates 0x4C.
	char m_08[0x44];
};

#endif // CANONICAL_DX8MESHRENDERERCLASS_H
