// cl: /O1 /DNDEBUG /MD
//
// BfmeResetShaderRef::Release_Device_Resources, retail 0x00151553, 34 bytes.
// Dedicated TU so dx8wrapper.cpp Reset_Device cannot see this body (mirrors
// bfme_reset_texture_ref_device.cpp's split for the "FXSH"-tagged sibling).
// Releases the D3DX-effect-style device object through its own vtable slot
// 0x114/4=69, called STDMETHODCALLTYPE-style with the object explicitly
// pushed rather than via ECX -- that is the shape retail's `push eax / call
// [ecx+0x114]` requires.

struct BfmeResetShaderEffectVTable
{
	void *unused[69];
	void (__stdcall *OnLostDevice)(struct BfmeResetShaderEffectObj *);
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
	void Release_Device_Resources();
};

void BfmeResetShaderRef::Release_Device_Resources()
{
	if (pointer && pointer->backend && pointer->backend->effect)
		pointer->backend->effect->vtbl->OnLostDevice(pointer->backend->effect);
}
