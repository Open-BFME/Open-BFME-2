// cl: /O2 /DNDEBUG /MD
//
// RenderObjClass scene-pointer virtuals. Scene lives at +0x78
// (vptr + 0x74 pad). /O2 emits mov-imm0 for Notify_Removed;
// /O1 would and-imm0 instead.
//   Notify_Added   0x0013BCD0  10 bytes  Scene = scene
//   Notify_Removed 0x0013BCE0  10 bytes  Scene = 0

class SceneClass;

class RenderObjClass
{
	unsigned char _M_layout[0x74];
	SceneClass *Scene;

public:
	virtual void Notify_Added(SceneClass *scene);
	virtual void Notify_Removed(SceneClass *scene);
};

void RenderObjClass::Notify_Added(SceneClass *scene)
{
	Scene = scene;
}

void RenderObjClass::Notify_Removed(SceneClass *)
{
	Scene = 0;
}
