// cl: /O1 /DNDEBUG /MD
//
// BfmeResetTextureRef::Recreate_Device_Resources, retail 0x00132CD9, 54 bytes.
// Dedicated TU so dx8wrapper.cpp Reset_Device cannot see this body (mirrors
// bfme_reset_texture_ref_device.cpp's split for the Release sibling).
// Recreates a missing default-pool COM texture: the resource and backend must
// exist while the COM pointer and pool must both read zero, then the seven
// saved backend creation arguments feed the backend texture worker at
// 0x001310E3 (pinned in this TU's own spelling; two sibling call sites pass
// literals). The &&-chain lowers to the in-memory com/pool checks
// (cmp [eax+8],0 / cmp [eax+0x50],0) exactly like the rowed Release sibling.

struct BfmeResetComTexture
{
	virtual long __stdcall QueryInterface(void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct BfmeResetTextureBackend
{
	void CreateTexture(int width, int height, int createArg4C, int createArg44, int pool, int usage, int createArg48);

	int unused0;                 // +0x00
	int unused4;                 // +0x04
	BfmeResetComTexture *com;    // +0x08: null while the texture is missing
	char pad0C[0x28 - 0x0C];
	int width;                   // +0x28: surface-desc Width, worker arg 1
	int height;                  // +0x2C: surface-desc Height, worker arg 2
	char pad30[0x44 - 0x30];
	int createArg44;             // +0x44: worker arg 4
	int createArg48;             // +0x48: worker arg 7 (stored, not forwarded)
	int createArg4C;             // +0x4C: worker arg 3
	int pool;                    // +0x50: 0 selects default-pool management
	int usage;                   // +0x54: worker arg 6
};

struct BfmeResetTextureResource
{
	char pad[0x14];
	BfmeResetTextureBackend *backend;
};

struct BfmeResetTextureRef
{
	BfmeResetTextureResource *pointer;
	void Recreate_Device_Resources();
};

void BfmeResetTextureRef::Recreate_Device_Resources()
{
	if (pointer && pointer->backend && pointer->backend->com == 0 && pointer->backend->pool == 0)
		pointer->backend->CreateTexture(
			pointer->backend->width, pointer->backend->height,
			pointer->backend->createArg4C, pointer->backend->createArg44,
			pointer->backend->pool, pointer->backend->usage,
			pointer->backend->createArg48);
}
