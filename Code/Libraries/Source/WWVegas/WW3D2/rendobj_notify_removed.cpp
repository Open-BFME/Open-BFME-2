// cl: /O2 /DNDEBUG /MD
//
// RenderObjClass::Notify_Removed, retail 0x0013BCE0, 10 bytes.
// Scene pointer lives at +0x78 (vptr + 0x74 pad). /O2 emits
// mov dword [ecx+78h],0; /O1 would and-imm0 instead.

class SceneClass;

class RenderObjClass
{
	unsigned char _M_layout[0x74];
	SceneClass *Scene;

public:
	virtual void Notify_Removed(SceneClass *scene);
};

void RenderObjClass::Notify_Removed(SceneClass *)
{
	Scene = 0;
}
