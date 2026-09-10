// ?Recreate_Device_Resources@BfmeResetShaderRef@@QAEXXZ
// partial score=0.88 date=2026-09-09
// cl: /O1 /DNDEBUG /MD
//
// BfmeResetShaderRef::Recreate_Device_Resources, retail 0x00151575, 34 bytes.
// Dedicated TU. Same guards as Release_Device_Resources then OnResetDevice
// at vtable +0x118.

struct BfmeResetEffect9
{
#define V(n) virtual long __stdcall _v##n() = 0;
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(0a) V(0b) V(0c) V(0d) V(0e) V(0f)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
	V(18) V(19) V(1a) V(1b) V(1c) V(1d) V(1e) V(1f)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27)
	V(28) V(29) V(2a) V(2b) V(2c) V(2d) V(2e) V(2f)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37)
	V(38) V(39) V(3a) V(3b) V(3c) V(3d) V(3e) V(3f)
	V(40) V(41) V(42) V(43) V(44)
#undef V
	virtual long __stdcall OnLostDevice() = 0;
	virtual long __stdcall OnResetDevice() = 0;
};

struct BfmeResetShaderBackend
{
	int unused0;
	BfmeResetEffect9 *effect;
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
	BfmeResetShaderResource *res = pointer;
	if (res)
	{
		BfmeResetShaderBackend *backend = res->backend;
		if (backend)
		{
			if (backend->effect)
				backend->effect->OnResetDevice();
		}
	}
}
