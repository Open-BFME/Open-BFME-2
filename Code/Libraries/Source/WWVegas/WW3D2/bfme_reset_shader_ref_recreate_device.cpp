// cl: /O1 /DNDEBUG /MD
//
// BfmeResetShaderRef::Recreate_Device_Resources, retail 0x00151575, 34 bytes.
// Dedicated TU so dx8wrapper.cpp Reset_Device cannot see this body (mirrors
// bfme_reset_shader_ref_device.cpp's split for the Release sibling).
// Re-invokes the D3DX-effect-style device object through its own vtable slot
// 0x118/4=70, called STDMETHODCALLTYPE-style with the object explicitly
// pushed rather than via ECX -- the exact mirror of Release_Device_Resources
// (slot 69, OnLostDevice) with the OnResetDevice slot. The &&-chain lowers to
// the in-memory effect check (cmp [ecx+4],0) plus the backend re-materialize
// (mov eax,ecx) exactly like the rowed Release sibling.

struct BfmeResetShaderEffectVTable
{
	void *unused[70];
	void (__stdcall *OnResetDevice)(struct BfmeResetShaderEffectObj *);
};

struct BfmeResetShaderEffectObj
{
	BfmeResetShaderEffectVTable *vtbl;
};

struct BfmeResetShaderBackend
{
	int unused0;
	BfmeResetShaderEffectObj *effect;
};

struct BfmeResetShaderResource
{
	char pad[0x14];
	BfmeResetShaderBackend *backend;
};

struct BfmeResetShaderRef
{
	BfmeResetShaderResource *pointer;
	void Recreate_Device_Resources();
};

void BfmeResetShaderRef::Recreate_Device_Resources()
{
	if (pointer && pointer->backend && pointer->backend->effect)
		pointer->backend->effect->vtbl->OnResetDevice(pointer->backend->effect);
}
